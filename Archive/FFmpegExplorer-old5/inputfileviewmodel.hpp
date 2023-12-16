#ifndef INPUTFILEVIEWMODEL_HPP
#define INPUTFILEVIEWMODEL_HPP

#include <QObject>
#include <QTimer>
#include <QProcess>
#include <QtConcurrent>

#include "viewmodelbase.hpp"

class InputFileViewModel : public ViewModelBase
{
    Q_OBJECT

    QML_READONLY_PROPERTY(QString, filePath)
    QML_READONLY_PROPERTY(bool, hasAnalysed)
    QML_READONLY_PROPERTY(bool, isCorrupt)

    // In seconds
    QML_READONLY_PROPERTY(qreal, duration)
    QML_READONLY_PROPERTY(qreal, startTrim)
    QML_READONLY_PROPERTY(qreal, endTrim)

    QML_READONLY_PROPERTY(QVariantMap, formatInfo)
    QML_READONLY_PROPERTY(QVariantList, streamsInfo)

public:
    explicit InputFileViewModel(QObject *parent = nullptr);

    void analyse();
signals:

public slots:
};

#endif // INPUTFILEVIEWMODEL_HPP
