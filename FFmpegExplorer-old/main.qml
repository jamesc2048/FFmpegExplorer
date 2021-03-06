import QtQuick 2.7
import QtQml 2.2
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import Encoder 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "FFmpeg Explorer"

    Component.onCompleted: {
        console.log("Application Window instantiated");

        timer.running = true;
    }

    Timer {
        id: timer
        interval: 2000
        repeat: false
        onTriggered: checkForUpdates();
    }

    //Component.onDestroyed: console.log("destroyed");
    Component.onDestruction: console.log("Application Window destroyed");
    //Component.onStatusChanged: console.log("status changed " + status)
    //Component.onProgressChanged: console.log("progress changed " + progress);

    Encoder {
        id: encoder
    }

    menuBar: MenuBar {
        Menu {
            title: "File"
            Action { text: "Something" }
            Action { text: "Something Else" }
        }

        Menu {
            title: "Stuff"
            Action { text: "Something" }
            Action { text: "Something Else" }
        }
    }

    Page {
        id: root
        anchors.fill: parent

        header: TabBar {
            id: taskBar

            width: parent.width
            TabButton {
                text: qsTr("Home")
            }
            TabButton {
                text: qsTr("Discover")
            }
            TabButton {
                text: qsTr("Activity")
            }
        }

//        header: ToolBar {
//            Label {
//                text: "FFmpeg Explorer"
//                font.pixelSize: 20
//                anchors.centerIn: parent
//            }
//        }

//        CustomStackView {
//            id: stackView
//            anchors.fill: parent

//            initialItem: ListControl {}
//        }

        MediaSelectorForm {

        }

        footer: ColumnLayout {
            RowLayout {
                visible: encoder.isRunningEncode

                ProgressBar {
                    from: 0
                    to: encoder.totalEncodeFiles
                    value: encoder.currentEncodeFile

                    Layout.fillWidth: true
                }

                Text {
                    text: "Progress: " + (encoder.currentEncodeFile + 1) + "/" + encoder.totalEncodeFiles
                }
            }

            RowLayout {
                Button {
                    text: "Add Files"
                    Layout.fillWidth: true

                    onClicked: {
                        fileDialog.open()
                    }
                }

                Button {
                    text: "Add Directory"
                    Layout.fillWidth: true

                    onClicked: {
                        directoryDialog.open()
                    }
                }

                Button {
                    text: "Pause/Resume Encode"
                    Layout.fillWidth: true

                    onClicked: encoder.pauseResumeEncoding()
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Choose a file"
        modality: Qt.WindowModal
        selectMultiple: false

        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrl)
            encoder.addToEncode(fileDialog.fileUrl)
        }

        onRejected: {
            console.log("Canceled")
        }
    }

    FileDialog {
        id: directoryDialog
        title: "Choose a directory"
        modality: Qt.WindowModal
        selectFolder: true
        folder: "2"

        onAccepted: {
            console.log("You chose: " + directoryDialog.folder)
            encoder.addToEncodeFromDirectory(directoryDialog.folder)
        }

        onRejected: {
            console.log("Canceled")
        }
    }

    function checkForUpdates() {
        // BUG in Qt, this causes hang if using HTTPS.
        Utilities.getWebResponse("http://httpbin.org/ip", function(response) {
            console.log(response);
        });
    }

//    function checkForUpdates() {
//        console.log("checkForUpdates start");
//        var req = new XMLHttpRequest();
//        req.open("GET", "https://crisafulli.me/ffmpegexplorer/versioncheck", true);

//        req.onreadystatechange = function() {
//            console.log("checkForUpdates readyStateChange");

//            if (req.readyState == XMLHttpRequest.DONE) {
//                var response = req.responseText;

//                console.log("Headers -->");
//                console.log(req.getAllResponseHeaders ());
//                console.log("Last modified -->");
//                console.log(req.getResponseHeader ("Last-Modified"));
//                console.log(response);
//            }
//        }

//        req.send();
//    }
}
