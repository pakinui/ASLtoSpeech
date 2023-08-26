#include "../src/camera.h"

#include <QApplication>
#include <QtTest/QtTest>


class CameraTesting: public QObject
{
    Q_OBJECT
public:
    CameraTesting();
    ~CameraTesting();

private Q_SLOTS:
    void test_case_1();
};

CameraTesting::CameraTesting(){

}

CameraTesting::~CameraTesting(){

}

void CameraTesting::test_case_1(){
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

QTEST_APPLESS_MAIN(CameraTesting)
#include "camera_tests.moc"
