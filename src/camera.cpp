/**
 * @file camera.cpp
 * @brief Contains the implementation of the Camera class and associated functions.
 *
 * This file contains the implementation of the Camera class, which represents the main
 * application window and provides functionalities related to camera capture, image processing,
 * and user interaction.
 */
#include "camera.h"
#include "ui_camera.h"
#include "text_to_speech/ttsCall.h"
#include <Python.h>
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


int count = 1; ///< counter for the number of frames
PyObject *pModule; ///< the python inference_classifier module(file)
PyObject *pFunc; ///<  the python 'function'overlay' def in the class (class_object)
PyObject *helloFunc; ///<  the python 'print_hello' def in the class (class_object)
QVideoSink *sink; ///< the QVideoSink object that is used to display the video frame
QVideoFrame old_frame; ///< the previous video frame
PyObject *class_object; ///< the python class object from inference_classifier
PyObject *instance; ///< the python instance of the class object
QString captures_path; ///< Path to where images are saved
QString imgOutputPath; ///< Path where camera frames are saved
QString detectedText; ///< Path wehre detected texts are saved
bool cameraActive; ///< Boolean to check if camera is active
QString lastTranslate; ///< The last translated text
QString currentSubtitle;
QString lastTranslateString;


/**
 * @brief Camera::Camera() : ui(new Ui::Camera) constructs a new Camera:: Camera object
 *
 * The Camera::Camera() : ui(new Ui::Camera) constructor initializes the Camera object 
 * and sets up various connections for button clicks and video frame updates. It also 
 * initializes camera resources.
 */
Camera::Camera() : ui(new Ui::Camera)
{
//    qDebug() << "working?";
    ui->setupUi(this);
    stacked = ui->stackedWidget;

    enableTyping();

//    QPlainTextEdit *historyTextEdit;
    connect(ui->translateButton, &QPushButton::clicked, this, &Camera::translateText);


    m_captureSession.setCamera(&m_camera);

    m_captureSession.setVideoOutput(ui->viewfinder);
    ui->viewfinder->show();

    sink = ui->viewfinder->videoSink();
    m_captureSession.setVideoOutput(sink);

    setupMenus();
//    updateCameras();

//    qDebug() << "workddding?";
    QString currentPath = QDir::currentPath();
    QString newPath = currentPath + "/../../src"; // The current path (of this file)
    std::string pythonCode = "import sys; sys.path.append('"+ newPath.toStdString() +"')";
    captures_path = currentPath + "/../../resources/captures"; // path to where images are saved
    imgOutputPath = captures_path + "/output.jpg"; // path where camera frames are saved
//    qDebug() << "workiasdasdddng?";
    Py_Initialize();
    PyRun_SimpleString(pythonCode.c_str());
//    qDebug() << "working111?";
    pModule = PyImport_ImportModule("inference_classifier");
    if(!pModule){
        qDebug() << "111?";

        PyErr_Print();
    }else{
        class_object = PyObject_GetAttrString(pModule, "PythonTest");
        if(!class_object){
            qDebug() << "222?";
            PyErr_Print();
        }else{
            instance = PyObject_CallObject(class_object, NULL); // Create an instance of the Python class module
            if(!instance){
                qDebug() << "333";
                PyErr_Print();
            }else{
                pFunc = PyObject_GetAttrString(instance, "sign_identifier"); // The Python function to identify the ASL sign.
                if(!pFunc){
                    qDebug() << "444?";
                    PyErr_Print();
                }else{
                    m_captureSession.setImageCapture(&m_imageCapture);
                    m_imageCapture.capture();
                    m_camera.start();
                    //qDebug() << "working111111112?";
                    /**
                     * @brief Connect Camera::imageAvailable to QVideoSink::videoFrameChanged.
                     *
                     * Everytime QVideoSink has a new frame, Camera::imageAvailable is called.
                     */
                    connect(sink, &QVideoSink::videoFrameChanged, this, &Camera::imageAvailable);
                }
//                qDebug() << "1fff";
            }
//            qDebug() << "2fff";
        }
//        qDebug() << "3fff";

    }

    connect(QApplication::instance(), &QApplication::aboutToQuit, this, &Camera::onAboutToQuit);
    closeSettings();
}

