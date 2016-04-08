#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <string>
#include "io.h"
#include <tuple>
#include <vector>
#include "MyObject.h"
#include <QString>
#include <map>
#include <QAction>
using std::map;
using std::shared_ptr;
using std::string;
using std::tuple;
using std::vector;

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT
    map<QAction *, int> mp;
    vector <QAction *> v;
public:
    explicit View(QWidget *parent = 0);
    ~View();
    void setPlugin();
signals:
    void ImageUpload(const QString &fileName);
    void on_repair_triggered();
    void on_refresh_plugins_triggered();
    void applyPlugin(int);

public slots:
    void erasePluginAct();
    void on_actionExit_triggered();
    void Log(const string & str);
    void print_results(tuple<int, vector<shared_ptr<IObject>>, Image>);
    void addPlugin(const char *, int i);
    void recognizePlugin();
    void refreshImage(Image);
private slots:
    void on_actionOpen_triggered();
    void SetImage(const QString &fileName);



private:
    Ui::View *ui;
    QString fileName;
};

#endif // VIEW_H
