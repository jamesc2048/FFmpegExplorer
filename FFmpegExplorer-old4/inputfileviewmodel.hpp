#ifndef INPUTFILE_HPP
#define INPUTFILE_HPP

#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>

#include "viewmodelbase.hpp"

class InputFileViewModel : public ViewModelBase
{
    Q_OBJECT

    QML_READONLY_PROPERTY(bool, isValid)
    QML_READONLY_PROPERTY(QString, filePath)
    QML_READONLY_PROPERTY(qreal, duration)
    QML_READONLY_PROPERTY(qreal, startTrim)
    QML_READONLY_PROPERTY(qreal, endTrim)

public:
    explicit InputFileViewModel(QObject *parent = nullptr);

    void analyseFile();

signals:

public slots:
};

#endif // INPUTFILE_HPP
