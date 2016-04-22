import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4

import "../operating"
import "../userManage"
import "../listener.js" as Logic

Item {
    id: root
    width: 800
    height: 800
    property string groupId
    property string groupName
    property string roomStatus
    property int mode: 0 //  0-(MEETING)会议模式，1-(DISPATCHING)调度模式
    property int specialIntercom: 0 // -- 会议室专向对讲： 0-(off)关闭 ，1-(on)开启
    property var selection: []
    property var tmpselection: []
    property int conferenceIndex
    property var attendeeMap
    property int rectx
    property int recty
    property int flag:0
    property int count:0
    MessageDialog{
        id:warningDialog
        modality: Qt.ApplicationModal
        title: "提示信息"
    }
    Timer{
        id:warningtime
        interval: 3000
        running: false
        repeat: true
        onTriggered:{
            warningDialog.close()
        }
    }

    function onAttendeeNotify(notice)
    {
        if (notice.type === "update")
        {
            if (notice.class === "vi_attendees")
            {
                var id = notice.where.accountId + notice.where.fromId;
                for (var i = 0; i < attendeesModel.count; ++i)
                {
                    var at = attendeesModel.get(i);
                    var at_id = at.accountId + at.fromId;
                    if (id ===at_id)
                    {
                        Logic.updatePerson(at, notice);
                        break;
                    }
                }
                operate.onSelectedAttendeeChange(groupId, roomStatus, selection);
            }
            else if(notice.class === "attendees")
            {
                var id = notice.value.accountId + notice.value.fromId;
                for (var i = 0; i < attendeesModel.count; ++i)
                {
                    var at = attendeesModel.get(i);
                    var at_id = at.accountId + at.fromId;
                    if (id ===at_id)
                    {
                        if(at.role==="1"&&notice.value.role==="4")
                        {
                            flag=0;
                            operate.commandercount(flag);
                        }
                        else if(notice.value.role==="1")
                        {
                            flag=1;
                            operate.commandercount(flag);
                        }

                        Logic.updateAttendeePerson(at, notice);
                        break;
                    }
                }
                operate.onSelectedAttendeeChange(groupId, roomStatus, selection);
            }

            return;
        }
        else if(notice.type === "delete")
        {
            if(notice.class==="tr_cmd")
            {
                var ida = notice.where.accountId1 + notice.where.fromId1;
                var idb= notice.where.accountId2+notice.where.fromId2;
                for (var i = 0; i < attendeesModel.count; ++i)
                {
                    var at = attendeesModel.get(i);
                    var at_id = at.accountId + at.fromId;

                    if (ida ===at_id)
                    {
                        Logic.updateTransfer(at,notice);
                    }
                    else if(idb===at_id)
                    {
                        Logic.updateTransfer(at,notice);
                    }
                    else
                    {

                    }
                }
                operate.onSelectedAttendeeChange(groupId, roomStatus, selection);
            }
        }
    }
    function onVoiceAttendeeNotify(da)
    {
        var ids=da.accountId+da.fromId
        for (var i= 0; i<attendeesModel.count; ++i)
        {
            var atVoice= attendeesModel.get(i);
            var at_ids = atVoice.accountId + atVoice.fromId;
            if (ids ===at_ids)
            {
                atVoice.voiceLevelPerson=da.voiceLevel
                //console.log("atVoice.voicelevel:"+atVoice.voiceLevelPerson)
            }
        }
    }

    function updateAttendeeField(accoutId, fromId, field, value)
    {
        var id = accoutId + fromId;

        for (var i = 0; i < attendeesModel.count; ++i)
        {
            var at = attendeesModel.get(i);
            var at_id = at.accountId + at.fromId;
            if (id === at_id)
            {
                at[field] = value;
                break;
            }
        }

        operate.onSelectedAttendeeChange(groupId, roomStatus, selection);

    }
    function updateTransferPeer(accoutaId,fromaId,accoutbId,frombId)
    {
        var aid=accoutaId+fromaId;
        var bid=accoutbId+frombId;
        for(var i = 0; i < attendeesModel.count; ++i)
        {
            var at = attendeesModel.get(i);
            var at_id = at.accountId + at.fromId;
            if (aid === at_id)
            {
                at.oppositeAccountId =accoutbId ;
                at.oppositeFromId=frombId;
            }
            if(bid===at_id)
            {
                at.oppositeAccountId = accoutaId;
                at.oppositeFromId=fromaId;
            }
        }
    }
    function deletTransferPeer(userA,userB)
    {
        var usernameA=userA;
        var usernameB=userB;
        for(var i=0;i<attendeesModel.count;++i)
        {
            var atA=attendeesModel.get(i);
            var at_usera=atA.realName
            if(usernameA===atA.realName)
            {
                atA.oppositeAccountId = "";
                atA.oppositeFromId="";
            }
        }
        for(var i=0;i<attendeesModel.count;++i)
        {
            var atB=attendeesModel.get(i);
            var at_userb=atB.realName
            if(usernameB===atB.realName)
            {
                atB.oppositeAccountId = "";
                atB.oppositeFromId="";
            }
        }
    }

    function reloadRoom(room)
    {
        setGroup(room.groupId, "", room.status, room.mode);
    }

    function setGroup(grpId, grpName, status)
    {
        if (grpId !== groupId)
        {
            selection = [];
            setRoomStatus(status);
            Logic.queryAttendees(grpId, onResetAttendees);

            groupId = grpId;
            groupName = grpName;
            operate.onFocusRoomChange();
        }
    }

    function onResetAttendees(grpId, attendees)
    {
        attendeesModel.clear();
        attendeeMap = {};
        for (var i = 0; i < attendees.length; ++i)
        {
            var id = attendees[i].accountId + attendees[i].fromId;
            attendeeMap[id] = attendees[i];
            if(attendees[i].role=="1")
            {
                count=1;
            }
            else
            {
                count=0;
            }
            if(count=="1")
            {
                flag=1
                operate.commandercount(flag);
            }
            else
            {
            }
            attendeesModel.append(attendees[i]);
        }
        if (attendeesModel.count > 0 )
        {
            grid.currentIndex = 0;
            var sel = [];
            sel.push(attendeesModel.get(0));
            selection = sel;
        }
    }

    function setRoomName(name)
    {
        groupName = name;
    }


    function attendeesOfRoom()
    {
        var count = attendeesModel.count;
        var atts = [];
        for (var i = 0; i < count; i++)
        {
            var att = attendeesModel.get(i);
            atts.push(att);
        }

        return atts;
    }


    function setRoomStatus(status)
    {
        console.log("kkk***kkk:"+status)
        roomStatus = status;
        footer.updateStatus(status);
        operate.onSelectedAttendeeChange(groupId, roomStatus, selection);
    }

    function changeGroup(grpId, grpName)
    {
        postSetGroupRequest(grpId, grpName);
    }

    function postSetGroupRequest(grpId, grpName)
    {
        var path = "xnode/ws/conferences/conference[" + (conferenceIndex + 1).toString() + "]/group";
        var handlers = {
            onTimeout: function (req){
                operate.showErrorMessage("网络超时，请重试......");
                console.log("postSetGroupRequest group " + grpId + "timeout")
            },
            onRequestSuccess: function(resp) {
                //TODO: set group , reload group
                if(resp.result.overall)
                {
                    var result=resp.result.overall
                    if (parseInt(result) === 0)
                    {
                        if (groupId)
                            operate.onNotifyGroupChange(-1, groupId, "idle");
                        setGroup(grpId, grpName, "idle");
                        operate.onNotifyGroupChange(conferenceIndex, grpId, "idle");
                        Logic.queryRooms(function (rooms){
                            var room = rooms[conferenceIndex];
                            setRoomStatus(room.status);})
                    }
                    else if(parseInt(result) === 1)
                    {
                        warningDialog.text=resp.result.detail.group["@reason"];
                        warningDialog.open();
                        warningtime.running=true;
                    }
                    else
                    {
                    }
                }
                else
                {

                }
                showErrorMessage("");
            },
            onRequestError: function (req){
                showErrorMessage("网络连接异常，请重试......");
                console.log("postSetGroupRequest group " + grp.name + "failed")
            },
        }

        var xml = "<set>" + grpId + "</set>";

        Logic.post(work.target, path, xml, handlers);
    }

    function specialControl(spec)
    {
        var path = "xnode/ws/conferences/conference[" + (conferenceIndex + 1).toString() + "]/specialIntercom";
        var handlers = {
            onTimeout: function (req){
                operate.showErrorMessage("网络超时，请重试......");
            },
            onRequestSuccess: function(resp) {
                //TODO: set group , reload group
                if(resp.result.overall)
                {
                    var result= resp.result.overall

                    if (parseInt(result) === 0)
                    {
                        specialIntercom = spec ? 1 : 0;
                    }
                    else if(parseInt(result)===1)
                    {
                        warningDialog.text=resp.result.detail.specialIntercom["@reason"];
                        warningDialog.open();
                        warningtime.running=true;
                    }
                }
                else
                {

                }
                showErrorMessage("");
            },
            onRequestError: function (req){
                operate.showErrorMessage("网络连接异常，请重试......");
                console.log("broadCastControl group failed")
            },
        }
        var value = spec ? "1" : "0"

        var xml = "<set>" + value + "</set>";
        console.log("xml:" + xml);
        Logic.post(work.target, path, xml, handlers);
    }

    function broadCastControl(broadCast)
    {
        var path = "xnode/ws/conferences/conference[" + (conferenceIndex + 1).toString() + "]/mode";
        var handlers = {
            onTimeout: function (req){
                operate.showErrorMessage("网络超时，请重试......");
                console.log("broadCastControl room " + (conferenceIndex+1) + "timeout")
            },
            onRequestSuccess: function(resp) {
                //TODO: set group , reload group
                if(resp.result.overall)
                {
                    var result= resp.result.overall

                    if (parseInt(result) === 0)
                    {
                        mode = broadCast ? 1 : 0;
                    }
                    else if(parseInt(result) === 1)
                    {
                        warningDialog.text=resp.result.detail.mode["@reason"];
                        warningDialog.open();
                        warningtime.running=true;
                    }
                }
                else
                {

                }
                operate.showErrorMessage("");
            },
            onRequestError: function (req){
                operate.showErrorMessage("网络连接异常，请重试......");
            },
        }
        var value = broadCast ? "1" : "0"

        var xml = "<set>" + value + "</set>";
        console.log("xml:" + xml);
        Logic.post(work.target, path, xml, handlers);
    }

    /**
     * cmd: start, stop
     *
     */
    function meetingControl(cmd)
    {
        var path = "xnode/ws/conferences/conference[" + (conferenceIndex+1).toString() + "]/control";
        var handlers = {
            onTimeout: function (req){
                operate.showErrorMessage("网络超时，请重试......");
            },
            onRequestSuccess: function(resp) {
                if(resp.result.overall)
                {
                    var result= resp.result.overall

                    if (parseInt(result)=== 0)
                    {
                        if (cmd === "start")
                            setRoomStatus("running");
                        else if (cmd === "stop")
                            setRoomStatus("idle");
                    }
                    else if(parseInt(result)=== 1)
                    {
                        warningDialog.text=resp.result.detail.control["@reason"];
                        warningDialog.open();
                        warningtime.running=true;
                    }
                    else
                    {

                    }
                }
                else
                {

                }
                operate.showErrorMessage("");
            },
            onRequestError: function (req){
                operate.showErrorMessage("网络连接异常，请重试......");
            },
        }

        var xml = "<set>" + cmd + "</set>"

        Logic.post(work.target, path, xml, handlers);
    }


    function callAttendee(person)
    {
        callControl("invite", person)
    }

    function byeAttendee(person)
    {
        callControl("bye", person);
    }


    function callControl(cmd, person)
    {
        var path = "xnode/ws/conferences/conference[" + (conferenceIndex+1).toString() + "]/call";
        var handlers = {
            onTimeout: function (req){
                operate.showErrorMessage("网络超时，请重试......");
                console.log("callControl group " + group + "timeout")
            },
            onRequestSuccess: function(resp) {
                if(resp.result.overall)
                {
                    var result= resp.result.overall

                    if (parseInt(result) === 0)
                    {

                    }
                    else if(parseInt(result) === 1)
                    {
                        warningDialog.text=resp.result.detail.call["@reason"];
                        warningDialog.open();
                        warningtime.running=true;
                    }
                    else
                    {

                    }
                }
                else
                {

                }

                operate.showErrorMessage("");
            },
            onRequestError: function (req){
                operate.showErrorMessage("网络连接异常，请重试......");
                console.log("callControl " + "failed")
            },
        }

        if(person.length)
        {
            for(var i=0;i<person.length;++i)
            {
                var xml = "<set>" + cmd + "," + person[i].fromId + "," + person[i].accountId + "</set>";
                Logic.post(work.target, path, xml, handlers);
            }
        }
        else
        {
            var xml1 = "<set>" + cmd + "," + person.fromId + "," + person.accountId + "</set>";
            Logic.post(work.target, path, xml1, handlers);
        }
    }

    // control role,specialIntercom
    function controlAttendeeField(person, field, value)
    {
        var path = "xnode/ws/attendees/command";
        var handlers = {
            onTimeout: function (req){
                operate.showErrorMessage("网络超时，请重试......");
                console.log("controlAttendeeField field " + field + "timeout")
            },
            onRequestSuccess: function(resp) {
                if(resp.result.overall)
                {
                    var result= resp.result.overall
                    if (parseInt(result) === 0)
                    {
                        if(person.length)
                        {
                            for(var i=0;i<person.length;++i)
                            {
                                updateAttendeeField(person[i].accountId, person[i].fromId, field, value);
                            }
                        }
                        else
                        {
                            updateAttendeeField(person.accountId, person.fromId, field, value);
                        }
                    }
                    else if(parseInt(result) === 1)
                    {
                        warningDialog.text=resp.result.detail.command["@reason"];
                        warningDialog.open();
                        warningtime.running=true;
                    }
                    else
                    {

                    }
                }
                else
                {

                }
                operate.showErrorMessage("");
            },
            onRequestError: function (req){
                operate.showErrorMessage("网络连接异常，请重试......");
                console.log("controlAttendeeField " + "failed")
            },
        }

        if(person.length)
        {
            var xml="<set>"
            for(var i=0;i<person.length;++i)
            {
                //                var xml = "<set> change " + field + "='" + value + "' where accountId='" + person[i].accountId + "' and fromId='" + person[i].fromId + "' </set>";
                if(i==person.length-1)
                {
                    xml+=" change " + field + "='" + value + "' where accountId='" + person[i].accountId + "' and fromId='" + person[i].fromId + "'</set>";
                }
                else
                {
                    xml+=" change " + field + "='" + value + "' where accountId='" + person[i].accountId + "' and fromId='" + person[i].fromId + "';\n";
                }
            }
            console.log("xml:" + xml);
            Logic.post(work.target, path, xml, handlers);
        }
        else
        {
            var xml2= "<set> change " + field + "='" + value + "' where accountId='" + person.accountId + "' and fromId='" + person.fromId + "' </set>";
            console.log("xml:" + xml2);
            Logic.post(work.target, path, xml2, handlers);
        }
    }

    // apply for micGranted and receiver
    function permissionControl(field, person, bEnable)
    {
        var path = "xnode/ws/attendees/command";
        var value = bEnable ? "1":"0";

        var handlers = {
            onTimeout: function (req){
                //operate.showErrorMessage("网络超时，请重试......");
                console.log("permissionControl group timeout name is permission")
            },
            onRequestSuccess: function(resp) {
                if(resp.result.overall)
                {
                    var result= resp.result.overall
                    if (parseInt(result) === 0)
                    {
                        if(person.length)
                        {
                            for(var i=0;i<person.length;++i)
                            {
                                updateAttendeeField(person[i].accountId, person[i].fromId, Logic.getAttendeeLocalField(field), value);
                            }
                        }
                        else
                        {
                            updateAttendeeField(person.accountId, person.fromId, Logic.getAttendeeLocalField(field), value);
                        }
                    }
                    else if(parseInt(result) === 1)
                    {
                        warningDialog.text=resp.result.detail.command["@reason"];
                        warningDialog.open();
                        warningtime.running=true;
//                        if(person.length)
//                        {
//                            for(var i=0;i<person.length;++i)
//                            {
//                                value = bEnable ? "0":"1";
//                                updateAttendeeField(person[i].accountId, person[i].fromId, Logic.getAttendeeLocalField(field), value);
//                            }
//                        }
//                        else
//                        {
//                            updateAttendeeField(person.accountId, person.fromId, Logic.getAttendeeLocalField(field), value);
//                        }
                        console.log("permissionControl " + "failed,code:" + result);
                    }
                }
                else
                {
                }
                operate.showErrorMessage("");
            },
            onRequestError: function (req){
                operate.showErrorMessage("网络连接异常，请重试......");
                console.log("permissionControl " + "failed")
            },
        }
        if(person.length)
        {
            var xml="<set>"
            for(var i=0;i<person.length;++i)
            {
                //var xml = "<set> change " + field + "='" + value + "' where accountId='" + person[i].accountId + "' and fromId='" + person[i].fromId + "' </set>";

                if(i==person.length-1)
                {
                    xml+=" change " + field + "='" + value + "' where accountId='" + person[i].accountId + "' and fromId='" + person[i].fromId + "'</set>";
                }
                else
                {
                    xml+=" change " + field + "='" + value + "' where accountId='" + person[i].accountId + "' and fromId='" + person[i].fromId + "';\n";
                }
            }
            console.log("xml:" + xml);
            Logic.post(work.target, path, xml, handlers);
        }
        else
        {
            var xml2= "<set> change " + field + "='" + value + "' where accountId='" + person.accountId + "' and fromId='" + person.fromId + "' </set>";
            //console.log("xml:" + xml2);
            Logic.post(work.target, path, xml2, handlers);
        }
    }

    function updateMode()
    {
        footer.updateMode(mode);
    }

    function updateSpecialIntercom()
    {
        footer.updateSpecial(specialIntercom);
    }
    function findRealName(transferAccountId,transferFormId)
    {
        var ids=transferAccountId+transferFormId
        for (var i= 0; i<attendeesModel.count; ++i)
        {
            var at= attendeesModel.get(i);
            var at_ids = at.accountId + at.fromId;
            if (ids ===at_ids)
            {
                return at.realName
            }
        }
    }

    ListModel {
        id: attendeesModel
    }

    ScrollView{
        width: parent.width;
        height: parent.height -58;
        style:ScrollViewStyle{
            handle: Item{
                implicitHeight: 12;
                implicitWidth: 12;
                Rectangle{
                    color:"#315980";
                    anchors.fill: parent;
                    visible: true;
                }
            }
            decrementControl: Image{
                width: 12; height: 12;
                source: "../images/arrow_up.png";
            }
            incrementControl: Image{
                width: 12; height: 12;
                source: "../images/arrow_down.png";
            }
            scrollBarBackground: Item{
                implicitHeight: 12;
                implicitWidth: 12;
            }
        }

        GridView {
            id: grid
            width: parent.width
            height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin:30
            cellWidth: 180
            cellHeight:120
            property bool ctrl_pressed: false
            Keys.onPressed: {
                if (event.key == Qt.Key_Control) {
                    grid.ctrl_pressed=true;
                    event.accepted = true;
                }
            }
            Keys.onReleased: {
                grid.ctrl_pressed=false
            }

            onActiveFocusChanged : {
                grid.ctrl_pressed=false
            }

//            add: Transition {
//                NumberAnimation { properties: "x"; from: 0; duration:5 }
//            }

            delegate: Item {
                id: gridDelegate
                width: grid.cellWidth
                height: grid.cellHeight
                        Image {
                            id: isonlineimage
                            height: 90
                            source:"../images/user_back_image.png"
                            Image {
                                id: selectedimage
                                anchors.top:parent.top
                                anchors.topMargin: -7
                                anchors.left: parent.left
                                anchors.leftMargin: -10
                                width: 180
                                height:  106
                                source:
                                {
                                    if(selected==true)
                                    {
                                        return "../images/current.png";
                                    }
                                    else
                                    {
                                        return "";
                                    }
                                }
                            }
                            Image {
                                id: specialImage
                                x:130
                                y:10
                                visible: {
                                    if(mode===1)
                                    {
                                        if(role==="1"||role==="2"||role==="3"||oppositeAccountId||oppositeFromId)//1-指挥员,2-越级用户,3-广播用户,4-下级用户
                                        {
                                            return false;
                                        }
                                        else
                                        {
                                            return footer.special;
                                        }
                                    }
                                    else
                                    {
                                        return false
                                    }
                                }
                                source: {
                                    return Logic.getspecialImage(specialIntercom);
                                }
                            }

                            Image {
                                id: userimg
                                x:22
                                y:13
                                sourceSize.height: 100
                                sourceSize.width: 60
                                source:
                                {
                                    if(onlineStatus=="AVAILABLE"||onlineStatus=="ON_THE_PHONE")
                                    {
                                        if(mode=="0")
                                        {
                                            return "../images/user_normal_image.png"
                                        }
                                        else
                                        {
                                             return Logic.getRoleImage(role);
                                        }
                                    }
                                    else
                                    {
                                        if(mode=="0")
                                        {
                                            return "../images/user_normal_off_image.png"
                                        }
                                        else
                                        {
                                            return Logic.getChineseRoleImage(role);
                                        }
                                    }
                                }
                            }
                            Image {
                                id: voicelevelbottomImages
                                x:8
                                y:10
                                width: 5
                                height: 55
                                source: "../images/vioceLevel1.png"
                                Image {
                                    id: voiceleveltopImages
                                    anchors.bottom: parent.bottom
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    height:
                                    {
                                        if(voiceLevelPerson<2&&voiceLevelPerson>0)
                                        {
                                            return 1;
                                        }
                                        else if(voiceLevelPerson>=2&&voiceLevelPerson<=27)
                                        {
                                            return voiceLevelPerson*2;
                                        }
                                        else if(voiceLevelPerson>27&&voiceLevelPerson<=54)
                                        {
                                            return  voiceLevelPerson;
                                        }
                                        else if(voiceLevelPerson>54)
                                        {
                                            return 54;
                                        }
                                        else
                                        {
                                            return 0;
                                        }
                                    }
                                    source: "../images/voiceLevel3.png"
                                }
                            }
                            Text {
                                id: rolenametext
                                x:60
                                y:30
                                color: "#cccccc"
                                font.pixelSize: 13
                                text: {
                                    return"["+ Logic.getChineseRoleName(role)+"]";
                                }
                            }
                            Image {
                                id: isonlineImage
                                anchors.left:
                                    if(mode===1)
                                    {
                                        return listenimage.right
                                    }
                                    else
                                    {
                                        return parent.left
                                    }
                                anchors.bottom:parent.bottom
                                visible: true
                                source:
                                {
                                    if(mode===1)
                                    {
                                        if(onlineStatus=="AVAILABLE"||onlineStatus=="ON_THE_PHONE")
                                        {
                                            return "../images/mid_on.png"
                                        }
                                        else
                                        {
                                            return "../images/mid_off.png"
                                        }
                                    }
                                    else
                                    {
                                        if(onlineStatus=="AVAILABLE"||onlineStatus=="ON_THE_PHONE")
                                        {
                                            return "../images/all_on_image.png"
                                        }
                                        else
                                        {
                                            return "../images/all_off_image.png"
                                        }
                                    }
                                }
                            }
                            Image {
                                id: listenimage
                                anchors.left: parent.left
                                anchors.bottom: parent.bottom
                                visible: {
                                    if(mode===0)
                                        return false;
                                    else
                                        return true;
                                }
                                source: {
                                    if(listenable==1)
                                    {
                                        return "../images/left_on.png"
                                    }
                                    else
                                    {
                                        return "../images/left_off.png"
                                    }
                                }
                            }
                            Image {
                                id: speckimage
                                anchors.right: parent.right
                                anchors.bottom: parent.bottom
                                visible: {
                                    if(mode===0)
                                        return false;
                                    else
                                        return true;
                                }
                                source:
                                    if(speakable==1)
                                    {
                                        return "../images/right_on.png"
                                    }
                                    else
                                    {
                                        return "../images/right_off.png"
                                    }
                            }
                            Text {
                                id: phonestatustext
                                anchors.left: parent.left
                                anchors.leftMargin: 22
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 20
                                color: "white"
                                font.pixelSize: 12
                                text: {
                                    return  Logic.getChineseOnlineState(onlineStatus);
                                }
                            }
                            Text {
                                id: transfer
                                anchors.left: parent.left
                                anchors.leftMargin: 64
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 20
                                visible: true
                                color: "white"
                                font.pixelSize: 12
                                width:92;
                                height: 16;
                                elide: Text.ElideRight
                                ToolTip{
                                    space: 2;
                                    toolTip: parent.text
                                }
                                text: {
                                    if(oppositeAccountId&&oppositeFromId)
                                    {
                                        var str=findRealName(oppositeAccountId,oppositeFromId)
                                        return "转接=>"+str;
                                    }
                                    else
                                    {
                                        return ""
                                    }
                                }
                            }
                            Image{
                                id:progressImage
                                x:15
                                anchors.bottom: isonlineimage.bottom
                                anchors.bottomMargin: 10
                                width: 138
                                visible: {
                                    if(phoneStatus==="CONNECTING"||phoneStatus==="RINGING")
                                    {
                                        return true;
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                }
                                source: "../images/dise.png"
                                Image {
                                    id: image
                                    height: 8
                                    sourceSize.width: 128
                                    source: "../images/baitiao1.png"
                                    SequentialAnimation {
                                        id:sequen
                                        running: true
                                        NumberAnimation  {
                                            target: image
                                            properties: "x"
                                            from:0
                                            to: 10
                                            duration: 350
                                            loops: Animation.Infinite
                                        }
                                    }
                                }
                            }
                            Text {
                                id: nameTxt
                                x:60
                                y:10
                                text: realName
                                font.bold: true
                                font.pixelSize: 15
                                color: "white"
                                width:65;
                                height: 20;
                                elide: Text.ElideRight
                                ToolTip{
                                    space: 2;
                                    toolTip: parent.text
                                }
                            }
                        }
            }
            model: attendeesModel
            onCurrentIndexChanged: {
            }
            function clearSelection()
            {
                var count = attendeesModel.count;
                for (var i = 0; i < count; ++i)
                {
                    var obj = attendeesModel.get(i);
                    obj.selected = false;
                }
                root.selection = []
            }

            //            function updateSelection()
            //            {
            //                var count = attendeesModel.count;
            //                for (var i = 0; i < count; ++i)
            //                {
            //                    var selected = false
            //                    var obj = attendeesModel.get(i);
            //                    for (var j = 0; j < selection.length; j++)
            //                    {
            //                        if (selection[j] == obj)
            //                        {
            //                            obj.selected = true;
            //                            selected = true;
            //                            break
            //                        }
            //                    }
            //                    if (!selected)
            //                    {
            //                        obj.selected = false;
            //                    }
            //                }
            //            }
            function reverseSelect(removes)
            {
                var count = attendeesModel.count;
                for (var i = 0; i < count; ++i)
                {
                    var obj = attendeesModel.get(i);
                    for (var j = 0; j < removes.length; j++)
                    {
                        if (removes[j] == obj)
                        {
                            obj.selected = false;
                            break
                        }
                    }
                }
            }

            function rectSelection(rect)
            {
                var ind = indexAt(rect.x, rect.y);
                if (ind !== -1)
                {
                    var data = attendeesModel.get(ind);
                    data.selected = true;
                }

                var x2 = rect.x + rect.width;
                var y2 = rect.y + rect.height;

                x2 = Math.ceil(x2 / cellWidth) * cellWidth;
                y2 = Math.ceil(y2 / cellHeight) * cellHeight;
                var sel = [];
                var removed = [];
                for (var x = rect.x; x < x2; x += grid.cellWidth)
                {
                    for (var y = rect.y; y < y2; y += grid.cellHeight)
                    {
                        ind = indexAt(x, y);
                        if (ind !== -1)
                        {
                            var data2 = attendeesModel.get(ind);
                            data2.selected = true;
                            var found = false;
                            if (grid.ctrl_pressed)
                            {
                                for(var i=0;i<root.selection.length;++i)
                                {
                                    if(data2==root.selection[i])
                                    {
                                        found = true;
                                        removed.push(data2);
                                        break;
                                    }
                                }
                            }
                            if (!found)
                                sel.push(data2)
                        }
                    }
                }
                var clone = [];
                for (var i = 0; i < root.selection.length; i++)
                {
                    clone[i] = root.selection[i];
                }
                if (sel.length > 0)
                {
                    clone = clone.concat(sel)
                }
                reverseSelect(removed)
                for (var i = 0; i < removed.length; i++)
                {
                    for (var j = 0; j < clone.length; j++)
                    {
                        if ( removed[i] == clone[j])
                        {
                            clone.splice(j,1)
                            break;
                        }
                    }
                }
                if (clone.length > 0)
                {
                    root.selection = clone;
                }
            }

            Rectangle {
                id: selectRect
                color:"white"
                border.color: "#00f6ff"
                border.width: 2
                opacity:0.2
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton|Qt.LeftButton
                onClicked: {
                    grid.forceActiveFocus();
                    if(mouse.button==Qt.LeftButton)
                    {
                    }
                    else if(mouse.button==Qt.RightButton)
                    {
                        if(mode===1)
                        {
                            contentMenu.popup();
                        }
                    }
                }
                onPressed: {
                    if(mouse.button==Qt.LeftButton)
                    {
                        if (grid.ctrl_pressed)
                        {
                        }
                        else
                        {
                            grid.clearSelection();
                        }
                        selectRect.x = mouseX;
                        selectRect.y = mouseY;

                        selectRect.width = 0;
                        selectRect.height = 0;
                        selectRect.visible = true;
                        rectx=selectRect.x;
                        recty=selectRect.y;
                    }
                    else
                    {

                    }

                }

                onPositionChanged: {
                    if (selectRect.visible)
                    {
                        selectRect.x=rectx;
                        selectRect.y=recty;
                        if(mouseX-selectRect.x>0&&mouseY-selectRect.y>0)
                        {
                            selectRect.width = mouseX - selectRect.x;
                            selectRect.height = mouseY - selectRect.y;
                        }
                        else if(mouseX-selectRect.x<0&&mouseY-selectRect.y>0)
                        {
                            selectRect.width=-(mouseX-rectx);
                            selectRect.x=rectx-selectRect.width;
                            selectRect.height=mouseY-selectRect.y;
                        }
                        else if(mouseX-selectRect.x>0&&mouseY-selectRect.y<0)
                        {
                            selectRect.width = mouseX - selectRect.x;
                            selectRect.height=-(mouseY-selectRect.y);
                            selectRect.y=recty-selectRect.height;
                        }
                        else
                        {
                            selectRect.width=selectRect.x-mouseX;
                            selectRect.x=rectx-(selectRect.width+1);

                            selectRect.height=selectRect.y-mouseY
                            selectRect.y=recty-(selectRect.height+1);
                        }
                    }
                }

                onReleased: {
                    if(mouse.button==Qt.LeftButton)
                    {
                        if (selectRect.visible)
                        {
                            selectRect.x=rectx;
                            selectRect.y=recty;

                            if(mouseX-selectRect.x>0&&mouseY-selectRect.y>0)
                            {
                                selectRect.width = mouseX - selectRect.x;
                                selectRect.height = mouseY - selectRect.y;
                            }
                            else if(mouseX-selectRect.x<0&&mouseY-selectRect.y>0)
                            {
                                selectRect.width=selectRect.x-mouseX;
                                selectRect.x=rectx-selectRect.width;
                                selectRect.height=mouseY-selectRect.y;
                            }
                            else if(mouseX-selectRect.x>0&&mouseY-selectRect.y<0)
                            {
                                selectRect.width = mouseX - selectRect.x;
                                selectRect.height=selectRect.y-mouseY;
                                selectRect.y=recty-selectRect.height;
                            }
                            else
                            {
                                selectRect.width=selectRect.x-mouseX;
                                selectRect.x=rectx-selectRect.width;

                                selectRect.height=selectRect.y-mouseY
                                selectRect.y=recty-selectRect.height;
                            }
                        }

                        grid.rectSelection(selectRect);
                    }
                    else
                    {

                    }

                    if (selectRect.visible)
                    {
                        selectRect.visible = false;
                    }
                }
            }
            Component.onCompleted: {
            }
        }
    }
    RoomFooter {
        id: footer
        height: 50
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        nameText: groupName

        onLoad: {
            var currgrId=operate.currentGroupId;
            var currRoomId=operate.currentRoomId;
            attendeesModel.clear()
            Logic.queryAttendees(currgrId, onResetAttendees);
        }

        onStart: {
            meetingControl("start");
        }

        onStop: {
            meetingControl("stop");
        }

        onChangeMode: {
            broadCastControl(broadCast);
        }

        onChangeSpecial: {
            specialControl(spec);
        }

        onOpenTransferPage: {
            if (!transferDlg.visible)
            {
                transferDlg.groupId = groupId;
                transferDlg.attendees = attendeesOfRoom();
                transferDlg.open();
                transferDlg.load();
            }
        }
    }

    TransferManageDialog {
        id: transferDlg
        onUpdate: {
            root.updateTransferPeer(accounta,froma, accountb, fromb);
            operate.onSelectedAttendeeChange(groupId, roomStatus, selection);
        }
        onDeltransfer: {
            root.deletTransferPeer(usera,userb);
            operate.onSelectedAttendeeChange(groupId, roomStatus, selection);
        }
    }

    onSelectionChanged: {
        operate.onSelectedAttendeeChange(groupId, roomStatus, selection);
    }

    onModeChanged: {
        updateMode();
        operate.onRoomBroadcastChange(groupId, mode === 1);
    }

    onSpecialIntercomChanged: {
        updateSpecialIntercom();
    }

}

