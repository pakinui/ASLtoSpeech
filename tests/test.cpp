/**
 * @file test.cpp
 * @brief Contains the unit tests for the application.
 * 
 * This file contains thorough and extensive unit tests for the application.
 */
#include "../src/text_to_speech/ttsCall.h"
#include <QTest>
#include <QString>
#include <Python.h>


#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <filesystem>

/**
 * @class Test
 * @brief The Test class for our application.
 * 
 * This class contains the unit tests for our application.
 * It contains tests for the text-to-speech functionality,
 * the Python functionality, and the GUI functionality.
*/
class Test: public QObject
{
    Q_OBJECT
    QString currentPath = QDir::currentPath();
    private Q_SLOTS:
    void testPython();
    void importScript();
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

//TEST_CASE( "speech.wav file created", "[file_check]" ) {
//     TextToSpeech test;
//     test.TextToSpeech::tts("testing");
//    //tts("testing");

//    std::string filePath = "speech.wav";


//    DWORD fileAttributes = GetFileAttributesA(filePath.c_str());

//    if (fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
//        REQUIRE(true);
//    } else {
//        REQUIRE(false);
//    }
//}

//TEST_CASE("matching strings", "[strings]") {
//    TextToSpeech test;
//    test.tts("testing");

//    SECTION("string matching"){
//        if (test.getString() == "testing"){
//            REQUIRE(true);
//        }else{
//            REQUIRE(false);
//        }
//    }
//    REQUIRE(true);
//}


/// These two lines must be at the very bottom.
QTEST_MAIN(Test)
#include "test.moc"
