#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QProcess>

#include "mainviewmodel.hpp"

inline QQmlContext *mainContext;

int main(int argc, char *argv[])
{
    // Register type for model. Necessary to make Q_PROPERTY work inside Encoder class.
    qRegisterMetaType<QQmlObjectListModel<EncodeItemViewModel> *>("QQmlObjectListModel<EncodeItemViewModel> *");
    // Weird issue where QProcess types are not registered with metatype system.
    qRegisterMetaType<QProcess::ExitStatus>("QProcess::ExitStatus");
    qRegisterMetaType<QProcess::ProcessState>("QProcess::ProcessState");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    mainContext = engine.rootContext();

    MainViewModel viewModel;
    mainContext->setContextProperty("viewModel", &viewModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    auto e = engine.rootObjects().first();
    auto b = engine.rootObjects().size();
    auto a = engine.rootObjects().first()->objectName();

    QObject* model = e->findChild<QObject *>("encodeListModelObj");
    QVariant ret;
    bool bn = QMetaObject::invokeMethod(model, "appendChild", Q_RETURN_ARG(QVariant, ret), Q_ARG(QVariant, "CRAZY"));
    auto aa = model->findChild<QObject *>("aaa");
    qDebug() << a << b << e << model << aa << bn << ret;

    return app.exec();
}
