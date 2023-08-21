#ifndef CAMERA_H
#define CAMERA_H

#include <QMainWindow>
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
#include <QList>
#include <QPair>
#include <QVideoWidget>
#include <QMediaPlayer>

//#include "python_wrapper.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Camera;
}
QT_END_NAMESPACE

class Camera : public QMainWindow
{
    Q_OBJECT

public:
    //Camera(QWidget *parent = nullptr);
    //~Camera();
    Camera();

private:
    Ui::Camera *ui;
    QList<QPair<QString, QString>> history;
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

//private slots:
    void displayCameraError();
    void updateCameraDevice(QAction *action);
    void updateCameras();
    void setCamera(const QCameraDevice &cameraDevice);
    void updateCameraActive(bool active);
    void translateText();
    void searchDictionary();
    void startCamera();
    void addToHistory(const QString &original, const QString &translated);
    void stopCamera();
    QString getHistoryText();





};

#endif // CAMERA_H

