import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    signal detailsPageClicked(var modelParams)

    id: inputPage

    ListModel {
        id: inputListModel

        function getNewModel() {
            return {
                filePath: "",
                startTrim: 0,
                endTrim: 0,
                duration: 0
            }
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
                    text: model.filePath
                }

                Text {
                    Layout.fillWidth: true
                    text: model.startTime
                }

                Button {
                    Layout.preferredWidth: 50
                    text: "Details"
                    onClicked: inputPage.detailsPageClicked(inputListModel.get(index))
                }

                Button {
                    text: "Remove"
                    onClicked: inputListModel.remove(index)
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
            model: inputListModel

            Layout.fillWidth: true
            Layout.preferredHeight: childrenRect.height
            clip: true

            delegate: inputListDelegate

            visible: inputListModel.count > 0
        }

        Text {
            visible: inputListModel.count == 0
            text: "Add input to begin"
            Layout.alignment: Qt.AlignCenter
            padding: 5
        }

        Button {
            text: "Add Input"
            Layout.alignment: Qt.AlignLeft

            onClicked: {
                var model = inputListModel.getNewModel()
                model.filePath = new Date().toString()
                model.startTime = 20
                model.endTime = 50

                inputListModel.append(model)

                console.log(JSON.stringify(inputListModel))
            }
        }
    }
}
