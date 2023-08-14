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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Camera
{
public:
    QAction *actionStartCamera;
    QAction *actionStopCamera;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
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
    QWidget *tab_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Camera)
    {
        if (Camera->objectName().isEmpty())
            Camera->setObjectName("Camera");
        Camera->resize(800, 500);
        Camera->setMinimumSize(QSize(800, 500));
        actionStartCamera = new QAction(Camera);
        actionStartCamera->setObjectName("actionStartCamera");
        actionStopCamera = new QAction(Camera);
        actionStopCamera->setObjectName("actionStopCamera");
        centralwidget = new QWidget(Camera);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(800, 500));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("\n"
"QLabel {\n"
"	color: rgb(50, 50, 100);\n"
"    font-weight: bold;\n"
"    font-size: 12px; /* Adjust the font size as needed */\n"
" }"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName("horizontalLayout");
        stackedWidget = new QStackedWidget(widget);
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

        horizontalLayout->addWidget(stackedWidget);

        tabWidget = new QTabWidget(widget);
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
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget->addTab(tab_3, QString());

        horizontalLayout->addWidget(tabWidget);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addWidget(widget);

        Camera->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Camera);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        Camera->setMenuBar(menubar);
        statusbar = new QStatusBar(Camera);
        statusbar->setObjectName("statusbar");
        Camera->setStatusBar(statusbar);

        retranslateUi(Camera);

        stackedWidget->setCurrentIndex(1);
        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Camera);
    } // setupUi

    void retranslateUi(QMainWindow *Camera)
    {
        Camera->setWindowTitle(QCoreApplication::translate("Camera", "MainWindow", nullptr));
        actionStartCamera->setText(QCoreApplication::translate("Camera", "StartCamera", nullptr));
        actionStopCamera->setText(QCoreApplication::translate("Camera", "StopCamera", nullptr));
        label_4->setText(QCoreApplication::translate("Camera", "Sign Language to Speech Translator", nullptr));
        label_2->setText(QCoreApplication::translate("Camera", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("Camera", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Camera", "Trans", nullptr));
        label->setText(QCoreApplication::translate("Camera", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Camera", "Dict", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("Camera", "Hist", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Camera: public Ui_Camera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_H
