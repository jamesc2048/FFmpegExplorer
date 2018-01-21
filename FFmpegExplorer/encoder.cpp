#include "encoder.h"


EncodeItemViewModel::EncodeItemViewModel(QString path, QObject *parent) : QObject(parent)
{
    m_path = path;
    m_progress = 0;
    m_duration = 0;
    m_isComplete = false;
    m_isPaused = false;
    m_isEncoding = false;
    m_encodeProcess = nullptr;

    durationRegex.setPattern(R"(Duration: (\d{2}:\d{2}:\d{2}\.\d{2}))");
    progressRegex.setPattern(R"(time=(\d{2}:\d{2}:\d{2}\.\d{2}))");

    auto fi = QFileInfo(m_path);

    if (!fi.exists())
    {
        throw std::invalid_argument("file doesn't exist! and it should...");
    }

    m_name = fi.exists() ? fi.baseName() : "(Not found)";
}

void EncodeItemViewModel::startEncode()
{
    //        QTimer *timer = new QTimer(this);
    //        connect(timer, &QTimer::timeout, this, [&]() {
    //            set_progress(get_progress() + 0.1);
    //        });
    //        timer->start(100);
    //        return;

    m_encodeProcess = new QProcess(this);

    connect(m_encodeProcess, &QProcess::readyReadStandardOutput, this, [&]() {
        qWarning() << "Standard out from signal: " << m_encodeProcess->readAllStandardOutput();
    });

    connect(m_encodeProcess, &QProcess::readyReadStandardError, this, [&]() {
        QString ffmpegOutput = m_encodeProcess->readAllStandardError();
        qWarning() << "Standard error from signal: " << ffmpegOutput;

        processFfmpegOutput(ffmpegOutput);
    });

    connect(m_encodeProcess, &QProcess::stateChanged, this, [&](const QProcess::ProcessState state) {
        qWarning() << "State changed: " << state;
    });

    connect(m_encodeProcess, &QProcess::started, this, [&]() {
        // TODO Windows specific!
        Q_PID procInfo = m_encodeProcess->pid();
        qWarning() << "procInfo" << procInfo;
        //PROCESS_INFORMATION * processInfo = procId;

#ifdef Q_OS_WIN
        HANDLE handle = procInfo->hProcess;

        qWarning() << "Setting priority for" << procInfo << handle <<
                      SetPriorityClass(handle, IDLE_PRIORITY_CLASS);

#endif
#ifdef Q_OS_LINUX
        // TODO
        qWarning() << "Not setting process priority as not implemented on this OS";
#endif

#ifdef Q_OS_MACOS
        // TODO
        qWarning() << "Not setting process priority as not implemented on this OS";
#endif
    });

    connect(m_encodeProcess, &QProcess::errorOccurred, this, [&](const QProcess::ProcessError error) {
        qWarning() << "Error: " << error;
        set_hasError(true);
    });

    void (QProcess::* castFinished)(int, QProcess::ExitStatus) = &QProcess::finished;
    connect(m_encodeProcess, castFinished, this, [&](int exitCode, QProcess::ExitStatus exitStatus) {
        qWarning() << "Finished. Exit status: " << exitStatus << " Exit code: " << exitCode;

        set_isEncoding(false);
        set_isComplete(true);
        set_progress(m_duration);

        emit finishedEncode();
        // Empty because we're reading from signals.
        //qWarning() << "Standard out:" << m_encodeProcess->readAllStandardOutput();
        //qWarning() << "Standard error:" << m_encodeProcess->readAllStandardError();
        m_encodeProcess->deleteLater();
    });

    QStringList args { "-i",
                       m_path,
                       //"-c", "copy",
                       "-c:v", "libx265",
                       "-b:a", "64k",
                       m_path + "-enc.mp4",
                       "-y"};

    qWarning() << "About to start ffmpeg with args " << args.join(", ");
    m_encodeProcess->start("ffmpeg", args);

    set_isEncoding(true);
}

void EncodeItemViewModel::processFfmpegOutput(QString ffmpegOutput)
{
    // General structure:
    // Input info: Input #0, mov,mp4,m4a,3gp,3g2,mj2, from 'D:\\testDir\\20170127_083818.mp4':\r\n  Metadata:\r\n    major_brand     : mp42\r\n    minor_version   : 0\r\n    compatible_brands: isommp42\r\n    creation_time   : 2017-01-27T08:38:51.000000Z\r\n    com.android.version: 6.0\r\n  Duration: 00:00:31.85, start: 0.000000, bitrate: 17133 kb/s\r\n
    // Stream #0:0(eng): Video: h264 (High) (avc1 / 0x31637661), yuv420p, 1920x1080, 16923 kb/s, SAR 1:1 DAR 16:9, 29.94 fps, 29.92 tbr, 90k tbn, 180k tbc (default)\r\n    Metadata:\r\n      creation_time   : 2017-01-27T08:38:51.000000Z\r\n      handler_name    : VideoHandle\r\n    Stream #0:1(eng): Audio: aac (LC) (mp4a / 0x6134706D), 48000 Hz, stereo, fltp, 156 kb/s (default)\r\n    Metadata:\r\n      creation_time   : 2017-01-27T08:38:51.000000Z\r\n      handler_name    : SoundHandle\r\n
    // Progress stuff: frame=  199 fps=8.8 q=29.0 size=    6067kB time=00:00:07.01 bitrate=7080.7kbits/s speed=0.309x    \r
    //m_processOutput << ffmpegOutput;

    int index = durationRegex.indexIn(ffmpegOutput);
    if (index != -1)
    {
        QString cap = durationRegex.cap(1);

        QTime time(cap.mid(0, 2).toInt(),
                   cap.mid(3, 2).toInt(),
                   cap.mid(6, 2).toInt(),
                   cap.mid(9, 2).toInt() * 10);

        int dur = QTime(0, 0, 0).secsTo(time);
        set_duration(dur);

        qWarning() << "duration:" << index << cap << time << dur;
    }

    index = progressRegex.indexIn(ffmpegOutput);
    if (index != -1)
    {
        QString cap = progressRegex.cap(1);
        //QTime time = QTime::fromString(cap, "hh:mm:ss.zzz");
        QTime time(cap.mid(0, 2).toInt(),
                   cap.mid(3, 2).toInt(),
                   cap.mid(6, 2).toInt(),
                   cap.mid(9, 2).toInt() * 10);

        int prog = QTime(0, 0, 0).secsTo(time);
        qWarning() << "progress:" << index << cap << time << prog;

        set_progress(prog);
    }
}

