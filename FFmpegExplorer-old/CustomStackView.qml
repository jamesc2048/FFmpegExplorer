import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

StackView {
    pushEnter: Transition {
              PropertyAnimation {
                  property: "opacity"
                  from: 0
                  to: 1
                  duration: 1000
              }
          }

    pushExit: Transition {
        PropertyAnimation {
            property: "opacity"
            from: 1
            to: 0
            duration: 1000
        }
    }

    popEnter: Transition {
        PropertyAnimation {
            property: "opacity"
            from: 0
            to: 1
            duration: 1000
        }
    }

    popExit: Transition {
      PropertyAnimation {
          property: "opacity"
          from: 1
          to: 0
          duration: 1000
      }
  }
}
