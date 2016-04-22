import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import "../logManger"
import "../listener.js"as Logic

ScrollView{
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
            source: "../images/arrow_up.png"
        }
        incrementControl:Image{
            width:13
            height: 13
            source: "../images/arrow_down.png"
        }
        scrollBarBackground: Item {
            implicitWidth: 13
            implicitHeight: 13
        }
    }

    ListView{
        id:meetingLogView
        x: 0
        y: 487
        width: parent.width
        height: 331
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        model:operateLogModel
        focus: true

        delegate:
            Item {
            id: loglistview
            width: parent.width
            height:
            {
                getLogListHeight(meetEvent,meetDescribe);
            }

            RowLayout{
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter:parent.verticalCenter
                spacing: 8
                Text {
                    id: time
                    text:timeToLocalTime(meetTime)
                    color: "black"
                    anchors.verticalCenter: parent.verticalCenter
                    Layout.preferredWidth: 200
                }
                Text {
                    text: meetEvent
                    color: "black"
                    anchors.verticalCenter: parent.verticalCenter
                    Layout.preferredWidth: 120
                }
                Text {
                    text:
                    {
                        showMeetingInfo(meetEvent,meetDescribe)
                    }
                    verticalAlignment: Text.AlignVCenter
                    color:"black"
                    anchors.verticalCenter: parent.verticalCenter
                    Layout.preferredWidth: 360
                }
            }
        }
    }
}





