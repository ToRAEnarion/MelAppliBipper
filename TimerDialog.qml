import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QtQuick.Window 2.11
import Qt.labs.folderlistmodel 2.15

import "formatNumber.js" as Logic

Dialog {
    id: timerDialog
    property TimerModel timerModel

    title: "New Timer"
    modal: true
    standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel

     onAccepted: {
         timerModel.append({
             "hour": tumblerHour.currentIndex,
             "minutes": tumblerMinutes.currentIndex,
             "secondes": tumblerSecondes.currentIndex,
             "activated": true,
             "label": timerDescriptionTextField.currentIndex,
         })
     }

     onRejected: timerDialog.close()

     contentItem: ColumnLayout {



         Component {
             id: fileDelegate
             Text { text: fileName }
         }

         ComboBox {
             anchors.top: parent
             model: folderModel
             textRole: 'fileName'
//             delegate: fileDelegate
//             model: ["First", "Second", "Third"]

             FolderListModel {
                 id: folderModel
                 nameFilters: ["*.wav"]
             }
         }
         RowLayout {
             id: rowTumbler
             MyTumblerStyle{
                 id: tumblerHour
                 model:24
             }
             MyTumblerStyle{
                 id: tumblerMinutes
                 model:60
             }
             MyTumblerStyle{
                 id: tumblerSecondes
                 model:60
             }
         }

         TextField {
             id: timerDescriptionTextField
             anchors.bottom: parent
             placeholderText: qsTr("description")
             cursorVisible: true
         }

     }
}

