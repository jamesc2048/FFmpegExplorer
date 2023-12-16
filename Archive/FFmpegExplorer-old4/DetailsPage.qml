import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    property var model

    Component.onCompleted: console.log(JSON.stringify(model))

    ScrollView {
        anchors.fill: parent

        ColumnLayout {
            Text {
                text: model.filePath
            }

            RowLayout {
                TextInput {
                    text: model.startTrim.toFixed(2)
                }

                RangeSlider {
                    // range should go from video start to video duration
                    from: 0
                    to: 100

                    first.value: model.startTrim
                    first.onMoved: {
                        console.log(first.value)
                        model.startTrim = first.value
                    }

                    second.value: model.endTrim
                    second.onMoved: {
                        console.log(second.value)
                        model.endTrim = second.value
                        model.duration = model.endTrim - model.startTrim
                    }
                }

                TextInput {
                    text: model.endTrim.toFixed(2)
                }
            }
        }
    }
}
