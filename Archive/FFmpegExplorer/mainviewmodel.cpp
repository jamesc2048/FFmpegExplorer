#include "mainviewmodel.hpp"

MainViewModel::MainViewModel(QObject *parent) : ViewModelBase(parent)
{
    set_sampleText(QString("Hello world at %1")
                   .arg(QDateTime::currentDateTime().toString()));

    set_inputViewModel(new InputViewModel(this));
    set_outputViewModel(new OutputViewModel(this));
    set_filterViewModel(new FilterViewModel(this));
}
