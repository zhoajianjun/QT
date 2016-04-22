import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

BorderImage {
    source: "../images/meeting_back_image.png"
    width: parent.width
    //color: "#7d8f9c"
    height: 30

    RowLayout{
        anchors.left:parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        spacing: 8

        Text {
            text: qsTr("时间")
            verticalAlignment: Text.AlignVCenter
            color: "white"
            font.bold: true
            font.pixelSize: 15
            anchors.verticalCenter: parent.verticalCenter
            Layout.preferredWidth: 200
        }
        Text {
            text: qsTr("事件")
            color:"white"
            font.bold: true
            font.pixelSize: 15
            anchors.verticalCenter: parent.verticalCenter
            Layout.preferredWidth: 120
        }
        Text {
            id: name
            width: 343
            text: qsTr("描述")
            verticalAlignment: Text.AlignVCenter
            color:"white"
            font.bold: true
            font.pixelSize: 15
            anchors.verticalCenter: parent.verticalCenter
            Layout.preferredWidth: 362
        }
    }
}

