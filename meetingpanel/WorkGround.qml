import QtQuick 2.0
import QtQuick.Dialogs 1.2

import "operating"
import "userManage"
import "logManger"

import "listener.js" as Logic

Rectangle {

    id: root

    width: 1200
    height: 800
    color:"#bbc5cc"

    property var target
    property bool running: false

    signal logout()

    function setTarget(tgt)
    {
        target = tgt
    }

    function start()
    {
        running = true;
        var handlers = {
            onTimeout: function (req){
                console.log("continuousQuery timeout");
            },
            onRequestSuccess: onNotify,
            onRequestError: function (req){
                console.log("ContinuousQuery Error");
            },
            isWorkRunning: isWorkRunning
        };
        Logic.startListen(target, handlers);
    }

    function stop()
    {
        running = false;
    }

    function onNotify(resp)
    {
        var detail = null;
        //console.log("resp:", Logic.serialize(resp, 5));
        if (resp && resp.result && resp.result.detail)
        {
            detail = resp.result.detail;
        }

        var objectNodes = [];
        if (!detail)
        {
            return;
        }

        if (detail.o)
        {
            Logic.parseAttendeeJsonObject(detail.o, objectNodes)
            for (var i = 0; i < objectNodes.length; i++)
            {
                operate.onNotify(objectNodes[i]);
            }
            //console.log("resp:", Logic.serialize(detail.o, 6));
        }

        var objectVioceNodes = [];
        if (detail.r)
        {
            Logic.parseVoiceJsonObject(detail.r, objectVioceNodes)
            for (var i = 0; i < objectVioceNodes.length; i++)
            {
                operate.onNotify(objectVioceNodes[i]);
            }
        }
        var objectSystemNodes=[]
        if(detail.n)
        {
            Logic.parseSystemNoticeJsonObject(detail.n,objectSystemNodes)
            for (var i=0;i<objectSystemNodes.length;i++)
            {
                if(objectSystemNodes[i].module==="system")
                {
                    if(objectSystemNodes[i].text)
                    {
                        warningDialog.text=objectSystemNodes[i].text;
                        warningDialog.open();
                        warningtime.running=true
                    }
                    else
                    {

                    }
                }
                else
                {

                }
            }
        }
    }

    function isWorkRunning()
    {
        return running;
    }

    function load()
    {
        operate.load();
    }

    function showUserManagePage()
    {
        operate.visible = false;
        manage.visible = true;
        manage.load();
    }

    function showOperateView()
    {
        manage.visible = false;
        operate.visible = true;
        operate.load();
    }
    function showlogMangerPage()
    {
        logmanger.quaryTodayLog("0")
        operate.visible = false;
        logmanger.visible=true
    }


    MessageDialog{
        id:warningDialog
        modality: Qt.ApplicationModal
        title: "提示信息"
//        standardButtons: StandardButton.Ok
//        onAccepted: {
//            warningDialog.close();
//        }
    }

    BorderImage {
        id: topImages
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        source: "../images/top.png"
    }
    OperateView {
        id: operate
        anchors.fill: parent
    }

    UserManagePage {
        id: manage
        anchors.fill: parent
    }
    LogQueryPage{
        id:logmanger
        anchors.fill: parent

    }

    Timer{
        id:warningtime
        interval: 2500
        running: false
        repeat: true
        onTriggered:{
            warningDialog.close()
        }
    }

    Component.onCompleted: {
        manage.visible = false;
    }
}
