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
#include <QGraphicsScene>
#include <QGraphicsWidget>


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
TextToSpeech text2Speech;
QTimer* progressTimer;
const int progressDuration = 200; // 2 seconds in milliseconds

QString lastCharacter; ///< The last character identified
int lastCharacterCount; ///< The number of times in a row the last chracter is found
QString currentCharacter;
QString timerCharacter; // The letter for this current progress bar

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
    progressBar = ui->progressBar;

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

    progressTimer = new QTimer(this);
    progressTimer->setInterval(progressDuration / 100); // Update the progress bar every 10 milliseconds
    //connect(progressTimer, &QTimer::timeout, this, &Camera::updateProgressBar);

    femaleButton = ui->femaleButton;
    maleButton = ui->maleButton;

}

void Camera::closeSettings(){
    //qDebug() << "Camera active" << cameraActive << m_camera.isActive();
    if(cameraActive){
        m_camera.start();
    }
    stacked->setCurrentIndex(1);
    cameraMenu->menuAction()->setVisible(true);

}

void Camera::closeHelp(){
    //qDebug() << "Camera active" << cameraActive << m_camera.isActive();
    if(cameraActive){
        m_camera.start();
    }
    stacked->setCurrentIndex(1);
    cameraMenu->menuAction()->setVisible(true);

}

