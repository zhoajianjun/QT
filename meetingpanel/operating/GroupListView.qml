import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
Item {  
    id: root
    width: 300
    height: 300
    property var focusGroupId;
    property bool groupSelect: false
    property int currentRoom

    function clear()
    {
        lmodel.clear();
    }

    function updateGroup(grpId, roomIndex, status)
    {
        for (var i = 0; i < lmodel.count; i++)
        {
            var grp = lmodel.get(i);
            if (grp.groupId === grpId)
            {
                grp.room = roomIndex;
                grp.running = (status === "running");
                break;
            }
        }
    }

    function setGroups(grps, currentId)
    {
        lmodel.clear();
        for (var i = 0; i < grps.length; i++)
        {
            lmodel.append(grps[i]);
        }
        focusGroupId = currentId;
    }



    BorderImage {
        id: grouplistimage
        x: 0
        height: 50
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        source: "../images/list.png"
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("群列表")
            anchors.centerIn: parent
            color: "#eeeeee"
        }
    }

    ListModel {
        id: lmodel
    }
    Rectangle{
        id: rectangle1
        x: 0
        y: 50
        width: parent.width
        anchors.top:grouplistimage.bottom
        anchors.bottom: parent.bottom
        height: parent.height
        color: "#7d8f9c"

        ScrollView{
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 8
            style: ScrollViewStyle {
                handle: Item{
                    implicitWidth: 12
                    implicitHeight: 12
                    Rectangle {
                        color: "#425e7b"
                        anchors.fill: parent
                        visible: true
                    }
                }
                decrementControl:Image{
                    width:12
                    height: 12
                    source: "../images/arrow_up.png"
                }
                incrementControl:Image{
                    width:12
                    height: 12
                    source: "../images/arrow_down.png"
                }
                scrollBarBackground: Item {
                    implicitWidth: 12
                    implicitHeight: 12
                }
            }

            ListView {
                id: listView
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                anchors.bottomMargin: 0
                anchors.topMargin: 0
                model: lmodel

                delegate:  Item {
                    id: it
                    width: parent.width
                    height: 35

                    Image{
                        id:grouplistrect
                        width: parent.width
                        height: parent.height
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.rightMargin: 2
                        source: groupId === focusGroupId ?"../images/list_current_image.png":"../images/list_back_image.png"
                        Text {
                            anchors.verticalCenter: grouplistrect.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 60
                            width: grouplistrect.width
                            height: 35
                            text: (room >= 0 ? name + "(会议室"+ (room+1).toString() + ")" : name)
                            elide: Text.ElideMiddle
                            color: groupId === focusGroupId ? "white" : "black"
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {

                        }
                        onDoubleClicked: {
                            listView.currentIndex = index
                            var grp = lmodel.get(index);
                            if (grp.room >= 0)
                            {
//                                root.currentRoom=room;
                                operate.focusRoom(room);
                            }
                            else
                            {
                                operate.changeCurrentGroup(grp.groupId, grp.name);
                            }
                        }
                    }
                }
            }
        }
    }
}

