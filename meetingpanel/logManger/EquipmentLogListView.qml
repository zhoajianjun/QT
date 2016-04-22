import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import "../logManger"
import "../listener.js"as Logic
TableView {
    id: tableView
    frameVisible: true
    currentRow: rowCount ? 0 : -1
    itemDelegate: Item {
        Text {
            anchors.verticalCenter: parent.verticalCenter
            color: "black"
            text: styleData.value
            anchors.left: parent.left
            anchors.leftMargin: 12
        }
    }
    rowDelegate: Rectangle{
        height: 30
        color: styleData.alternate? "#9cacb8" : "#a7b3bc"
        BorderImage{
            id: selected
            anchors.fill: parent
            source: "../images/selectedrow.png"
            visible: styleData.selected
            border{left:2; right:2; top:2; bottom:2}
            SequentialAnimation {
                running: true; loops: Animation.Infinite
                NumberAnimation { target:selected; property: "opacity"; to: 1.0; duration: 900}
                NumberAnimation { target:selected; property: "opacity"; to: 0.5; duration: 900}
            }
        }
    }

    TableViewColumn {
        role:"equipmentTime";
        title: qsTr("时间")
        width: tableView.viewport.width / 4
    }
    TableViewColumn {
        role: "equipmentUsername";
        title: qsTr("用户名");
        width: tableView.viewport.width / 4
    }
    TableViewColumn {
        role: "equipmentType";
        title: qsTr("设备类型")
        width: tableView.viewport.width / 4
    }
    TableViewColumn {
        role:"equipmentEvent";
        title:qsTr("事件")
        width:tableView.viewport.width/4
    }

    style: TableViewStyle {
        headerDelegate: BorderImage {
            id: name
            source: "../images/top.png"
            height: 30
            width: tableView.width/4
            Text {
                id: textItem
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: styleData.textAlignment
                anchors.leftMargin: 12
                text: styleData.value
                color: "white"
            }
        }
        handle: Item{
            implicitWidth: 12
            implicitHeight: 12
            Rectangle {
                color: "#7d8f9c"
                anchors.fill: parent
                visible: true
            }
        }
        decrementControl:Image{
            width:12
            height: 12
            source:
            {
                if(styleData.horizontal)
                {
                    return "../images/arrow_left.png"
                }
                else
                {
                    return "../images/arrow_up.png"
                }
            }
        }
        incrementControl:
            Image{
            width:12
            height: 12
            source:
            {
                if(styleData.horizontal)
                {
                    "../images/arrow_right.png"
                }
                else
                {
                    "../images/arrow_down.png"
                }
            }
        }
        scrollBarBackground: Rectangle {
            implicitWidth: 12
            implicitHeight: 12
            color: "#a7b3bc"
        }

    }

    model: equipmentListModel
}


//ScrollView{
//    function standardOutput(value){
//        return value < 10 ? ("0" + value) : value
//    }

//    function timeToLocalTime(time)
//    {
//        var today = new Date(time*1000);
//        var year=today.getFullYear()
//        var month=standardOutput(today.getMonth()+1)
//        var days=standardOutput(today.getDate())
//        var hours=standardOutput(today.getHours())
//        var minutes=standardOutput(today.getMinutes())
//        var seconds=standardOutput(today.getSeconds())
//        var timelist=year+'-'+month+'-'+days+' '+hours+':'+minutes+':'+seconds
//        return timelist
//    }


//    style: ScrollViewStyle {
//        handle: Item{
//            implicitWidth: 13
//            implicitHeight: 13
//            Rectangle {
//                color: "#123863"
//                anchors.fill: parent
//                visible: true
//            }
//        }
//        decrementControl:Image{
//            width:13
//            height: 13
//            source:"../images/arrow_up.png"
//        }
//        incrementControl:Image{
//            width:13
//            height:13
//            source:"../images/arrow_down.png"
//        }
//        scrollBarBackground: Item {
//            implicitWidth: 13
//            implicitHeight: 13
//        }
//    }
//    ListView {
//        anchors.fill: parent
//        model: equipmentListModel
//        focus: false
//        delegate:
//            Item {
//            id: logdelegate
//            width: parent.width
//            height: 35
//            RowLayout {
//                width: parent.width
//                anchors.left: parent.left
//                anchors.leftMargin: 40
//                anchors.verticalCenter: parent.verticalCenter
//                spacing: 8
//                Text {
//                    id: timeText
//                    color: "white"
//                    text: timeToLocalTime(equipmentTime)
//                    Layout.preferredWidth: (parent.width-40)/2
//                }
//                Text {
//                    id: userNameText
//                    color: "white"
//                    text:equipmentUsername.toString()
//                    Layout.preferredWidth: (parent.width-40)/2
//                }

//            }
//            MouseArea{
//                anchors.fill: parent
//                onClicked:
//                {
//                    logdelegate.ListView.view.currentIndex=index
//                    if(modelIndex=="0")
//                    {
//                        Logic.quaryloglist(uuid,getLogListView);
//                    }
//                    else
//                    {
//                        Logic.quarylEquipmentLog()

//                    }
//                }
//            }
//        }

//        highlight: Rectangle{
//            color: "#123863"
//            border.color: "gray"
//            border.width: 1

//        }
//    }
//}

