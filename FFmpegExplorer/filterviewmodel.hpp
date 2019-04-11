#ifndef FILTERVIEWMODEL_HPP
#define FILTERVIEWMODEL_HPP

#include <QObject>

#include "viewmodelbase.hpp"

class FilterViewModel : public ViewModelBase
{
    Q_OBJECT
public:
    explicit FilterViewModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // FILTERVIEWMODEL_HPP
