#include "model.h"
#include "rgb2bin.h"
#include <tuple>
#include <vector>
#include "diversed_object.h"
#include "distance_transform.h"
#include "io.h"
#include <QString>
#include <pluginmanager.h>
#include <cstdio>
using std::tuple;
using std::vector;
Model::Model()
{
}

void Model::setPluginsDir(const char *path)
{
    char *newpath = new char[strlen(path)];
    strcpy(newpath, path);
    int i;
    for (i = strlen(path) - 1; path[i] != '/' && i > 0; i--);
    newpath[i] = '\0';
    sprintf(newpath, "%s/plugins", newpath);
    manager.setdir(newpath);
}

void Model::apply_plugin(int id)
{
    Image ans = manager.ApplyPlugin(id, source_image);
    const char *name = manager.Plugins[id]->stringType();
    emit Plugindone(ans);
    emit SayAboutEvent(string("Plugin ") + name + " was applied");
    source_image = ans;
}

void Model::refresh_plugins()
{
  manager.deletePlugins();
  emit Pluginsdelete();
  manager.findandload();
  for (int i = 0; i < (int)manager.Plugins.size(); i++)
  {
      emit newPlugin((manager.Plugins[i])->stringType(), i);
  }
}

void Model::load_image(const char *path)
{
    source_image = ::load_image(path);
    filepath = string(path);
    SayAboutEvent(string("Image ") + filepath + string(" loaded"));
}

void Model::repair_mechanism()
{
    // Base: return array of found objects and index of the correct gear
    // Bonus: return additional parameters of gears
    if (source_image.n_cols * source_image.n_rows == 0)
    {
        emit SayAboutEvent(string("Please select image"));
        return;
    }
    auto object_array = vector<shared_ptr<IObject>>();
    rgb2bright obj_for_hist;
    auto Imag = source_image.unary_map(obj_for_hist);
    auto ans = Imag.unary_map(bright2bin(obj_for_hist.otsu_threshold()));
    Diversed_object pic(ans);
    emit SayAboutEvent(string("Obtained connected components"));
    auto obj = pic.get_objects();
    auto iter = obj.begin();
    for (auto i = obj.begin(); i != obj.end(); i++)
    {
        uint a, b, c, d;
        shared_ptr<IObject> tmp;
        bool is_broken;
        DistanceTransform q((*i).GetBinPic(pic.get_Matrix()));
        q.distance_transform();
        tie(c, d) = (*i).center_byDT(q.get_answer());
        (*i).compute_radius(pic.get_Matrix());

        if ( (*i).detect_type() == GEAR)
        {
                tie(a, b) = (*i).detect_mass_center(pic.get_Matrix());
                auto teeth = (*i).get_teeth(pic.get_Matrix());
                Diversed_object hlp(teeth);
                int obj_count = hlp.get_obj_count();
                emit SayAboutEvent("detect number of cogs");
                is_broken =  ((a - c) * (a - c) + (b - d) * (b - d)) > 8;
                tmp.reset(new Gear(make_tuple(c, d), (*i).rmin, (*i).rmax, is_broken, obj_count));
                object_array.push_back(tmp);
                if (is_broken){
                    emit SayAboutEvent("Detected broken gear");
                    iter = i;
                }
        } else
        {
                tmp.reset( new Axis(make_tuple(c,d)));
                object_array.push_back(tmp);
                iter = i;
                emit SayAboutEvent("Detected axis");
        }
    }

    double dist1 = MyINFINITY, dist2 = MyINFINITY;

    auto one = obj.begin(), two = obj.begin();


    for (auto i = obj.begin(); i != obj.end(); i++){
        if (i == iter)
            continue;
        double tmp = distance_beetwen_objects(*i, *iter);
        if (tmp < dist2){
            if (tmp < dist1){
                dist2 = dist1;
                two = one;
                dist1 = tmp;
                one = i;
            }else{
                dist2 = tmp;
                two = i;
            }
        }
    }

    int result_idx = 0;
    answer_image = source_image.deep_copy();
    for (int i = 1; i <= 3; i++){
        char *gearname = new char[filepath.size() + 3];
        uint j;
        sprintf(gearname, "%s", filepath.c_str());
        for (j = filepath.size() - 1; j != 0 && filepath[j] != '.'; j--);
        if (j == 0) throw "mistake in name of image";
        gearname[j] = '\0';
        sprintf(gearname, "%s_%d.bmp", gearname, i);
        Image detail = ::load_image(gearname);
        rgb2bright otherobjforhist;
        auto tmpobj = detail.unary_map(otherobjforhist);
        auto binaryimg = tmpobj.unary_map(bright2bin(otherobjforhist.otsu_threshold()));
        Diversed_object gear(binaryimg);
        if (gear.get_obj_count() != 1) throw "invalid gear image";
        auto gear_obj = gear.get_objects();
        DistanceTransform qw(gear_obj[0].GetBinPic(gear.get_Matrix()));
        qw.distance_transform();
        gear_obj[0].center_byDT(qw.get_answer());
        gear_obj[0].compute_radius(gear.get_Matrix());
        if (suitable_gear(gear_obj[0], *one, *iter) && suitable_gear(gear_obj[0], *two, *iter)){
            gear_obj[0].insert(answer_image, detail, gear.get_Matrix(), *iter);
            result_idx = i;
            break;
        }
        delete []gearname;
    }
    emit SayAboutEvent("Mechanism was repaired");
    answer = make_tuple(result_idx, object_array, answer_image);
    emit ResultsOfWork(answer);
}
