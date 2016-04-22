import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4

import "../listener.js" as Logic


Item {
    id: base
    width: 800
    height: 150

    signal call(var per)
    signal bye(var per)
    signal deaf(var per, bool bDeaf)
    signal mute(var per, bool bMute)
    signal promote(var per,  string role)
    signal specialty(var per, bool bEnable)

    property var person
    property bool bDeaf
    property bool bMute
    property string role
    property bool bEnable
    property bool meetingOpened: false
    property bool broadcast: false
    MessageDialog {
        id: messageShow;
        modality: Qt.ApplicationModal;
        title: "消息提示！";
        text:"此操作只有在解除转接后生效！"
        standardButtons: StandardButton.Ok;
        onAccepted: {
            messageShow.close();
        }

    }
    MessageDialog{
        id:transferMessage
        modality: Qt.ApplicationModal;
        title: "消息提示！";
        text:"设置成功转接列表将删除!"
        standardButtons: StandardButton.Yes|StandardButton.No
        onYes:{
            base.promote(person, Logic.getRoleValue("COMMANDER"));
            commanderBtn.checked=false;
        }
        onNo: commanderBtn.checked=false;
    }
    MessageDialog{
        id:specialMessage
        modality: Qt.ApplicationModal;
        title: "消息提示！";
        text:"设置成功专向将失效!"
        standardButtons: StandardButton.Yes|StandardButton.No
        onYes: {
            base.promote(person, Logic.getRoleValue("COMMANDER"));
            commanderBtn.checked=false;
        }
        onNo:  commanderBtn.checked=false;
    }
    MessageDialog{

        id:superiorMessage
        modality: Qt.ApplicationModal;
        title: "消息提示！";
        text:"设置成功越级将失效!"
        standardButtons: StandardButton.Yes|StandardButton.No
        onYes: {
            base.promote(person, Logic.getRoleValue("COMMANDER"));
            commanderBtn.checked=false;
        }
        onNo: {
            commanderBtn.checked=false;
        }
    }
    MessageDialog{
        id:announceMessage
        modality: Qt.ApplicationModal;
        title: "消息提示！";
        text:"设置成功广播将失效!"
        standardButtons: StandardButton.Yes|StandardButton.No
        onYes: {
            base.promote(person, Logic.getRoleValue("COMMANDER"));
            commanderBtn.checked=false;
        }
        onNo: commanderBtn.checked=false;
    }

    MessageDialog{
        id:commanderMessage
        modality: Qt.ApplicationModal;
        title: "消息提示！";
        text:"每组只能有一个指挥员"
        standardButtons: StandardButton.Ok
        onAccepted: {
            commanderMessage.close();
            commanderBtn.checked=false;
        }
    }


    function setPerson(per, roomstatus)
    {
        person = per;
        meetingOpened = roomstatus === "running";
        updatePerson(person);
    }

    function getPersonId()
    {
        if (person)
            return person.accountId + person.fromId;
        else
            return null;
    }

    function refresh()
    {
        console.log("CommandPad refresh");
        updatePerson(person);
    }

    function updateMode()
    {
        if (broadcast)
        {
            promoteBtn.visible = true;
            specialtyBtn.visible = true;
            announceBtn.visible = true;
            commanderBtn.visible=true
            deafBtn.visible = true;
            muteBtn.visible = true;

        }
        else
        {
            promoteBtn.visible = false;
            specialtyBtn.visible = false;
            announceBtn.visible = false;
            commanderBtn.visible=false;
            deafBtn.visible = false;
            muteBtn.visible = false;
        }
        updatePerson(person)
    }

    function updatePerson(attendee)
    {
        if (attendee)
        {
            enabled = true;
            muteBtn.checked = (attendee.speakable === "0");
            deafBtn.checked = (attendee.listenable === "0");
            callBtn.enabled = meetingOpened && (attendee.phoneStatus === "DISCONNECTED");
            byeBtn.enabled = meetingOpened&&(attendee.phoneStatus === "CONNECTED")||(attendee.phoneStatus === "CONNECTING");

            //console.log("meetingOpened is " + meetingOpened);
            if (broadcast)
            {
                promoteBtn.visible = true;
                announceBtn.visible = true;
                commanderBtn.visible=true;
                promoteBtn.checked = false;
                announceBtn.checked = false;
                commanderBtn.checked=false
                if (attendee.role === Logic.getRoleValue("COMMANDER"))
                {
                    promoteBtn.visible = false;
                    announceBtn.visible = false;
                    deafBtn.visible=false;
                    muteBtn.visible=false;
                    specialtyBtn.visible=false;
                    commanderBtn.visible=true;
                    commanderBtn.checked=true;
                }
                else if (attendee.role === Logic.getRoleValue("SUPERIOR"))
                {
                    promoteBtn.checked = true;
                    deafBtn.visible=true;
                    muteBtn.visible=true;
                    specialtyBtn.visible=false;
                }else if (attendee.role === Logic.getRoleValue("ANNOUNCER"))
                {
                    announceBtn.checked = true;
                    specialtyBtn.visible = false;
                    deafBtn.visible=true;
                    muteBtn.visible=true;
                    promoteBtn.visible=true;
                    announceBtn.visible=true;
                }
                else if(attendee.specialIntercom==="1")
                {
                    promoteBtn.visible = false;
                    specialtyBtn.visible = true;
                    commanderBtn.visible=true
                    announceBtn.visible = false;
                    deafBtn.visible = true;
                    muteBtn.visible = true;
                }
                else if(attendee.oppositeAccountId||attendee.oppositeFromId)
                {
                    promoteBtn.visible = false;
                    specialtyBtn.visible = false;
                    announceBtn.visible = false;
                    commanderBtn.visible=true
                    deafBtn.visible = true;
                    muteBtn.visible = true;
                }
                else
                {
                    promoteBtn.visible = true;
                    specialtyBtn.visible = true;
                    announceBtn.visible = true;
                    deafBtn.visible = true;
                    muteBtn.visible = true;
                    commanderBtn.visible=true
                }

                specialtyBtn.checked = attendee.specialIntercom === "1";
            }
        }
        else
        {
            enabled = false;
        }

    }
    Timer{
        id:commanderTime
        interval: 3000
        repeat: true
        running: true
        onTriggered: {
            commanderMessage.close()
            commanderBtn.checked=false
            commanderTime.stop();
        }
    }


    onMeetingOpenedChanged: {
        updatePerson(person)
    }

    onBroadcastChanged: {
        updateMode();
    }

    BorderImage{
        id:footermid
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        source: "../images/command_bottom.png"
        Row {
            anchors.right: parent.right
            anchors.rightMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            spacing: 15

            FancyButton {
                id: callBtn
                width: 80
                height: 30
                text: qsTr("呼叫")
                onClicked: {
                    if(operate.personLength==1)
                    {
                        base.call(person);
                    }
                    else
                    {
                        base.call(operate.manyPerson);
                    }
                }
            }
            FancyButton {
                id: byeBtn

                width: 80
                height: 30
                text: qsTr("挂断")

                onClicked: {
                    if(operate.personLength==1)
                    {
                        base.bye(person);
                    }
                    else
                    {
                         base.bye(operate.manyPerson);
                    }

                }
            }

            CheckButton {
                id: deafBtn //No Listening

                width: 80
                height: 30
                text: qsTr("分隔")

                onClicked: {
                    if(operate.personLength==1)
                    {
                        if(person.oppositeAccountId||person.oppositeFromId)
                        {
                            if(checked)
                            {
                                messageShow.open();

                                base.deaf(person,checked)
                            }
                            else
                            {
                                base.deaf(person,checked)
                            }
                        }
                        else
                        {
                            base.deaf(person,checked)
                        }
                    }
                    else
                    {
                       base.deaf(operate.manyPerson, checked);
                    }
                }
            }

            CheckButton {
                id: muteBtn
                width: 80
                height: 30
                text: qsTr("屏蔽")
                onClicked: {
                    if(operate.personLength==1)
                    {
                        if(person.oppositeAccountId||person.oppositeFromId)
                        {
                            if(checked)
                            {
                                messageShow.open();
                                base.mute(person,checked)
                            }
                            else
                            {
                                base.mute(person,checked)
                            }
                        }
                        else
                        {
                            base.mute(person,checked)
                        }
                    }
                    else
                    {
                        base.mute(operate.manyPerson, checked);
                    }
                }
            }
            CheckButton{
                id:commanderBtn
                width: 80
                height: 30
                text:qsTr("指挥员")
                onClicked: {
                    if(operate.personLength==1)
                    {
                        if(checked)
                        {
                            if(person.oppositeAccountId&&person.oppositeFromId)
                            {
                                if(operate.flag=="0")
                                {
                                    transferMessage.open();
                                }
                                else
                                {
                                    base.promote(person, Logic.getRoleValue("COMMANDER"));
                                }
                            }
                            else if(person.specialIntercom=="1")
                            {
                                if(operate.flag=="0")
                                {
                                    specialMessage.open();
                                }
                                else
                                {
                                    base.promote(person, Logic.getRoleValue("COMMANDER"));
                                }
                            }
                            else if(person.role=="2")
                            {
                                if(operate.flag=="0")
                                {
                                    superiorMessage.open();
                                }
                                else
                                {
                                    base.promote(person, Logic.getRoleValue("COMMANDER"));
                                }
                            }
                            else if(person.role=="3")
                            {
                                if(operate.flag=="0")
                                {
                                    announceMessage.open();
                                }
                                else
                                {
                                    base.promote(person, Logic.getRoleValue("COMMANDER"));
                                }
                            }
                            else
                            {
                                if(operate.flag=="0")
                                {
                                    base.promote(person, Logic.getRoleValue("COMMANDER"));
                                    commanderBtn.checked=false;
                                }
                                else
                                {
                                    base.promote(person, Logic.getRoleValue("COMMANDER"));
                                }
                            }
                        }
                        else
                        {
                            base.promote(person, Logic.getRoleValue("SUBORDINATE"));
                        }
                    }
                    else
                    {
                        commanderMessage.open();
                        commanderTime.start();
                    }
                }

            }

            CheckButton {
                id: promoteBtn

                width: 80
                height: 30
                text: qsTr("越级")

                onClicked: {
                    if(operate.personLength==1)
                    {
                        if (checked)
                        {
                            base.promote(person, Logic.getRoleValue("SUPERIOR"));
                            announceBtn.checked = false;
                        }
                        else
                        {
                            if (person.role === Logic.getRoleValue("SUPERIOR"))
                            {
                                base.promote(person, Logic.getRoleValue("SUBORDINATE"));
                            }
                        }
                    }
                    else
                    {

                        if (checked)
                        {
                            base.promote(operate.manyPerson, Logic.getRoleValue("SUPERIOR"));
                            announceBtn.checked = false;
                        }
                        else
                        {
                            if (person.role === Logic.getRoleValue("SUPERIOR"))
                            {
                                base.promote(operate.manyPerson, Logic.getRoleValue("SUBORDINATE"));
                            }
                        }
                    }
                }
            }

            CheckButton {
                id: announceBtn

                width: 80
                height: 30
                text: qsTr("广播")

                onClicked: {
                    if(operate.personLength==1)
                    {
                        if (checked)
                        {
                            base.promote(person, Logic.getRoleValue("ANNOUNCER"));
                            promoteBtn.checked = false;
                        }
                        else
                        {
                            if (person.role === Logic.getRoleValue("ANNOUNCER"))
                            {
                                base.promote(person, Logic.getRoleValue("SUBORDINATE"));
                            }
                        }
                    }
                    else
                    {
                        if (checked)
                        {
                            base.promote(operate.manyPerson, Logic.getRoleValue("ANNOUNCER"));
                            promoteBtn.checked = false;
                        }
                        else
                        {
                            if (person.role === Logic.getRoleValue("ANNOUNCER"))
                            {
                                base.promote(operate.manyPerson, Logic.getRoleValue("SUBORDINATE"));
                            }
                        }
                    }

                }
            }

            CheckButton {
                id: specialtyBtn

                width: 80
                height: 30
                text: qsTr("加入专向")
                onClicked: {

                    if(operate.personLength==1)
                    {
                        base.specialty(person, checked);
                    }
                    else
                    {                       
                            base.specialty(operate.manyPerson, checked);
                    }

                }
            }
        }
    }


    Component.onCompleted: {

        setPerson(null);
        updateMode();
    }
}



