import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: "FFmpeg Explorer"

    header: ToolBar {
        //contentHeight: toolButton.implicitHeight

//        ToolButton {
//            id: toolButton
//            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
//            font.pixelSize: Qt.application.font.pixelSize * 1.6
//            onClicked: {
//                if (stackView.depth > 1) {
//                    stackView.pop()
//                } else {
//                    drawer.open()
//                }
//            }
//        }

        Label {
            text: window.title
            anchors.centerIn: parent
            font.pixelSize: 18
        }
    }

//    Drawer {
//        id: drawer
//        width: window.width * 0.66
//        height: window.height

//        Column {
//            anchors.fill: parent

//            ItemDelegate {
//                text: qsTr("Page 1")
//                width: parent.width
//                onClicked: {
//                    drawer.close()
//                }
//            }
//            ItemDelegate {
//                text: qsTr("Page 2")
//                width: parent.width
//                onClicked: {
//                    drawer.close()
//                }
//            }
//        }
//    }

    ColumnLayout {
        anchors.fill: parent

        TabBar {
            id: tabBar
            Layout.fillWidth: true

            TabButton {
                text: "Setup"
            }

            TabButton {
                text: "Encode Queue"
            }
        }

        StackLayout {
            Layout.fillWidth: true

            currentIndex: tabBar.currentIndex

            SetupPage {

            }

            EncodeQueuePage {

            }
        }
    }
}
