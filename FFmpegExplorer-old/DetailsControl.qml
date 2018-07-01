import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2


RowLayout {
    property var modelData

    Text { text: modelData.name }

    Button {
        text: "click"
        onClicked: stackView.pop()
    }
}
