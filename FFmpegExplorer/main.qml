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

    Component.onCompleted: {
        // constructor, kind of
        viewModel.encodeFinished.connect(function()
        {
            console.log("encode finished!")
            messageDialog.open()
        })
    }

    MessageDialog {
        id: messageDialog

        icon: StandardIcon.Information
        title: "Encode Completed"
        text: "Encode completed successfully!"
        onAccepted: {

        }
    }

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

    StackView {
        id: stackView
        initialItem: "SetupView.qml"

        anchors.fill: parent

        Component.onCompleted: {
            viewModel.encodeStarting.connect(function()
            {
                console.log("encode starting")
                stackView.push("EncodeView.qml")
            })
        }
    }
}
