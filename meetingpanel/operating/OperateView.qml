import QtQuick 2.0

import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
//import readfile 1.0

import "../listener.js" as Logic

Item {
    id:root
    width: 100
    height: 60
    property var person
    property var groupList
    property string errorstring
    property var meetingRooms:[];
    property var manyPerson: []
    property var personLength
    property int flag: 0
    property int currentGroupId

    //room { index, groupId, status}
    function onNotify(notice)
    {
        if (notice.class === "vi_attendees")
        {
            roomView.onNotify(notice);
        }
        else if(notice.class==="attendees")
        {
            roomView.onNotify(notice);
        }
        else if(notice.class==="tr_cmd")
        {
            roomView.onNotify(notice);
        }
        else if(notice.app==="voice_level")
        {
            roomView.onVoiceAttendeeNotify(notice);
        }
        else
        {

        }
    }

    function currentRoomGroupId()
    {
        return roomView.currentRoomGroupId();
    }

    function onFocusRoomChange()
    {
        var room = roomView.currentRoomIndex();
        var grpId = roomView.currentRoomGroupId();
        currentGroupId=grpId;

        //TODO:
        groupListView.focusGroupId = grpId;
        var info = roomView.getCurrentGroupInfo();
        if (!info)
        {
            commandRect.setPerson(null, "idle");
            userInfoView.updatePerson(null);
        }
        else
        {
            onSelectedAttendeeChange(info.groupId, info.status, info.selection)
            commandRect.broadcast = info.broadcast;
        }
    }

    function load()
    {
        var curIndex = roomView.currentRoomIndex();

        roomView.clearRoom();
        groupListView.clear();
        commandRect.setPerson(null, "idle");
        Logic.queryRooms(
                    onGetRooms,
                    function(){

                roomView.focusRoom(curIndex);
            });
    }

    function onGetRooms(rooms, post_handler)
    {
        meetingRooms = rooms;
        roomView.updateRooms(rooms);
        Logic.queryGroups(onGetGroups, post_handler);
    }

    function onGetGroups(grps, post_handler)
    {
        fillGroupList(grps);
        setAllRoomName();
        groupListView.setGroups(groupList, currentRoomGroupId());
        if (post_handler)
        {
            post_handler();
        }
    }

    function changeCurrentGroup(grpId, grpName)
    {
        if (grpId !== currentRoomGroupId())
        {
            roomView.changeCurrentGroup(grpId, grpName);
        }
    }

    function focusRoom(room)
    {
        roomView.focusRoom(room);
    }


    function getRoomOfGroup(grpId)
    {
        for (var i = 0; i < meetingRooms.length; ++i)
        {
            if (meetingRooms[i].groupId === grpId)
            {
                console.log("group" + grpId + " in room " + i);
                var it = {
                    index: i,
                    groupId: grpId,
                    name: meetingRooms[i].name
                };
                return it;
            }
        }
        return null;
    }


    function fillGroupList(grps)
    {
        groupList = [];
        for (var i = 0; i < grps.length; ++i)
        {
            var grp = grps[i];
            var rm = getRoomOfGroup(grp.groupId);
            var index = rm ? rm.index : -1;
            var run = rm ? rm.running === "running" : false;
            var it = {
                groupId: grp.groupId,
                name: grp.name,
                room: index,
                running: run
            }
            groupList.push(it);
        }
    }

    function setAllRoomName()
    {
        for (var i = 0; i < meetingRooms.length; i++)
        {
            //TODO: groupList find all rooms.
            var roomIndex = i;
            var name = "";

            var grpId = meetingRooms[i].groupId;
            for (var j = 0; j < groupList.length; j++)
            {
                if (grpId === groupList[j].groupId)
                {
                    name = groupList[j].name;
                    break;
                }
            }
            roomView.setRoomName(roomIndex, name);
        }
    }
    function commandercount(count)
    {
        flag=count
    }


    function onSelectedAttendeeChange(groupId, status, selection)
    {
        if (groupId == currentRoomGroupId())
        {

            if (selection.length == 1)
            {
                userInfoView.updatePerson(selection[0]);
                commandRect.setPerson(selection[0], status)
                personLength=selection.length
            }
            else if (selection.length == 0)
            {
                userInfoView.updatePerson(null);
                commandRect.setPerson(null, status);
            }
            else if(selection.length>1)
            {
                for(var i=0;i<selection.length;++i)
                {
                    userInfoView.updatePerson(selection[i]);
                    commandRect.setPerson(selection[i],status)
                }
                manyPerson=selection;
                personLength=selection.length
            }
        }
    }

    function onRoomBroadcastChange(groupId, broadCast)
    {
        if (groupId === currentRoomGroupId())
        {
            commandRect.broadcast = broadCast;
        }
    }

    function onNotifyGroupChange(roomIndex, grpId, status)
    {
        for (var i = 0; groupList.length; i++)
        {
            var grp = groupList[i];
            if (grp.groupId === grpId)
            {
                grp.status = status;
                grp.index = roomIndex;
                break;
            }
        }
        groupListView.updateGroup(grpId, roomIndex, status);
    }

    function getuserconfig()
    {
        var userconf=mainWin.readjson();
        return userconf.mainTitle;
    }
    function setDateTime(){
        var today = new Date();
        var year = today.getFullYear();
        var month = today.getMonth() + 1;
        var nowday = today.getDate();
        var hours = today.getHours();
        var minutes = today.getMinutes();
        var seconds = today.getSeconds();
        textEdit2.text=standardOutput(hours)+ ":" +standardOutput(minutes) + ":" + standardOutput(seconds)
    }
    function standardOutput(value){
        return value < 10 ? ("0" + value) : value
    }
    function showErrorMessage(message)
    {
        errorstring=message;
    }

    Timer{
        id:updateTime
        running: false
        repeat: false
        interval: 3000
        onTriggered: {
            commanderMessage.close();
            updateTime.running=false
            commanderItem.checked=false
        }
    }

    Text {
        id: errorMessage
        text: errorstring
        anchors.left: parent.left
        anchors.leftMargin: 300
        anchors.top:parent.top
        anchors.topMargin: 60
        color: "red"
        font.pixelSize: 15
    }
    MessageDialog {
        id: messageDialog
        modality: Qt.ApplicationModal
        title: "退出"
        text: "确定要退出此程序吗?"
        standardButtons: StandardButton.Ok | StandardButton.No
        onAccepted: {
            console.log("And of course you could only agree.")
            Qt.quit()
        }
        onRejected: {
            messageDialog.close()
        }
    }

    Item {
        id: headerRect
        height: 110

        Text {
            id: mainTitleText
            text: "指挥调度系统"
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top:parent.top
            anchors.topMargin: 29
            color: "white"
            font.pixelSize: 30
        }

        Image{
            id:exitsystem;
            anchors.right: parent.right;
            anchors.rightMargin: 20
            anchors.top: parent.top;
            anchors.topMargin: 27
            source:"../images/quitsystem01.png";
            fillMode: Image.PreserveAspectCrop;
            MouseArea{
                id:exitMouserArea
                anchors.fill: parent
                hoverEnabled: true;
                onEntered:exitsystem.source = "../images/quitsystem02.png";
                onExited:  exitsystem.source = "../images/quitsystem01.png";
                onClicked: {
                    messageDialog.open();
                }
                onReleased: {
                    exitsystem.state == "clicked"
                }
            }
            states: [
                State {
                    name: "clicked"
                    PropertyChanges { target: exitsystem;source:"../images/quitsystem01.png"}
                },
                State {
                    name: "unclicked"
                    when: exitMouserArea.pressed
                    PropertyChanges { target: exitsystem;source:"../images/quitsystem03.png" }
                }
            ]
            state: "clicked"

        }
        Image{
            id:refreshbtn;
            anchors.right: logMangerbtn.left;
            anchors.rightMargin: 10
            anchors.top: parent.top;
            anchors.topMargin: 27
            source:"../images/refresh01.png";
            fillMode: Image.PreserveAspectCrop;
            MouseArea{
                id:refreshmouserArea
                anchors.fill: parent
                hoverEnabled: true;
                onEntered:refreshbtn.source = "../images/refresh02.png";
                onExited:  refreshbtn.source = "../images/refresh01.png";
                onClicked: {
                    refreshbtn.state == "clicked" ? refreshbtn.state = "unclicked" : refreshbtn.state = "clicked";
                    root.load();
                }
                onReleased: {
                    refreshbtn.state == "clicked"
                }
            }
            states: [
                State {
                    name: "clicked"
                    PropertyChanges { target: refreshbtn;source:"../images/refresh01.png"}
                },
                State {
                    name: "unclicked"
                    when: refreshmouserArea.pressed
                    PropertyChanges { target: refreshbtn;source:"../images/refresh03.png"  }
                }
            ]
            state: "clicked"

        }
        Image{
            id:userMangerbtn;
            anchors.right: exitsystem.left;
            anchors.rightMargin: 10
            anchors.top: parent.top;
            anchors.topMargin: 27
            source:"../images/userManger01.png";
            fillMode: Image.PreserveAspectCrop;
            MouseArea{
                id:userMangerMouseArea
                anchors.fill: parent
                hoverEnabled: true;
                onEntered:userMangerbtn.source = "../images/userManger02.png";
                onExited:  userMangerbtn.source = "../images/userManger01.png";
                onClicked: {
                    userMangerbtn.state == "clicked" ? userMangerbtn.state = "unclicked" : userMangerbtn.state = "clicked";
                    work.showUserManagePage();
                }
                onReleased: {
                    userMangerbtn.state == "clicked"
                }
            }
            states: [
                State {
                    name: "clicked"
                    PropertyChanges { target: userMangerbtn;source:"../images/userManger01.png"}
                },
                State {
                    name: "unclicked"
                    when: userMangerMouseArea.pressed
                    PropertyChanges { target: userMangerbtn;source:"../images/userManger03.png"  }
                }
            ]

            state: "clicked"
        }
        Image{
            id:logMangerbtn;
            anchors.right: userMangerbtn.left;
            anchors.rightMargin: 10
            anchors.top: parent.top;
            anchors.topMargin: 27
            //source:"../images/logManger01.png";
            fillMode: Image.PreserveAspectCrop;
            MouseArea{
                id:logMouseArea
                anchors.fill: parent
                hoverEnabled: true;
                onEntered:logMangerbtn.source = "../images/logManger02.png";
                onExited:  logMangerbtn.source = "../images/logManger01.png";
                onClicked: {
                    work.showlogMangerPage()
                }
                onReleased: {
                    logMouseArea.state == "clicked"
                }
            }
            states: [
                State {
                    name: "clicked"

                    PropertyChanges { target: logMangerbtn;source:"../images/logManger01.png"}
                },
                State {
                    name: "unclicked"
                    when: logMouseArea.pressed
                    PropertyChanges { target: logMangerbtn;source:"../images/logManger.png"  }
                }
            ]
            state: "clicked"
        }

        Item{
            id:timeItem
            width:197
            height: 50
            anchors.right: refreshbtn.left
            anchors.rightMargin: 45
            anchors.top: parent.top
            anchors.topMargin: 25
            Text {
                id: timetext
                x: 0
                y: 0
                width: 83
                height: 50

                color: "white"
                text: "当前时间: "
                font.bold: true
                font.pointSize: 13
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter

            }
            TextEdit {
                id: textEdit2
                x: 83
                y: 10
                width: 106
                height: 32
                text: ""
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 13
                color: "white"
            }


            Timer{
                interval: 500
                running: true
                repeat: true
                onTriggered:{
                    setDateTime()
                }
            }

        }



        Component.onCompleted: {
            mainTitleText.text=getuserconfig();
        }
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    SplitView {
        handleDelegate: Rectangle{
            width: 8
            height: 1
            color: "#bbc5cc"
        }
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: headerRect.bottom
        anchors.bottom: commandRect.top
        orientation: Qt.Horizontal
        Rectangle{
            id:userandgroupitem
            width: 250
            height: 1000
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.bottom: parent.bottom
            color:"#bbc5cc"
            border.color: "#bbc5cc"
            Layout.maximumWidth: 400
            Layout.maximumHeight: 600
            SplitView{
                handleDelegate: Rectangle{
                    width: 3
                    height: 1
                    color: "#7d8f9c"
                }
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                orientation: Qt.Vertical
                GroupListView {
                    id: groupListView
                    width: userandgroupitem.width
                    height: 200
                    
                    Layout.maximumWidth: 400
                    Layout.minimumHeight: 150
                    Layout.maximumHeight: 600
                }

                PersonInfoRect {
                    id: userInfoView
                    width: userandgroupitem.width
                    height: 400
                    y:400
                    Layout.maximumWidth: 400
                    Layout.maximumHeight: 1000
                }
            }
        }

        RoomView {
            id: roomView
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 8
            Layout.minimumWidth: 50
            Layout.fillWidth: true
            color: "#a7b3bc"
        }

    }

    CommandPad {
        id: commandRect
        height: 80
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        onCall: {
            roomView.currentRoomCall(per);
        }

        onBye: {
            roomView.currentRoomBye(per);
        }

        onDeaf: {
            roomView.currentRoomDeaf(per, bDeaf);
        }

        onMute: {
            roomView.currentRoomMute(per, bMute);
        }

        onPromote: {
            roomView.currentRoomPromote(per, role);
        }

        onSpecialty: {
            roomView.currentRoomSpecialty(per, bEnable);
        }
    }
    MessageDialog{
        id:transferMessage
        modality: Qt.ApplicationModal;
        title: "消息提示！";
        text:"设置成功转接列表将删除!"
        standardButtons: StandardButton.Yes|StandardButton.No
        onYes:{
            roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("COMMANDER"));
        }
        onNo:
        {
            transferMessage.close();
            commanderItem.checked=false;
        }
    }
    MessageDialog{
        id:specialMessage
        modality: Qt.ApplicationModal;
        title: "消息提示！";
        text:"设置成功专向将失效!"
        standardButtons: StandardButton.Yes|StandardButton.No
        onYes: {
            roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("COMMANDER"));
        }
        onNo:
        {
            specialMessage.close();
            commanderItem.checked=false;
        }
    }
    MessageDialog{
        id:superiorMessage
        modality: Qt.ApplicationModal;
        title: "消息提示！";
        text:"设置成功越级将失效!"
        standardButtons: StandardButton.Yes|StandardButton.No
        onYes: {
            roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("COMMANDER"));
        }
        onNo:
        {
            superiorMessage.close();
            commanderItem.checked=false;
        }
    }
    MessageDialog{
        id:announceMessage
        modality: Qt.ApplicationModal;
        title: "消息提示！";
        text:"设置成功广播将失效!"
        standardButtons: StandardButton.Yes|StandardButton.No
        onYes: {
            roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("COMMANDER"));
        }
        onNo:
        {
            announceMessage.close();
            commanderItem.checked=false;
        }
    }
    MessageDialog{
        id:commanderMessage
        modality: Qt.ApplicationModal;
        title: "消息提示！";
        text:"每组只能有一个指挥员"
        standardButtons: StandardButton.Ok
        onAccepted: {
            commanderMessage.close();
            commanderItem.checked=false;
        }
    }

    Menu { // 右键菜单
        id: contentMenu
        style: MenuStyle {
            frame: Rectangle {
                color: "#123863"
                border.color: "#315980"
            }
            itemDelegate {
                background:Rectangle{
                    color: styleData.selected?"#123863":"#315980"
                    border.color: "#315980"
                }
                label: Text {
                    color: {
                        if(enabled)
                        {
                            return "white";
                        }
                        else
                        {
                            return "gray"
                        }
                    }
                    text: styleData.text
                }
            }
        }
        MenuItem {
            id:callItem
            text:"呼叫"
            onTriggered: {
                if(operate.personLength==1)
                {
                    roomView.currentRoomCall(commandRect.person);
                }
                else
                {
                    roomView.currentRoomCall(operate.manyPerson)
                }
            }
        }
        MenuItem {
            id:byeItem
            text:"挂断"
            onTriggered: {
                if(operate.personLength==1)
                {
                    roomView.currentRoomBye(commandRect.person);
                }
                else
                {
                    roomView.currentRoomBye(operate.manyPerson)
                }
            }
        }
        MenuItem {
            id:deafItem
            text:"分隔"
            checkable: true;
            visible: true
            enabled: {
                if(commandRect.person
                        &&commandRect.person.role
                        &&commandRect.person.role==="1")
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }

            checked:
            {
                if(commandRect.person
                        &&commandRect.person.listenable
                        &&commandRect.person.listenable!=1)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            onTriggered: {
                if(commandRect.person.listenable
                        &&commandRect.person.listenable==1){
                    if(operate.personLength==1)
                    {
                        roomView.currentRoomDeaf(commandRect.person,!commandRect.bDeaf);
                    }
                    else
                    {
                        roomView.currentRoomDeaf(operate.manyPerson,!commandRect.bDeaf)
                    }
                }
                else
                {
                    if(operate.personLength==1)
                    {
                        roomView.currentRoomDeaf(commandRect.person,commandRect.bDeaf);
                    }
                    else
                    {
                        roomView.currentRoomDeaf(operate.manyPerson,commandRect.bDeaf);
                    }
                }
            }
        }
        MenuItem {
            id:muteItem
            text:"屏蔽"
            checkable: true;
            enabled: {
                if(commandRect.person
                        &&commandRect.person.role
                        &&commandRect.person.role==="1")
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            checked: {
                if(commandRect.person
                        &&commandRect.person.speakable
                        &&commandRect.person.speakable!=1)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            onTriggered: {
                if(commandRect.person.speakable
                        &&commandRect.person.speakable==1)
                {
                    if(operate.personLength==1)
                    {
                        roomView.currentRoomMute(commandRect.person,!commandRect.bMute);
                    }
                    else
                    {
                        roomView.currentRoomMute(operate.manyPerson,!commandRect.bMute)
                    }
                    //roomView.currentRoomMute(commandRect.person,!commandRect.bMute );
                }
                else
                {
                    if(operate.personLength==1)
                    {
                        roomView.currentRoomMute(commandRect.person,commandRect.bMute);
                    }
                    else
                    {
                        roomView.currentRoomMute(operate.manyPerson,commandRect.bMute)
                    }
                    //roomView.currentRoomMute(commandRect.person,commandRect.bMute );
                }
            }
        }
        MenuItem{
            id:commanderItem
            text:"指挥员"
            checkable: true
            visible:true
            checked: {
                if(commandRect.person
                        &&commandRect.person.role
                        &&commandRect.person.role==="1")
                {
                    return true;
                }
                else
                {
                    return false;
                }

            }
            onTriggered: {
                if(commandRect.person.role
                        &&commandRect.person.role==="4")
                {
                    if(operate.personLength==1)
                    {
                        if(commandRect.person.oppositeAccountId&&commandRect.person.oppositeFromId)
                        {
                            if(flag=="0")
                            {
                                transferMessage.open();
                            }
                            else
                            {
                                roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("COMMANDER"));
                            }
                        }
                        else if(commandRect.person.specialIntercom=="1")
                        {
                            if(flag=="0")
                            {
                                specialMessage.open();
                            }
                            else
                            {
                                roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("COMMANDER"));
                            }
                        }
                        else
                        {
                            roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("COMMANDER"));
                        }
                    }
                    else
                    {
                        updateTime.running=true;
                        commanderMessage.open();
                        commanderItem.checked=false
                    }
                }
                else if(commandRect.person.role
                        &&commandRect.person.role==="2")
                {
                    if(operate.personLength==1)
                    {
                        if(flag=="0")
                        {
                            superiorMessage.open();
                        }
                        else
                        {
                            roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("COMMANDER"));
                        }
                    }
                    else
                    {
                        updateTime.running=true;
                        commanderMessage.open();
                        commanderItem.checked=false
                    }
                }
                else if(commandRect.person.role
                        &&commandRect.person.role==="3")
                {
                    if(operate.personLength==1)
                    {
                        if(flag=="0")
                        {
                            announceMessage.open();
                        }
                        else
                        {
                            roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("COMMANDER"));
                        }
                    }
                    else
                    {
                        updateTime.running=true;
                        commanderMessage.open();
                        commanderItem.checked=false
                    }
                }
                else if(commandRect.person.role
                        &&commandRect.person.role==="1")
                {
                    if(operate.personLength==1)
                    {
                        roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("SUBORDINATE"));
                    }
                    else
                    {
                        updateTime.running=true;
                        commanderMessage.open();
                        commanderItem.checked=false
                    }
                }
                else
                {
                }
            }
        }
        MenuItem {
            id:promoteItem
            text:"越级"
            checkable: true
            enabled: {
                if(commandRect.person
                        &&commandRect.person.role
                        &&commandRect.person.role==="1")
                {
                    return false;
                }
                else if(commandRect.person&&commandRect.person.specialIntercom=="1")
                {
                    return false;
                }
                else if(commandRect.person&&commandRect.person.oppositeAccountId&&commandRect.person.oppositeFromId)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            visible:true
            checked: {
                if(commandRect.person
                        &&commandRect.person.role
                        &&commandRect.person.role==="2")
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }

            onTriggered:{
                console.log("role;"+commandRect.person.role)
                if(commandRect.person.role
                        &&commandRect.person.role==="4")
                {
                    if(operate.personLength==1)
                    {
                        roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("SUPERIOR"));
                    }
                    else
                    {
                        roomView.currentRoomPromote(operate.manyPerson,Logic.getRoleValue("SUPERIOR"))
                    }
                    //roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("SUPERIOR") );
                }
                else
                {
                    if(commandRect.person.role
                            &&commandRect.person.role==="3")
                    {
                        if(operate.personLength==1)
                        {
                            roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("SUPERIOR"));
                        }
                        else
                        {
                            roomView.currentRoomPromote(operate.manyPerson,Logic.getRoleValue("SUPERIOR"))
                        }
                        // roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("SUPERIOR") );
                    }
                    else
                    {
                        if(operate.personLength==1)
                        {
                            roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("SUBORDINATE"));
                        }
                        else
                        {
                            roomView.currentRoomPromote(operate.manyPerson,Logic.getRoleValue("SUBORDINATE"))
                        }
                        //roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("SUBORDINATE"));
                    }
                }
            }
        }

        MenuItem {
            id:announceitem
            text:"广播"
            checkable: true
            enabled: {
                if(commandRect.person
                        &&commandRect.person.role
                        &&commandRect.person.role==="1")
                {
                    return false;
                }
                else if(commandRect.person&&commandRect.person.specialIntercom=="1")
                {
                    return false;
                }
                else if(commandRect.person&&commandRect.person.oppositeAccountId&&commandRect.person.oppositeFromId)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            checked: {
                if(commandRect.person
                        &&commandRect.person.role
                        && commandRect.person.role==="3")
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            onTriggered: {
                if(commandRect.person.role
                        &&commandRect.person.role==="4")
                {
                    if(operate.personLength==1)
                    {
                        roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("ANNOUNCER"));
                    }
                    else
                    {
                        roomView.currentRoomPromote(operate.manyPerson,Logic.getRoleValue("ANNOUNCER"))
                    }
                    //roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("ANNOUNCER") );
                }
                else
                {
                    if(commandRect.person.role
                            &&commandRect.person.role==="3")
                    {
                        if(operate.personLength==1)
                        {
                            roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("SUBORDINATE"));
                        }
                        else
                        {
                            roomView.currentRoomPromote(operate.manyPerson,Logic.getRoleValue("SUBORDINATE"))
                        }
                        //roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("SUBORDINATE") );
                    }
                    else
                    {
                        if(commandRect.person.role
                                &&commandRect.person.role==="2")
                        {
                            if(operate.personLength==1)
                            {
                                roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("ANNOUNCER"));
                            }
                            else
                            {
                                roomView.currentRoomPromote(operate.manyPerson,Logic.getRoleValue("ANNOUNCER"))
                            }
                            //roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("ANNOUNCER"));
                        }
                        else
                        {

                            if(operate.personLength==1)
                            {
                                roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("SUPERIOR"));
                            }
                            else
                            {
                                roomView.currentRoomPromote(operate.manyPerson,Logic.getRoleValue("SUPERIOR"))
                            }
                            //roomView.currentRoomPromote(commandRect.person,Logic.getRoleValue("SUPERIOR"));
                        }
                    }
                }
            }
        }
        MenuItem {
            id:addSpecialtyItem
            text:"加入专向"
            enabled: {
                if(commandRect.person
                        &&commandRect.person.role
                        &&commandRect.person.role==="1")
                {
                    return false;
                }
                else if((commandRect.person
                        &&commandRect.person.role
                        &&commandRect.person.role==="2")
                        ||(commandRect.person
                        &&commandRect.person.role
                        &&commandRect.person.role==="3"))
                {
                    return false;
                }
                else if(commandRect.person&&commandRect.person.oppositeAccountId&&commandRect.person.oppositeFromId)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            checkable: true
            checked: {
                if( commandRect.person
                        &&commandRect.person.specialIntercom
                        && commandRect.person.specialIntercom!=0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }

            onTriggered: {
                if(commandRect.person.specialIntercom
                        &&commandRect.person.specialIntercom==0)
                {
                    if(operate.personLength==1)
                    {
                        roomView.currentRoomSpecialty(commandRect.person,!commandRect.bEnable);
                    }
                    else
                    {
                        roomView.currentRoomSpecialty(operate.manyPerson,!commandRect.bEnable)
                    }
                    // roomView.currentRoomSpecialty(commandRect.person,!commandRect.bEnable );
                }
                else
                {
                    if(operate.personLength==1)
                    {
                        roomView.currentRoomSpecialty(commandRect.person,commandRect.bEnable);
                    }
                    else
                    {
                        roomView.currentRoomSpecialty(operate.manyPerson,commandRect.bEnable)
                    }
                    //roomView.currentRoomSpecialty(commandRect.person,commandRect.bEnable);
                }
            }
        }
    }
}

