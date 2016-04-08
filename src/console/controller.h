#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model.h"
class controller : public QObject
{
    Q_OBJECT
    Model &m;
    bool expl = false;
public:
    void setplugdir(const char *);
    explicit controller(Model &m, QObject *parent = 0);
    int parse_input(int argc, char **argv);
signals:

public slots:
    void PluginsExist();
};

#endif // CONTROLLER_H
