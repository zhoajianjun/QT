import QtQuick 2.0
import "../logManger"

Rectangle {
    id: modelRect
    color: "#9d8f7c"
    ListView {
        id: rootView
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        delegate: groupsDelegate
        model: listModel

        Component {
            id: groupsDelegate
            Item {
                id: container
                y:2
                width: 150
                height: childrenRect.height
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                       container.ListView.view.currentIndex=index
                        modelIndex=index;
                        console.log("modelIndex:"+modelIndex)
                        if(index=="0")
                        {
                           operateLogModel.clear()
                            if(dateComboBox.currentIndex=="0")
                            {
                              quaryTodayLog("0");
                            }
                            else if(dateComboBox.currentIndex=="1")
                            {
                                quaryTodayLog("1");
                            }
                            else if(dateComboBox.currentIndex=="2")
                            {
                                quaryTodayLog("2");
                            }
                        }
                        else
                        {
                            operateLogModel.clear()
                            if(dateComboBox.currentIndex=="0")
                            {
                              quaryTodayLog("0");
                            }
                            else if(dateComboBox.currentIndex=="1")
                            {
                                quaryTodayLog("1");
                            }
                            else if(dateComboBox.currentIndex=="2")
                            {
                                quaryTodayLog("2");
                            }
                        }

                    }
                }

                Column {
                    id: mainColumn
                    Row {
                        id: mainRow
                        spacing: 3
                        property bool expanded: false

                        Image {
                            id: expander
                            source: "../images/arrow_down_image_02.png"
                            rotation: mainRow.expanded ? -90 : 0
                            opacity: elements.count === 0 ? 0 : 1
                            Behavior on rotation {
                                NumberAnimation {duration: 110}
                            }

                            MouseArea {
                                visible: expander.opacity === 1 ? true : false
                                id: expanderMouseArea
                                anchors.fill: parent
                                onClicked: {
                                    mainRow.expanded = !mainRow.expanded
                                }
                            }
                        }

                        Text {
                            id: name
                            text: group
                            color: "black"
                            font.pixelSize: 16
                        }
                    }

                    Item {
                        width: 80
                        height: childView.contentHeight
                        visible: mainRow.expanded

                        ListView {
                            id: childView
                            anchors.fill: parent
                            model: elements
                            delegate: groupsDelegate
                            highlight: Rectangle {
                                anchors.left: parent.left
                                anchors.leftMargin: 15
                                color: "lightsteelblue";
                                radius: 5
                            }
                            focus: true
                        }
                    }
                }
            }
        }

        ListModel {
            id:listModel
            ListElement {
                group: "日志类型"
                elements: [
                    ListElement {group: "用户操作日志"; elements: []},
                    ListElement {group: "设备上下线日志"; elements: []}
                ]
            }
        }
    }

}
