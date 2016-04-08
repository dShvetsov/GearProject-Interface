#include "view.h"
#include <QApplication>
#include "model.h"
#include "controller.h"
#include <QMainWindow>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View w;
    Model m;
    controller c(m);
    c.setplugdir(argv[0]);
    QObject::connect(&w, SIGNAL(ImageUpload(QString)), &c, SLOT(loadImage(QString)));
    QObject::connect(&m, SIGNAL(SayAboutEvent(string)), &w, SLOT(Log(string)));
    QObject::connect(&w, SIGNAL(on_repair_triggered()), &c, SLOT(repair()));
    QObject::connect(&m, SIGNAL(ResultsOfWork(tuple<int,vector<shared_ptr<IObject> >,Image>)),
                     &w, SLOT(print_results(tuple<int,vector<shared_ptr<IObject> >,Image>)));
    QObject::connect(&m, SIGNAL(Plugindone(Image)), &w, SLOT(refreshImage(Image)));
    QObject::connect(&w, SIGNAL(on_refresh_plugins_triggered()), &c, SLOT(refresh_plugins()));
    QObject::connect(&m, SIGNAL(newPlugin(const char*,int)), &w, SLOT(addPlugin(const char*,int)));
    QObject::connect(&w, SIGNAL(applyPlugin(int)), &c, SLOT(PluginCall(int)));
    QObject::connect(&m, SIGNAL(Pluginsdelete()), &w, SLOT(erasePluginAct()));
    w.setPlugin();
    w.show();
    return a.exec();
}
