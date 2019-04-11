import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ColumnLayout {
        width: parent.width

        Text {
            text: "woww"
        }

        ListView {
            Layout.fillWidth: true
            Layout.preferredHeight: contentHeight

            clip: true
            model: viewModel.inputViewModel.inputFiles

            delegate: RowLayout {
                width: parent.width
                height: 50

                Text {
                    text: "wow"
                }

            }
        }

        Text {
            text: "woww"
        }
    }
}
