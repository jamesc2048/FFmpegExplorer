#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>

#include "viewmodelbase.hpp"
#include "inputviewmodel.hpp"
#include "outputviewmodel.hpp"

class MainViewModel : public ViewModelBase
{
    Q_OBJECT

    QML_READONLY_PROPERTY(InputViewModel *, inputViewModel)
    QML_READONLY_PROPERTY(OutputViewModel *, outputViewModel)

public:
    MainViewModel(QObject *parent = nullptr);
    ~MainViewModel();
};

#endif // MAINVIEWMODEL_H
