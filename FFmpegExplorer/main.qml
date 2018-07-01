import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: "FFmpeg Explorer"

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: "\u2630" // "\u25C0"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                drawer.open()
            }
        }

        Label {
            text: "FFmpeg Explorer"
            font.pixelSize: 16
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.5
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Page 1")
                width: parent.width

                onClicked: {
                    drawer.close()
                }
            }
        }
    }

    // Begin main UI
    ScrollView {
        id: scrollView

        anchors.fill: parent
        anchors.topMargin: 5
        anchors.bottomMargin: 5

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        ColumnLayout {
            width: window.width - 10


            Label {
                text: "Input File"
                font.pixelSize: 16
                Layout.alignment: Qt.AlignHCenter
            }

            // Input file block
            RowLayout {
                Layout.margins: 10

                TextField {
                    Layout.fillWidth: true

                    placeholderText: "Input file"
                    text: fileDialogInput.fileUrl.toString().replace("file:///", "")

                    onTextChanged: {
                        console.log("textChanged " + text)

                        viewModel.input.inputUrl = text
                        viewModel.debugLog()
                    }
                }

                Button {
                    text: "Choose Input"
                    onClicked: fileDialogInput.open()
                }

                FileDialog {
                    id: fileDialogInput
                    selectExisting: true
                    selectMultiple: false
                }
            }

            CheckBox {
                id: inputOptionsCb
                text: "Input Options:"
            }

            Frame {
                visible: inputOptionsCb.checked
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    RowLayout {
                        Label {
                            text: "Start time (-ss):"
                        }

                        TextField {
                            selectByMouse: true
                            id: inputStartTimeTb
                            Layout.fillWidth: true

                            placeholderText: "seconds or HH:MM:SS format"
                            text: viewModel.input.startTime

                            Binding {
                                target: viewModel.input
                                property: "startTime"
                                value: inputStartTimeTb.text
                            }
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Duration (-t):"
                        }

                        TextField {
                            id: inputDurationTb
                            Layout.fillWidth: true
                            selectByMouse: true

                            text: viewModel.input.duration
                            placeholderText: "seconds or HH:MM:SS format"

                            Binding {
                                target: viewModel.input
                                property: "duration"
                                value: inputDurationTb.text
                            }
                        }
                    }
                }
            }

            Label {
                text: "Output File"
                font.pixelSize: 16
                Layout.alignment: Qt.AlignHCenter
            }

            // Output file block
            RowLayout {
                Layout.margins: 10

                TextField {
                    Layout.fillWidth: true

                    placeholderText: "Output file"
                    text: fileDialogOutput.fileUrl.toString().replace("file:///", "")

                    onTextChanged: {
                        console.log("textChanged " + text)

                        viewModel.output.outputUrl = text
                        viewModel.debugLog()
                    }
                }

                Button {
                    text: "Choose Output"
                    onClicked: fileDialogOutput.open()
                }

                FileDialog {
                    id: fileDialogOutput
                    selectExisting: false
                    selectMultiple: false
                }
            }

            CheckBox {
                id: outputOptionsCb
                text: "Output Options:"
            }

            Frame {
                visible: outputOptionsCb.checked
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    RowLayout {
                        Label {
                            text: "Start time (-ss):"
                        }

                        TextField {
                            Layout.fillWidth: true

                            placeholderText: "seconds or HH:MM:SS format"
                        }
                    }

                    RowLayout {
                        Label {
                            text: "End time (-to):"
                        }

                        TextField {
                            id: endTimeTb
                            Layout.fillWidth: true

                            placeholderText: "seconds or HH:MM:SS format"
                            enabled: durationTb.text.length == 0
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Duration (-t):"
                        }

                        TextField {
                            id: durationTb
                            Layout.fillWidth: true

                            placeholderText: "seconds or HH:MM:SS format"
                            enabled: endTimeTb.text.length == 0
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Max File size (-fs):"
                        }

                        TextField {
                            Layout.fillWidth: true

                            placeholderText: "num bytes or standard suffix (E.G. 300k, 2M)"
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Max frames to output (-frames):"
                        }

                        TextField {
                            Layout.fillWidth: true

                            placeholderText: "Num frames"
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Disable Video (-vn):"
                        }

                        CheckBox {
                            id: disableVideoCb
                            Layout.fillWidth: true
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Video codec (-c:v):"
                        }

                        TextField {
                            Layout.fillWidth: true

                            placeholderText: "Video codec name"
                            enabled: !disableVideoCb.checked
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Video bitrate (-b:v):"
                        }

                        TextField {
                            Layout.fillWidth: true

                            placeholderText: "Bitrate (e.g. 300k)"
                            enabled: !disableVideoCb.checked
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Disable audio (-an):"
                        }

                        CheckBox {
                            id: disableAudioCb
                            Layout.fillWidth: true
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Audio codec (-c:a):"
                        }

                        TextField {
                            Layout.fillWidth: true

                            placeholderText: "Audio codec name"
                            enabled: !disableAudioCb.checked
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Audio bitrate (-b:a):"
                        }

                        TextField {
                            Layout.fillWidth: true

                            placeholderText: "Bitrate (e.g. 128k)"
                            enabled: !disableAudioCb.checked
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Frame rate (-r):"
                        }

                        TextField {
                            Layout.fillWidth: true

                            placeholderText: "Frame rate override"
                            enabled: !disableVideoCb.checked
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Frame size (-s):"
                        }

                        TextField {
                            Layout.fillWidth: true

                            placeholderText: "Abbreviation (E.G. xga, wxga) or widthXheight"
                            enabled: !disableVideoCb.checked
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Pixel format (-pix_fmt):"
                        }

                        TextField {
                            Layout.fillWidth: true

                            placeholderText: "Pixel format string (e.g. yuv420p)"
                            enabled: !disableVideoCb.checked
                        }
                    }

                    RowLayout {
                        Label {
                            text: "Filter graph (-filter):"
                        }

                        TextField {
                            Layout.fillWidth: true

                            placeholderText: "FFmpeg filtergraph string"
                        }
                    }
                }
            }


            Button {
                text: "Start Encode"
                Layout.fillWidth: true

                onClicked: {
                    viewModel.startEncode()
                }
            }
        }
    }
}
