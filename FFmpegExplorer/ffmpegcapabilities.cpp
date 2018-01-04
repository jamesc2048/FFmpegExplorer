#include "ffmpegcapabilities.h"

FfmpegCapabilities::FfmpegCapabilities(QObject *parent) : QObject(parent)
{
    analysisState = AnalysisState::NotAnalysed;

    checkForFfmpegInstallation();
}

void FfmpegCapabilities::analyseFfmpeg()
{
    QRegExp encoderRegex(R"(\s([\w\.]{6})\s(\w+)\s+(.+))"); // for -encoders
    QRegExp codecDetailsRegex(R"("\s{2}-([\w-]+)\s+<(\w+)>\s+([\w\.]{8})\s.+)"); // for -h encoder=libx264 for example

    QString ffmpegOutput = Utilities::getCommandOutput("ffmpeg", { "-encoders" });
    qDebug() << ffmpegOutput;

    for (const auto &outLine : ffmpegOutput.split('\n'))
    {
        int index = encoderRegex.indexIn(outLine);

        if (index != -1)
        {
            QString codecCaps = encoderRegex.cap(1).trimmed();
            QString codec = encoderRegex.cap(2).trimmed();
            QString codecDescription = encoderRegex.cap(3).trimmed();

            qDebug() << codec << codecCaps << codecDescription;

            //encoderCapabilities.append({ codecCaps, codec, codecDescription });
        }
    }
}

void FfmpegCapabilities::checkForFfmpegInstallation()
{
    // TODO windows only!
    ffmpegFilePath = QStandardPaths::findExecutable("ffmpeg");

    if (ffmpegFilePath.isEmpty())
    {
        ffmpegFilePath = QStandardPaths::findExecutable("ffmpeg", { QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) });
    }

    if (ffmpegFilePath.isEmpty())
    {
        QString path =
                QDir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).filePath("ffmpeg.exe");

        downloadFfmpeg(path);
    }

    QProcess ffmpegProcess;

    ffmpegProcess.start(ffmpegFilePath);
    ffmpegProcess.waitForFinished();

    if (ffmpegProcess.error() != QProcess::UnknownError)
    {
        // ffmpeg not present! download
        // TODO UI for this.

    }
}

bool FfmpegCapabilities::downloadFfmpeg(QString pathToSave)
{
    QNetworkAccessManager nam;

    QNetworkRequest req(QUrl("https://crisafulli.me/public/ffmpeg-3.4-win64-static/bin/ffmpeg.exe"));
    QNetworkReply *reply = nam.get(req);

    QEventLoop loop;
    connect(&nam, &QNetworkAccessManager::finished, &loop,
                [&](QNetworkReply *r) { loop.quit(); });

    loop.exec();

    QByteArray data = reply->readAll();
    QFile f(pathToSave);
    f.open(QIODevice::WriteOnly);

    f.write(data);
    f.close();

    reply->deleteLater();

    return true;
}
