#include "camera.h"
#include "ui_camera.h"
#include "text_to_speech/ttsCall.h"
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
PyObject *pModule; // the python inference_classifier module(file)
PyObject *pFunc; //  the python 'function'overlay' def in the class (class_object)
PyObject *helloFunc; //  the python 'print_hello' def in the class (class_object)
QVideoSink *sink;
QVideoFrame old_frame;
PyObject *class_object; // the python class object from inference_classifier
PyObject *instance;
QString captures_path;
QString imgOutputPath;


Camera::Camera() : ui(new Ui::Camera)
{
    //qDebug() << "beginning";
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
//    QString newPath = currentPath + "/../../src";
//    std::string pythonCode = "import sys; sys.path.append('"+ newPath.toStdString() +"')";
//    PyRun_SimpleString(pythonCode.c_str());
////    qDebug() << newPath;
//    pModule = PyImport_ImportModule("inference_classifier");

//    PyErr_Print();
//    // Create a Python object that wraps the C++ object.
//    PyObject *python_object = PyCapsule_New(sink, "sink", nullptr);

//    // Pass the Python object to Python.
//    PyModule_AddObject(pModule, "sink", python_object);
//    Py_Finalize();
    Py_Initialize();
    QString currentPath = QDir::currentPath();
    QString newPath = currentPath + "/../../src";
    std::string pythonCode = "import sys; sys.path.append('"+ newPath.toStdString() +"')";
    PyRun_SimpleString(pythonCode.c_str());
    pModule = PyImport_ImportModule("inference_classifier");


    captures_path = currentPath + "/../../resources/captures";
    // Create a file in the `captures` folder with the unique filename.


    imgOutputPath = captures_path + "/output.jpg";
    // Create a file in the `captures` folder with the unique filename.
    //        QString path = QString("/captures/%1.jpg").arg(filename);
    //        QString path2 = newPath2 + path;
    //qDebug() << newPath2;


    if(!pModule){
        PyErr_Print();
    }else{
        //qDebug() << "yo";

    }
    class_object = PyObject_GetAttrString(pModule, "PythonTest");

    if(!class_object){
        PyErr_Print();
    }else{
        //qDebug() << "yo233";
    }
    // Create an instance of the PythonTest class



    instance = PyObject_CallObject(class_object, NULL);
    if(!instance){
        PyErr_Print();
    }else{
        //qDebug() << "yo233 instance";
    }

    pFunc = PyObject_GetAttrString(instance, "overlay");

    if(!pFunc){
        PyErr_Print();
    }else{
        //qDebug() << "yo2";
    }
    //Py_Finalize();


    m_captureSession.setImageCapture(&m_imageCapture);

    m_imageCapture.capture();
    //m_imageCapture.setCaptureInterval(500); // 5 frames per second

    m_camera.start();

//    connect(&m_imageCapture, &QImageCapture::imageAvailable, this, &Camera::imageAvailable, Qt::QueuedConnection);
    connect(sink, &QVideoSink::videoFrameChanged, this, &Camera::imageAvailable);
    //sink->setSubtitleText("hii");


}


// This slot is called when a new frame is captured.
void Camera::imageAvailable(QVideoFrame frame) {
//    const uchar *frame_data = frame.bits(2);
//    int height = frame.height();
//    int width = frame.width();
//    int c = frame.planeCount();
    //qDebug() << c;
//    Py_Initialize();

    // Convert QVideoFrame to QImage
    //QImage image1(frame.bits(2),
//                 frame.width(),
//                 frame.height(),
//                 frame.bytesPerLine(2),
//                 QImage::Format_RGB888);
//    QImage image1 = frame.toImage();

//    // Convert QImage to QPixmap (if needed)
//    QPixmap pixmap = QPixmap::fromImage(image1);

//    // Convert QPixmap to Python bytes object (if needed)
//    QByteArray byteArray;
//    QBuffer buffer(&byteArray);
//    pixmap.save(&buffer, "PNG"); // Use any desired format here
//    PyObject *bytesObject = PyBytes_FromStringAndSize(byteArray.constData(), byteArray.size());
    // below saves the frames as images in resources/captures
    // currently just overwrites the old image with the current frame
    // but it can save each frame individually
    if(count%9 == 0){

        QImage image = frame.toImage();
        // Do something with the frame.
        // Load or create a QImage

        if (image.isNull())
        {
            qDebug() << "Failed to load image.";

        }

     //Generate a unique filename using the current time.
       // QString filename = QString::number(1);
    //    count += 1;


//        QString newPath2 = captures_path + "/output.jpg";
//        // Create a file in the `captures` folder with the unique filename.
////        QString path = QString("/captures/%1.jpg").arg(filename);
////        QString path2 = newPath2 + path;
//        //qDebug() << newPath2;
//        QFile file(newPath2);
        QFile imgFile(imgOutputPath);

        // Save the QImage object to the file.
        imgFile.open(QIODevice::WriteOnly);
        image.save(&imgFile, "JPG");
        imgFile.close();

        //qDebug() << path2 << "saved";

     //Save the QImage to a file

        if (image.save(imgOutputPath))
        {
            //qDebug() << "Image saved successfully.";
        }
        else
        {
            qDebug() << "Failed to save image.";
        }

        //Py_Initialize();

        PyObject *result = PyObject_CallObject(pFunc, NULL);

        //PyObject *result = PyObject_CallFunctionObjArgs(pFunc, NULL);
        Py_DECREF(result);
        if(result){
            QString resultString = QString::fromUtf8(PyUnicode_AsUTF8(result));

            //qDebug() << resultString;
            sink->setSubtitleText(resultString);

        }


        //Py_Finalize();

    }
    count ++;


//    QString currentPath = QDir::currentPath();
//    QString newPath = currentPath + "/../../src";
//    std::string pythonCode = "import sys; sys.path.append('"+ newPath.toStdString() +"')";
//    PyRun_SimpleString(pythonCode.c_str());
//    PyObject* pModule = PyImport_ImportModule("inference_classifier");
//    if(!pModule){
//        PyErr_Print();
//    }else{
//        qDebug() << "yo";
//    }


//    PyObject *pFunc = PyObject_GetAttrString(pModule, "overlay");
//    if(!pFunc){
//        PyErr_Print();
//    }else{
//        qDebug() << "yo2";
//    }
//    qDebug() << "hi";
    // Create a flat C array to hold the image data
//    size_t frame_size = height * width * 3;

//    unsigned char *flat_array = new unsigned char[frame_size];

//    // Convert flat array into a Python bytes object
//    PyObject *pBytes = PyBytes_FromStringAndSize(reinterpret_cast<const char *>(flat_array), frame_size);

    //QImage image = frame.toImage();
//    QString resultString = QString::fromUtf8(PyUnicode_AsUTF8(pValue));

//    QString str = "hello " + resultString;
//    sink->setSubtitleText(str);

    // Create a Python object that wraps the C++ object.
    //PySide6.QtMultimedia.QVideoSink video_sink = new PySide6.QtMultimedia.QVideoSink(video_sink_cpp);

    // Pass the Python object to the Python.
    //python_code.video_sink = video_sink;

    //sink->setVideoFrame(frame);
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
    Py_Finalize(); // stop the py
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
