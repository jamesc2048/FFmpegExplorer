#include "pch.h"

#include "encoder.h"
#include "application.h"

void messageHandler(QtMsgType type, const QMessageLogContext &, const QString & msg)
{
    QString txt;

    switch (type)
    {
        case QtDebugMsg:
            txt = QString("Debug: %1").arg(msg);
            break;

        case QtWarningMsg:
            txt = QString("Warning: %1").arg(msg);
        break;

        case QtCriticalMsg:
            txt = QString("Critical: %1").arg(msg);
        break;

        case QtFatalMsg:
            txt = QString("Fatal: %1").arg(msg);
        break;

        case QtInfoMsg:
            txt = QString("Info: %1").arg(msg);
        break;
    }

    fprintf(stderr, "%s\n", txt.toLatin1().data());
//    static QFile outFile("FfmpegGUI-log.txt");

//    if (!outFile.isOpen())
//    {
//        outFile.open(QIODevice::WriteOnly);
//    }

//    static QTextStream ts(&outFile);
//    ts << txt << endl;
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageHandler);

    // Create QML module "Encoder 1.0"
    qmlRegisterType<Encoder>("Encoder", 1, 0, "Encoder");

    // Register type for model. Necessary to make Q_PROPERTY work inside Encoder class.
    qRegisterMetaType<QQmlObjectListModel<EncodeItemViewModel> *>("QQmlObjectListModel<EncodeItemViewModel> *");
    // Weird issue where QProcess types ar enot registered.
    qRegisterMetaType<QProcess::ExitStatus>("QProcess::ExitStatus");
    qRegisterMetaType<QProcess::ProcessState>("QProcess::ProcessState");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    Application app(argc, argv);

    app.setApplicationName("FFmpeg GUI");
    app.setApplicationVersion("0.1.0.0");

    QQmlApplicationEngine engine;


    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    //engine.rootContext()->setContextProperty("testModel", model);

    return app.exec();
}
