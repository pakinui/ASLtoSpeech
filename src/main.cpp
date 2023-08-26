/**
 *  @file main.cpp
 *  @brief This file ...
 *  @author
 *
 *  Description...
 *
 */
#include "camera.h"
#include <Python.h>
#include <QApplication>
#include <QStyleFactory>
#include <QWidget>
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringLiteral>
#include <QDir>
#include "ui_camera.h"

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
//    Py_Initialize();
//    QString currentPath = QDir::currentPath();
//    QString newPath = currentPath + "/../../src";
//    std::string pythonCode = "import sys; sys.path.append('"+ newPath.toStdString() +"')";
//    PyRun_SimpleString(pythonCode.c_str());
//    PyObject *pModule = PyImport_ImportModule("webcam_pattern_detection");
//    PyErr_Print();

//    Py_Finalize();

    QApplication a(argc, argv);
    Camera w;
    w.show();

    return a.exec();
}

