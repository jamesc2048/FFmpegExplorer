import QtQuick 2.0
import QtQuick.Window 2.0
import QtWebEngine 1.0

Window {
    width: 1024
    height: 768
    visible: true

    title: viewModel.title

    WebEngineView {
        anchors.fill: parent
        url: "https://www.qt.io"
    }

    Timer {
        interval: 2000
        triggeredOnStart: true
        running: true
        onTriggered: viewModel.title = "aaaaa!!!"
    }
}
