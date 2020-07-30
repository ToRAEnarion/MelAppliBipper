import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import MelAppliBipper.CppTypes 0.1
import "formatNumber.js" as Logic

ApplicationWindow {
    id:window
    visible: true
    width: 640
    height: 480

    BipperManager {
        id: bipperManager
    }

    GridLayout {
        anchors.fill: parent
        rows: 3
        columns: 3
        Rectangle {
            id: view_A
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 3
            Layout.row: 0
            GroupBox {
                id:paramGroupBox
                anchors.fill: parent
                anchors.margins: 5
                title: qsTr("Paramètres")
                Layout.fillHeight: true
                Layout.fillWidth: true

                GridLayout{
                    columns: 2
                    anchors.fill: parent
                    ExclusiveGroup { id: tabPositionGroup }
                    Rectangle {
                        color: "darkseagreen";  Layout.fillHeight: true; Layout.fillWidth: true

                        ColumnLayout {
                            anchors.fill: parent
                            RadioButton {
                                id: cycleRadioButton
                                text: "Cycle"
                                exclusiveGroup: tabPositionGroup
                            }
                            RowLayout {
                                Tumbler {
                                    id: tumblerCycle
                                    enabled: cycleRadioButton.checked
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    anchors.centerIn: parent
                                    model: 100
                                    delegate: TumblerDelegate {text: Logic.formatNumber(modelData)}
                                }
                            }
                        }
                    }

                    Rectangle {
                        color: "darkseagreen"; Layout.fillHeight: true; Layout.fillWidth: true ;  Layout.row: 0;Layout.column: 1
                        ColumnLayout {
                            anchors.fill: parent
                            RadioButton {
                                id: durationRadioButton
                                text:"Durée"
                                exclusiveGroup: tabPositionGroup
                            }
                            RowLayout {
                                enabled: durationRadioButton.checked
                                Tumbler {
                                    id: tumblerHour
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    model:24
                                    delegate: TumblerDelegate {text: Logic.formatNumber(modelData)}
                                }
                                Tumbler{
                                    id: tumblerMinutes
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    model:60
                                    delegate: TumblerDelegate {text: Logic.formatNumber(modelData)}
                                }
                                Tumbler{
                                    id: tumblerSecondes
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    model:60
                                    delegate: TumblerDelegate {text: Logic.formatNumber(modelData)}
                                }
                            }
                        }
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
            RowLayout{
                anchors.fill: parent
                ListView {
                    id: timerListView
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    model: TimerModel{} // MODEL DOIT ETR CELUI DE BENJ
                }
                RoundButton {
                    id: addTimerButton
                    text:"+"
                    //icon.source: "resources.qrc:/icons/addIcon.png"
                    //icon.name: "add"
                    icon.height: height
                    icon.width: width
                    onClicked: {
                        onClicked: timerDialog.open()
                        //bipperManager.switchIsPlaying()
                        //addTimerButton.text="add"
                        //addTimerButton.text = bipperManager.IsPlaying ? "pause" : "play"
                        //bipperManager.playSound(-1)
                    }
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
            timerModel: timerListView.model // une fonction de bennj qui rempli la listview ? MODEL DOIT ETRE CELUI DE BENJ https://www.youtube.com/watch?v=9BcAYDlpuT8
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


