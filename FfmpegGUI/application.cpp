#include "application.h"



Application::Application(int argc, char **argv) : QGuiApplication(argc, argv)
{
//    qsu = QSimpleUpdater::getInstance();

//    connect (qsu, SIGNAL (checkingFinished  (QString)),
//               this,        SLOT (updateChangelog   (QString)));
//    connect (qsu, SIGNAL (appcastDownloaded (QString, QByteArray)),
//               this,        SLOT (displayAppcast    (QString, QByteArray)));
    examineFfmpeg();
}

bool Application::notify(QObject *receiver, QEvent *event)
{
    try
    {
        return QGuiApplication::notify(receiver, event);
    }
    catch (std::exception& e)
    {
        qCritical() << "std::exception thrown. type: " << typeid(e).name() << " details: " << e.what();
    }

    return false;
}

void Application::examineFfmpeg()
{
    QProcess ffmpegProcess;

    ffmpegProcess.start("ffmpeg", { "-h", "encoder=libx264" });
    ffmpegProcess.waitForFinished();
    qDebug() << ffmpegProcess.readAllStandardOutput().split('\n');
}
