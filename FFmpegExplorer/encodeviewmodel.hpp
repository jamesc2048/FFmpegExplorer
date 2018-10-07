#ifndef ENCODEVIEWMODEL_HPP
#define ENCODEVIEWMODEL_HPP

#include <QObject>
#include "viewmodelbase.hpp"
#include "qmlutils.hpp"
#include "encodeitemviewmodel.hpp"

class EncodeViewModel : public ViewModelBase
{
    Q_OBJECT

    QML_WRITABLE_PROPERTY(QQmlObjectListModel<EncodeItemViewModel> *, encodeItems)

    // List of queued encodeItems
    // Ways to start, stop, enqueue and dequeue items
    // actually calling FFmpeg on the files. Or maybe set that up in EncodeItemViewModel

public:
    EncodeViewModel(QObject *parent = nullptr);

    Q_INVOKABLE void startEncode();
};

#endif // ENCODEVIEWMODEL_HPP
