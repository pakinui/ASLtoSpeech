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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
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
    QWidget *translationTab;
    QVBoxLayout *verticalLayout_2;
    QWidget *topArea;
    QTextEdit *translationDisplay;
    QWidget *bottomArea;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *translateInput;
    QPushButton *translateButton;
    QWidget *dictionaryTab;
    QVBoxLayout *verticalLayout_4;
    QWidget *searchArea;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *dictionaryInput;
    QPushButton *dictionaryButton;
    QWidget *dictDisplayArea;
    QVBoxLayout *verticalLayout_6;
    QTextEdit *dictionaryTextOutput;
    QLabel *dictionaryPhoto;
    QVideoWidget *videoDisplay;
    QWidget *historyTab;
    QTextEdit *historyDisplay;

    void setupUi(QMainWindow *Camera)
    {
        if (Camera->objectName().isEmpty())
            Camera->setObjectName("Camera");
        Camera->resize(800, 500);
        Camera->setMinimumSize(QSize(800, 500));
        Camera->setStyleSheet(QString::fromUtf8("background-color: #F5EFEE;"));
        actionStartCamera = new QAction(Camera);
        actionStartCamera->setObjectName("actionStartCamera");
        actionStopCamera = new QAction(Camera);
        actionStopCamera->setObjectName("actionStopCamera");
        centralwidget = new QWidget(Camera);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(800, 500));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, -1, -1, 15);
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
        QBrush brush(QColor(245, 239, 238, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
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
        viewfinderPage->setStyleSheet(QString::fromUtf8("background-color: #E8E3E1"));
        gridLayout_6 = new QGridLayout(viewfinderPage);
        gridLayout_6->setObjectName("gridLayout_6");
        viewfinder = new QVideoWidget(viewfinderPage);
        viewfinder->setObjectName("viewfinder");

        gridLayout_6->addWidget(viewfinder, 0, 0, 1, 1);

        stackedWidget->addWidget(viewfinderPage);

        horizontalLayout->addWidget(stackedWidget);

        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: #E8E3E1;\n"
"border-style: none;\n"
"\n"
""));
        translationTab = new QWidget();
        translationTab->setObjectName("translationTab");
        translationTab->setStyleSheet(QString::fromUtf8("background-color: #E8E3E1"));
        verticalLayout_2 = new QVBoxLayout(translationTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        topArea = new QWidget(translationTab);
        topArea->setObjectName("topArea");
        translationDisplay = new QTextEdit(topArea);
        translationDisplay->setObjectName("translationDisplay");
        translationDisplay->setGeometry(QRect(3, 0, 171, 321));
        translationDisplay->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        translationDisplay->setReadOnly(true);

        verticalLayout_2->addWidget(topArea);

        bottomArea = new QWidget(translationTab);
        bottomArea->setObjectName("bottomArea");
        verticalLayout_3 = new QVBoxLayout(bottomArea);
        verticalLayout_3->setObjectName("verticalLayout_3");
        translateInput = new QTextEdit(bottomArea);
        translateInput->setObjectName("translateInput");

        verticalLayout_3->addWidget(translateInput);

        translateButton = new QPushButton(bottomArea);
        translateButton->setObjectName("translateButton");

        verticalLayout_3->addWidget(translateButton);

        verticalLayout_3->setStretch(0, 6);
        verticalLayout_3->setStretch(1, 1);

        verticalLayout_2->addWidget(bottomArea);

        verticalLayout_2->setStretch(0, 8);
        verticalLayout_2->setStretch(1, 2);
        tabWidget->addTab(translationTab, QString());
        dictionaryTab = new QWidget();
        dictionaryTab->setObjectName("dictionaryTab");
        dictionaryTab->setStyleSheet(QString::fromUtf8("background-color: #E8E3E1"));
        verticalLayout_4 = new QVBoxLayout(dictionaryTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        searchArea = new QWidget(dictionaryTab);
        searchArea->setObjectName("searchArea");
        verticalLayout_5 = new QVBoxLayout(searchArea);
        verticalLayout_5->setObjectName("verticalLayout_5");
        dictionaryInput = new QTextEdit(searchArea);
        dictionaryInput->setObjectName("dictionaryInput");

        verticalLayout_5->addWidget(dictionaryInput);

        dictionaryButton = new QPushButton(searchArea);
        dictionaryButton->setObjectName("dictionaryButton");

        verticalLayout_5->addWidget(dictionaryButton);

        verticalLayout_5->setStretch(0, 3);
        verticalLayout_5->setStretch(1, 1);

        verticalLayout_4->addWidget(searchArea);

        dictDisplayArea = new QWidget(dictionaryTab);
        dictDisplayArea->setObjectName("dictDisplayArea");
        verticalLayout_6 = new QVBoxLayout(dictDisplayArea);
        verticalLayout_6->setObjectName("verticalLayout_6");
        dictionaryTextOutput = new QTextEdit(dictDisplayArea);
        dictionaryTextOutput->setObjectName("dictionaryTextOutput");
        dictionaryTextOutput->setReadOnly(true);

        verticalLayout_6->addWidget(dictionaryTextOutput);

        dictionaryPhoto = new QLabel(dictDisplayArea);
        dictionaryPhoto->setObjectName("dictionaryPhoto");

        verticalLayout_6->addWidget(dictionaryPhoto);

        videoDisplay = new QVideoWidget(dictDisplayArea);
        videoDisplay->setObjectName("videoDisplay");

        verticalLayout_6->addWidget(videoDisplay);

        verticalLayout_6->setStretch(0, 1);
        verticalLayout_6->setStretch(1, 4);
        verticalLayout_6->setStretch(2, 3);

        verticalLayout_4->addWidget(dictDisplayArea);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 8);
        tabWidget->addTab(dictionaryTab, QString());
        historyTab = new QWidget();
        historyTab->setObjectName("historyTab");
        historyDisplay = new QTextEdit(historyTab);
        historyDisplay->setObjectName("historyDisplay");
        historyDisplay->setGeometry(QRect(3, 3, 181, 421));
        historyDisplay->setReadOnly(true);
        tabWidget->addTab(historyTab, QString());

        horizontalLayout->addWidget(tabWidget);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addWidget(widget);

        Camera->setCentralWidget(centralwidget);

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
        label_4->setText(QCoreApplication::translate("Camera", "Sign Language to Speech Translator", nullptr));
        label_2->setText(QCoreApplication::translate("Camera", "TextLabel", nullptr));
        translateButton->setText(QCoreApplication::translate("Camera", "Translate", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(translationTab), QCoreApplication::translate("Camera", "Trans", nullptr));
        dictionaryButton->setText(QCoreApplication::translate("Camera", "PushButton", nullptr));
        dictionaryPhoto->setText(QCoreApplication::translate("Camera", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(dictionaryTab), QCoreApplication::translate("Camera", "Dict", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(historyTab), QCoreApplication::translate("Camera", "Hist", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Camera: public Ui_Camera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_H
