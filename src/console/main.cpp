#include <QCoreApplication>
#include "model.h"
#include "view.h"
#include "controller.h"
#include <QTimer>
int main(int argc, char *argv[])
{
    if (argc != 4 && argc != 5)
    {
        std::cout << "Usage: " << std::endl << argv[0]
             << " <in_image.bmp> <out_image.bmp> <out_result.txt>" << std::endl;
        return 0;

    }
    QCoreApplication a(argc, argv);
    Model m;
    controller c(m);
    c.setplugdir(argv[0]);
    View w(argv[2], argv[3]);
    QObject::connect(&m, SIGNAL(SayAboutEvent(string)), &w, SLOT(Log(string)));
    QObject::connect(&m, SIGNAL(ResultsOfWork(tuple<int,vector<shared_ptr<IObject> >,Image>)),
                     &w, SLOT(print_results(tuple<int,vector<shared_ptr<IObject> >,Image>)));
    QObject::connect(&m, SIGNAL(Plugindone(Image)), &w, SLOT(refreshImage(Image)));
    QObject::connect(&m, SIGNAL(newPlugin(const char*,int)), &w, SLOT(addPlugin(const char*,int)));
    QObject::connect(&w, SIGNAL(finish()), &a, SLOT(quit()));
    QObject::connect(&w, SIGNAL(PluginsExist()), &c, SLOT(PluginsExist()));
    c.parse_input(argc, argv);
    QTimer::singleShot(0, &a, SLOT(quit()));
    return a.exec();
}

