/**
 *  @file main.cpp
 *  @brief This file ...
 *  @author
 *
 *  Description...
 *
 */
#include "camera.h"

#include <QApplication>
#include <QStyleFactory>
#include <QWidget>
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringLiteral>

#include "ui_camera.h"

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Camera w;
    w.show();


    return a.exec();
}

