#ifndef MODEL_H
#define MODEL_H
#include "io.h"
#include <tuple>
#include "matrix.h"
#include "MyObject.h"
#include <QObject>
#include <string>
#include "pluginmanager.h"
using std::string;
using std::tuple;
using std::vector;
using std::shared_ptr;

class Model : public QObject
{
    Q_OBJECT
private:
    PluginManager manager;
    Image source_image;
    Image answer_image;
    string filepath;
    tuple<int, vector<shared_ptr<IObject>>, Image> answer;
public:
    void setPluginsDir(const char *path);
    void load_image(const char *path);
    void repair_mechanism();
    void refresh_plugins();
    void apply_plugin(int id);
    Model();
signals:
    void SayAboutEvent(const string &);
    void ResultsOfWork(tuple<int, vector<shared_ptr<IObject>>, Image>);
    void newPlugin(const char *, int);
    void Plugindone(Image);
    void Pluginsdelete();
};

#endif // MODEL_H
