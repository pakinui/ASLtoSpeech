/**
 * @file main.cpp
 * @brief Contains the main function for the application.
 *
 * This file contains the main function that initializes the application and
 * displays the main camera window. It includes necessary headers and sets up the
 * application environment.
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
 * @brief The entry point for the application.
 *
 * This function is the entry point for the application. It initializes the GUI
 * application, sets up necessary resources, creates the main camera window,
 * and starts the event loop.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return The exit status of the application.
 */
int main(int argc, char *argv[])
{
//    Py_Initialize();
//    QString currentPath = QDir::currentPath();
//    QString newPath = currentPath + "/../345Application";
//    std::string pythonCode = "import sys; sys.path.append('"+ newPath.toStdString() +"')";
//    PyRun_SimpleString(pythonCode.c_str());
//    PyObject *pModule = PyImport_ImportModule("webcam_pattern_detection");
//    PyErr_Print();

//    Py_Finalize();

    // Initialize the GUI application
    QApplication a(argc, argv);

    // Create the main camera window
    Camera w;
    w.show();

    // Start the event loop
    return a.exec();
}

