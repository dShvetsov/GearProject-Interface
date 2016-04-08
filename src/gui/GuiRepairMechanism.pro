#-------------------------------------------------
#
# Project created by QtCreator 2015-10-07T23:04:05
#
#-------------------------------------------------

QT       += core gui

CONFIG += C++11
LIBS += -ldl
#QMAKE_LFLAGS += -ldl,
QMAKE_CXXFLAGS += -std=c++11 -g
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuiRepairMechanism
TEMPLATE = app

DESTDIR = ../

SOURCES += main.cpp\
        view.cpp \
    ../src/distance_transform.cpp \
    ../src/diversed_object.cpp \
    ../src/gear_object.cpp \
    ../src/histogram.cpp \
    ../src/io.cpp \
    ../src/main1.cpp \
    ../src/matrix_example.cpp \
    ../src/model.cpp \
    ../src/pluginmanager.cpp \
    ../src/rgb2bin.cpp \
    ../externals/EasyBMP/src/EasyBMP.cpp \
    controller.cpp

HEADERS  += view.h \
    ../src/distance_transform.h \
    ../src/diversed_object.h \
    ../src/gear_object.h \
    ../src/histogram.h \
    ../src/model.h \
    ../src/MyObject.h \
    ../src/pluginmanager.h \
    ../src/rgb2bin.h \
    ../include/io.h \
    ../include/matrix.h \
    ../include/matrix.hpp \
    ../externals/EasyBMP/include/EasyBMP.h \
    ../externals/EasyBMP/include/EasyBMP_BMP.h \
    ../externals/EasyBMP/include/EasyBMP_DataStructures.h \
    ../externals/EasyBMP/include/EasyBMP_VariousBMPutilities.h \
    controller.h

INCLUDEPATH += ../externals/EasyBMP/include/ \
 ../include/ \
../src/
FORMS    += view.ui
