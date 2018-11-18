#include "inputfileviewmodel.hpp"

InputFileViewModel::InputFileViewModel(QObject *parent) : ViewModelBase(parent)
{
    //set_filePath("wowowow");
    set_duration(55.6);
    set_startTrim(3.33);
    set_endTrim(6.66);
    set_isValid(true);
}

void InputFileViewModel::analyseFile()
{
    qDebug() << "Analysing file" << get_filePath();

    // Populate fields with output of FFprobe
    // TODO: reimplement this with raw AVFormat / AVCodec

    QString filePath = get_filePath();

    if (filePath.isEmpty())
    {
        set_isValid(false);
        return;
    }

    if (!QFile::exists(filePath))
    {
        set_isValid(false);
        return;
    }

    QProcess* proc = new QProcess(this);

    // TODO actual path and not system wide. Check for existance
    QString ffprobePath = "ffprobe";
    QStringList args = QStringList() << "-v" << "quiet"
                                     << "-print_format" << "json"
                                     << "-show_format"
                                     << "-show_streams"
                                     << filePath;
    proc->start(ffprobePath, args);

    connect(proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [=](int exitCode, QProcess::ExitStatus exitStatus)
    {
        qDebug() << "Finished analyse" << exitCode << exitStatus;

        QByteArray standardOut = proc->readAllStandardOutput();
        QByteArray standardError = proc->readAllStandardError();
        qDebug() << standardOut << "\n" << standardError;

        if (exitCode == 1)
        {
            set_isValid(false);
            return;
        }

        QJsonDocument jsonDoc = QJsonDocument::fromJson(standardOut);

        if (jsonDoc.isEmpty())
        {
            set_isValid(false);
            return;
        }

        QJsonObject json = jsonDoc.object();

        QJsonValue format = json["format"];
        qDebug() << format;
        qDebug() << "Duration" << format["duration"];
        qDebug() << "Size" << format["size"];
        qDebug() << "BitRate" << format["bit_rate"];

        set_duration(format["duration"].toString().toDouble());

        set_isValid(exitCode == 0);


        qDebug() << "Deleting proc " << (void *)proc;
        proc->deleteLater();

//        {
//            "streams": [
//                {
//                    "index": 0,
//                    "codec_name": "h264",
//                    "codec_long_name": "H.264 / AVC / MPEG-4 AVC / MPEG-4 part 10",
//                    "profile": "Main",
//                    "codec_type": "video",
//                    "codec_time_base": "1/2000",
//                    "codec_tag_string": "[0][0][0][0]",
//                    "codec_tag": "0x0000",
//                    "width": 1280,
//                    "height": 720,
//                    "coded_width": 1280,
//                    "coded_height": 720,
//                    "has_b_frames": 0,
//                    "sample_aspect_ratio": "1:1",
//                    "display_aspect_ratio": "16:9",
//                    "pix_fmt": "yuv420p",
//                    "level": 31,
//                    "chroma_location": "left",
//                    "field_order": "progressive",
//                    "refs": 1,
//                    "is_avc": "true",
//                    "nal_length_size": "4",
//                    "r_frame_rate": "30/1",
//                    "avg_frame_rate": "1000/1",
//                    "time_base": "1/1000",
//                    "start_pts": 4007,
//                    "start_time": "4.007000",
//                    "bits_per_raw_sample": "8",
//                    "disposition": {
//                        "default": 1,
//                        "dub": 0,
//                        "original": 0,
//                        "comment": 0,
//                        "lyrics": 0,
//                        "karaoke": 0,
//                        "forced": 0,
//                        "hearing_impaired": 0,
//                        "visual_impaired": 0,
//                        "clean_effects": 0,
//                        "attached_pic": 0,
//                        "timed_thumbnails": 0
//                    },
//                    "tags": {
//                        "VARIANT_BITRATE": "3396000",
//                        "DURATION": "03:52:38.540000000"
//                    }
//                },
//                {
//                    "index": 1,
//                    "codec_name": "aac",
//                    "codec_long_name": "AAC (Advanced Audio Coding)",
//                    "profile": "LC",
//                    "codec_type": "audio",
//                    "codec_time_base": "1/44100",
//                    "codec_tag_string": "[0][0][0][0]",
//                    "codec_tag": "0x0000",
//                    "sample_fmt": "fltp",
//                    "sample_rate": "44100",
//                    "channels": 2,
//                    "channel_layout": "stereo",
//                    "bits_per_sample": 0,
//                    "r_frame_rate": "0/0",
//                    "avg_frame_rate": "0/0",
//                    "time_base": "1/1000",
//                    "start_pts": 0,
//                    "start_time": "0.000000",
//                    "disposition": {
//                        "default": 1,
//                        "dub": 0,
//                        "original": 0,
//                        "comment": 0,
//                        "lyrics": 0,
//                        "karaoke": 0,
//                        "forced": 0,
//                        "hearing_impaired": 0,
//                        "visual_impaired": 0,
//                        "clean_effects": 0,
//                        "attached_pic": 0,
//                        "timed_thumbnails": 0
//                    },
//                    "tags": {
//                        "VARIANT_BITRATE": "488000",
//                        "DURATION": "03:52:38.512000000"
//                    }
//                }
//            ],
//            "format": {
//                "filename": "D:\\arletnoa.mkv",
//                "nb_streams": 2,
//                "nb_programs": 0,
//                "format_name": "matroska,webm",
//                "format_long_name": "Matroska / WebM",
//                "start_time": "0.000000",
//                "duration": "13958.540000",
//                "size": "5126647383",
//                "bit_rate": "2938214",
//                "probe_score": 100,
//                "tags": {
//                    "ENCODER": "Lavf58.12.100"
//                }
//            }
//        }
    });
}
