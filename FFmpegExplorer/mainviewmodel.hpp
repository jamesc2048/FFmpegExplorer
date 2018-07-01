#ifndef MAINVIEWMODEL_HPP
#define MAINVIEWMODEL_HPP

#include <QObject>
#include "qmlutils.hpp"
#include <QDebug>
#include <QProcess>
#include <memory>
#include <QThread>

class EncodeThread : public QThread
{
    Q_OBJECT

    QML_WRITABLE_PROPERTY(QString, inputUrl);
    QML_WRITABLE_PROPERTY(QString, outputUrl);
    QML_WRITABLE_PROPERTY(QString, progress);

    void run() override
    {
        QString ffmpegPath = "ffmpeg";
        QStringList args = QStringList() << "-i"
                                         << get_inputUrl()
                                         << get_outputUrl();

        QProcess process;

        process.start(ffmpegPath, args);
        //process.setReadChannel(QProcess::StandardOutput);

        if (process.waitForStarted())
        {
            while (process.state() == QProcess::Running)
            {
                process.waitForReadyRead();

                qDebug() << "StdError" << process.readAllStandardError();
                qDebug() << "StdOutput" << process.readAllStandardError();
            }

            qDebug() << "Exited process with " << process.exitStatus();
        }
    }

public:
    EncodeThread(QObject *parent = nullptr) : QThread(parent)
    {

    }

    signals:
        void resultReady(const QString &s);
};

class MainViewModel : public QObject
{
    Q_OBJECT

    QML_WRITABLE_PROPERTY(QString, inputUrl)
    QML_WRITABLE_PROPERTY(QString, outputUrl)

    QML_READONLY_PROPERTY(double, encodeProgress)

    std::unique_ptr<QProcess> ffmpegProcess;
public:
    explicit MainViewModel(QObject *parent = nullptr)
    {

    }

    Q_INVOKABLE void debugLog()
    {
        qDebug() << "ViewModel props:" << get_inputUrl() << get_outputUrl() << get_encodeProgress();
    }

    Q_INVOKABLE bool startEncode()
    {
        qDebug() << "Start Encode!!";
        qDebug() << "Input:" << get_inputUrl();
        qDebug() << "Output:" << get_outputUrl();

        // TODO set in options?
        QString ffmpegPath = "ffmpeg";

        QStringList args = QStringList() << "-i" << get_inputUrl() <<
                                            get_outputUrl();

        EncodeThread *encodeThread = new EncodeThread(this);
        encodeThread->set_inputUrl(get_inputUrl());
        encodeThread->set_outputUrl(get_outputUrl());
        encodeThread->start();

        return true;
    }

signals:

public slots:
};

#endif // MAINVIEWMODEL_HPP
