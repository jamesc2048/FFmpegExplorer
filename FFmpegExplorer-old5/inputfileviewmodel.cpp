#include "inputfileviewmodel.hpp"

InputFileViewModel::InputFileViewModel(QObject *parent) : ViewModelBase(parent)
{
    m_hasAnalysed = false;
    m_isCorrupt = false;
    m_duration = m_startTrim = m_endTrim = 0.0;
}

void InputFileViewModel::analyse()
{
    QtConcurrent::run([this]() {
        //QThread::msleep(2000);

        QProcess proc;

        proc.start("ffprobe",
                   QStringList() << get_filePath()
                   << "-v"
                   << "quiet"
                   << "-print_format"
                   << "json"
                   << "-show_format"
                   << "-show_streams");

        proc.waitForFinished(60 * 1000);

        QString output = proc.readAllStandardOutput();
        QString error = proc.readAllStandardError();

        qDebug() << output;
        qDebug() << error;

        if (proc.exitStatus() == QProcess::ExitStatus::NormalExit && proc.exitCode() == 0)
        {
            QJsonDocument doc = QJsonDocument::fromJson(output.toUtf8());
            QJsonObject obj;

            if(!doc.isNull())
            {
                if(doc.isObject())
                {
                    obj = doc.object();
                }
                else
                {
                    qDebug() << "Document is not an object";
                }
            }
            else
            {
                qDebug() << "Invalid JSON...";
            }

            qDebug() << obj["format"];

            QJsonObject formatObj = obj["format"].toObject();
            QJsonArray streamArr = obj["streams"].toArray();

            QVariantMap qm = formatObj.toVariantMap();

            QVariantList ql;

            foreach (QJsonValue stream, streamArr)
            {
                ql.append(stream.toObject().toVariantMap());
            }

            qDebug() << ql << qm;

            set_streamsInfo(ql);
            set_formatInfo(qm);

            set_hasAnalysed(true);
            set_isCorrupt(!get_hasAnalysed());

        }
        else
        {
            set_hasAnalysed(false);
            set_isCorrupt(!get_hasAnalysed());
        }
    });
}