#ifdef Q_OS_WIN
typedef LONG (NTAPI *NtSuspendProcess)(IN HANDLE ProcessHandle);
#endif

void EncodeItemViewModel::pauseResumeEncoding()
{
    // TODO Windows specific!
#ifdef Q_OS_WIN
    Q_PID procInfo = m_encodeProcess->pid();
    qWarning() << "procInfo" << procInfo;
    //PROCESS_INFORMATION * processInfo = procId;

    HANDLE handle = procInfo->hProcess;

    NtSuspendProcess pfnNtSuspendProcess = (NtSuspendProcess)GetProcAddress(GetModuleHandle(L"ntdll"), "NtSuspendProcess");
    NtSuspendProcess pfnNtResumeProcess = (NtSuspendProcess)GetProcAddress(GetModuleHandle(L"ntdll"), "NtResumeProcess");

    if (!get_isPaused())
    {
        qWarning() << "Pausing encoding for " << procInfo << handle;
        pfnNtSuspendProcess(handle);

        set_isPaused(true);
    }
    else
    {
        qWarning() << "Resuming encoding for " << procInfo << handle;
        pfnNtResumeProcess(handle);

        set_isPaused(false);
    }
#endif
}


Encoder::Encoder(QObject *parent) : QObject(parent)
{
    m_encodeModel = new QQmlObjectListModel<EncodeItemViewModel>(this);
    m_totalEncodeFiles = 0;
    m_currentEncodeFile = 0;
    m_isRunningEncode = false;
}

void Encoder::continueEncode()
{
    if (++currentEncodeIndex >= m_encodeModel->count())
    {
        set_isRunningEncode(false);
        return;
    }

    set_currentEncodeFile(currentEncodeIndex);
    // TODO should show the real progress
    set_encodeProgress((double)currentEncodeIndex / (double)m_totalEncodeFiles);

    auto vm = m_encodeModel->at(currentEncodeIndex);
    vm->startEncode();

    connect(vm, &EncodeItemViewModel::finishedEncode, this, &Encoder::continueEncode);
}

void Encoder::encode()
{
    if (m_encodeModel->count() > 0)
    {
        set_isRunningEncode(true);
        currentEncodeIndex = 0;

        auto vm = m_encodeModel->at(currentEncodeIndex);
        vm->startEncode();

        connect(vm, &EncodeItemViewModel::finishedEncode, this, &Encoder::continueEncode);
    }
}

void Encoder::addToEncode(QUrl url)
{
    QString path = url.toLocalFile();

    qWarning() << path;
    auto encodeItem = new EncodeItemViewModel(path, m_encodeModel);
    m_encodeModel->append(encodeItem);

    set_totalEncodeFiles(m_totalEncodeFiles + 1);
    //encodeItem->startEncode();
}

void Encoder::addToEncodeFromDirectory(QUrl url)
{
    QString dirPath = url.toLocalFile();

    qWarning() << dirPath;

    QDir dir(dirPath);
    qWarning() << dir.entryInfoList(QDir::Files).count();

    QDirIterator it(dirPath, { "*.mp4", "*.mkv", "*.mov", "*.wmv" }, QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext())
    {
        auto file = it.next();
        qWarning() << file;

        // don't encode if encoded, don't encode if has already been encoded
        // TODO add option to control this!
        if (!file.endsWith("-enc.mp4") && !QFile(file + "-enc.mp4").exists())
        {
            addToEncode(QUrl::fromLocalFile(file));
        }
    }

    encode();

    //        foreach (QFileInfo info, QDir(dirPath).entryInfoList(QDir::Files)) {
    //            qWarning() << info.absoluteFilePath();
    //            addToEncode(QUrl::fromLocalFile(info.absoluteFilePath()));
    //        }
}

void Encoder::removeFromEncode(int index)
{
    auto encodeModel = m_encodeModel->at(index);
    m_encodeModel->remove(index);

    encodeModel->deleteLater();
}

void Encoder::pauseResumeEncoding()
{
    for (EncodeItemViewModel *model : (*m_encodeModel).toList())
    {
        if (model->get_isEncoding())
        {
            qDebug() << "Toggling pause for this encode";
            model->pauseResumeEncoding();
        }
    }
}
