import QtQuick 2.0
import QtQuick.Controls.Styles 1.4


 RadioButtonStyle {
     indicator: Rectangle {
        implicitWidth: 16
        implicitHeight: 16
        radius: 8
        border.color: control.activeFocus ? "#009688" : "#009688"
        border.width: 1

        Rectangle {
            anchors.fill: parent
            visible: control.checked
            color: "#009688"
            radius: 8
            anchors.margins: 4
        }
    }
 }


