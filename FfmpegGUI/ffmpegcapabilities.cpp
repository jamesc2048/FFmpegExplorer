#include "ffmpegcapabilities.h"

FfmpegCapabilities::FfmpegCapabilities(QObject *parent) : QObject(parent)
{
    analysisState = AnalysisState::NotAnalysed;
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

            encoderCapabilities.append({ codecCaps, codec, codecDescription });
        }
    }
}
