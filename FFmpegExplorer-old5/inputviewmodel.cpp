#include "inputviewmodel.hpp"

InputViewModel::InputViewModel(QObject *parent) : ViewModelBase(parent)
{
    set_inputFiles(new QQmlObjectListModel<InputFileViewModel>(this));

//    get_inputFiles()->append(new InputFileViewModel(this));
//    get_inputFiles()->append(new InputFileViewModel(this));
//    get_inputFiles()->append(new InputFileViewModel(this));

    set_selectedInputFile(nullptr);
}

void InputViewModel::addInputUrls(QList<QUrl> urls)
{
    qDebug() << urls;

    foreach (QUrl url, urls) {
        QString path = url.toLocalFile();

        InputFileViewModel* ifvm = new InputFileViewModel(this);
        ifvm->set_filePath(path);

        get_inputFiles()->append(ifvm);

        ifvm->analyse();
    }
}
