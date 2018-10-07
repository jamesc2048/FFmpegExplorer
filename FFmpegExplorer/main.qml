import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

ApplicationWindow {
    objectName: "mainWindow"
    id: window
    visible: true
    width: 640
    height: 480
    title: "FFmpeg Explorer"

    // Tabs?:
    // Simple mode
    // Advanced mode
    // Encode Queue

    ListModel
    {
        function appendChild(st) {
            append({
                       inputFileName: st,
                       outputFileName: "wowowow"})
        }

        id: encodeListModel
        objectName: "encodeListModelObj"

        ListElement {
            inputFileName: "wowowow"
            outputFileName: "wowowow"
            progressPercent: 0.0
        }

        ListElement {
            inputFileName: "bbbb"
            outputFileName: "wowowow"

            progressPercent: 0.0
        }
    }

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

         ToolButton {
            id: toolButton
            text: "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                drawer.open()
            }
        }

        Label {
            text: "FFmpeg Explorer"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            anchors.centerIn: parent
        }
    }

    Settings {
        // Must have settings like:
        // Default save location directory.
        // Default filename append for encoded files (e.g. "-enc")
        // Save in same directory as file? if so, disables save location directory
        id: settings
        objectName: "settingsObj"

        property string defaultSaveDirectory
        property string defaultFileNameAppend
        property bool saveInSameDirectory
    }

    Drawer {
        id: drawer
        width: Math.min(window.width * 0.3, 300)
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: "Something"
                width: parent.width
                onClicked: {
                    drawer.close()
                }
            }
            ItemDelegate {
                text: "Something more"
                width: parent.width
                onClicked: {
                    drawer.close()
                }
            }
        }
    }

    // make into 2 tabs? Setup, and Queue?
    ColumnLayout {
        anchors.fill: parent

        TabBar {
            id: bar
            Layout.fillWidth: true

            TabButton {
                text: "Simple"
            }
            TabButton {
                text: "Advanced"
            }
            TabButton {
                text: "Queue"
            }

        }

        // TODO add loading from controls! separate QML files
        StackLayout {

              currentIndex: bar.currentIndex


              Text {
                  anchors.fill: parent

                  text: {
                      return encodeListModel.count
                      //viewModel.encodeViewModel.encodeItems.size()
                  }
              }

              Button {
                  height: 50
                  text: "wow"
                  onClicked: {
                      viewModel.encodeViewModel.startEncode();
                      encodeListModel.setProperty(0, "inputFileName", "xxxxxx")
                      encodeListModel.append({ inputFileName: new Date().toString() })
                  }
              }

              ListView {
                 anchors.fill: parent


                 //model: viewModel.encodeViewModel.encodeItems
                 model: encodeListModel

                 delegate: ItemDelegate {
                     width: parent.width
                            //Layout.fillWidth: true

                         Text {
                             width: parent.width
                             text: inputFileName
                         }
                     }
              }

          }
    }
}
