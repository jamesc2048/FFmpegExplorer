import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

ItemDelegate {
    width: parent.width

    onClicked: {
        stackView.push("qrc:/DetailsControl.qml", { modelData: { name: name } })
        console.log(index)
        console.log(model)
        //console.log(modelData)
        //console.log(model.modelData)
    }

    //clicked: null // TODO: navigate to other page on click for details?

    Component {
        id: text
    }

    RowLayout {
        anchors.fill: parent

        Text {
            Layout.preferredWidth: -1
            text: name
        }

        ProgressBar {
            id: progressBar
            Layout.fillWidth: true
            from: 0
            to: duration
            value: progress
            //indeterminate: progress == 0
            // TODO QT bug? causes hang when minimised, also causes high CPU usage!
            // Maybe due to binding to progress binding ?
            indeterminate: false
        }

        Text {
            Layout.preferredWidth: -1
            text: isComplete ? "Complete" : (progress / duration * 100.0).toFixed(2) + " %"
            visible: !progressBar.indeterminate
        }

        Button {
            text: "X"
            Layout.preferredWidth: 50

            onClicked: encoder.removeFromEncode(index)
        }
    }
}
