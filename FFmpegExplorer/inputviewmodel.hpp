#ifndef INPUTVIEWMODEL_HPP
#define INPUTVIEWMODEL_HPP

#include "pch.hpp"

#include "inputfilefileviewmodel.hpp>

class InputViewModel : public ViewModelBase
{
    Q_OBJECT

    QML_READONLY_PROPERTY(QQmlObjectListModel<InputFileViewModel> *, inputFiles)

public:
    InputViewModel(QObject *parent = nullptr);
};

#endif // INPUTVIEWMODEL_HPP
