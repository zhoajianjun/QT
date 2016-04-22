import QtQuick 2.0

Item {
    anchors.fill: parent

    property string toolTip
    property bool showToolTip: false
    property int space: 0;

    Rectangle {
        id: toolTipRectangle

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top ;
        anchors.topMargin: -space;
        //anchors.top: parent.bottom
        width: toolTipText.width + 4
        height: toolTipText.height + 4
        z: 200

        opacity: toolTip != "" && showToolTip ? 1 : 0

        color:"#315980" //"#ffffaa"  //"#315980";
        //border.color: "#0a0a0a"

        Text {
            //z: 200
            id: toolTipText
            text: toolTip
            //color: "black"
            color:"white";
            anchors.centerIn: parent
        }

        Behavior on opacity {
            PropertyAnimation {
                easing.type: Easing.InOutQuad
                duration: 250
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onEntered: showTimer.start()
        onExited: { showToolTip = false; showTimer.stop(); }
        hoverEnabled: true
    }

    Timer {
        id: showTimer
        interval: 250
        onTriggered: showToolTip = true;
    }
}
