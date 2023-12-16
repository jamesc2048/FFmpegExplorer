#ifndef VIEWMODELBASE_H
#define VIEWMODELBASE_H

#include <QObject>

#include "qmlutils.hpp"

class ViewModelBase : public QObject
{
    Q_OBJECT

public:
    explicit ViewModelBase(QObject *parent = nullptr);

signals:
    void propertyChanged(QString propertyName);
public slots:
};

#endif // VIEWMODELBASE_H
