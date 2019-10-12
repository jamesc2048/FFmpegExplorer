import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "FFmpeg Explorer"

    Text {
        anchors.centerIn: parent
        text: viewModel.sampleText

        Component.onCompleted: utilities.httpGet("http://example.com", function(reply) {
            console.log(reply)
        });
    }
}
