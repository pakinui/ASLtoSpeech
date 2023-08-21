#include "camera.h"

#include <QApplication>
#include <QStyleFactory>
#include <QWidget>
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringLiteral>

#include "ui_camera.h"
//#include "python_wrapper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Camera w;

    w.show();


    return a.exec();
}

