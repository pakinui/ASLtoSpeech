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


QT_BEGIN_NAMESPACE
namespace Ui {

// do we need comment here as well as the below Camera?
class Camera;
}
QT_END_NAMESPACE

/**
 * @class Camera
 * @brief The Camera class represents the main application window and camera functionalities.
 */
class Camera : public QMainWindow
{
    Q_OBJECT




public:
    /**
     * @brief Constructor for the Camera class.
     *
     * This constructor initializes the Camera class and sets up the UI and camera-related components.
     */
    Camera();


private:
    Ui::Camera *ui;
    QList<QPair<QString, QString>> history; ///< list to store history of translations
    QActionGroup *videoDevicesGroup = nullptr; ///< group of video devices

    QMediaDevices m_devices;
    QImageCapture m_imageCapture; ///< image capture instance
    QMediaCaptureSession m_captureSession; ///< media capture session instance
    QCamera m_camera; ///< camera instance
    QCamera *cam;




    QScopedPointer<QAudioInput> m_audioInput;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;

    void setupMenus();
    QMenu *fileMenu;
    QMenu *devicesMenu;
    QMenu *cameraMenu;



    bool m_isCapturingImage = false;
    bool m_applicationExiting = false;
    bool m_doImageCapture = true;

public Q_SLOTS:

private Q_SLOTS:
    /**
     * @brief displayCameraError
     */
    void displayCameraError();
    /**
     * @brief Update the camera device for the application to use.
     * @param action
     */
    void updateCameraDevice(QAction *action);
    /**
     * @brief updateCameras
     */
    void updateCameras();
    /**
     * @brief Set the applications camera.
     * @param cameraDevice The camera device for the application to use.
     */
    void setCamera(const QCameraDevice &cameraDevice);
    /**
     * @brief updateCameraActive
     * @param active
     */
    void updateCameraActive(bool active);
    /**
     * @brief translateText
     */
    void translateText();
    /**
     * @brief searchDictionary
     */
    void searchDictionary();
    /**
     * @brief addToHistory
     * @param original
     * @param translated
     */
    void addToHistory(const QString &original, const QString &translated);

    /**
     * @brief Start the current Camera.
     */
    void startCamera();

    /**
     * @brief Stop the current Camera.
     */
    void stopCamera();
    /**
     * @brief getHistoryText
     * @return
     */
    QString getHistoryText();

    void imageAvailable(QVideoFrame frame);
};

#endif // CAMERA_H