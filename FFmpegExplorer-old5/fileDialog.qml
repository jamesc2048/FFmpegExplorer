import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

FileDialog {
    id: fileDialog
    title: "Choose a file"
    folder: shortcuts.documents

    selectMultiple: true

    property var successCallback: null
    property var failCallback: null

    onAccepted: {
        if (successCallback) {
            successCallback(fileDialog.fileUrls)
        }
    }

    onRejected: {
        if (failCallback) {
            failCallback();
        }
    }

    Component.onCompleted: visible = true
}
