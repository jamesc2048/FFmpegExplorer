#include "inputviewmodel.hpp"

InputViewModel::InputViewModel(QObject *parent) : ViewModelBase(parent)
{
    set_inputFiles(new QQmlObjectListModel<InputFileViewModel>(this));

    get_inputFiles()->append(new InputFileViewModel(this));
    get_inputFiles()->append(new InputFileViewModel(this));
    get_inputFiles()->append(new InputFileViewModel(this));
}
