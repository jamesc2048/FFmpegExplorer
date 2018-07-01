import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Stack")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: "\u2630" // "\u25C0"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                drawer.open()
            }
        }

        Label {
            text: "FFmpeg Explorer"
            font.pixelSize: 16
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.5
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Page 1")
                width: parent.width

                onClicked: {
                    drawer.close()
                }
            }
        }
    }
}
