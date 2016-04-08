#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QString>
#include <QObject>
#include "model.h"

class controller : public QObject
{
   Q_OBJECT
public:
    controller(Model &_m, QObject *parent = 0);
    void setplugdir(const char *);

signals:
    void NewImage(const char *);
public slots:
    void loadImage(const QString &fileName);
    void repair();
    void refresh_plugins();
    void PluginCall(int);
private:
    Model &m;
};

#endif // CONTROLLER_H
