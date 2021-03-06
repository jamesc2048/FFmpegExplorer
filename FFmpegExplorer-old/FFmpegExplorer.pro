QT += qml quick quickcontrols2 network sql concurrent multimedia

# seems to apply to non windows configs too? bah.
#win32 {
#    message("Windows extras")
#    QT += winextras
#}

VERSION = 0.1.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

CONFIG += c++14
#QMAKE_CXXFLAGS += -std=c++17

SOURCES += main.cpp \
    encoder.cpp \
    qmlutils.cpp \
    application.cpp \
    ffmpegcapabilities.cpp \
    utilities.cpp

RESOURCES += qml.qrc

PRECOMPILED_HEADER = pch.hpp

RC_ICONS = icon.ico

CONFIG(debug, debug|release ) {
    # debug
    message("debug!")
} else {
    # release
    message("release!")
    CONFIG += qtquickcompiler
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ffmpegcapabilities.hpp \
    encoder.hpp \
    common.hpp \
    application.hpp \
    qmlutils.hpp \
    utilities.hpp

