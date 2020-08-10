#include "mainwindow.h"
#include <QApplication>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "bippermanager.h"
#include "bipperitem.h"
#include "chronometer.h"
//int main(int argc, char *argv[])
//{
//    qmlRegisterType<BipperManager>("MelAppliBipper.CppTypes", 0, 1, "BipperManager" );
//    qmlRegisterType<BipperItem>("MelAppliBipper.CppTypes", 0, 1, "BipperItem" );

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}


int main(int argc, char *argv[])
{
    // BipperManager and BipperItem will be usable with: import MelAppliBipper.CppTypes 0.1
    qmlRegisterType<BipperManager>("MelAppliBipper.CppTypes", 0, 1, "BipperManager" );
    qmlRegisterType<BipperItem>("MelAppliBipper.CppTypes", 0, 1, "BipperItem" );
    qmlRegisterType<Chronometer>("Chronometer",1,0,"Chronometer");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
