#include "application.h"

Application::Application(int argc, char **argv) : QGuiApplication(argc, argv)
{
//    qsu = QSimpleUpdater::getInstance();

//    connect (qsu, SIGNAL (checkingFinished  (QString)),
//               this,        SLOT (updateChangelog   (QString)));
//    connect (qsu, SIGNAL (appcastDownloaded (QString, QByteArray)),
//               this,        SLOT (displayAppcast    (QString, QByteArray)));
    findOrDownloadFfmpegBinary();

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
    catch (...)
    {
        qCritical() << "unknown exception thrown";
    }

    return false;
}


void Application::findOrDownloadFfmpegBinary()
{
//    // Is it in path? Use that.
//    QString ffmpegOut = Utilities::getCommandOutput(, {});

//    if (!ffmpegOut.isEmpty())
//    {
//        return;
//    }
}

void Application::examineFfmpeg()
{
    ffmpegCapabilities = std::make_unique<FfmpegCapabilities>();

    ffmpegCapabilities->analyseFfmpeg();
}
