#include "utilities.h"


QString Utilities::getCommandOutput(const QString &exePath, const QStringList &args)
{
    QProcess p;

    p.start(exePath, args);
    p.waitForFinished();

    if (p.exitStatus() == QProcess::ExitStatus::NormalExit)
    {
        return p.readAllStandardOutput();
    }

    return {};
}
