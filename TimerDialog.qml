import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QtQuick.Window 2.11

Dialog {
    id: timerDialog
    property TimerModel timerModel
    title: "Add new alarm"
    modal: true
    standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel
}
