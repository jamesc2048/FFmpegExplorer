#include "application.h"

Application::Application(int& argc, char **argv) : QGuiApplication(argc, argv)
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
        //qDebug() << "notify" << receiver << event;
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

//void Application::checkForUpdates()
//{
//    QtConcurrent::run([]()
//    {
//        qDebug() << __FUNCTION__;
//        QNetworkAccessManager nam;
//        QNetworkRequest req(QUrl("https://crisafulli.me/ffmpegexplorer/versioncheck"));

//        req.setHeader(QNetworkRequest::KnownHeaders::UserAgentHeader, QString("FFmpeg GUI version %1").arg(APP_VERSION));

//        QNetworkReply *reply = nam.get(req);
//        QByteArray bytes = reply->readAll();

//        qDebug("Received reply from server: %s", bytes.data());

//        QList<QByteArray> versionNums = bytes.split('.');

//        if (versionNums.length() == 4)
//        {
//            qDebug("Split version in 3 parts: %s", versionNums.join(", ").data());
//            QVersionNumber num(versionNums[0].toInt(), versionNums[1].toInt(), versionNums[2].toInt());

//            auto splitCurrentVersion = QString(APP_VERSION).split('.');


//            // alert user new version is available
//            // TODO
//        }
//        else
//        {

//        }

//        reply->deleteLater();
//    });
//}

