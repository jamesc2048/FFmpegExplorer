import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Page {
    ColumnLayout {
        width: parent.width

        GroupBox {
            width: parent.width

            RowLayout {
                width: parent.width
                Layout.fillWidth: true

                Text {
                    text: "Input"
                }

                TextInput {
                    Layout.fillWidth: true
                    text: "Hi!!"
                }
            }
        }

        GroupBox {
            RowLayout {
                Text {
                    text: "Output"
                }

                TextInput {
                    text: "Hi 2!!"
                }
            }
        }
    }
}
