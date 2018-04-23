import QtQuick 2.7
import QtQml 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Page {
    anchors.fill: parent

    ColumnLayout {
        width: parent.width

        GroupBox {
            title: "Inputs"
            width: parent.width
            contentWidth: width

            ColumnLayout {
                width: parent.width

                TextInput {
                    text: "oy"

                }

                Button {
                    text: "Add more inputs"
                    onClicked: console.log("lol")
                }
            }
        }

        GroupBox {
            title: "Outputs"
            width: parent.width
            contentWidth: width

            ColumnLayout {
                ColumnLayout {
                    id: aaa

                    TextInput {
                        text: "oy"
                    }
                }

                Button {
                    text: "Add more outputs"
                    onClicked: { Qt.quit() }
                }
            }
        }
    }
}
