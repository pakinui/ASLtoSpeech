#include "camera.h"
#include "ui_camera.h"
#include <Python.h>
//// #include "dictionary.h" // Include the Dictionary class header
//// #include "translationtab.h"
//// #include "dictionarytab.h"
#include <opencv2/opencv.hpp>

#include <QAudioDevice>

#include <QAudioInput>
#include <QCameraDevice>
#include <QMediaDevices>
#include <QMediaFormat>
#include <QMediaMetaData>
#include <QMediaRecorder>
#include <QVideoWidget>
#include <QMenu>
#include <QLineEdit>
#include <QMessageBox>

#include <QAction>
#include <QActionGroup>
#include <QImage>
#include <QKeyEvent>
#include <QPalette>

#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QColor>
#include <QPlainTextEdit>

#include <QString>
#include <QList>
#include <QPair>

#include <QResource>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QProcessEnvironment>
#include <QDebug>
#include <QDir>
#include <iostream>
#include <QApplication>
#include <QCamera>
#include <QVBoxLayout>
#include <QPixmap>

Camera::Camera() : ui(new Ui::Camera)
{

//    ui->setupUi(this);

//    QPlainTextEdit *historyTextEdit;
//    connect(ui->translateButton, &QPushButton::clicked, this, &Camera::translateText);
//    connect(ui->dictionaryButton, &QPushButton::clicked, this, &Camera::searchDictionary);
//    ui->translateButton->setStyleSheet("background-color: #F5EFEE; color: black;");

//    m_captureSession.setCamera(&m_camera);
//    m_captureSession.setVideoOutput(ui->viewfinder);
//    ui->viewfinder->show();


//    setupMenus();
//    updateCameras();

//    m_camera.start();
}

void Camera::translateText()
{
    QString inputText = ui->translateInput->toPlainText();
    // Translation logic

    // QString translatedText = performTranslation(inputText);
    // ui->translationDisplay->setPlainText(translatedText);

    // Create standard string of input text
    std::string inputTextStdString = inputText.toStdString();
    // Call the text-to-speech function with the standard string of input text
    tts(inputTextStdString);

    ui->translationDisplay->setPlainText(inputText);
    // Store translation in history data structure
    // addToHistory(inputText, translatedText);
    addToHistory(inputText, inputText);
}

void Camera::addToHistory(const QString &original, const QString &translated)
{
    history.append(QPair<QString, QString>(original, translated));
    ui->historyDisplay->setPlainText(getHistoryText());
}

QString Camera::getHistoryText()
{
    QString historyText;
    for (const QPair<QString, QString> &entry : history)
    {
        historyText += "Original: " + entry.first + "\n";
        historyText += "Translated: " + entry.second + "\n\n";
    }
    return historyText;
}

void Camera::searchDictionary()
{
    QString searchTerm = ui->dictionaryInput->toPlainText();

    //    QResource jsonResource(":/data/1000.json");
    //    QString dataFilePath = jsonResource.absoluteFilePath(); // Construct the file path

    // qDebug() << dataFilePath;
    //  Create an instance of the Dictionary class
    // Dictionary dictionary(":/data/data/1000.json", ui->videoDisplay, ui->dictionaryPhoto);

    // dictionary.search(searchTerm);

    // Dictionary search logic
    // QString searchResult = performDictionarySearch(searchTerm);
    // ui->dictionaryDisplay->setPlainText(searchResult);
    ui->dictionaryTextOutput->setPlainText(searchTerm);
}

void Camera::updateCameraDevice(QAction * action)
{
    setCamera(qvariant_cast<QCameraDevice>(action->data()));
}

void Camera::startCamera()
{
    qDebug() << "starting camera";

    m_camera.start();
}

void Camera::stopCamera()
{
    m_camera.stop();
    qDebug() << "stopping camera";
}

void Camera::updateCameraActive(bool active)
{
    if (active)
    {
        ui->actionStartCamera->setEnabled(false);
        ui->actionStopCamera->setEnabled(true);
    }
    else
    {
        ui->actionStartCamera->setEnabled(true);
        ui->actionStopCamera->setEnabled(false);
    }
}

void Camera::setupMenus()
{
    fileMenu = new QMenu("File", this);
    // Create QAction instances
    QAction *settingsAction = new QAction("Settings", this);
    QAction *closeAction = new QAction("Close", this);
    QAction *helpAction = new QAction("Help", this);

    // Add actions to the menu
    fileMenu->addAction(settingsAction);
    fileMenu->addAction(helpAction);
    fileMenu->addSeparator(); // Adds a separator line
    fileMenu->addAction(closeAction);

    // Add the menu to the menu bar
    menuBar()->addMenu(fileMenu);

    // Devices menu
    // Prob can remove and put in settings?
    devicesMenu = new QMenu("Devices", this);
    //    QAction *deviceAction = new QAction("Choose device", this);
    //    devicesMenu->addAction(deviceAction);
    menuBar()->addMenu(devicesMenu);

    // Camera menu
    cameraMenu = new QMenu("Camera", this);

    QAction *startCameraAction = new QAction("Start Camera", this);
    QAction *stopCameraAction = new QAction("Stop Camera", this);
    QAction *cameraSettingsAction = new QAction("Camera Settings", this);

    cameraMenu->addAction(startCameraAction);
    cameraMenu->addAction(stopCameraAction);
    cameraMenu->addAction(cameraSettingsAction);

    // Adding start and stop camera button connections
    connect(startCameraAction, &QAction::triggered, this, &Camera::startCamera);
    connect(stopCameraAction, &QAction::triggered, this, &Camera::stopCamera);

    menuBar()->addMenu(cameraMenu);
}

void Camera::displayCameraError()
{
    if (m_camera.error() != QCamera::NoError)
        QMessageBox::warning(this, tr("Camera Error"), m_camera.errorString());
}

void Camera::setCamera(const QCameraDevice &cameraDevice)
{
    // m_camera.reset(new QCamera(cameraDevice));
    // m_captureSession.setCamera(m_camera.data());

    // connect(m_camera.data(), &QCamera::activeChanged, this, &Camera::updateCameraActive);
    // connect(m_camera.data(), &QCamera::errorOccurred, this, &Camera::displayCameraError);

    if (!m_mediaRecorder)
    {
        m_mediaRecorder.reset(new QMediaRecorder);
        m_captureSession.setRecorder(m_mediaRecorder.data());
    }

    m_captureSession.setVideoOutput(ui->viewfinder);

    updateCameraActive(m_camera.isActive());
    //    updateRecorderState(m_mediaRecorder->recorderState());
    //    readyForCapture(m_imageCapture->isReadyForCapture());

    //    updateCaptureMode();
    m_doImageCapture = 1;

    m_camera.start();
}

void Camera::updateCameras()
{
    devicesMenu->clear();
    /*
     * This will add all available cameras to the devicesMenu.
     * You can then select which camera you would like to use
     * from the list.
     * */
    const QList<QCameraDevice> availableCameras = QMediaDevices::videoInputs();
    for (const QCameraDevice &cameraDevice : availableCameras)
    {
        QAction *videoDeviceAction = new QAction(cameraDevice.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraDevice));
        if (cameraDevice == QMediaDevices::defaultVideoInput())
            videoDeviceAction->setChecked(true);

        devicesMenu->addAction(videoDeviceAction);
    }
}
