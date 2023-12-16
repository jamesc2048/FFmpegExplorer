#include <QProcess>
#include "backend.hpp"

Backend::Backend(QObject *parent)
    : QObject{parent}
{}

// Needs to be async/callback
void Backend::runProcess(QString exe, QStringList args, QJSValue callback)
{
    // Runs process and returns output
    QProcess* proc = new QProcess(this);
    proc->setProcessChannelMode(QProcess::ProcessChannelMode::SeparateChannels);

    qDebug() << "Starting process" << exe << "with args" << args;
    proc->start(exe, args);

    connect(proc, &QProcess::errorOccurred, [](QProcess::ProcessError err) {
        qDebug() << "Error occurred:" << err;
    });

    connect(proc, &QProcess::started, []() {
        qDebug() << "Started";
    });

    connect(proc, &QProcess::finished, [=]() {
        qDebug() << "Finished: exit" << proc->exitCode();
        callback.call({ QString::fromLocal8Bit(proc->readAllStandardOutput()), QString::fromLocal8Bit(proc->readAllStandardError()) });
        proc->deleteLater();
    });
}
