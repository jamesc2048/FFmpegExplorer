import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

FileDialog {
    id: directoryDialog
    title: "Choose a directory"
    folder: shortcuts.documents

    selectFolder: true

    property var successCallback: null
    property var failCallback: null

    onAccepted: {
        if (successCallback) {
            successCallback(directoryDialog.fileUrl)
        }
    }

    onRejected: {
        if (failCallback) {
            failCallback();
        }
    }

    Component.onCompleted: visible = true
}
