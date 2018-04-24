import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

RowLayout {
    anchors.fill: parent
    property bool isOutput: false
    property string selectedFileName: "Select file"

    TextInput {
        Layout.fillWidth: true
        text: selectedFileName
    }

    Button {
        Layout.fillWidth: true

        text: "Add"
        onClicked: {
            fileDialog.open()
        }
    }

    FileDialog {
        id: fileDialog
        title: "Choose a file"
        modality: Qt.WindowModal
        selectMultiple: false

        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrl)
            selectedFileName = fileDialog.fileUrl
            console.log(selectedFileName)
            console.log(isOutput)
        }

        onRejected: {
            console.log("Canceled")
        }
    }
}

