import QtQuick 2.11
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2


ScrollView {
    clip: true
    height: parent.height
    contentWidth: parent.width

    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    Component {
        id: listDelegate

        RowLayout {
            height: 40
            width: parent.width

            Text {
                Layout.margins: 5
                Layout.alignment: Qt.AlignLeft
                text: filePath
            }

            Button {
                Layout.margins: 5
                Layout.alignment: Qt.AlignRight
                text: "X"

                // change to viewmodel call
                onClicked: viewModel.inputViewModel.inputFiles.remove(index)
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        Label {
            Layout.alignment: Qt.AlignCenter
            text: "Inputs"
            font.pixelSize: 18
        }

        ListView {
            id: inputList
            Layout.fillWidth: true
            Layout.preferredHeight: childrenRect.height

            spacing: 2

            model: viewModel.inputViewModel.inputFiles
            delegate: listDelegate
        }

        Button {
            text: "Add Input"
            onClicked: viewModel.inputViewModel.inputModel.append({ fileName: new Date().toString() })
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

            spacing: 2

//            model: outputModel
            delegate: listDelegate
        }

        Button {
            text: "Add Output"
            onClicked: outputModel.append({ fileName: new Date().toString() })
        }
    }
}