void Camera::closeSettings(){
    //qDebug() << "Camera active" << cameraActive << m_camera.isActive();
    if(cameraActive){
        m_camera.start();
    }
    stacked->setCurrentIndex(1);
    cameraMenu->menuAction()->setVisible(true);

}

void Camera::openSettings(){
    //    qDebug() << "settings open";
    cameraActive = m_camera.isActive();
    //qDebug() << "Camera activ1e" << cameraActive << m_camera.isActive();
    if(m_camera.isActive()){
        m_camera.stop();
    }

    stacked->setCurrentIndex(2);
    cameraMenu->menuAction()->setVisible(false);

}

void Camera::onAboutToQuit(){
//    qDebug() << "Quitting";
    Py_Finalize();
}
/**
 * @brief Slot called when a new video frame is captured.
 *
 * This slot processes the incoming video frame, interacts with a Python module,
 * and updates the video frame display. It also performs necessary data conversion
 * between C++ and Python.
 *
 * @note Currently only calls the Python function every 9 frames as to reduce lag.
 *
 * @param frame The incoming video frame.
 */
void Camera::imageAvailable(QVideoFrame frame) {

    frame.setMirrored(true);

    if(count%3 == 0){ // Only call the Python function every 9 frames

        QImage image = frame.toImage();
        if (image.isNull())
        {
            qDebug() << "Failed to load image.";
        }

        QFile imgFile(imgOutputPath);
        // Save the QImage object to the file.
        imgFile.open(QIODevice::WriteOnly);
        image.save(&imgFile, "JPG");
        imgFile.close();

        if (!image.save(imgOutputPath))
        {
            qDebug() << "Failed to save image.";
        }
        if(count%4 == 0){
            PyObject *result = PyObject_CallObject(pFunc, NULL);
            Py_DECREF(result);
            if(result){
                QString resultString = QString::fromUtf8(PyUnicode_AsUTF8(result));
                if(resultString =="del" && detectedText.length() != 0){
                    detectedText.remove(detectedText.length() - 1, 1);
                    ui->translateInput->setPlainText(detectedText);
                }else if(resultString != "del"){
                    if(resultString == "space"){
                        resultString = " ";
                    }
                    if(detectedText.size() >= 1){
                        resultString = resultString.toLower();
                    }
                    detectedText.append(resultString);
                    ui->translateInput->setPlainText(detectedText);
                }
//                sink->setSubtitleText(resultString);
                setSubtitle(resultString);
            }
        }
    }
    count ++;
}

void Camera::setSubtitle(QString str){
    sink->setSubtitleText(str);
    currentSubtitle = str;
}

//bool Camera::getImageAvailable(){
//    bool test = true;
//    return test;
//}

/**
 * @brief Translates and displays input text using text-to-speech.
 *
 * This function is triggered when the "Translate" button is clicked in the GUI.
 * It retrieves the input text from the UI, performs translation logic (if any),
 * and then uses the text-to-speech function to generate speech from the input text.
 * The translated text is displayed in the GUI, and the original and translated text
 * are stored in the history for reference.
 *
 * @note Not currently active.
 */
void Camera::translateText()
{

    TextToSpeech text2Speech;
    // Translation logic
    QString inputText = ui->translateInput->toPlainText();
    if(inputText != ""){ // if there is text to give to tts

        // Create standard string of input text
        std::string inputTextStdString = inputText.toStdString();

        // Call the text-to-speech function with the standard string of input text
        text2Speech.TextToSpeech::tts(inputTextStdString);

        // Store translation in history data structure
        addToHistory(inputText);
        detectedText = "";
        ui->translateInput->setPlainText(detectedText);
    }
}

/**
 * @brief Adds an entry to the translation history.
 *
 * This function appends a pair of original and translated text to the translation
 * history data structure. It updates the history display in the GUI to reflect the
 * new entry.
 *
 * @note Not currently active.
 *
 * @param original The original text before translation.
 * @param translated The translated text (or modified text) after translation.
 */
void Camera::addToHistory(const QString &original)
{
//    if (!lastTranslateString){
//        qDebug() << "first one";
//        QString currentHistory = "";
//    }else{

//    }
//    QList<QString> subList = orinigal;
//    subList.append("_______________");
//    subList.append(history.mid(2));


    history.prepend(original);
    ui->historyDisplay->setPlainText(getHistoryText());
    ui->translationDisplay->setPlainText(getHistoryForTranslate());
    lastTranslate = original;
}

