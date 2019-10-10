#include "mainviewmodel.hpp"

MainViewModel::MainViewModel(QObject *parent) : ViewModelBase(parent)
{
    set_inputViewModel(new InputViewModel(this));
}
