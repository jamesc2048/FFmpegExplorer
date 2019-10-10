#ifndef MAINVIEWMODEL_HPP
#define MAINVIEWMODEL_HPP

#include <QObject>

#include "viewmodelbase.hpp"

#include "inputviewmodel.hpp"
#include "outputviewmodel.hpp"
#include "filterviewmodel.hpp"

class MainViewModel : public ViewModelBase
{
    Q_OBJECT

    QML_READONLY_PROPERTY(InputViewModel *, inputViewModel)
    QML_READONLY_PROPERTY(OutputViewModel *, outputViewModel)
    QML_READONLY_PROPERTY(FilterViewModel *, filterViewModel)

public:
    explicit MainViewModel(QObject *parent = nullptr);


};

#endif // MAINVIEWMODEL_HPP
