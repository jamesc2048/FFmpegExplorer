#ifndef UTILITIES_H
#define UTILITIES_H

#include <QProcess>

namespace Utilities
{
    QString getCommandOutput(const QString&, const QStringList&);
}

#endif // UTILITIES_H
