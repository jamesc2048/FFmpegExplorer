#ifndef INPUTFILEVIEWMODEL_HPP
#define INPUTFILEVIEWMODEL_HPP

#include <QObject>

#include "viewmodelbase.hpp"

class InputFileViewModel : public ViewModelBase
{
    Q_OBJECT

    QML_READONLY_PROPERTY(QString, filePath)
    QML_READONLY_PROPERTY(bool, isValid)

    // In seconds
    QML_READONLY_PROPERTY(qreal, duration)
    QML_READONLY_PROPERTY(qreal, startTrim)
    QML_READONLY_PROPERTY(qreal, endTrim)

public:
    explicit InputFileViewModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // INPUTFILEVIEWMODEL_HPP
