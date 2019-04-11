#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "mainviewmodel.hpp"
#include "inputfileviewmodel.hpp"


int main(int argc, char *argv[])
{
    qRegisterMetaType<QQmlObjectListModel<InputFileViewModel> *>("QQmlObjectListModel<InputFileViewModel> *");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl)
    {
        if (!obj && url == objUrl)
        {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);

    MainViewModel viewModel;
    engine.rootContext()->setContextProperty("viewModel", &viewModel);

    engine.load(url);

    return app.exec();
}
