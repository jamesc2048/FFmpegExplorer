TEMPLATE = subdirs

SUBDIRS += FFmpegExplorer \
            ../JACFFmpegLib


FFmpegExplorer.depends = ../JACFFmpegLib
