import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: "FFmpeg Explorer"

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

    ColumnLayout {
        width: parent.width

        Label {
            text: "Input File"
            font.pixelSize: 16
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            TextInput {
                Layout.fillWidth: true
                text: fileDialogInput.fileUrl.toString().replace("file:///", "")

                onTextChanged: {
                    console.log("textChanged " + text)

                    viewModel.inputUrl = text
                    viewModel.debugLog()
                }
            }

            Button {
                text: "Choose Input"
                onClicked: fileDialogInput.open()
            }

            FileDialog {
                id: fileDialogInput
                selectExisting: true
                selectMultiple: false
            }
        }

        Label {
            text: "Output File"
            font.pixelSize: 16
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            TextInput {
                Layout.fillWidth: true
                text: fileDialogOutput.fileUrl.toString().replace("file:///", "")

                onTextChanged: {
                    console.log("textChanged " + text)

                    viewModel.outputUrl = text
                    viewModel.debugLog()
                }
            }

            Button {
                text: "Choose Output"
                onClicked: fileDialogOutput.open()
            }

            FileDialog {
                id: fileDialogOutput
                selectExisting: false
                selectMultiple: false
            }
        }

        Button {
            text: "Start Encode"
            Layout.fillWidth: true

            onClicked: {
                viewModel.startEncode()
            }
        }
    }
}
