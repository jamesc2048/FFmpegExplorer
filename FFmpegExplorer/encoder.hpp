#ifndef ENCODER_H
#define ENCODER_H

#include "pch.hpp"
#include "qmlutils.hpp"

// Easier models by using QML tricks library.
// https://github.com/Cavewhere/lib-qt-qml-tricks

class EncodeItemViewModel : public QObject
{
    Q_OBJECT
    QML_WRITABLE_PROPERTY(QString, path)
    QML_WRITABLE_PROPERTY(double, progress)
    QML_WRITABLE_PROPERTY(double, duration)
    QML_WRITABLE_PROPERTY(QString, name)
    QML_WRITABLE_PROPERTY(bool, isEncoding)
    QML_WRITABLE_PROPERTY(bool, isComplete)
    QML_WRITABLE_PROPERTY(bool, isPaused)
    QML_WRITABLE_PROPERTY(bool, hasError)

    QProcess *m_encodeProcess;
    QStringList m_processOutput;

    QRegExp durationRegex;
    QRegExp progressRegex;

signals:
    void finishedEncode();

public:
    EncodeItemViewModel(QString path, QObject *parent = nullptr);

    void startEncode();
    void processFfmpegOutput(QString ffmpegOutput);
    void pauseResumeEncoding();
};

class Encoder : public QObject
{
    Q_OBJECT

    QML_WRITABLE_PROPERTY(bool, isRunningEncode)
    QML_WRITABLE_PROPERTY(double, encodeProgress)
    QML_WRITABLE_PROPERTY(int, currentEncodeFile)
    QML_WRITABLE_PROPERTY(int, totalEncodeFiles)

    Q_PROPERTY(QQmlObjectListModel<EncodeItemViewModel>* encodeModel MEMBER m_encodeModel)
    QQmlObjectListModel<EncodeItemViewModel> * m_encodeModel;

public:
    explicit Encoder(QObject *parent = nullptr);

    int currentEncodeIndex;

signals:

public slots:
    void continueEncode();
    void encode();
    void addToEncode(QUrl url);
    void addToEncodeFromDirectory(QUrl url);
    void removeFromEncode(int index);
    void pauseResumeEncoding();
};

#endif // ENCODER_H
