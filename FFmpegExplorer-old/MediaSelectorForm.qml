import QtQuick 2.7
import QtQml 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Page {
    function addInOut(initialText, container) {
        var c = Qt.createComponent("InOutFileSelection.qml")
        var t = c.createObject(container, { isOutput: container === outputContainer})
    }

    anchors.fill: parent

    ColumnLayout {
        id: mainLayout
        width: parent.width

        GroupBox {
            title: "Inputs"
            Layout.fillWidth: true

            ColumnLayout {
                ColumnLayout {
                    id: inputContainer
                    width: parent.width

                    InOutFileSelection {
                        Layout.fillWidth: true
                        isOutput: false
                    }
                }

                Button {
                    text: "Add more inputs"
                    onClicked: addInOut("Input", inputContainer)
                }
            }
        }

        GroupBox {
            title: "Outputs"
            Layout.fillWidth: true

            ColumnLayout {
                ColumnLayout {
                    id: outputContainer

                    InOutFileSelection {
                        Layout.fillWidth: true
                        isOutput: true
                    }
                }

                Button {
                    text: "Add more outputs"
                    onClicked: addInOut("Output", outputContainer)
                }
            }
        }
    }
}