/**
 * @brief Retrieves formatted text for displaying translation history.
 *
 * This function generates a formatted text string containing all entries in the
 * translation history data structure. Each entry includes the original and
 * translated (or modified) text. The formatted text is suitable for display in the
 * history spot in the GUI.
 *
 * @note Not currently active.
 *
 * @return A text string containing translation history.
 */
QString Camera::getHistoryText()
{
    QString historyText;

    for (const QString &string : history)
    {
        historyText += string + "\n";

    }
    return historyText;
}

QString Camera::getHistoryForTranslate()
{
    QString historyText;
    int count = 0;
    for (const QString &string : history)
    {
        if (count == 1){
            historyText += "---------------\n";
        }
        historyText += string + "\n";
        count++;
    }
    return historyText;
}


///**
// * @brief updates the camera device for the application to use.
// *
// * This function updates the camera device for the application to use.
// *
// * @param action the QAction corresponding to the camera device to use
// */
//void Camera::updateCameraDevice(QAction * action)
//{
//    setCamera(qvariant_cast<QCameraDevice>(action->data()));
//}

/**
 * @brief Starts the current camera.
 * 
 * This function starts the current camera.
 *
 * @note Not currently active.
 */
void Camera::startCamera()
{
    //qDebug() << "starting camera";
    cameraActive = true;
    m_camera.start();
    Py_Initialize();
}

/**
 * @brief Stops the current camera.
 * 
 * This function stops the current camera.
 *
 * @note Not currently active.
 */
void Camera::stopCamera()
{
    cameraActive = false;
    m_camera.stop();
    //qDebug() << "stopping camera";
//    Py_Finalize(); // Stop the Python
}


/**
 * @brief Sets up the application menus.
 *
 * This function creates and sets up menus for the application, such as File,
 * Devices, and Camera menus. It also connects menu actions to corresponding
 * functions in the Camera class.
 */
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

    connect(settingsAction, &QAction::triggered, this, &Camera::openSettings);

    connect(closeAction, &QAction::triggered, this, &Camera::closeApp);

    connect(ui->exitSettingsButton, &QPushButton::clicked, this, &Camera::closeSettings);
    connect(ui->enableTypingCheckBox, &QCheckBox::toggled, this, &Camera::enableTyping);
    // Add the menu to the menu bar
    menuBar()->addMenu(fileMenu);

    // Devices menu
    // Prob can remove and put in settings?
//    devicesMenu = new QMenu("Devices", this);
//    //    QAction *deviceAction = new QAction("Choose device", this);
//    //    devicesMenu->addAction(deviceAction);
//    menuBar()->addMenu(devicesMenu);

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

void Camera::closeApp(){
    onAboutToQuit(); // To stop python
    qDebug() << "closing";
    this->close();
}

void Camera::enableTyping(){
    bool checked = ui->enableTypingCheckBox->isChecked();

    if(checked){

        ui->translateInput->setReadOnly(false);
    }else{

        ui->translateInput->setReadOnly(true);
    }
}

/**
 * @brief Displays a camera error message.
 *
 * This function displays a camera error message in a message box if
 * there is an error with the camera.
 */
void Camera::displayCameraError()
{
    if (m_camera.error() != QCamera::NoError){
        QString errString = m_camera.errorString();
        QMessageBox::warning(this, tr("Camera Error"), errString);
    }
}

/**
 * @brief Returns the current camera.
 *
 * This function returns the current camera that is being used.
 *
 * @return The current camera that is being used.
 */
bool Camera::getCameraActive(){

    return cameraActive;

}



/**
 * @brief Returns the last translated text.
 *
 * This function returns the last translated text, which is the last entry in the
 * translation history.
 *
 * @return The last translated text.
 */
QString Camera::getLastHistory(){
    return lastTranslate;
}

QString Camera::getTranslateText(){
    QString text = ui->translateInput->toPlainText();
    return text;
}

void Camera::setTranslateText(QString str){
    ui->translateInput->setPlainText(str);
}

QString Camera::getSubtitle(){
    return currentSubtitle;
}
