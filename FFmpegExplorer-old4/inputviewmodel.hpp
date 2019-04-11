#ifndef INPUTVIEWMODEL_HPP
#define INPUTVIEWMODEL_HPP

#include "viewmodelbase.hpp"
#include "inputfileviewmodel.hpp"

class InputViewModel : public ViewModelBase
{
    Q_OBJECT

    QML_READONLY_PROPERTY(QQmlObjectListModel<InputFileViewModel> *, inputFiles)

public:
    InputViewModel(QObject *parent = nullptr);

    Q_INVOKABLE void addNewInputFile(QString path);
};

#endif // INPUTVIEWMODEL_HPP
