#ifndef INPUTFILEVIEWMODEL_HPP
#define INPUTFILEVIEWMODEL_HPP

#include <QObject>

#include "viewmodelbase.hpp"

class InputFileViewModel : public ViewModelBase
{
    Q_OBJECT
public:
    explicit InputFileViewModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // INPUTFILEVIEWMODEL_HPP
