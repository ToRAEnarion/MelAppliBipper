import QtQuick 2.12
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.12

import Chronometer 1.0
import MelAppliBipper.CppTypes 0.1

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
                Layout.fillHeight: true
                Layout.fillWidth: true

                GridLayout{
                    columns: 2
                    anchors.fill: parent                    
                    ExclusiveGroup { id: tabPositionGroup }
                    Rectangle {
                        border.color: Material.color(Material.Grey)
                        radius: 9
                        Layout.fillHeight: true; Layout.fillWidth: true
                        ColumnLayout {
                            anchors.fill: parent
                            RadioButton {
                                id: cycleRadioButton
                                Layout.margins: 5
                                exclusiveGroup: tabPositionGroup
                                text: "Cycle"
                                style: MyRadioButtonStyle{}
                            }
                                MyTumblerStyle{
                                    id: tumblerCycle
                                    Layout.fillWidth: false
                                    anchors.centerIn: parent
                                    model: 100
                                    enabled: cycleRadioButton.checked
                                }
                        }
                    }

                    Rectangle {
                        border.color: Material.color(Material.Grey)
                        radius: 9
                        Layout.fillHeight: true; Layout.fillWidth: true ;  Layout.row: 0;Layout.column: 1
                        ColumnLayout {
                            anchors.fill: parent
                            RadioButton {
                                exclusiveGroup: tabPositionGroup
                                checked: true
                                id: durationRadioButton
                                Layout.margins: 5
                                text:"Durée"
                                style: MyRadioButtonStyle{}
                            }
                            RowLayout {
                                enabled: durationRadioButton.checked
                                anchors.centerIn: parent
                                MyTumblerStyle{
                                    id: tumblerHour
                                    model:24                                    
                                    onCurrentIndexChanged: {bipperManager.MaxTime = tumblerHour.currentIndex*60*24 + tumblerMinutes.currentIndex*60 + tumblerSecondes.currentIndex}
                                }
                                MyTumblerStyle{
                                    id: tumblerMinutes
                                    model:60
                                    onCurrentIndexChanged: {bipperManager.MaxTime = tumblerHour.currentIndex*60*24 + tumblerMinutes.currentIndex*60 + tumblerSecondes.currentIndex}
                                }
                                MyTumblerStyle{
                                    id: tumblerSecondes
                                    model:60
                                    onCurrentIndexChanged: {bipperManager.MaxTime = tumblerHour.currentIndex*60*24 + tumblerMinutes.currentIndex*60 + tumblerSecondes.currentIndex}
                                }
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            id: view_C
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.columnSpan: 3; Layout.row: 1
            RowLayout{
                anchors.fill: parent
                spacing: 5

                ListView {
                    id: timerListView
                    clip:true
                    anchors.fill: parent
                    model: TimerModel{} // MODEL DOIT ETR CELUI DE BENJ
                    delegate: TimerDelegate{}
                }
                RoundButton {
                    id: addTimerButton
                    text: "+"
                    //icon.source: "/icons/add"
                    anchors.right: parent.right
                    anchors.rightMargin: 5
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
        TimerDialog {
            id: timerDialog
            x: Math.round((parent.width - width) / 2)
            y: Math.round((parent.height - height) / 2)
            timerModel: timerListView.model // une fonction de bennj qui rempli la listview ? MODEL DOIT ETRE CELUI DE BENJ https://www.youtube.com/watch?v=9BcAYDlpuT8
        }

        Rectangle {
            id: chronometerDisplay; Layout.fillHeight: true; Layout.fillWidth: true; Layout.columnSpan: 3; Layout.row: 2
            Chronometer {
                id: chronometer
                // Set its positioning and dimensions
                anchors.centerIn: parent
                width: 150
                height: 150

                // Determine the properties that Q_PROPERTY
                name: "chronometer"
                backgroundColor: "whiteSmoke"
                borderActiveColor: Material.color(Material.DeepOrange)
                borderNonActiveColor: Material.color(Material.Teal)
                completeTime: bipperManager.CompleteCycleTime
                currentTime: bipperManager.CurrentTime

                // Add the text that will be put up timer
                Text {
                    id: textTimer
                    anchors.centerIn: chronometer
                    font.bold: true
                    font.pixelSize: 15
                }

                // If you change the time, put the time on the timer ??
                onCircleTimeChanged: {
                    textTimer.text = Qt.formatTime(circleTime, "hh:mm:ss")
                }
            }
            RoundButton {
                id: startstop_button
                anchors.left: parent.left
                anchors.topMargin: 5
                anchors.leftMargin: 5
                text: bipperManager.IsPlaying ? "Pause" : "Start"
                onClicked: {
                    bipperManager.switchIsPlaying()
                }
            }
            RoundButton {
                id: clear
                text: "Clear"
                onClicked: bipperManager.onResetTriggered()
                anchors.right: parent.right
                anchors.topMargin: 5
                anchors.rightMargin: 5
            }
        }
    }
}


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


