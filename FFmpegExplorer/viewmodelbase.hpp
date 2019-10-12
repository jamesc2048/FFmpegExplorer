#ifndef VIEWMODELBASE_H
#define VIEWMODELBASE_H

#include "pch.hpp"

class ViewModelBase : public QObject
{
    Q_OBJECT

public:
    explicit ViewModelBase(QObject *parent = nullptr);

signals:
    // Signal called by macros QML_WRITEABLE_PROPERTY etc
    void propertyChanged(QString propertyName);

public slots:
};

#endif // VIEWMODELBASE_H
