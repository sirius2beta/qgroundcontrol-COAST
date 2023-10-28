import QtQuick 2.15

import QGroundControl   1.0
import QGroundControl.Controls  1.0
import QGroundControl.ScreenTools   1.0
import Rockit 1.0


Rectangle {
    id: _root
    width:300
    height:100
    visible: true
    radius: 5

    Rectangle{
        id:boxTitle
        height:25
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        color: "#555555"
        radius: 5
        Rectangle{
            anchors.bottom: boxTitle.bottom
            anchors.left: boxTitle.left
            width: boxTitle.width
            height:5
            color: "#555555"
        }

        QGCLabel{
            text: qsTr("AutoConnectTool")
            anchors.verticalCenter: boxTitle.verticalCenter
            anchors.left: boxTitle.left
            anchors.leftMargin: 10
        }

    }

    QGCLabel{
        id: ipLabel
        anchors.left: parent.left
        anchors.margins: 5
        anchors.topMargin: 15
        anchors.top: boxTitle.bottom
        text:   qsTr("IP")
    }

    QGCTextField{
        id: ipField
        anchors.left: ipLabel.right
        anchors.right: connectButton.left
        anchors.margins: 5
        anchors.topMargin: 10
        anchors.verticalCenter: ipLabel.verticalCenter
        KeyNavigation.tab: connectButton
        text: QGroundControl.autoConnectTool.targetIP


    }

    QGCButton {
        id:                 connectButton
        anchors.right: parent.right
        anchors.verticalCenter: ipLabel.verticalCenter
        anchors.margins: 5
        anchors.topMargin: 10
        text:               qsTr("Connect")
        activeFocusOnTab: true
        onClicked: {
            QGroundControl.autoConnectTool.targetIP = ipField.text
        }
    }
}
