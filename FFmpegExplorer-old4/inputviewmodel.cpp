#include "inputviewmodel.hpp"

InputViewModel::InputViewModel(QObject *parent) : ViewModelBase (parent)
{
    set_inputFiles(new QQmlObjectListModel<InputFileViewModel>());

    get_inputFiles()->append(new InputFileViewModel(this));
    get_inputFiles()->append(new InputFileViewModel(this));
    get_inputFiles()->append(new InputFileViewModel(this));
}

void InputViewModel::addNewInputFile(QString path)
{
    auto ivf = new InputFileViewModel(this);
    ivf->set_filePath(path);

    get_inputFiles()->append(ivf);

    ivf->analyseFile();
}


