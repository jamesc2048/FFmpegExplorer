#ifndef OUTPUTVIEWMODEL_HPP
#define OUTPUTVIEWMODEL_HPP

#include <QObject>

#include "viewmodelbase.hpp"

class OutputViewModel : public ViewModelBase
{
    Q_OBJECT
public:
    explicit OutputViewModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // OUTPUTVIEWMODEL_HPP
