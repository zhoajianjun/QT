import QtQuick 2.0

Rectangle {
    id: root
    width: 200
    height: 50

    property var group

    signal select(var condidate)

    color: "#dedede"

    function addItem(item)
    {
        lmodel.append(item)
    }

    function setGroup(g)
    {
        group = g

        for (var i = 0; i < lmodel.count; i++)
        {
            var grp = lmodel.get(i);
            if (grp.name === g.name)
            {
                listView.currentIndex = i;
            }
        }

        groupText.text = "组: " + g.name;
    }

    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: true

        hoverEnabled: true

        onEntered: {
            //console.log("Enter Menu");
        }
        onExited: {
            //console.log("Exit Menu");
            root.state = "fold"
        }

        Rectangle {
            id: textRect
            x: 0
            y: 0
            width: 200
            height: 50
            color: "steelblue"

            Text {
                id: groupText
                text: qsTr("")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 12
                color: "white"
            }

            MouseArea {
                anchors.fill: parent
                //propagateComposedEvents: true
                onClicked: {
                    if (root.state == "unfold")
                    {
                        root.state = "fold";
                        console.log("fold");
                    }
                    else{
                        root.state = "unfold";
                        console.log("unfold");
                    }
                }
            }
        }
        ListView {
            id: listView
            x:0
            y:50
            height: 1
            width: parent.width
            opacity: 0
            delegate: Item {
                id: t
                x: 0
                width: parent.width
                height: 50
                Rectangle {
                    id: row1
                    //spacing: 10
                        width: parent.width
                        height: 40
                        color: t.ListView.isCurrentItem ? "red" : "grey"

                    Text {
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                    }
                }


                MouseArea {
                    anchors.fill: parent
                    propagateComposedEvents: true

                    hoverEnabled: true
                    onEntered: {
                        //console.log("Enter Row:" + name);
                    }
                    onExited: {
                        //console.log("Exit Row:" + name);
                    }

                    onClicked: {
                        if (index == 0)
                            listView.currentIndex = index;
                        console.log("menuModel[index]" + lmodel.get(index).name);
                        //setGroup(lmodel.get(index));
                        root.select(lmodel.get(index));
                        root.state = "fold";
                    }
                }
            }
            model: ListModel {
                id: lmodel

            }
        }

    }


    states: [
        State {
            name: "unfold"

            PropertyChanges {
                target: listView
                visible: true
                x: 0
                y: 50
                height: 50 * lmodel.count

                anchors.topMargin: 0
                anchors.leftMargin: 0
                opacity: 1
            }

            PropertyChanges {
                target: root
                height: 50 + listView.height
            }
        },
        State {
            name: "fold"

            PropertyChanges{
                target: listView
                visible:false
            }

            PropertyChanges {
                target: root
                height: 50
            }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "height"; easing.type: Easing.Linear }
    }
    Component.onCompleted: {
        state = "fold"
    }
}

