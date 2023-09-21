/**
 * @file test.cpp
 * @brief Contains the unit tests for the application.
 *
 * This file contains thorough and extensive unit tests for the application.
 */
#include "../src/text_to_speech/ttsCall.h"
#include "../src/camera.h"
//#include "../src/camera.cpp"
#include <QTest>
#include <QString>
#include <Python.h>
#include <QSignalSpy>
#include <QDebug>

#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <filesystem>

/**
 * @class Test
 * @brief This is the class implemented for testing of our application.
 *
 * This class contains the unit tests for our application.
 * It contains tests for QObjects, Python, scripts, text-to-speech functionality,
 * the Camera, the History, and the Translator.
 */
class Test: public QObject
{
    Q_OBJECT
    QString currentPath = QDir::currentPath();
    Camera *camera;

    private Q_SLOTS:
        void testPython();
        void importScript();
        void testTTS();

        void testCameraConstructor();
        void testCameraStart();
        void testCameraStop();
        void testAddToHistory();
        void testTranslateTextAddedToHistory();
        void clearTranslateTextAfterTranslate();
//        void testImageAvailable();
        void testSubtitles();

};

void Test::testPython(){

    Py_Initialize();
    int result =PyRun_SimpleString("print('Hello, World!')");
    QVERIFY(result != -1);
    Py_Finalize();

}

void Test::importScript()
{
    QString newPath = currentPath + "/../../src"; // The current path (of this file)
    std::string pythonCode = "import sys; sys.path.append('"+ newPath.toStdString() +"')";

    Py_Initialize();
    PyRun_SimpleString(pythonCode.c_str());
    PyObject *pModule = PyImport_ImportModule("inference_classifier");
    if(!pModule){
        PyErr_Print();
    }
    QVERIFY(pModule);

    PyObject *class_object = PyObject_GetAttrString(pModule, "PythonTest");
    if(!class_object){
        PyErr_Print();
    }
    QVERIFY(pModule);

    PyObject *instance = PyObject_CallObject(class_object, NULL); // Create an instance of the Python class module
    if(!instance){
        PyErr_Print();
    }
    QVERIFY(instance);

    PyObject *pFunc = PyObject_GetAttrString(instance, "sign_identifier"); // The Python function to identify the ASL sign.
    if(!pFunc){
        PyErr_Print();
    }
    QVERIFY(pFunc);


    Py_Finalize();
}

void Test::testTTS(){
    TextToSpeech test;

    test.tts("testing");

    QVERIFY(test.getString() == "testing");
}



void Test::testCameraConstructor() {
    // Create a new Camera object.
    Py_Initialize();
    camera = new Camera();
    camera->show();
    // Check that the camera object's properties are initialized correctly.
    QVERIFY(camera->m_camera.isAvailable());


}

void Test::testCameraStart(){
   // QVERIFY(true);

    qDebug() << camera->m_camera.isAvailable();
    while (!camera->m_camera.isAvailable()){
        qDebug() << "waiting";
    }
    camera->startCamera();


    // Check that the camera is available.
    QVERIFY(camera->getCameraActive());


}

void Test::testCameraStop(){
//    QVERIFY(true);

    qDebug() << camera->m_camera.isAvailable();
    while (!camera->m_camera.isAvailable()){
        qDebug() << "waiting111";
    }
    camera->stopCamera();


    // Check that the camera is available.
    // If you remove the ! it is false which is what we want
    // So !bool is want we want for a pass
    QVERIFY(!camera->getCameraActive());
}

void Test::testTranslateTextAddedToHistory(){

    QString str = "Hello1";
    camera->setTranslateText(str);
    camera->translateText();


    QVERIFY(camera->getLastHistory() == str);

//    QVERIFY(true);
}

void Test::clearTranslateTextAfterTranslate(){
    QString str = "Hello2";
    camera->setTranslateText(str);
    camera->translateText();


    QVERIFY(camera->getTranslateText() == "");
}


//void Test::testImageAvailable(){
//    QVERIFY(true);
//}

void Test::testSubtitles(){
    QString str = "subtitle";
    camera->setSubtitle(str);
    QVERIFY(camera->getSubtitle() == str);
}

void Test::testAddToHistory(){

    QString str = "hello";
    camera->addToHistory(str);
    QVERIFY(camera->getLastHistory() == "hello");
    Py_Finalize();
}

/// These two lines must be at the very bottom.
QTEST_MAIN(Test)
#include "test.moc"
