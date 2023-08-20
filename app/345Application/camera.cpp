#include "camera.h"
#include "ui_camera.h"
// to use min(), max()
#include <algorithm>
#include "python_files/include/python.h"
// #include "dictionary.h" // Include the Dictionary class header
// #include "translationtab.h"
// #include "dictionarytab.h"
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

Camera::Camera() : ui(new Ui::Camera)
{

    ui->setupUi(this);

    QPlainTextEdit *historyTextEdit;
    connect(ui->translateButton, &QPushButton::clicked, this, &Camera::translateText);
    connect(ui->dictionaryButton, &QPushButton::clicked, this, &Camera::searchDictionary);
    ui->translateButton->setStyleSheet("background-color: #F5EFEE; color: black;");

    m_captureSession.setCamera(&m_camera);

    m_captureSession.setVideoOutput(ui->viewfinder);
    ui->viewfinder->show();

    setupMenus();
    updateCameras();

    PyObject *mp = PyImport_ImportModule("mediapipe");
    PyObject *np = PyImport_ImportModule("numpy");
    PyObject *pickle = PyImport_ImportModule("pickle");

    if (mp == NULL || np == NULL || pickle == NULL)
    {
        PyErr_Print();
        qDebug() << "Error";
    }
    else
    {
        PyRun_SimpleString("print('All moduels are successfully imported!')");
    }

    // Load model dictionary
    PyObject *pModelDict = PyObject_CallMethod(pickle, "load", "(s)", "./ASL_model.p");
    PyObject *pModel = PyObject_GetAttrString(pModelDict, "model");

    // Get references to the required classes and functions
    PyObject *pMpHands = PyObject_GetAttrString(mp, "solutions");
    PyObject *pMpHandsClass = PyObject_GetAttrString(pMpHands, "Hands");

    // Create a dictionary to store the constructor arguments
    PyObject *pArgsDict = PyDict_New();
    PyDict_SetItemString(pArgsDict, "static_image_mode", Py_True);                        // static_image_mode=True
    PyDict_SetItemString(pArgsDict, "min_detection_confidence", PyFloat_FromDouble(0.3)); // min_detection_confidence=0.3

    // Create an instance of the Hands class with the specified parameters
    PyObject *pHands = PyObject_Call(pMpHandsClass, PyTuple_New(0), pArgsDict);

    m_camera.start(); // to start the camera
    cv::VideoCapture cap(0);

    while (true)
    {
        // Read frame
        cv::Mat frame;
        cap.read(frame);

        // Get the shape of the frame
        PyObject *pFrameShape = PyObject_GetAttrString(frame, "shape");

        // Extract the height, width, and number of channels
        PyObject *pHeight = PyLong_FromSsize_t(0);
        PyObject *pWidth = PyLong_FromSsize_t(0);
        PyObject *pChannels = PyLong_FromSsize_t(0);

        if (PyTuple_Check(pFrameShape) && PyTuple_Size(pFrameShape) == 3)
        {
            pHeight = PyTuple_GetItem(pFrameShape, 0);
            pWidth = PyTuple_GetItem(pFrameShape, 1);
            pChannels = PyTuple_GetItem(pFrameShape, 2);
        }

        // Convert the PyObject* values to C++ types
        int H = PyLong_AsLong(pHeight);
        int W = PyLong_AsLong(pWidth);

        // Clean up
        Py_XDECREF(pFrameShape);
        Py_XDECREF(pHeight);
        Py_XDECREF(pWidth);
        Py_XDECREF(pChannels);

        // Convert frame to RGB
        cv::Mat frameRgb;
        cv::cvtColor(frame, frameRgb, cv::COLOR_BGR2RGB);

        PyObject *dataAux = PyList_New(0);
        PyObject *x_ = PyList_New(0);
        PyObject *y_ = PyList_New(0);

        // Process hands
        PyObject *pResults = PyObject_GetAttrString(pHands, "process");

        // Get multi_hand_landmarks
        PyObject *pMultiHandLandmarks = PyObject_GetAttrString(pResults, "multi_hand_landmarks");

        if (pMultiHandLandmarks != NULL && PyList_Check(pMultiHandLandmarks))
        {
            int num_detected_hands = PyList_Size(pMultiHandLandmarks);

            for (int h = 0; h <= num_detected_hands; ++h)
            {
                PyObject *pHandLandmarks = PyList_GetItem(pMultiHandLandmarks, h);
                PyObject *pLandmakrtPoint = PyObject_GetAttrString(pHandLandmarks, "landmarks");

                for (int i = 0; h <= PyList_Size(pLandmakrtPoint); ++i)
                {
                    PyObject *pLandmark = PyList_GetItem(pLandmakrtPoint, i);

                    PyObject *pX = PyObject_GetAttrString(pLandmark, "x");
                    PyObject *pY = PyObject_GetAttrString(pLandmark, "y");

                    double x = PyFloat_AsDouble(pX);
                    double y = PyFloat_AsDouble(pY);

                    PyObject *pX1 = PyFloat_FromDouble(x);
                    PyObject *pY1 = PyFloat_FromDouble(y);
                    Py_DECREF(pX);
                    Py_DECREF(pY);

                    PyList_Append(x_, pX1);
                    PyList_Append(y_, pY1);

                    // Release pX and pY
                    Py_DECREF(pX1);
                    Py_DECREF(pY1);

                    Py_DECREF(pLandmark);
                }

                double min_x = *std::min_element(x_.begin(), x_.end());
                double min_y = *std::min_element(y_.begin(), y_.end());
                double max_x = *std::max_element(x_.begin(), x_.end());
                double max_y = *std::max_element(y_.begin(), y_.end());

                for (int h = 0; h <= num_detected_hands; ++h)
                {
                    PyObject *pLandmark = PyList_GetItem(pLandmakrtPoint, h);

                    PyObject *pX = PyObject_GetAttrString(pLandmark, "x");
                    PyObject *pY = PyObject_GetAttrString(pLandmark, "y");

                    double x = PyFloat_AsDouble(pX);
                    double y = PyFloat_AsDouble(pY);

                    double x_diff = x - min_x;
                    double y_diff = y - min_y;

                    // Append x_diff and y_diff to data_aux list
                    PyObject *pXDiff = PyFloat_FromDouble(x_diff);
                    PyObject *pYDiff = PyFloat_FromDouble(y_diff);
                    PyList_Append(dataAux, pXDiff);
                    PyList_Append(dataAux, pYDiff);

                    // Release pX, pY, pXDiff, pYDiff
                    Py_DECREF(pX);
                    Py_DECREF(pY);
                    Py_DECREF(pXDiff);
                    Py_DECREF(pYDiff);

                    // Release pLandmark
                    Py_DECREF(pLandmark);
                }

                int data_aux_size = PyList_Size(dataAux);

                // data_aux += data_aux
                for (int i = 0; i < data_aux_size; ++i)
                {
                    PyObject *pData = PyList_GetItem(dataAux, i);

                    // Append pData to pDataAuxList again
                    PyList_Append(dataAux, pData);

                    // Release pData
                    Py_DECREF(pData);
                }

                int x1 = static_cast<int>(min_x * W) - 10;
                int y1 = static_cast<int>(min_y * H) - 10;
                int x2 = static_cast<int>(max_x * W) - 10;
                int y2 = static_cast<int>(max_y * H) - 10;

                // Convert data_aux to a numpy array
                PyObject *pNpArrayDataAux = PyObject_CallMethod(np, "array", "(O)", data_aux);

                // Create a list containing the numpy array
                PyObject *pInputList = PyList_New(1);
                PyList_SetItem(pInputList, 0, pNpArrayDataAux);

                // Call model.predict
                PyObject *pPrediction = PyObject_CallMethod(pModel, "predict", "(O)", pInputList);
                Py_DECREF(pInputList);

                // Get the predicted class label
                PyObject *pPredictedClassLabel = PyList_GetItem(pPrediction, 0);

                // Release objects
                Py_DECREF(pNpArrayDataAux);
                Py_DECREF(pPrediction);
            }
            // Write frame to video writer
            out.write(frame);

            // Show frame
            cv::imshow("frame", frame);

            // Exit on 'q' key press
            if (cv::waitKey(1) == 'q')
            {
                break;
            }
        }

        // Create instances of the tab classes
        //    TranslationTab translationTab(ui->historyTextEdit, ui->translateLineEdit);
        //    DictionaryTab dictionaryTab(ui->dictionaryTextBrowser, ui->dictionaryLineEdit);
    }

    void Camera::translateText()
    {
        QString inputText = ui->translateInput->toPlainText();
        // Translation logic

        // QString translatedText = performTranslation(inputText);
        // ui->translationDisplay->setPlainText(translatedText);

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
