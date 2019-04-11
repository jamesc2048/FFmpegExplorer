#include "inputviewmodel.hpp"

InputViewModel::InputViewModel(QObject *parent) : ViewModelBase(parent)
{
    set_inputFiles(new QQmlObjectListModel<InputFileViewModel>(this));

}
