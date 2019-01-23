import QtQuick 2.11
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2


ScrollView {
    height: parent.height
    contentWidth: parent.width

    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    Component {
        id: listDelegate

        Rectangle {
            height: 50
            width: parent.width

            border.width: 1
            border.color: "black"

            color: index % 2 ? "#eee" : "white"

            RowLayout {
                anchors.fill: parent

                Text {
                    Layout.alignment: Qt.AlignLeft
                    text: model.modelData
                }

                Button {
                    Layout.alignment: Qt.AlignRight
                    text: "X"

                    onClicked: model.remove(index)
                }
            }
        }
    }

    ListModel {
        id: inputModel

        ListElement {
            fileName: "Test 1"
        }

        ListElement {
            fileName: "Test 2"
        }

        ListElement {
            fileName: "Test 3"
        }
    }

    ListModel {
        id: outputModel

        ListElement {
            fileName: "Test 1"
        }

        ListElement {
            fileName: "Test 2"
        }

        ListElement {
            fileName: "Test 3"
        }
    }

    ColumnLayout {
        width: parent.width

        Label {
            Layout.alignment: Qt.AlignCenter
            text: "Inputs"
            font.pixelSize: 18
        }

        ListView {
            id: inputList
            Layout.fillWidth: true
            Layout.preferredHeight: childrenRect.height

            spacing: 5

            model: inputModel
            delegate: listDelegate
        }

        Button {
            text: "Add Input"
            onClicked: inputModel.append({ fileName: new Date().toString() })
        }

        Label {
            Layout.alignment: Qt.AlignCenter
            text: "Outputs"
            font.pixelSize: 18
        }

        ListView {
            id: outputList
            Layout.fillWidth: true
            Layout.preferredHeight: childrenRect.height

            spacing: 5

            model: outputModel
            delegate: listDelegate
        }

        Button {
            text: "Add Output"
            onClicked: outputModel.append({ fileName: new Date().toString() })
        }
    }
}

