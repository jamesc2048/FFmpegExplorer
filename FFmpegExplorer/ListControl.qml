import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

ListView {
    id: mainList
    anchors.margins: 5
    anchors.fill: parent

    property var gridWidths: [100, 200, 100]

    header: null
    footer: null

    ScrollBar.vertical: ScrollBar { }

    //model: [{name: "test1", duration: 100, progress: 50 }, {name: "test2", duration: 100, progress: 40 }]
    model: encoder.encodeModel

    remove: Transition {
        ParallelAnimation {
            NumberAnimation { property: "opacity"; to: 0; duration: 2000 }
            //NumberAnimation { properties: "x,y"; to: 100; duration: 1000 }
        }
    }

    delegate: ListControlDelegate { }
}
