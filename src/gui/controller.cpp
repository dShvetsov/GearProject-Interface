#include "controller.h"
#include <QMessageBox>
controller::controller(Model &_m, QObject *parent):QObject(parent), m(_m)
{

}

void controller::loadImage(const QString &fileName)
{
    m.load_image(fileName.toStdString().c_str());
}

void controller::setplugdir(const char *str)
{
    m.setPluginsDir(str);
}

void controller::refresh_plugins(){
    m.refresh_plugins();
}

void controller::PluginCall(int i){
    m.apply_plugin(i);
}

void controller::repair(){
    m.repair_mechanism();
}
