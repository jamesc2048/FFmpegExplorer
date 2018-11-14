#ifndef ENCODEITEMVIEWMODEL_H
#define ENCODEITEMVIEWMODEL_H

#include <QObject>
#include "viewmodelbase.hpp"
#include "qmlutils.hpp"

class EncodeItemViewModel : public ViewModelBase
{
    Q_OBJECT

    // TODO support for multiple inputs/outputs per EncodeItem?
    QML_WRITABLE_PROPERTY(QString, inputFileName)
    QML_WRITABLE_PROPERTY(QString, outputFileName)
    QML_WRITABLE_PROPERTY(QString, ffmpegInputParameters)
    QML_WRITABLE_PROPERTY(QString, ffmpegOutputParameters)
    // 0.0 to 1.0
    QML_WRITABLE_PROPERTY(double, progress)
    // TODO add detected fields here, like duration, framerate etc?

    // TODO this should probably also start/stop the actual encode.
    // This way we can have multiple FFmpeg encodes running in parallel. They get started by EncodeViewModel.

public:
    EncodeItemViewModel(QObject *parent = nullptr);
};

#endif // ENCODEITEMVIEWMODEL_H
