/********************************************************************************
** Form generated from reading UI file 'camera.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_H
#define UI_CAMERA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Camera
{
public:
    QAction *actionStartCamera;
    QAction *actionStopCamera;
    QWidget *centralwidget;
    QGridLayout *gridLayout_5;
    QStackedWidget *stackedWidget;
    QWidget *previewPage;
    QGridLayout *gridLayout_7;
    QLabel *label_2;
    QWidget *viewfinderPage;
    QGridLayout *gridLayout_6;
    QVideoWidget *viewfinder;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_9;
    QLabel *label_3;
    QWidget *tab_2;
    QGridLayout *gridLayout_8;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Camera)
    {
        if (Camera->objectName().isEmpty())
            Camera->setObjectName("Camera");
        Camera->resize(436, 260);
        actionStartCamera = new QAction(Camera);
        actionStartCamera->setObjectName("actionStartCamera");
        actionStopCamera = new QAction(Camera);
        actionStopCamera->setObjectName("actionStopCamera");
        centralwidget = new QWidget(Camera);
        centralwidget->setObjectName("centralwidget");
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName("gridLayout_5");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        QPalette palette;
        QBrush brush(QColor(192, 192, 192, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        stackedWidget->setPalette(palette);
        previewPage = new QWidget();
        previewPage->setObjectName("previewPage");
        gridLayout_7 = new QGridLayout(previewPage);
        gridLayout_7->setObjectName("gridLayout_7");
        label_2 = new QLabel(previewPage);
        label_2->setObjectName("label_2");

        gridLayout_7->addWidget(label_2, 0, 0, 1, 1);

        stackedWidget->addWidget(previewPage);
        viewfinderPage = new QWidget();
        viewfinderPage->setObjectName("viewfinderPage");
        gridLayout_6 = new QGridLayout(viewfinderPage);
        gridLayout_6->setObjectName("gridLayout_6");
        viewfinder = new QVideoWidget(viewfinderPage);
        viewfinder->setObjectName("viewfinder");

        gridLayout_6->addWidget(viewfinder, 0, 0, 1, 1);

        stackedWidget->addWidget(viewfinderPage);

        gridLayout_5->addWidget(stackedWidget, 0, 0, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout_9 = new QGridLayout(tab);
        gridLayout_9->setObjectName("gridLayout_9");
        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");

        gridLayout_9->addWidget(label_3, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        gridLayout_8 = new QGridLayout(tab_2);
        gridLayout_8->setObjectName("gridLayout_8");
        label = new QLabel(tab_2);
        label->setObjectName("label");

        gridLayout_8->addWidget(label, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout_5->addWidget(tabWidget, 0, 1, 1, 1);

        Camera->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Camera);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 436, 17));
        Camera->setMenuBar(menubar);
        statusbar = new QStatusBar(Camera);
        statusbar->setObjectName("statusbar");
        Camera->setStatusBar(statusbar);

        retranslateUi(Camera);

        stackedWidget->setCurrentIndex(1);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Camera);
    } // setupUi

    void retranslateUi(QMainWindow *Camera)
    {
        Camera->setWindowTitle(QCoreApplication::translate("Camera", "MainWindow", nullptr));
        actionStartCamera->setText(QCoreApplication::translate("Camera", "StartCamera", nullptr));
        actionStopCamera->setText(QCoreApplication::translate("Camera", "StopCamera", nullptr));
        label_2->setText(QCoreApplication::translate("Camera", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("Camera", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Camera", "Tab 1", nullptr));
        label->setText(QCoreApplication::translate("Camera", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Camera", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Camera: public Ui_Camera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_H
