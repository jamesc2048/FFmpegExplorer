import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

Window {
    visible: true
    width: 800
    height: 600
    title: "FFmpeg Explorer"
    id: window

    Component.onCompleted: {
        console.log("Loaded!")

        utilities.httpGet("http://3.crisafulli.me/")
    }

    StackView {
        id: stackView
        width: parent.width

        initialItem: mainView

        Component {
            id: mainView

            ColumnLayout {
                width: parent.width

                Text {
                    text: "Input Files"
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
                            Layout.fillWidth: true
                            text: (filePath == "" ? "(No Path)" : filePath) + " Duration: " + duration
                            verticalAlignment: Qt.AlignVCenter
                        }

                        Button {
                            height: 30

                            text: "Details"
                            onClicked: {
                                viewModel.inputViewModel.selectedInputFile =
                                        viewModel.inputViewModel.inputFiles.get(index)

                                stackView.push(detailsView)
                            }
                        }

                        Button {
                            height: 30

                            text: "Remove"
                            onClicked: viewModel.inputViewModel.inputFiles.remove(index)
                        }
                    }
                }

                Button {
                    text: "Add Input File"

                    onClicked: {
                        var c = Qt.createComponent("fileDialog.qml");

                        c.createObject(window, {
                           successCallback: function(urls) {
                               console.log("FileDialog:", urls);

                               viewModel.inputViewModel.addInputUrls(urls)
                           }
                        })
                    }
                }
            }
        }

        Component {
            id: detailsView

            ColumnLayout {
                Text {
                    text: {
                        var selected = viewModel.inputViewModel.selectedInputFile;

                        if (selected) {
                            return selected.duration
                        }

                        return "No selected";
                    }
                }

                Text {
                    text: viewModel.inputViewModel.selectedInputFile.filePath
                }

                Button {
                    text: "Back"

                    onClicked: stackView.pop()
                }
            }
        }
    }
}
