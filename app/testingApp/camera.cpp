#include "camera.h"
#include "ui_camera.h"

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


Camera::Camera() : ui(new Ui::Camera)
{

    ui->setupUi(this);

    m_captureSession.setCamera(&m_camera);

    m_captureSession.setVideoOutput(ui->viewfinder);
    ui->viewfinder->show();

    setupMenus();
    updateCameras();


    m_camera.start(); // to start the camera
}


void Camera::updateCameraDevice(QAction *action){
    setCamera(qvariant_cast<QCameraDevice>(action->data()));
}

void Camera::startCamera(){
    qDebug() << "starting camera";
    m_camera.start();
}

void Camera::stopCamera(){
    m_camera.stop();
    qDebug() << "stopping camera";
}

void Camera::updateCameraActive(bool active){
    if (active) {
        ui->actionStartCamera->setEnabled(false);
        ui->actionStopCamera->setEnabled(true);

    } else {
        ui->actionStartCamera->setEnabled(true);
        ui->actionStopCamera->setEnabled(false);
    }
}

void Camera::setupMenus(){
    fileMenu = new QMenu("File", this);
    // Create QAction instances
    QAction *startCameraAction = new QAction("Start Camera", this);
    QAction *stopCameraAction = new QAction("Stop Camera", this);
    QAction *cameraSettingsAction = new QAction("Camera Settings", this);
    QAction *closeAction = new QAction("Close", this);

    // Add actions to the menu
    fileMenu->addAction(startCameraAction);
    fileMenu->addAction(stopCameraAction);
    fileMenu->addAction(cameraSettingsAction);
    fileMenu->addSeparator(); // Adds a separator line
    fileMenu->addAction(closeAction);

    // Adding start and stop camera button connections
    connect(startCameraAction, &QAction::triggered, this, &Camera::startCamera);
    connect(stopCameraAction, &QAction::triggered, this, &Camera::stopCamera);
    // Add the menu to the menu bar
    menuBar()->addMenu(fileMenu);

    // Devices menu
    //Prob can remove and put in settings?
    devicesMenu = new QMenu("Devices", this);
    //    QAction *deviceAction = new QAction("Choose device", this);
    //    devicesMenu->addAction(deviceAction);
    menuBar()->addMenu(devicesMenu);
}

void Camera::displayCameraError()
{
    if (m_camera.error() != QCamera::NoError)
        QMessageBox::warning(this, tr("Camera Error"), m_camera.errorString());
}


void Camera::setCamera(const QCameraDevice &cameraDevice){
    //m_camera.reset(new QCamera(cameraDevice));
    //m_captureSession.setCamera(m_camera.data());

    //connect(m_camera.data(), &QCamera::activeChanged, this, &Camera::updateCameraActive);
    //connect(m_camera.data(), &QCamera::errorOccurred, this, &Camera::displayCameraError);

    if (!m_mediaRecorder) {
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

void Camera::updateCameras(){
    devicesMenu->clear();
    /*
     * This will add all available cameras to the devicesMenu.
     * You can then select which camera you would like to use
     * from the list.
     * */
    const QList<QCameraDevice> availableCameras = QMediaDevices::videoInputs();
    for (const QCameraDevice &cameraDevice : availableCameras) {
        QAction *videoDeviceAction = new QAction(cameraDevice.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraDevice));
        if (cameraDevice == QMediaDevices::defaultVideoInput())
            videoDeviceAction->setChecked(true);

        devicesMenu->addAction(videoDeviceAction);
    }
}

