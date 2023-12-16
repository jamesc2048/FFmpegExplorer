import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import FFmpegExplorer

// Simple mode: only allow 1 output, allow -vf and -af
// Complex mode: allow N inputs, allow -filter_complex

ApplicationWindow {
    width: 1024
    height: 768
    visible: true
    title: "FFmpeg Explorer"

    Backend {
        id: backend
    }

    ListModel {
        id: inputModel
    }

    FileDialog {
        id: inputDialog
        fileMode: FileDialog.OpenFile

        onAccepted: () => {
            var trimmedFile = inputDialog.selectedFile.toString().substring(8);
            console.log(trimmedFile)

            backend.runProcess("ffprobe",
                               [ "-v", "quiet", "-of", "json", "-show_format", "-show_streams",
                                trimmedFile ],
                               (out, err) => {
                                   //console.log(out);
                                   //console.log(err);
                                   var j = JSON.parse(out);

                                   console.log(j);

                                    inputModel.append({
                                        filename: trimmedFile,
                                        probe: out
                                    })
                               })
        }
    }

    Flickable {
        anchors.fill: parent
        // Have to do this because of interaction between Layouts/legacy layouts.
        contentHeight: col.height
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
        }

        ColumnLayout {
            id: col
            anchors.margins: 5

            GroupBox {
                title: "Input files"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    Repeater {
                        model: inputModel
                        delegate: ColumnLayout {
                            Label {
                                text: filename
                            }
                            Label {
                                text: probe
                            }
                        }
                    }

                    Button {
                        text: "Add new input file"
                        onClicked: () => {
                            inputDialog.open()
                        }
                    }
                }
            }

            GroupBox {
                title: "Filters"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    Label {
                        text: "Filter 1"
                    }

                    Label {
                        text: "Filter 2"
                    }
                }
            }

            GroupBox {
                title: "Output File"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    Label {
                        text: "Output"
                    }
                }
            }
        }
    }
}
