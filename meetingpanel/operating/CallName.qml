import QtQuick 2.3
import QtQuick.Controls 1.2

Item {
    id:btn
    anchors.centerIn: parent
    width: 100
    height: 50
    clip: true
    opacity: 1
    Image {
        id: name
        x: 0
        y: 0
        width: 100
        height: 50
        source: "../images/hei.png"
        Image {
            id: name1
            x: 3
            y: 8
            width: 29
            height: 34
           // source: ../images/yueji .svg"
        }

        Text {
            id: text1
            x: 33
            y: 8
            width: 67
            height: 34
            color: "#FFFAF0"
            text: qsTr("点名")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 20
        }
    }
    MouseArea {
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        clip:true
        anchors.fill: parent
        onClicked: btn.state == 'clicked' ? btn.state = "" : btn.state = 'clicked';
       // onContainsMouseChanged: btn.state == 'clicked' ? btn.state = "" : btn.state = 'clicked';

    }

    states: [
        State {
            name: "clicked"
            PropertyChanges { target: name;source:"../images/jianbian.png"                     }

        }
    ]
}
