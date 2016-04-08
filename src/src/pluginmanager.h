#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <string>
#include <set>
#include <dirent.h>
#include <map>
#include <io.h>
#include <vector>
#include <dlfcn.h>
#include <../API.h>
using std::vector;
using std::map;
using std::set;
using std::string;

typedef void *HAND;

class PluginManager : public QObject
{
    Q_OBJECT



    int mask_filter(const dirent *);
    HAND *pLib = NULL;
    int fLength = 0;
    char *pluginsDir = NULL;
public:
    vector <IPlugin *> Plugins;//IUnaryPlugin*
    void regPlugin(const char *path);
    void setdir(char *);
    int findDLLs(const char *in_pluginsDir, vector<string> &out_file_names);
    void find_plugins(const char *in_pluginDir);

    int LoadDLLs(const char *in_pluginsDir, const vector<string> &in_file_names,
     vector<string> &out_lib_names);
    void findandload();
    void deletePlugins();
    Image ApplyPlugin(int id, Image &im);
    void LoadPlugins(const vector<string> &in_pLibNames);
    void regPlugin();
    ~PluginManager();
    explicit PluginManager(QObject *parent = 0);

signals:

public slots:
};

#endif // PLUGINMANAGER_H
