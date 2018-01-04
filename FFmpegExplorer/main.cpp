#include "pch.h"

#include "encoder.h"
#include "application.h"
#include "utilities.h"

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

    std::cout << txt.toLatin1().data() << std::endl;
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

    app.setApplicationName("FFmpeg Explorer");
    app.setApplicationVersion(APP_VERSION);

    QQmlApplicationEngine engine;

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    std::unique_ptr<QMLUtilities> utilitiesInstance = std::make_unique<QMLUtilities>();
    engine.rootContext()->setContextProperty("Utilities", utilitiesInstance.get());

    return app.exec();
}
