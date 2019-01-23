import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3

Page {
    signal detailsPageClicked(var modelParams)

    id: inputPage

//    ListModel {
//        id: inputListModel

//        function getNewModel() {
//            return {
//                filePath: "",
//                startTrim: 0,
//                endTrim: 0,
//                duration: 0
//            }
//        }
//    }

    FileDialog {
        id: directoryDialog
        title: "Choose a directory"
        modality: Qt.WindowModal
        selectFolder: true
        folder: "2"

        onAccepted: {
            console.log("You chose: " + directoryDialog.folder)
        }

        onRejected: {
            console.log("Canceled")
        }
    }

    MessageDialog {
        id: messageDialog

        icon: StandardIcon.Information
        title: "Encode Completed"
        text: "Encode completed successfully!"

        onAccepted: {

        }
    }

    Component {
        id: inputListDelegate

        Item {
            height: 40
            width: parent.width

            RowLayout {
                anchors.fill: parent

                // preview image
                Image {
                    source: "https://www.google.com/images/branding/googlelogo/2x/googlelogo_color_272x92dp.png"
                    Layout.maximumHeight: 30
                    Layout.preferredWidth: 50
                    fillMode: Image.PreserveAspectFit
                }


                Text {
                    Layout.fillWidth: true
                    text: model.isValid ? filePath : "Not a video file!"
                    color: model.isValid ? "black" : "red"
                }

                Text {
                    Layout.fillWidth: true
                    text: model.duration
                }

                Button {
                    Layout.preferredWidth: 50
                    text: "Details"
                    onClicked: inputPage.detailsPageClicked(inputListModel.get(index))
                }

                Button {
                    text: "Remove"
                    onClicked: viewModel.inputViewModel.inputFiles.remove(index)
                }
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton

                onClicked: {
                    if (mouse.button === Qt.RightButton) {
                        contextMenu.popup()
                    }
                    else {
                        inputListView.currentIndex = index
                        mouse.accepted = false
                    }
                }

                Menu {
                    id: contextMenu

                    MenuItem {
                        text: "Remove"
                        onClicked: inputListModel.remove(index)
                    }

                    MenuItem {
                        text: "Details"
                        // To go details page
                        //onClicked: inputListModel.remove(index)
                    }
                }
            }
        }
    }

    ColumnLayout {
        width: parent.width

        ListView {
            id: inputListView
            //highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            focus: true
            model: viewModel.inputViewModel.inputFiles

            Layout.fillWidth: true
            Layout.preferredHeight: childrenRect.height
            clip: true

            delegate: inputListDelegate

            visible: viewModel.inputViewModel.inputFiles.count > 0
        }

        Text {
            visible: viewModel.inputViewModel.inputFiles.count == 0
            text: "Add input to begin"
            Layout.alignment: Qt.AlignCenter
            padding: 5
        }

        Button {
            text: "Add Input"
            Layout.alignment: Qt.AlignLeft

            onClicked: fileDialog.open()

            FileDialog {
                id: fileDialog
                title: "Choose a file"
                modality: Qt.WindowModal
                selectMultiple: false

                onAccepted: {
                    console.log("You chose: " + fileDialog.fileUrl)

                    // TODO eliminating this might make it troublesome to pass URLs?
                    var url = fileDialog.fileUrl.toString().replace("file:///", "");
                    viewModel.inputViewModel.addNewInputFile(url)
                }

                onRejected: {
                    console.log("Canceled")
                }
            }
        }
    }
}



