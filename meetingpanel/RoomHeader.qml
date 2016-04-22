import QtQuick 2.0
import QtQuick.Controls 1.3

Rectangle {
    id: root
    width: 800
    height: 50

    property alias status: meetingStatusText.text
    signal start()
    signal stop()

    function updateStatus(status)
    {

    }

    Rectangle {
        id: rect1
        x: 328
        width: 224
        color: "#00000000"
        anchors.right: parent.right
        anchors.rightMargin: 250
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        Text {
            id: meetingStatusText
            text: qsTr("Unknown")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12
        }
    }

    Button {
        id: button1
        x: 581
        text: qsTr("Start")
        anchors.right: parent.right
        anchors.rightMargin: 134
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10

        onClicked: {
            root.start()
        }
    }

    Button {
        id: button2
        x: 700
        text: qsTr("Stop")
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10

        onClicked: {
            root.stop()
        }

    }
}

