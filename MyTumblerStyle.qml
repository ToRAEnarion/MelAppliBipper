import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.12
import "formatNumber.js" as Logic

Tumbler {
    id:tumbler
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.margins: 5
    delegate: TumblerDelegate {text: Logic.formatNumber(modelData) }

    Rectangle {
          anchors.horizontalCenter: tumbler.horizontalCenter
          y: tumbler.height * 0.4
          width: tumbler.width*0.5
          height: 1
          color: Material.color(Material.DeepOrange)
      }
      Rectangle {
          anchors.horizontalCenter: tumbler.horizontalCenter
          y: tumbler.height * 0.6
          width: tumbler.width * 0.5
          height: 1
          color: Material.color(Material.DeepOrange)
      }
}
