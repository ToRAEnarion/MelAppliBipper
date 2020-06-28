#include "mainwindow.h"
#include <QApplication>
#include <QQmlEngine>

#include "bippermanager.h"
#include "bipperitem.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<BipperManager>("MelAppliBipper.CppTypes", 0, 1, "BipperManager" );
    qmlRegisterType<BipperItem>("MelAppliBipper.CppTypes", 0, 1, "BipperItem" );

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
