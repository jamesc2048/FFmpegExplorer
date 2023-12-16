#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>
#include "qmlutils.hpp"
#include "viewmodelbase.hpp"
#include "encodeviewmodel.hpp"

class MainViewModel : public ViewModelBase
{
    Q_OBJECT

    QML_WRITABLE_PROPERTY(QString, inputFileName)

    QML_WRITABLE_PROPERTY(EncodeViewModel *, encodeViewModel);

public:
    explicit MainViewModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MAINVIEWMODEL_H
