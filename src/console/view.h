#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <string>
#include <tuple>
#include <string>
#include "io.h"
#include <vector>
#include "MyObject.h"
#include <sstream>

using std::ofstream;
using std::vector;
using std::tuple;
using std::string;
using std::shared_ptr;
class View : public QObject
{
    const char *path_dst_image;
    const char *path_dst_ans;
    Q_OBJECT
public:
    explicit View(const char *im, const char *file, QObject *parent = 0);

signals:
    void finish();
    void PluginsExist();
public slots:
    void Log(const string &s);
    void addPlugin(const char *, int i);
    void refreshImage(Image);
    void print_results(tuple<int, vector<shared_ptr<IObject>>, Image>);
};

#endif // VIEW_H
