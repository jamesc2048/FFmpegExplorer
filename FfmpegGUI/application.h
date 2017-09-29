#ifndef APPLICATION_H
#define APPLICATION_H

#include "pch.h"
#include "ffmpegcapabilities.h"

class Application : public QGuiApplication
{
private:
    QSimpleUpdater *qsu;
    std::unique_ptr<FfmpegCapabilities> ffmpegCapabilities;
    QString ffmpegPath;

    void findOrDownloadFfmpegBinary();
public:
    Application(int argc, char** argv);

    virtual ~Application() {}

    virtual bool notify(QObject *receiver, QEvent *event) override;

    void examineFfmpeg();
};

#endif // APPLICATION_H
