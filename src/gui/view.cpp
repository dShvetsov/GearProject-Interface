#include "view.h"
#include "ui_view.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include "EasyBMP.h"
#include "io.h"
#include <QTextStream>
#include <string>
#include <iostream>
#include <sstream>
#include <QAction>
#include "time.h"
#include <cstdio>
using std::stringstream;
using std::endl;

void View::setPlugin()
{
    emit on_refresh_plugins_triggered();
}

View::View(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);
    connect(this, SIGNAL(ImageUpload(QString)), this, SLOT(SetImage(QString)));
}

View::~View()
{
    delete ui;
}

void View::on_actionExit_triggered()
{
    QApplication::quit();
}

void View::on_actionOpen_triggered()
{
    fileName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.bmp");
    emit ImageUpload(fileName);
}

void View::SetImage(const QString &fileName)
{
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }
        ui->ImageLabel->setPixmap(QPixmap::fromImage(image));
    }
}

void View::Log(const string & str)
{
    time_t t = time(NULL);
    tm *q = localtime(&t);
    stringstream s;
    char tmp[20];
    std::sprintf(tmp, "%.2d:%.2d:%.2d", q->tm_hour, q->tm_min, q->tm_sec);
    s << tmp << "  " << str << endl;
    string print_str = s.str();
    ui->text->append(print_str.c_str());
}

void View::addPlugin(const char * str, int i)
{
    QAction *act = ui->PluginMenu->addAction(str);
    mp[act] = i;
    connect(act, SIGNAL(triggered()), this, SLOT(recognizePlugin()));
    v.push_back(act);
}

void View::erasePluginAct()
{
    for (auto i = v.begin(); i != v.end(); i++){
        delete *i;
    }
    v.clear();
    mp.clear();
}

void View::refreshImage(Image im)
{
    QString tmp_image = fileName + "tmp.bmp";
    save_image(im, tmp_image.toStdString().c_str());
    if (!tmp_image.isEmpty()) {
        QImage image(tmp_image);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }
        ui->ImageLabel->setPixmap(QPixmap::fromImage(image));
    }
    remove(tmp_image.toStdString().c_str());
}

void View::recognizePlugin()
{
    QAction* a = qobject_cast<QAction *> (sender());
    emit applyPlugin(mp[a]);
}

void View::print_results(tuple<int, vector<shared_ptr<IObject> >, Image> data)
{
    stringstream fout;
    vector<shared_ptr<IObject>> object_array;
    int result_idx;
    Image dst_image;
    tie(result_idx, object_array, dst_image) = data;

    fout << result_idx << endl;
    fout << object_array.size() << endl;
    for (const auto &obj : object_array)
        obj->Write(fout);
    ui->text->append(fout.str().c_str());
    QString tmp_image = fileName + "tmp.bmp";
    save_image(dst_image, tmp_image.toStdString().c_str());
    if (!tmp_image.isEmpty()) {
        QImage image(tmp_image);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }
        ui->AnswerImage->setPixmap(QPixmap::fromImage(image));
    }
    remove(tmp_image.toStdString().c_str());

}
