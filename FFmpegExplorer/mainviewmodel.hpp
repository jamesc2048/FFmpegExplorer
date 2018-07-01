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

    QML_WRITABLE_PROPERTY(QString, args);
    QML_WRITABLE_PROPERTY(QString, progress);

    void run() override
    {
        QString ffmpegPath = "ffmpeg";

        QProcess process;

        QString finalCommand = (QStringList() << ffmpegPath << get_args()).join(" ");

        qDebug() << "Final command" << finalCommand;

        process.start(finalCommand);
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
        else
        {
            qDebug() << "Process did not start:" << process.error();
        }
    }

public:
    EncodeThread(QObject *parent = nullptr) : QThread(parent)
    {

    }

    signals:
        void propertyChanged(QString propertyName);
        void resultReady(const QString &s);
};

class InputViewModel : public QObject
{
    Q_OBJECT

    QML_WRITABLE_PROPERTY(QString, inputUrl)
    QML_WRITABLE_PROPERTY(QString, startTime)
    QML_WRITABLE_PROPERTY(QString, duration)

public:
    InputViewModel(QObject *parent = nullptr) : QObject(parent)
    {
    }

    QStringList getFFmpegInputOpts()
    {
        QStringList opts;

        if (!get_startTime().isEmpty())
        {
            opts << "-ss" << get_startTime();
        }

        if (!get_duration().isEmpty())
        {
            opts << "-t" << get_duration();
        }

        opts << "-i" << QString("\"%1\"").arg(get_inputUrl());

        return opts;
    }

signals:
    void propertyChanged(QString propertyName);
};

class OutputViewModel : public QObject
{
    Q_OBJECT

    QML_WRITABLE_PROPERTY(QString, outputUrl)

public:
    OutputViewModel(QObject *parent = nullptr) : QObject(parent)
    {
    }

    QStringList getFFmpegOutputOpts()
    {
        QStringList opts;

        opts << QString("\"%1\"").arg(get_outputUrl());

        return opts;
    }
signals:
    void propertyChanged(QString propertyName);
};

class MainViewModel : public QObject
{
    Q_OBJECT

    QML_WRITABLE_PROPERTY(InputViewModel *, input)
    QML_WRITABLE_PROPERTY(OutputViewModel *, output)

    QML_READONLY_PROPERTY(double, encodeProgress)

    std::unique_ptr<QProcess> ffmpegProcess;

public:
    explicit MainViewModel(QObject *parent = nullptr) : QObject(parent)
    {
        set_input(new InputViewModel(this));

        connect(get_input(), &InputViewModel::propertyChanged, [this](QString pn) {
           qDebug() << "property changed!" << pn << get_input()->property(pn.toLatin1());
        });

        set_output(new OutputViewModel(this));

        connect(get_output(), &OutputViewModel::propertyChanged, [this](QString pn) {
           qDebug() << "property changed!" << pn << get_output()->property(pn.toLatin1());
        });
    }

    Q_INVOKABLE void debugLog()
    {
        qDebug() << "ViewModel props:" << get_input()->get_inputUrl() << get_output()->get_outputUrl() << get_encodeProgress();
    }

    Q_INVOKABLE bool startEncode()
    {
        qDebug() << "Start Encode!!";

        QStringList inputArgs = get_input()->getFFmpegInputOpts();
        QStringList outputArgs = get_output()->getFFmpegOutputOpts();

        qDebug() << "Input args:" << inputArgs;
        qDebug() << "Output args:" << outputArgs;

        // TODO set in options?
        QString ffmpegPath = "ffmpeg";

        QStringList args = inputArgs << outputArgs;
        qDebug() << "Final args:" << args;

        EncodeThread *encodeThread = new EncodeThread(this);
        encodeThread->set_args(args.join(" "));
        encodeThread->start();

        return true;
    }

signals:
    void propertyChanged(QString propertyName);

public slots:
};

#endif // MAINVIEWMODEL_HPP
