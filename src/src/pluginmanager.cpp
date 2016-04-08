#include "pluginmanager.h"
#include <string>
#include <dirent.h>
#include <string>
#include <stdio.h>
#include "../API.h"
#include <dlfcn.h>
PluginManager::PluginManager(QObject *parent) : QObject(parent)
{
    findandload();
}

void PluginManager::setdir(char * name)
{
    pluginsDir = name;
}

void PluginManager::findandload()
{
    if (pluginsDir == NULL){
        return;
    }
    vector<string> files;
    vector<string> pLibNames;

  // find all dlls in a folder specified by the pluginDir
  fLength = findDLLs(pluginsDir, files);
    if (fLength < 0){
        return;
    }
    // array of dll handlers
    pLib = new HAND[fLength];
  fLength = LoadDLLs(pluginsDir, files, pLibNames);
  LoadPlugins(pLibNames);
}

void PluginManager::deletePlugins()
{
    for (int i=0; i<fLength; i++)//free libraries
      {
          int failed = dlclose(pLib[i]);
          if (failed)
              std::cerr << "FreeLibrary error";
      }
    Plugins.clear();
    free(pLib);
    fLength = 0;
}

int mask_filter(const dirent * d)
{
    char a[] = {".so"};
    if (strstr(d->d_name, a) != NULL){
        return 1;
    }
else return 0;
}


int PluginManager::findDLLs(const char *in_pluginsDir, vector<string> &out_file_names)
{
    dirent **namelist;
    int n = scandir (in_pluginsDir, &namelist, ::mask_filter , alphasort);
    if (n < 0){
        perror("scandir");
        return -1;
    }
    while (n-- > 0){
        out_file_names.push_back(namelist[n]->d_name);
        free (namelist[n]);
    }
    free(namelist);

  return out_file_names.size();
}

int PluginManager::LoadDLLs(const char *in_pluginsDir, const vector<string> &in_file_names,
  vector<string> &out_lib_names)
{
  auto files_num = in_file_names.size();
  char *buffer = new char[strlen(in_pluginsDir) + 1000];
  int k=0;
    for (size_t i=0; i<files_num; i++)
    {
        strcpy(buffer,in_pluginsDir);
        buffer = strcat(buffer, "//");
        buffer = strcat(buffer, in_file_names[i].c_str());

        pLib[k] = dlopen(buffer, RTLD_LAZY	);
        if (pLib[k] != NULL)
        {
            out_lib_names.push_back(buffer);
            k++;
        }
        else
        {
            std::cerr << "error with load library";
        }
    }
  delete [] buffer;
  return k;
}

void PluginManager::LoadPlugins(const vector<string> &in_pLibNames)
{
  fLength = in_pLibNames.size();
    for (size_t i=0; i<(size_t)fLength; i++)
    {
    // look for entry point
        void *tmp = dlsym(pLib[i],"registerPlugins");
        regFuncType function = (regFuncType)tmp;
        if (function != NULL)
        {

      // try to load all plugins stored in the dll
            IPlugin *pPlugin = NULL;
            pPlugin = function();
            Plugins.push_back(pPlugin);
        }
    }
}

PluginManager::~PluginManager(){
    deletePlugins();
    if (pluginsDir != NULL)
        delete pluginsDir;
}

Image PluginManager::ApplyPlugin(int id, Image &im)
{
    if (id < (int)Plugins.size())
    {
       return ((IPlugin*)Plugins[id])->operation(im);
    }
    return im;
}
