#include "mainviewmodel.hpp"

MainViewModel::MainViewModel(QObject *parent) : ViewModelBase(parent)
{
    set_encodeViewModel(new EncodeViewModel(this));
}
