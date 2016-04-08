#include "view.h"
#include <iostream>
#include <io.h>
#include <sstream>
#include <QCoreApplication>

using std::stringstream;
using std::tie;
View::View(const char *im, const char *file, QObject *parent) : QObject(parent)
{
    path_dst_ans = file;
    path_dst_image = im;
}

void View::Log(const string &str)
{
    time_t t = time(NULL);
    tm *q = localtime(&t);
    stringstream s;
    char tmp[20];
    std::sprintf(tmp, "%0.2d:%0.2d:%0.2d", q->tm_hour, q->tm_min, q->tm_sec);
    s << tmp << "  " << str;
    std::cout << s.str()  << std::endl;
}

void View::addPlugin(const char *plname, int i)
{
    emit PluginsExist();
    std::cout << "[" << i + 1 << "]" << ' ' <<  plname << std::endl;
}

void View::refreshImage(Image im)
{
    save_image(im, path_dst_image);
}

void View::print_results(tuple<int, vector<shared_ptr<IObject> >, Image> res)
{
    ofstream fout(path_dst_ans);

    vector<shared_ptr<IObject>> object_array;
    Image dst_image;
    int result_idx;
    tie(result_idx, object_array, dst_image) = res;
    save_image(dst_image, path_dst_image);

    fout << result_idx << std::endl;
    fout << object_array.size() << std::endl;
    for (const auto &obj : object_array)
        obj->Write(fout);
    emit finish();
}
