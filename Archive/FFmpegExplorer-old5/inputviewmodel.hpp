#ifndef INPUTVIEWMODEL_HPP
#define INPUTVIEWMODEL_HPP

#include <QObject>

#include "viewmodelbase.hpp"

#include "inputfileviewmodel.hpp"

class InputViewModel : public ViewModelBase
{
    Q_OBJECT

    QML_READONLY_PROPERTY(QQmlObjectListModel<InputFileViewModel> *, inputFiles)
    QML_WRITABLE_PROPERTY(InputFileViewModel *, selectedInputFile)

public:
    explicit InputViewModel(QObject *parent = nullptr);

    Q_INVOKABLE void addInputUrls(QList<QUrl> urls);

};

#endif // INPUTVIEWMODEL_HPP
