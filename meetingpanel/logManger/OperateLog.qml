import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Rectangle {
    id:titleRect
    width: 100
    height: 30
    color: "#315980"
    BorderImage {
        source: "../images/meeting_back_image.png"
        width: parent.width
        height: 30

        RowLayout{
            id: rowLayout1
            anchors.left:parent.left
            anchors.leftMargin: 10
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter
            spacing: 8

            Text {
                id:startMeetingTimeText
                text: qsTr("开始时间")
                color: "white"
                font.bold: true
                font.pixelSize: 15
                anchors.verticalCenter: parent.verticalCenter
                Layout.preferredWidth: (parent.width-10)/3
            }

            Text {
                id:meetingRoomIndex
                text: qsTr("会议室")
                color: "white"
                font.bold: true
                font.pixelSize: 15
                anchors.verticalCenter: parent.verticalCenter
                Layout.preferredWidth: (parent.width-10)/4
            }
            Text {
                text: qsTr("用户组")
                color: "white"
                font.bold: true
                font.pixelSize: 15
                anchors.verticalCenter: parent.verticalCenter
                Layout.preferredWidth: (parent.width-10)/3
            }
        }
    }
}