void Camera::setProgressBarValue(int value){
    progressBar->setValue(value);
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

void Camera::openHelp(){
    //    qDebug() << "settings open";
    cameraActive = m_camera.isActive();
    //qDebug() << "Camera activ1e" << cameraActive << m_camera.isActive();
    if(m_camera.isActive()){
        m_camera.stop();
    }

    stacked->setCurrentIndex(0);
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
    QString resultString = ui->translateInput->toPlainText();

    if(count%3 == 0){ // Only call the Python function every 9 frames
        QString inputText = ui->translateInput->toPlainText();
        detectedText = inputText;
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
        if(count%2 == 0){
            PyObject *result = PyObject_CallObject(pFunc, NULL);
            Py_DECREF(result);
            if(result){

                QString resultString = QString::fromUtf8(PyUnicode_AsUTF8(result));

                currentCharacter = resultString.toLower();
                updateProgressBar();

                setSubtitle(resultString);
            }
        }
    }
    count ++;
}

void Camera::signTimer(){
    progressTimer = new QTimer(this);
    progressTimer->setInterval(progressDuration / 10); // Update the progress bar every 10 milliseconds
    connect(progressTimer, &QTimer::timeout, this, &Camera::updateProgressBar);

}

void Camera::updateProgressBar() {
    int currentValue = progressBar->value();
    if (currentCharacter != ""){
        if (currentValue < 10) {


            if(currentCharacter == timerCharacter){
                if(currentCharacter =="del" && detectedText.length() != 0){
                    progressBar->setValue(currentValue + 2);
                }else if(currentCharacter =="space" && detectedText.length() != 0){
                    progressBar->setValue(currentValue + 2);
                }else{
                    progressBar->setValue(currentValue + 1);
                }

            }else{
                progressBar->setValue(0);
                progressTimer->stop(); // Stop the timer
                timerCharacter = currentCharacter;
                startProgressBar();



            }

        } else {
            // The progress bar is full, add the letter to the text box and reset the progress bar



            if(currentCharacter =="del" && detectedText.length() != 0){
                detectedText.remove(detectedText.length() - 1, 1);
                ui->translateInput->setPlainText(detectedText);
            }else if(currentCharacter =="space"){
                QString resultString = " ";
                detectedText.append(resultString);
                ui->translateInput->setPlainText(detectedText);

            }else{
                if(detectedText.size() == 0){
                    currentCharacter = currentCharacter.toUpper();

                }
                //qDebug() << currentCharacter;
                detectedText.append(currentCharacter);
                ui->translateInput->setPlainText(detectedText);
            }

            lastCharacter = currentCharacter;
            progressBar->setValue(0);
            progressTimer->stop(); // Stop the timer
        }
    }else{
        progressBar->setValue(0);
        progressTimer->stop(); // Stop the timer
    }


}

void Camera::startProgressBar() {
    progressBar->setValue(0); // Reset the progress bar
    progressTimer->start(); // Start the timer to update the progress bar
}


void Camera::setSubtitle(QString str){
    if(str == ""){
        sink->setSubtitleText(nullptr);

    }else{
        sink->setSubtitleText(str);

    }
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
    connect(helpAction, &QAction::triggered, this, &Camera::openHelp);

    connect(closeAction, &QAction::triggered, this, &Camera::closeApp);

    connect(ui->exitSettingsButton, &QPushButton::clicked, this, &Camera::closeSettings);
    connect(ui->enableTypingCheckBox, &QCheckBox::toggled, this, &Camera::enableTyping);
    connect(ui->helpExit, &QPushButton::clicked, this, &Camera::closeHelp);

    connect(ui->pitchSlider, &QSlider::sliderPressed, this, [=]() mutable {
        text2Speech.setPitch(ui->pitchSlider->value());
    });
    connect(ui->pitchSlider, &QSlider::valueChanged, this, [=]() mutable {
        text2Speech.setPitch(ui->pitchSlider->value());
    });

    connect(ui->volumeSlider, &QSlider::sliderPressed, this, [=]() mutable {
        text2Speech.setVolume(ui->volumeSlider->value());
    });
    connect(ui->volumeSlider, &QSlider::valueChanged, this, [=]() mutable {
        text2Speech.setVolume(ui->volumeSlider->value());
    });

    connect(ui->speedSlider, &QSlider::sliderPressed, this, [=]() mutable {
        text2Speech.setSpeed(ui->speedSlider->value());
    });
    connect(ui->speedSlider, &QSlider::valueChanged, this, [=]() mutable {
        text2Speech.setSpeed(ui->speedSlider->value());
    });

    connect(ui->maleButton, &QRadioButton::clicked, this, [=]() {

        text2Speech.setGender(getGender());

    });
    connect(ui->femaleButton, &QRadioButton::clicked, this, [=]() {
        text2Speech.setGender(getGender());

    });


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
    //QAction *cameraSettingsAction = new QAction("Camera Settings", this);

    cameraMenu->addAction(startCameraAction);
    cameraMenu->addAction(stopCameraAction);
    //cameraMenu->addAction(cameraSettingsAction);

    // Adding start and stop camera button connections
    connect(startCameraAction, &QAction::triggered, this, &Camera::startCamera);
    connect(stopCameraAction, &QAction::triggered, this, &Camera::stopCamera);

    menuBar()->addMenu(cameraMenu);

//    QGraphicsView view = ui->dictView;
//    QGraphicsScene scene;

//    QPixmap pixmap("..\ASL guideline.png");
//    scene.addPixmap(pixmap);

//    view.setScene(&scene);
//    view.show();


}

int Camera::getGender(){
    if(ui->maleButton->isChecked()){
//        qDebug() << "male";
        return -1;
    }else if(ui->femaleButton->isChecked()){
//        qDebug() << "female";
        return 1;
    }else{
//        qDebug() << "neither";
        return 0;
    }
}

/**
 * @brief Allows the application to be closed from the file menu.
 *
 * This function is called when the user selects the 'close' item in
 * the file menu.
 */
void Camera::closeApp(){
    onAboutToQuit(); // To stop python
//    qDebug() << "closing";
    this->close();
}

/**
 * @brief Updates the readOnly variable of the translate text input box.
 *
 * This function updates the readOnly function of the translate text input box.
 */
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

/**
 * @brief Returns the subtitle text.
 *
 * This function returns the current subtitle text.
 *
 * @return The current subtitle text.
 */
QString Camera::getSubtitle(){
    return currentSubtitle;
}
