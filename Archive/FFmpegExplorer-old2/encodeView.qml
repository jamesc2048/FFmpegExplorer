import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3

RowLayout {
    Text {
        text: "Encode Progress"
    }

    ProgressBar {
        Layout.fillWidth: true

        id: progressBar
        // testing
        from: 0
        to: 100

        value: viewModel.encodeProgress
    }

    Button {
        text: "Back"
        onClicked: stackView.pop()
    }
}


