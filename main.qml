import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

ApplicationWindow {
    id:window
      visible: true
          width: 640
          height: 480

      GridLayout {
          anchors.fill: parent
          rows: 3
          columns: 3

            Rectangle {
                id: view_A
                color: "yellow"
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 1
                Layout.rowSpan: 1

                GroupBox {
                    anchors.fill: parent
                    title: qsTr("Cycle")
                    checkable: true;
                    RowLayout {
                        anchors.fill: parent
                        Tumbler {
                            id: tumblerCycle
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            anchors.centerIn: parent
                            model: 100
                        }
                    }
                }
            }

            Rectangle {
                id: view_B
                color: "blue"
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 2
                Layout.rowSpan: 1
                Layout.row: 0
                Layout.column: 1

                GroupBox {
                    anchors.fill: parent
                    title: qsTr("Cycle")
                    checkable: true;
                    RowLayout {
                        anchors.fill: parent
                        Tumbler {
                            id: tumblerHour
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            model:24
                        }
                        Tumbler{
                            id: tumblerMinutes
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            model:60
                        }
                        Tumbler{
                            id: tumblerSecondes
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            model:60
                        }
                    }
                }
            }

          Rectangle {
              id: view_C
              color: "blueviolet"
              Layout.fillHeight: true
              Layout.fillWidth: true
              Layout.columnSpan: 3
              Layout.row: 1
              ColumnLayout{
                  anchors.fill: parent
                  ListView {
                      id: timerListView
                      Layout.rightMargin: 50
                      Layout.fillHeight: true
                      Layout.fillWidth: true
                      model: TimerModel{}
                  }
                  RoundButton {
                      id: addTimerButton
                      text: "+"
                      anchors.bottom: timerListView.bottom
                      anchors.bottomMargin: 8
                      anchors.horizontalCenter: parent.horizontalCenter
                      onClicked: timerDialog.open()
                  }
              }
          }

         Rectangle {
              id: view_D
              color: "red"
              Layout.fillHeight: true
              Layout.fillWidth: true
              Layout.columnSpan: 3
              Layout.row: 2
              Text { text: "view_D" ; anchors.centerIn: parent }
         }

         TimerDialog {
             id: timerDialog
             x: Math.round((parent.width - width) / 2)
             y: Math.round((parent.height - height) / 2)
             timerModel: timerListView.model
         }
      }
}


//    GridLayout {
//        id:grid
//        rows: 4
//        columns: 3
//        anchors.fill: parent

//        Rectangle { // row 0- column 0 <-> column 4
//            id:timer_grid
//            color: "blue"
//            Layout.fillHeight: true
//            Layout.fillWidth: true
//            Layout.row: 1
//            Layout.column: 2
//            Layout.margins: 10
//        }

//        Rectangle {
//            color: "yellow"

//            Layout.row: 2
//            Layout.column: 2
//        RowLayout {

//            spacing: 5

//        Button {
//              id: playpause_button

//              objectName: "button"
//              text: qsTr("Button")
//              checkable: true
//              onClicked: {
//                  bipperManager.switchIsPlaying()
//                  playpause_button.text = bipperManager.IsPlaying ? "pause" : "play"
//                  bipperManager.playSound(-1)
//              }
//          }
//        Button {
//              id: reset_buton

//              objectName: "reset_button"
//              text: qsTr("reset")
//              checkable: true
//              onClicked: {
//                  bipperManager.switchIsPlaying()
//                  bipperManager.playSound(1)
//              }
//          }
//        }

//        }

//    }

