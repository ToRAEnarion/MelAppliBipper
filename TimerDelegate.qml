import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.11
import QtQuick.Window 2.11


ItemDelegate {
    id: root
    width: parent.width
    checkable: true
    onClicked: ListView.view.currentIndex = index
    contentItem:
        ColumnLayout {
        spacing: 0
        RowLayout {
            ColumnLayout {

                id: timerColumn
                readonly property date alarmTime: new Date(model.hour, model.minutes,model.secondes)

                Label {
                    id: timeLabel
                    font.pixelSize: Qt.application.font.pixelSize*1.5
                    //text:"toto"
                    text: timerColumn.alarmTime.toLocaleTimeString(window.locale, Locale.ShortFormat)
                }
                RowLayout {
                    Label {
                        id: alarmAbout
                        text: "⸱ " + model.label
                        visible: model.label.length > 0 && !root.checked
                    }
                }
            }/*
            Item {
                Layout.fillWidth: true
            }*/
            Switch {
                checked: model.activated
                Layout.alignment: Qt.AlignTop
                onClicked: model.activated = checked
            }
        }
        CheckBox {
            id: alarmRepeat
            text: qsTr("Combobox sound todo")

            visible: root.checked
            onToggled: model.repeat = checked
        }
//        Flow {
//            visible: root.checked && model.repeat
//            Layout.fillWidth: true
//        }

        TextField {
            id: alarmDescriptionTextField
            placeholderText: qsTr("Enter description here")
            cursorVisible: true
            visible: root.checked
            text: model.label
            onTextEdited: model.label = text
        }
        Button {
            id: deleteAlarmButton
            text: qsTr("Delete")
//            width: 20
//            height: 20
            visible: root.checked
            onClicked: root.ListView.view.model.remove(root.ListView.view.currentIndex, 1)
        }
    }
}
