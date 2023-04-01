#include "ui.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "../Core/Core.h"
#include "../Headers/app_environment.h"
#include "../Headers/import_qml_plugins.h"
#include "QIcon"

int start_UI(int argc, char *argv[]) {
    set_qt_environment();

    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:Main/main.qml"_qs);
    QGuiApplication::setWindowIcon(QIcon(":content/Images/icon.png"));
    QObject::connect(
            &engine, &QQmlApplicationEngine::objectCreated, &app,
            [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            },
            Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    Core core;
    engine.rootContext()->setContextProperty("Core", &core);

    engine.load(url);
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return QGuiApplication::exec();
}