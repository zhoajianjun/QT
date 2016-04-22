import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

import "../listener.js" as Logic

Rectangle {

    function currentRoomIndex()
    {
        return tab.currentIndex;
    }
    function currentRoomGroupId()
    {
        if (tab.currentIndex < 0||tab.count==0)
            return null;

        var item = tab.getTab(tab.currentIndex).item;

        if (item == null)
        {
            return null;
        }
        return item.groupId;
    }

    function getCurrentGroupInfo()
    {
        if (tab.currentIndex < 0)
            return null;
        var item = tab.getTab(tab.currentIndex).item;
        if (item == null)
        {
            return null;
        }

        var info = {};
        info.groupId = item.groupId;
        info.status = item.roomStatus;
        info.selection = item.selection;
        info.broadcast = (item.mode === 1);
        return info;
    }

    function onNotify(notice)
    {
        if (notice.class === "vi_attendees")
        {
            onAttendeeNotify(notice, notice.where.groupId);
        }
        else if(notice.class === "attendees")
        {
            onAttendeeNotify(notice, notice.value.groupId);
        }
        else if(notice.class==="tr_cmd")
        {
            onAttendeeNotify(notice,notice.where.groupId)
        }
        else if(notice.app==="voice_level")
        {
            onVoiceAttendeeNotify(notice);
        }
        else
        {
            return;
        }
    }

    function onAttendeeNotify(notice, groupId)
    {
        for (var i = 0 ; i < tab.count; ++i)
        {
            var it = tab.getTab(i).item;
            if (it.groupId === groupId)
            {
                it.onAttendeeNotify(notice);
                return;
            }
        }
    }

    function onVoiceAttendeeNotify(notice)
    {
        var voiceData = notice.data.split("\n");
        for (var k = 0; k < voiceData.length; ++k)
        {
            var l = voiceData[k].split(" ");
            var da = {
                accountId : l[0],
                fromId: l[1],
                voiceLevel:l[2],
            };
            if (l.length >= 4)
            {
                var room = parseInt(l[3]);
                if(tab.count>tab.currentIndex)
                {
                    var it =tab.getTab(room - 1).item;
                    it.onVoiceAttendeeNotify(da);
                }
                else
                {
                    return null;
                }
            }
            else
            {
                for(var i=0;i<tab.count;++i)
                {
                    if(tab.count>tab.currentIndex)
                    {
                        var it1 =tab.getTab(i).item;
                        it1.onVoiceAttendeeNotify(da);
                    }
                    else
                    {
                        return null
                    }
                }
            }
        }
    }

    function changeCurrentGroup(grpId, grpName)
    {
        var item = tab.getTab(tab.currentIndex).item;

        item.changeGroup(grpId, grpName);
    }

    function focusRoom(room)
    {
        if (room >= tab.count)
        {
            room = 0;
        }

        if (tab.currentIndex !== room)
        {
            tab.currentIndex = room;
        }
    }

    function updateRooms(rooms)
    {
        clearRoom();
        for (var i = 0; i < rooms.length; i++)
        {
            console.log("rooms.length:"+rooms.length)
            if ( i < (tab.count - 1))
            {
                var item = tab.getTab(i).item;
                if (item.groupId !== rooms[i].groupId)
                {
                    item.reloadRoom(rooms[i]);
                }
                else
                {
                    item.setRoomStatus(rooms[i].status);
                }
            }
            else
            {
                createMeetingRoom(qsTr("会议室"), i, rooms[i]);
            }
        }
    }

    function setRoomName(roomIndex, name)
    {
        if (roomIndex < tab.count)
        {
            var it = tab.getTab(roomIndex).item;
            it.setRoomName(name);
        }
    }

    function createMeetingRoom(title, i, room)
    {
        var groupId = room.groupId;
        var status = room.status;
        var c = Qt.createComponent("Room.qml");
        var t = tab.addTab(title+ (i+1).toString(), c);
        t.active = true;
        t.item.mode = room.mode;
        t.item.specialIntercom = room.specialIntercom;
        if (groupId)
            t.item.setGroup(groupId, "", status);
        t.item.conferenceIndex = i;
    }

    function clearRoom()
    {
        var count = tab.count;
        for (var i = count-1; i >= 0; i--)
        {
            var item = tab.getTab(i);
            tab.removeTab(i);
            item.destroy();
            item = null;
        }
    }

    function currentRoomCall(person)
    {
        var item = tab.getTab(tab.currentIndex).item;
        item.callAttendee(person);
    }

    function currentRoomBye(person)
    {
        var item = tab.getTab(tab.currentIndex).item;
        item.byeAttendee(person);
    }

    function currentRoomDeaf(person, bDeaf)
    {
        var item = tab.getTab(tab.currentIndex).item;
        item.permissionControl("receiver", person, !bDeaf);
    }

    function currentRoomMute(person, bMute)
    {
        var item = tab.getTab(tab.currentIndex).item;
        item.permissionControl("micGranted", person, !bMute);
    }

    function currentRoomPromote(person, role)
    {
        var item = tab.getTab(tab.currentIndex).item;
        item.controlAttendeeField(person, "role", role);
    }

    function currentRoomSpecialty(person, bEnable)
    {
        var item = tab.getTab(tab.currentIndex).item;
        var value = bEnable ? "1" : "0";
        item.controlAttendeeField(person, "specialIntercom", value);
    }
    Image{
        visible: true
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.leftMargin: 8
        source: "../images/meeting_back_image.png"
    }

    TabView {
        id: tab
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        style: touchStyle
        onCurrentIndexChanged: {
            operate.onFocusRoomChange();
        }
    }

    Component {
        id: touchStyle
        TabViewStyle {
            tabsAlignment: Qt.AlignVCenter
            tabOverlap: 0
            frame:Item {
            }
            tab:Item{
                implicitWidth:control.width/control.count
                implicitHeight: 30
                BorderImage {
                    anchors.fill: parent
                    border.bottom: 20
                    border.top: 20
                    source:
                    {
                        if(styleData.hovered)
                        {
                            return  "../images/meeting_select_image02.png"
                        }
                        if(styleData.selected)
                        {
                            return "../images/meeting_select_image03.png"
                        }
                        else
                        {
                            return "../images/meeting_select_image01.png"
                        }
                    }
                        //styleData.selected ? "../images/meeting.png ":"../images/meeting12.png"
                    Text {
                        anchors.centerIn: parent
                        color: styleData.selected ? "black":"white"
                        text: styleData.title.toUpperCase()
                        font.pixelSize: 16
                    }
                }
            }
        }
    }
}
