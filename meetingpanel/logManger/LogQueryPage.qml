import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4
import "../logManger"
import "../operating"
import "../listener.js"as Logic

Rectangle {
    id:logquerypage
    width: 1000
    height: 800
    visible: false
    color: "#a7b3bc"
    property int logLength
    property var roomAndGroup:[]
    property var list: []
    property int modelIndex:0
    function getLogList(logs)
    {
        operateListModel.clear();
        if(!logs)
        {
            logDialog.open();
            warningTime.running=true
        }
        else
        {
            for(var i=0;i<logs.length;++i)
            {
                operateListModel.append(logs[i]);
            }
        }
    }
    function getEquipmentLog(equipmentlog)
    {
        equipmentListModel.clear();
        console.log(equipmentlog)
        if(!equipmentlog)
        {
            logDialog.open()
            warningTime.running=true
        }
        else
        {
            for(var i=0;i<equipmentlog.length;++i)
            {
                equipmentListModel.append(equipmentlog[i]);
            }
        }
    }
    function quaryTodayLog(index)
    {               
        var d = new Date();
        var year=d.getFullYear()
        var month=standardOutput(d.getMonth()+1)
        var week=d.getDay()+1
        var days=standardOutput(d.getDate())
        var secondTime=d.getTime()
        var fullYear=year+"-"+month+"-"+days
        var newTime = Date.parse(fullYear);
        if(index=="0")
        {
            if(modelIndex=="0")
            {
                Logic.queryLog(newTime/1000,secondTime/1000,getLogList);
            }
            else
            {
                Logic.quaryEquipmentLog(newTime/1000,secondTime/1000,getEquipmentLog)
            }
        }
        else if(index=="1")
        {
            var tmpTime = (week-1)*24*3600*1000
            var starttime=secondTime-newTime
            var time=secondTime-starttime-tmpTime
            if(modelIndex=="0")
            {
                Logic.queryLog(time/1000,secondTime/1000,getLogList);
            }
            else
            {
                Logic.quaryEquipmentLog(time/1000,secondTime/1000,getEquipmentLog)
            }
        }
        else if(index=="2")
        {
            var tmpTimes = (days-1)*24*3600*1000
            var starttimes=secondTime-newTime
            var times=secondTime-starttimes-tmpTimes
            if(modelIndex=="0")
            {
                Logic.queryLog(times/1000,secondTime/1000,getLogList);
            }
            else
            {
                Logic.quaryEquipmentLog(times/1000,secondTime/1000,getEquipmentLog)
            }
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
    function getCurrentTime(startTime,endTime)
    {
        operateLogModel.clear()
        var starttime=Date.parse(startTime)/1000;
        var endtime=Date.parse(endTime)/1000;
        var newTime = Date.parse(endTimeDate.text);
        var d = new Date();
        var year=d.getFullYear()
        var month=standardOutput(d.getMonth()+1)
        var days=standardOutput(d.getDate())
        var secondTime=standardOutput(d.getTime())
        var fullYear=year+'-'+month+"-"+days
        console.log(starttime+"   "+endtime)
        if(startTime&&endTime&&endTime>=startTime)
        {
            if(starttime==endtime)
            {
                if(fullYear==endTime)
                {
                    endtime=endtime+(secondTime-endtime*1000)/1000
                }
                else
                {
                    endtime=endtime+24*60*60
                }
            }
            else if(endtime>starttime)
            {
                endtime=endtime+24*60*60
            }
            if(modelIndex=="0")
            {
                Logic.queryLog(starttime,endtime,getLogList);
            }
            else
            {
                Logic.quaryEquipmentLog(starttime,endtime,getEquipmentLog)
            }
        }
        else
        {
            warningDialog.open();
            warningTime.running=true
        }
    }
    function getMeetingInfo(meetingEvent,meetingdescribe)
    {
        if(meetingEvent=="会议开始")
        {
            var  meetingRoomAndGroup=meetingdescribe.split(",");
            return meetingRoomAndGroup
        }

    }
    function getLogListHeight(meetingEvent,meetingDescribe)
    {
        if(meetingEvent=="与会人员")
        {
            var logtext=meetingDescribe.split(",")
            if(logtext.length>0&&logtext.length<=8)
            {
                return 60;
            }
            else if(logtext.length>8&&logtext.length<=16)
            {
                return 90;
            }
            else if(logtext.length>16&&logtext.length<=24)
            {
                return 120;
            }
            else if(logtext.length>24&&logtext.length<=32)
            {
                return 150;
            }
            else
            {
                return 180;
            }
        }
        else
        {
            return 40;
        }
    }
    function showMeetingInfo(meetingEvent,meetingDescribe)
    {
        if(meetingEvent=="与会人员")
        {
            var meetinglog=[]
            var logtext=meetingDescribe.split(",")
            for(var i=0;i<logtext.length;++i)
            {
                if(i!=0&&i%3==0)
                {
                    meetinglog.push('\n')
                }
                meetinglog.push(logtext[i])
            }
            return meetinglog.toString()
        }
        else
        {
            return meetingDescribe
        }
    }
    Timer{
        id:warningTime
        repeat: true
        running: false
        interval:1000
        onTriggered: {
            warningDialog.close()
            logDialog.close()
            running=false
        }

    }

    Image {
        id:topimages
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 70
        source: "../images/top.png"
        Text {
            id: titleText
            x:10
            y:10
            width: 114
            height: 37
            text: qsTr("日志查询")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            font.pixelSize: 22
            color: "white"
        }
    }
    MessageDialog {
        id: exitDialog
        modality: Qt.ApplicationModal
        title: "退出"
        text: "确定要退出此程序吗?"
        standardButtons: StandardButton.Ok | StandardButton.No
        onAccepted: {
            Qt.quit()
        }
        onRejected: {
            exitDialog.close()
        }
    }


    MessageDialog{
        id:warningDialog
        modality: Qt.ApplicationModal
        title: "提示信息"
        text: "请输入正确的查询时间！"
        standardButtons: StandardButton.Ok
        onAccepted: {
            warningDialog.close();
        }
    }

    MessageDialog {
        id: logDialog
        modality: Qt.ApplicationModal
        title: "提示信息"
        text: "没有数据信息！"
        standardButtons: StandardButton.Ok
        onAccepted: {
            logDialog.close();
        }
    }

    Image{
        id:exitsystem;
        anchors.right: parent.right;
        anchors.rightMargin: 20
        anchors.top: parent.top;
        anchors.topMargin: 27
        sourceSize.width: 100
        sourceSize.height: 35
        source:"../images/quitsystem01.png";
        fillMode: Image.PreserveAspectCrop;
        MouseArea{
            id:exitMouserArea
            anchors.fill: parent
            hoverEnabled: true;
            onEntered:exitsystem.source = "../images/quitsystem02.png";
            onExited:  exitsystem.source = "../images/quitsystem01.png";
            onClicked: {
                exitDialog.open();
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
        id:returnImage;
        anchors.right: exitsystem.left;
        anchors.rightMargin: 20
        anchors.top: parent.top;
        anchors.topMargin: 27
        sourceSize.width: 100
        sourceSize.height: 35
        source:"../images/returnMain01.png";
        fillMode: Image.PreserveAspectCrop;
        MouseArea{
            id:returnMouserArea
            anchors.fill: parent
            hoverEnabled: true;
            onEntered:returnImage.source = "../images/returnMain02.png";
            onExited:  returnImage.source = "../images/returnMain01.png";
            onClicked: {
                logquerypage.visible=false;
                work.showOperateView()
                operateListModel.clear();
                operateLogModel.clear()
                startTimeDate.text=""
                endTimeDate.text=""
            }
            onReleased: {
                returnImage.state == "clicked"
            }
        }
        states: [
            State {
                name: "clicked"
                PropertyChanges { target: exitsystem;source:"../images/returnMain01.png"}
            },
            State {
                name: "unclicked"
                when: exitMouserArea.pressed
                PropertyChanges { target: exitsystem;source:"../images/returnMain03.png" }
            }
        ]
        state: "clicked"
    }

    SplitView
    {
        id:split
        handleDelegate: Rectangle{
            width: 1
            height: 1
            color: "#7d8f9c"
        }
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 5

        anchors.top: topimages.bottom
        anchors.bottom: parent.bottom


    Item {
        id: leftModelItem
        width: 260
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        Layout.minimumWidth: 100
        Layout.maximumWidth: 300


        Image {
            id: dateModelImage
            height: 30
            width: parent.width
            anchors.top: leftModelItem.top
            anchors.topMargin: 2
            anchors.left:parent.left
            anchors.leftMargin: 0
            source: "../images/meeting_back_image.png"
            Text {
                id: modelText
                anchors.centerIn: parent
                color: "white"
                font.pixelSize:18
                text: qsTr("日志类型")
            }
        }
        LogTreeView{
            id:logTreeView
            width: parent.width
            height: 200
            color: "#7d8f9c"
            anchors.top: dateModelImage.bottom
            anchors.topMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

    Image {
        id: logModelImage
        height: 30
        width: parent.width
        anchors.top: logTreeView.bottom
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 0
        source: "../images/meeting_back_image.png"
        Text {
            id: dateText
            color: "white"
            font.pixelSize:18
            anchors.centerIn: parent
            text: qsTr("查询条件")
        }
    }

    Rectangle{
        id:dateRect
        x: 8
        width: parent.width
        height: 310
        anchors.top: logModelImage.bottom
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        color: "#7d8f9c"
        TextField
         {
             id:startTimeDate
             y:65
             width: parent.width
             height: 25
             anchors.left: parent.left
             anchors.leftMargin: 0
             anchors.top:dateComboBox.bottom
             anchors.topMargin: 10
             readOnly: true
             focus: true
             placeholderText:"开始时间"
             property string dateValue
             Calendar {
                 id: calendar
                 anchors.top: parent.bottom
                 anchors.topMargin: 0
                 width: parent.width
                 height: 200
                 visible: false
                 weekNumbersVisible: false
                 style: CalendarStyle {
                     gridVisible: true
                     dayDelegate: Rectangle {
                         gradient: Gradient {
                             GradientStop {
                                 position: 0.00
                                 color: styleData.selected ?"lightblue" : (styleData.visibleMonth && styleData.valid ?"#fff" : "#b6b6b6");
                             }
                             GradientStop {
                                 position: 1.00
                                 color: styleData.selected ?"lightblue" : (styleData.visibleMonth && styleData.valid ?"#fff" : "#b6b6b6");
                             }
                             GradientStop {
                                 position: 1.00
                                 color: styleData.selected ?"lightblue" : (styleData.visibleMonth && styleData.valid ?"#fff" : "#b6b6b6");
                             }
                         }

                         Label {
                             text: styleData.date.getDate()
                             anchors.centerIn: parent
                             color: styleData.valid ?"black" : "white"
                         }
                         Rectangle {
                             width: parent.width
                             height: 1
                             color: "#fff"
                             anchors.bottom: parent.bottom
                         }
                         Rectangle {
                             width: 1
                             height: parent.height
                             color: "#fff"
                             anchors.right: parent.right
                         }
                     }
                     navigationBar:Rectangle{
                         height: 25
                         Button {
                             id: previousMonth
                             width: parent.height
                             height: width
                             anchors.verticalCenter: parent.verticalCenter
                             anchors.left: parent.left
                             iconSource: "../images/date_arrow_left_image.png"
                             onClicked: control.showPreviousMonth()
                         }
                         Label {
                             id: date1
                             text: styleData.title
                             elide: Text.ElideRight
                             horizontalAlignment: Text.AlignHCenter
                             anchors.verticalCenter: parent.verticalCenter
                             anchors.left: previousMonth.right
                             anchors.leftMargin: 2
                             anchors.right: nextMonth.left
                             anchors.rightMargin: 2
                         }
                         Button {
                             id: nextMonth
                             width: parent.height
                             height: width
                             anchors.verticalCenter: parent.verticalCenter
                             anchors.right: parent.right
                             iconSource: "../images/date_arrow_right_image.png"
                             onClicked: control.showNextMonth()
                         }
                     }
                 }
                 onReleased:
                 {
                     startTimeDate.text = date;
                     startTimeDate.text = startTimeDate.text.substr(0, 10);
                     startTimeDate.dateValue = startTimeDate.text;
                     visible = false;
                     endTimeDate.visible=true;
                     queryBtn.visible=true
                 }
             }
             Button{
                 id: downBtn
                 width: 22
                 anchors.right: parent.right
                 anchors.rightMargin: 0
                 anchors.bottom: parent.bottom
                 anchors.bottomMargin: 0
                 anchors.top: parent.top
                 anchors.topMargin: 0
                 focus: true
                 iconSource: "../images/date.png"
                 onClicked:
                 {
                     if(startTimeDate.readOnly==false)
                     {
                         calendar.visible = !calendar.visible
                         calendar1.visible=false
                         //listmodel.clear()
                         //listmodelView.clear()
                         if(calendar.visible)
                         {
                             calendar.selectedDate=new Date();
                             endTimeDate.visible=false
                             queryBtn.visible=false
                         }
                         else
                         {
                             endTimeDate.visible=true
                             queryBtn.visible=true
                         }
                     }
                     else
                     {
                         calendar.visible=false
                     }
                 }
             }
             onDateValueChanged: {
                 startTimeDate.text = startTimeDate.dateValue;
                 calendar.selectedDate = startTimeDate.dateValue;
             }
         }
        TextField
        {
            id:endTimeDate
            width: parent.width
            height: 25
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: startTimeDate.bottom
            anchors.topMargin: 10
            readOnly: true
            focus: true
            placeholderText: "结束时间"
            property string dateValue
            Calendar {
                id: calendar1
                anchors.top: parent.bottom
                anchors.topMargin: 0
                width: parent.width
                height: 200
                visible: false
                weekNumbersVisible: false
                style: CalendarStyle {
                    gridVisible: true
                    dayDelegate: Rectangle {
                        gradient: Gradient {
                            GradientStop {
                                position: 0.00
                                color: styleData.selected ?"lightblue" : (styleData.visibleMonth && styleData.valid ?"#fff" : "#b6b6b6");
                            }
                            GradientStop {
                                position: 1.00
                                color: styleData.selected ?"lightblue" : (styleData.visibleMonth && styleData.valid ?"#fff" : "#b6b6b6");
                            }
                            GradientStop {
                                position: 1.00
                                color: styleData.selected ?"lightblue" : (styleData.visibleMonth && styleData.valid ?"#fff" : "#b6b6b6");
                            }
                        }

                        Label {
                            text: styleData.date.getDate()
                            anchors.centerIn: parent
                            color: styleData.valid ?"black" : "white"
                        }
                        Rectangle {
                            width: parent.width
                            height: 1
                            color: "#fff"
                            anchors.bottom: parent.bottom
                        }
                        Rectangle {
                            width: 1
                            height: parent.height
                            color: "#fff"
                            anchors.right: parent.right
                        }
                    }
                    navigationBar:Rectangle{
                        height: 25
                        Button {
                            id: previousMonths
                            width: parent.height
                            height: width
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            iconSource: "../images/date_arrow_left_image.png"
                            onClicked: control.showPreviousMonth()
                        }
                        Label {
                            id: dates
                            text: styleData.title
                            elide: Text.ElideRight
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: previousMonths.right
                            anchors.leftMargin: 2
                            anchors.right: nextMonths.left
                            anchors.rightMargin: 2
                        }
                        Button {
                            id: nextMonths
                            width: parent.height
                            height: width
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            iconSource: "../images/date_arrow_right_image.png"
                            onClicked: control.showNextMonth()
                        }
                    }
                }
                onReleased:
                {
                    endTimeDate.text = date;
                    endTimeDate.text = endTimeDate.text.substr(0, 10);
                    endTimeDate.dateValue = endTimeDate.text;
                    visible = false;
                    queryBtn.visible=true

                }
            }

            Button{
                id: downBtn1
                width: 22
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                iconSource: "../images/date.png"
                onClicked:
                {
                    if(endTimeDate.readOnly==false)
                    {
                        calendar1.visible = !calendar1.visible
                        calendar.visible=false
                        //listmodel.clear()
                        //listmodelView.clear()
                        if(calendar1.visible)
                        {
                            calendar1.selectedDate=new Date();
                            queryBtn.visible=false
                        }
                        else
                        {
                            queryBtn.visible=true
                        }
                    }
                    else
                    {
                        calendar1.visible=false
                    }
                }
            }
            onDateValueChanged: {
                endTimeDate.text = endTimeDate.dateValue;
                calendar1.selectedDate = endTimeDate.dateValue;
            }
        }
        ComboBox{
            id:dateComboBox
            width: parent.width
            anchors.top:parent.top
            anchors.topMargin: 10
            anchors.left:parent.left
            anchors.leftMargin: 0
            currentIndex: 0
            model: ListModel {
                id: dateSelectItems                
                ListElement { text: "今天";}
                ListElement { text: "本周";}
                ListElement { text: "本月";}
                ListElement { text: "自定义";}
            }
            onCurrentIndexChanged:
            {
                if(currentIndex=="3")
                {
                    operateListModel.clear();
                    operateLogModel.clear();
                    equipmentListModel.clear();
                    startTimeDate.readOnly=false;
                    endTimeDate.readOnly=false;
                }
                else
                {
                    //operateListModel.clear()
                    //operateLogModel.clear()
                    startTimeDate.text=""
                    endTimeDate.text=""
                    startTimeDate.readOnly=true
                    endTimeDate.readOnly=true
                }
                //console.log( dateSelectItems.get(currentIndex).text)
            }
        }
        ListModel {
            id:operateListModel
        }
        ListModel{
            id:equipmentListModel
        }

        ListModel{
            id:operateLogModel
        }

           FancyButton{
               id:queryBtn
               width: 100
               height: 27
               text: "查询"
               anchors.right:parent.right
               anchors.rightMargin: 30
               anchors.top:endTimeDate.bottom
               anchors.topMargin: 80
               onClicked: {
                   if(dateComboBox.currentIndex<=2)
                  {
                       quaryTodayLog(dateComboBox.currentIndex);
                       calendar.visible=false
                       calendar1.visible=false
                   }
                   else
                   { 
                       getCurrentTime(startTimeDate.text,endTimeDate.text);
                       calendar.visible=false
                       calendar1.visible=false
                   }
               }
           }
    }
    }
    Rectangle{
        id:rightModelItem
        color:"#a7b3bc"
        anchors.top:parent.top
        anchors.topMargin: -8
        anchors.left: leftModelItem.right
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        SplitView{
        handleDelegate: Rectangle{
            width: 1
            height: 1
            color: "lightgray"
        }
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        orientation: Qt.Vertical


        Item{
            id:logItem
            height: 375
            anchors.top:parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            Layout.minimumHeight:100
            Layout.maximumHeight:600
        OperateLog{
            id:operatelog
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            visible: {
                if(modelIndex=="0")
                {
                    return true;
                }
                else
                {
                   return false;
                }
            }
        }
        OperateLogListView{
            id:operateLogList
            anchors.top: operatelog.bottom
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            visible: {
                if(modelIndex=="0")
                {
                    return true
                }
                else
                {
                    return false
                }
            }
        }
        }
        Item{
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: logItem.bottom
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            OperateLogTitle{
                id:operateTitle
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                visible: {
                    if(modelIndex=="0")
                    {
                        return true
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            OperateLogView{
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.top: operateTitle.bottom
                anchors.topMargin: 5
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                visible: {
                    if(modelIndex=="0")
                    {
                        return true
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
        }


        EquipmentLogListView{
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            visible: {
                if(modelIndex=="1")
                {
                    return true
                }
                else
                {
                    return false
                }
            }
        }
    }
}
}

