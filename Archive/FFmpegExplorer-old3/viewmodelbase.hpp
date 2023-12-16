#ifndef VIEWMODELBASE_HPP
#define VIEWMODELBASE_HPP

#include <QObject>

class ViewModelBase : public QObject
{
    Q_OBJECT

protected:
    ViewModelBase(QObject *parent = nullptr);

signals:
    void propertyChanged(QString propName);
};


#endif // VIEWMODELBASE_HPP
