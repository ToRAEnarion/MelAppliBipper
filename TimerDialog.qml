import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QtQuick.Window 2.11
import "formatNumber.js" as Logic

Dialog {
    id: timerDialog
    property TimerModel timerModel

    title: "New Timer"
    modal: true
    standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel

     onAccepted: {}

     onRejected: timerDialog.close()

     contentItem: RowLayout {
         anchors.fill: parent
         RowLayout {
             id: rowTumbler
             anchors.centerIn: parent
             Tumbler {
                 id: hoursTumbler
                 model: 24
                 delegate: TumblerDelegate {
                     text: Logic.formatNumber(modelData)
                 }
             }
             Tumbler {
                 id: minutesTumbler
                 model: 60
                 delegate: TumblerDelegate {
                     text: Logic.formatNumber(modelData)
                 }
             }
             Tumbler {
                 id: secondesTumbler
                 model: 60
                 delegate: TumblerDelegate {
                     text: Logic.formatNumber(modelData)
                 }
             }
         }
     }
}
