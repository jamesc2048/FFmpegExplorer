import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import Encoder 1.0



ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Ffmpeg GUI"

    Encoder {
        id: encoder
    }

    Page {      
        id: root
        anchors.fill: parent

        header: ToolBar {
            Label {
                text: "Ffmpeg GUI"
                font.pixelSize: 20
                anchors.centerIn: parent
            }
        }

        CustomStackView {
            id: stackView
            anchors.fill: parent

            initialItem: ListControl {}
        }

        footer: ColumnLayout {
            RowLayout {
                visible: encoder.isRunningEncode

                ProgressBar {
                    from: 0
                    to: encoder.totalEncodeFiles
                    value: encoder.encodeProgress

                    Layout.fillWidth: true
                }

                Text {
                    text: "Progress: " + (encoder.currentEncodeFile + 1) + "/" + encoder.totalEncodeFiles
                }
            }

            RowLayout {
                Button {
                    text: "Add Files"
                    Layout.fillWidth: true

                    onClicked: {
                        fileDialog.open()
                    }
                }

                Button {
                    text: "Add Directory"
                    Layout.fillWidth: true

                    onClicked: {
                        directoryDialog.open()
                    }
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Choose a file"
        modality: Qt.WindowModal
        selectMultiple: false

        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrl)
            encoder.addToEncode(fileDialog.fileUrl)
        }

        onRejected: {
            console.log("Canceled")
        }
    }

    FileDialog {
        id: directoryDialog
        title: "Choose a directory"
        modality: Qt.WindowModal
        selectFolder: true
        folder: "2"

        onAccepted: {
            console.log("You chose: " + directoryDialog.folder)
            encoder.addToEncodeFromDirectory(directoryDialog.folder)
        }

        onRejected: {
            console.log("Canceled")
        }
    }

//    footer: TabBar {
//        id: tabBar
//        currentIndex: swipeView.currentIndex
//        TabButton {
//            text: qsTr("First")
//        }
//        TabButton {
//            text: qsTr("Second")
//        }
//    }
}
