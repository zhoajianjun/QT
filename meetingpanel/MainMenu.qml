import QtQuick 2.0

Rectangle {

    signal clicked(int index)

    function currentIndex()
    {
        return myView.currentIndex
    }

    ListModel {
        id: menuModel
        ListElement {
            name: "用户管理"
        }
        ListElement {
            name: "组群管理"
        }
        ListElement {
            name: "会议管理"
        }
    }

    ListView {
        id: myView
        width: parent.width
        height: 400
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        //highlight: Rectangle { z: 1000; color: "lightsteelblue"; radius: 5; opacity: 0.5}
        focus: true
        spacing: 4

        onCurrentIndexChanged: {
            console.log("curIndex is " + currentIndex)
            clicked(currentIndex);
        }

        model: menuModel
        delegate: Rectangle {
            id: rect
            height: 40
            anchors.bottomMargin: 3
            width: parent.width
            color: ListView.isCurrentItem ?  "blue":"#122334"

            Text {
                anchors.centerIn: parent
                color: "white"
                font.pixelSize: 23
                text: qsTr(name)
            }

            MouseArea {
                id: area
                width: parent.width
                height: parent.height
                onClicked: {
                    myView.currentIndex = index
                }
            }
        }
    }
//    states: [
//        State {
//            name: "State1"
//        }
//    ]
}
