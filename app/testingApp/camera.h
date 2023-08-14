#ifndef CAMERA_H
#define CAMERA_H

#include <QAudioInput>
#include <QCamera>
#include <QImageCapture>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QMediaMetaData>
#include <QMediaRecorder>
#include <QScopedPointer>
#include <QMenu>
#include <QMenuBar>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Camera;
}
class QActionGroup;
QT_END_NAMESPACE

class Camera : public QMainWindow
{
    Q_OBJECT

public:
    Camera();

public slots:


private slots:

    void displayCameraError();
    void updateCameraDevice(QAction *action);
    void updateCameras();
    void setCamera(const QCameraDevice &cameraDevice);
    void updateCameraActive(bool active);

    void startCamera();
    void stopCamera();

private:
    Ui::Camera *ui;

    QActionGroup *videoDevicesGroup = nullptr;

    QMediaDevices m_devices;
    QScopedPointer<QImageCapture> m_imageCapture;
    QMediaCaptureSession m_captureSession;
    QCamera m_camera;
    QScopedPointer<QAudioInput> m_audioInput;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;

    void setupMenus();
    QMenu *fileMenu;
    QMenu *devicesMenu;
    QMenu *cameraMenu;


    bool m_isCapturingImage = false;
    bool m_applicationExiting = false;
    bool m_doImageCapture = true;

};

#endif // CAMERA_H

