/**
 * @file camera.h
 * @brief Contains the declaration of the Camera class.
 *
 * This file defines the Camera class, which represents the main application window
 * and provides functionalities related to camera capture, image processing, and user interaction.
 */
#ifndef CAMERA_H
#define CAMERA_H

#include <QMainWindow>
#include <QAudioInput>
#include <QCamera>
#include <QImageCapture>
#include <QVideoFrame>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QMediaMetaData>
#include <QMediaRecorder>
#include <QScopedPointer>
#include <QMenu>
#include <QMenuBar>
#include <QList>
#include <QPair>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QImageCapture>
#include <QVideoSink>
#include <QtCore>

/**
 * @namespace Ui
 * @brief Contains user interface classes for the Camera application.
 *
 * The Ui namespace contains user interface classes specifically designed for
 * the Camera application. These classes define the graphical user interface
 * elements and forms used within the application.
 */
QT_BEGIN_NAMESPACE
namespace Ui {


class Camera;
}
QT_END_NAMESPACE

/**
 * @class Camera
 * @brief The Camera class represents the main application window and camera functionalities.
 * 
 * This class represents the main application window and provides functionalities related to
 * camera capture, image processing, and user interaction. It also provides a UI for the user
 * to interact with the application.
 */
class Camera : public QMainWindow
{
//    Q_OBJECT




public:
    /**
     * @brief Camera() is the constructor for the Camera class.
     *
     * The Camera() constructor initializes the Camera class and sets up the UI and camera-related components.
     */
    Camera();


//private:
    Ui::Camera *ui;
    QList<QString> history; ///< list to store history of translations
    QActionGroup *videoDevicesGroup = nullptr; ///< group of video devices

    QMediaDevices m_devices; ///< available multimedia input/output devices instance
    QImageCapture m_imageCapture; ///< image capture instance
    QMediaCaptureSession m_captureSession; ///< media capture session instance
    QCamera m_camera; ///< camera instance
    QCamera *cam;

    QScopedPointer<QAudioInput> m_audioInput;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;

    //Menu bar objects
    QMenu *fileMenu;
    QMenu *devicesMenu;
    QMenu *cameraMenu;

    bool m_isCapturingImage = false;
    bool m_applicationExiting = false;
    bool m_doImageCapture = true;

public Q_SLOTS:

//private Q_SLOTS:
    /**
     * @brief setupMenus
     *
     * Sets up the MenuBar in the applicatoin.
     */
    void setupMenus();
    /**
     * @brief displayCameraError
     * 
     * Displays an error message if the camera fails to start.
     */
    void displayCameraError();
    
    /**
     * @brief Update the camera device for the application to use.
     * 
     * This function updates the camera device for the application to use.
     * 
     * @param action
     */
    void updateCameraDevice(QAction *action);
    
    /**
     * @brief updateCameras
     * 
     * Updates the list of available cameras.
     */
    void updateCameras();
    
    /**
     * @brief Set the applications camera.
     * 
     * This function sets the camera for the application to use.
     * 
     * @param cameraDevice The camera device for the application to use.
     */
    void setCamera(const QCameraDevice &cameraDevice);
    
    
    /**
     * @brief translateText
     * 
     * Translates the text in the text box.
     */
    void translateText();


    /**
     * @brief addToHistory
     * 
     * Adds the text in the text box to the history.
     * 
     * @param original The original text.
     * @param translated The translated text.
     */
    void addToHistory(const QString &original);

    /**
     * @brief Start the current Camera.
     * 
     * This function starts the current Camera.
     */
    void startCamera();

    /**
     * @brief Stop the current Camera.
     * 
     * This function stops the current Camera.
     */
    void stopCamera();

    /**
     * @brief getHistoryText
     * 
     * Gets the text from the history.
     * 
     * @return The text from the history.
     */
    QString getHistoryText();

    /**
     * @brief imageAvailable
     * @param frame The current frame from the camera.
     *
     * This function is connected to the QVideoSink::imageAvailable function.
     * Everytime the camera recieves a new frame, this function is also called.
     * This checks the frame for a recognised ASL sign.
     */
    void imageAvailable(QVideoFrame frame);

    bool getImageAvailable();
    bool getCameraActive();
    QString getLastHistory();
};

#endif // CAMERA_H
