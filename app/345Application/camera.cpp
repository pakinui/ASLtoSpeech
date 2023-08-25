#include "camera.h"
#include "ui_camera.h"
#include <Python.h>

//// #include "dictionary.h" // Include the Dictionary class header
//// #include "translationtab.h"
//// #include "dictionarytab.h"
#include <opencv2/opencv.hpp>

#include <QAudioDevice>
#include <QPainter>
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

#include <QImageCapture>
#include <QVideoSink>
#include <QVideoFrameFormat>
#include <QtMultimedia>




int count = 1;
PyObject *pModule;
QVideoSink *sink;
QVideoFrame old_frame;


Camera::Camera() : ui(new Ui::Camera)
{
    qDebug() << "beginning";
    ui->setupUi(this);

//    QPlainTextEdit *historyTextEdit;
    connect(ui->translateButton, &QPushButton::clicked, this, &Camera::translateText);
    connect(ui->dictionaryButton, &QPushButton::clicked, this, &Camera::searchDictionary);
    ui->translateButton->setStyleSheet("background-color: #F5EFEE; color: black;");

    m_captureSession.setCamera(&m_camera);

    m_captureSession.setVideoOutput(ui->viewfinder);
    ui->viewfinder->show();

    sink = ui->viewfinder->videoSink();
    m_captureSession.setVideoOutput(sink);

    setupMenus();
    updateCameras();

//    QImageCapture *imageCapture = new QImageCapture();
    // Connect the imageCaptured() signal to a slot that will be called when a new frame is captured.
    //connect(m_camera, &QCamera::imageFrameReady, this, &Camera::imageAvailable);
    // Connect the imageCaptured() signal to a slot that will be called when a new frame is captured.
    //connect(m_imageCapture, &QImageCapture::imageCaptured, this, &Camera::imageCaptured);

    // Set the camera to be used by the image capture.
    //m_imageCapture->setCaptureSession(&m_captureSession);
//    Py_Initialize();
//    QString currentPath = QDir::currentPath();
//    QString newPath = currentPath + "/../345Application";
//    std::string pythonCode = "import sys; sys.path.append('"+ newPath.toStdString() +"')";
//    PyRun_SimpleString(pythonCode.c_str());
//    pModule = PyImport_ImportModule("inference_classifier");
//    PyErr_Print();

//    Py_Finalize();

    m_captureSession.setImageCapture(&m_imageCapture);

    m_imageCapture.capture();
    //m_imageCapture.setCaptureInterval(500); // 5 frames per second

    m_camera.start();

//    connect(&m_imageCapture, &QImageCapture::imageAvailable, this, &Camera::imageAvailable, Qt::QueuedConnection);
    connect(sink, &QVideoSink::videoFrameChanged, this, &Camera::imageAvailable);



}


// This slot is called when a new frame is captured.
void Camera::imageAvailable(QVideoFrame frame) {
    //qDebug() << count << "not working";
    if(count == 1){
        old_frame = frame;
    }
    if(count%20 == 0){
        qDebug() << count;

        //QImage image = frame.toImage();
        QString str = "hello " + QString::number(count);;
        sink->setSubtitleText(str);
        // Create a Python object that wraps the C++ object.
        //PySide6.QtMultimedia.QVideoSink video_sink = new PySide6.QtMultimedia.QVideoSink(video_sink_cpp);

        // Pass the Python object to the Python.
        //python_code.video_sink = video_sink;

        sink->setVideoFrame(old_frame);
        old_frame = frame;
        count++;
    }
    count++;
// below saves the frames as images in /captures
// currently just overwrites the old image with the current frame
// but it can save each frame individually

//    QImage image = frame.toImage();
//    // Do something with the frame.
//    // Load or create a QImage

//    if (image.isNull())
//    {
//        qDebug() << "Failed to load image.";

//    }

//    // Generate a unique filename using the current time.
//    QString filename = QString::number(count);
////    count += 1;

//    QString currentPath = QDir::currentPath();
//    QString newPath = currentPath + "/../345Application";
//    // Create a file in the `captures` folder with the unique filename.
//    QString path = QString("/captures/%1.jpg").arg(filename);
//    QString path2 = newPath + path;

//    QFile file(path2);

//    // Save the QImage object to the file.
//    file.open(QIODevice::WriteOnly);
//    image.save(&file, "JPG");
//    file.close();
//    //qDebug() << path2 << "saved";

//    // Save the QImage to a file

//    if (image.save(path2))
//    {
//        qDebug() << "Image saved successfully.";
//    }
//    else
//    {
//        qDebug() << "Failed to save image.";
//    }

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
