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

    ScrollView {
        anchors.fill: parent

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
                                text: (filePath == "" ? "(No Path)" : filePath) + " Duration: " + formatInfo["duration"]
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
                        text: "Format Info"
                        font.bold: true
                    }

                    Text {
                        text: {
                            var selected = viewModel.inputViewModel.selectedInputFile;

                            if (selected) {
                                var text = "";

                                for (var key in selected.formatInfo) {
                                    var val = selected.formatInfo[key];

                                    // Ignore "disposition" keys and so on for now
                                    if (typeof val != "object") {
                                        text += key + ": " + val + "\n";
                                    }
                                }

                                return text;
                            }

                            return "No selected";
                        }
                    }

                    Text {
                        text: "Streams Info"
                        font.bold: true
                    }

                    Text {
                        text: {
                            var selected = viewModel.inputViewModel.selectedInputFile;

                            if (selected) {
                                var text = "";

                                for (var i = 0; i < selected.streamsInfo.length; i++) {
                                    var stream = selected.streamsInfo[i];

                                    for (var key in stream) {
                                        var val = stream[key]

                                        // Ignore "disposition" keys and so on for now
                                        if (typeof val != "object") {
                                            text += key + ": " + val + "\n";
                                        }
                                    }
                                }

                                return text;
                            }

                            return "No selected";
                        }
                    }

                    Button {
                        text: "Back"

                        onClicked: stackView.pop()
                    }
                }
            }
        }
    }
}
