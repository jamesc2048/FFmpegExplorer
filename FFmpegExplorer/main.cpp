#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QProcess>

#include "mainViewModel.hpp"

int main(int argc, char *argv[])
{
    qRegisterMetaType<QQmlObjectListModel<InputFileViewModel> *>("QQmlObjectListModel<InputFileViewModel> *");
    qRegisterMetaType<QProcess::ExitStatus>("QProcess::ExitStatus");
    qRegisterMetaType<QProcess::ProcessState>("QProcess::ProcessState");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    MainViewModel viewModel;
    engine.rootContext()->setContextProperty("viewModel", &viewModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
