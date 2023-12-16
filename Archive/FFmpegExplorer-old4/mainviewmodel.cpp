#include "mainviewmodel.hpp"

MainViewModel::MainViewModel(QObject *parent) : ViewModelBase(parent)
{
    set_inputViewModel(new InputViewModel(this));
    set_outputViewModel(new OutputViewModel(this));

    outputViewModel_changed(get_outputViewModel());
}

MainViewModel::~MainViewModel()
{
    // children cleaned up by QObject parent
}
