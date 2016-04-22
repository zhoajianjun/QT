import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import "../logManger"
import "../listener.js"as Logic
ScrollView{
    function standardOutput(value){
        return value < 10 ? ("0" + value) : value
    }

    function timeToLocalTime(time)
    {
        var today = new Date(time*1000);
        var year=today.getFullYear()
        var month=standardOutput(today.getMonth()+1)
        var days=standardOutput(today.getDate())
        var hours=standardOutput(today.getHours())
        var minutes=standardOutput(today.getMinutes())
        var seconds=standardOutput(today.getSeconds())
        var timelist=year+'-'+month+'-'+days+' '+hours+':'+minutes+':'+seconds
        return timelist
    }
    function getMeetingInfo(meetingEvent,meetingdescribe)
    {
        if(meetingEvent=="会议开始")
        {
            var  meetingRoomAndGroup=meetingdescribe.split(",");
            return meetingRoomAndGroup
        }

    }
    function getLogListView(logslist)
    {
        operateLogModel.clear();
        for(var i=0;i<logslist.length;++i)
        {
            if(i==2)
            {
                var logtext=logslist[i].meetDescribe.split(",")
                for(var j=0;j<logtext.length;++j)
                {
                    if(j%3==0)
                    {
                        list+='\n'
                    }
                    list+=logtext
                }
            }
            operateLogModel.append(logslist[i]);
        }
    }


    style: ScrollViewStyle {
        handle: Item{
            implicitWidth: 13
            implicitHeight: 13
            Rectangle {
                color: "#123863"
                anchors.fill: parent
                visible: true
            }
        }
        decrementControl:Image{
            width:13
            height: 13
            source:"../images/arrow_up.png"
        }
        incrementControl:Image{
            width:13
            height:13
            source:"../images/arrow_down.png"
        }
        scrollBarBackground: Item {
            implicitWidth: 13
            implicitHeight: 13
        }
    }
    ListView {
        anchors.fill: parent
        model: operateListModel
        focus: false
        delegate:
            Item {
            id: logdelegate
            width: parent.width
            height: 35
            RowLayout {
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width
                anchors.verticalCenter: parent.verticalCenter
                spacing: 8
                Text {
                    id: timeText
                    color: "black"
                    text: timeToLocalTime(time)
                    Layout.preferredWidth: (parent.width-10)/3
                }
                Text {
                    id: meetingRoomText
                    color: "black"
                    text:
                    {
                        var meetingRoom=getMeetingInfo(event,describe);
                        return meetingRoom[1];
                    }
                    Layout.preferredWidth: (parent.width-10)/4
                }
                Text{
                    id: meetingGroupeText
                    color: "black"
                    text:{
                        var meetingGroupe=getMeetingInfo(event,describe);
                        return meetingGroupe[2];
                    }
                    Layout.preferredWidth: (parent.width-10)/3
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked:
                {
                    logdelegate.ListView.view.currentIndex=index
                    Logic.quaryloglist(uuid,getLogListView);
                }
            }
        }

        highlight: Rectangle{
            color: "#123863"
            border.color: "gray"
            border.width: 1

        }
    }
}


