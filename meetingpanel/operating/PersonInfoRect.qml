import QtQuick 2.0

import "../listener.js" as Logic
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Item {
    id: item1
    width: 200
    height: 600

    property var person

    function updatePerson(attendee)
    {
        person = attendee;
        if (attendee)
        {
            if (!attendee.userName)
            {
                console.log("no username field");
                return;
            }

            userNameTxt.text = attendee.userName;
            userTypeTxt.text = attendee.tu_type;
            nameTxt.text = attendee.realName;
            onlineTxt.text = Logic.getChineseOnlineState(attendee.onlineStatus);
            phoneStatusTxt.text = Logic.getChinesePhoneState(attendee.phoneStatus);
            listenableTxt.text = attendee.listenable === "1" ? "有":"无";
            speakableTxt.text = attendee.speakable ==="1" ? "有":"无";
            roleTxt.text = Logic.getChineseRoleName(attendee.role);
            specialTxt.text = attendee.specialIntercom ==="1" ? "是":"否";
            accountIdTxt.text = attendee.accountId;

        }
        else {
            userNameTxt.text = "--";
            userTypeTxt.text = "--";
            roleTxt.text = "--";
            specialTxt.text = "--";
            nameTxt.text = "--";
            onlineTxt.text = "--";
            phoneStatusTxt.text = "--";
            listenableTxt.text = "--";
            speakableTxt.text = "--";
            accountIdTxt.text = "--"
        }
    }

    Item {
        id: titleRect

        height: 50
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        Image {
            id: grouplistimage
            height: 50
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.verticalCenterOffset: 0
            anchors.verticalCenter: parent.verticalCenter
            source: "../images/list.png"
            Text {
                text: qsTr("用户信息")
                anchors.centerIn: grouplistimage
                color: "#eeeeee"
            }
        }
    }
    Rectangle{
        id:userbackrect
        width: parent.width
        height: parent.height
        anchors.top:titleRect.bottom
        anchors.bottom: parent.bottom
        color: "#7d8f9c"
        ScrollView{
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 8
            style: ScrollViewStyle {
                handle: Item{
                    implicitWidth: 12
                    implicitHeight: 12
                    Rectangle {
                        color: "#425e7b"
                        anchors.fill: parent
                        visible: true
                    }
                }
                decrementControl:Image{
                    width:12
                    height: 12
                    source: "../images/arrow_up.png"
                }
                incrementControl:Image{
                    width:12
                    height: 12
                    source: "../images/arrow_down.png"
                }
                scrollBarBackground: Item {
                    implicitWidth: 12
                    implicitHeight: 12
                }
            }
            Row {
                id: row1
                width: parent.width
                anchors.top:parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 25

                Column {
                    id: col1
                    anchors.top:parent.top
                    anchors.topMargin: 10
                    width: 100

                    Text {
                        id: nameTxt1
                        height: 30
                        text: qsTr("姓名:")
                        color: "black"
                        font.pixelSize: 12
                    }

                    Text {
                        id: userNameTxt1
                        height: 30
                        text: qsTr("用户名:")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: roleTxt1
                        height: 30
                        text: qsTr("用户角色:")
                        font.pixelSize: 12
                        color: "black"
                    }
                    Text {
                        id: specialTxt1
                        height: 30
                        text: qsTr("加入专向:")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: userTypeTxt1
                        height: 30
                        text: qsTr("用户类型:")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: onlineTxt1
                        height: 30
                        text: qsTr("在线状态:")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: phoneStatusTxt1
                        height: 30
                        text: qsTr("连接状态:")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: listenableTxt1
                        height: 30
                        text: qsTr("收听权:")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: speakableTxt1
                        height: 30
                        text: qsTr("发言权:")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: accountIdTxt1
                        height: 30
                        text: qsTr("账户ID:")
                        font.pixelSize: 12
                        color: "black"
                    }
                }

                Column {
                    id: col2
                    width: 12
                    anchors.top:parent.top
                    anchors.topMargin: 10
                    Text {
                        id: nameTxt
                        height: 30
                        text: qsTr("无")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: userNameTxt
                        height: 30
                        text: qsTr("无")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: roleTxt
                        height: 30
                        text: qsTr("无")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: specialTxt
                        height: 30
                        text: qsTr("无")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: userTypeTxt
                        height: 30
                        text: qsTr("无")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: onlineTxt
                        height: 30
                        text: qsTr("无")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: phoneStatusTxt
                        height: 30
                        text: qsTr("无")
                        font.pixelSize: 12
                        color: "black"
                    }


                    Text {
                        id: listenableTxt
                        height: 30
                        text: qsTr("无")
                        font.pixelSize: 12
                        color: "black"
                    }

                    Text {
                        id: speakableTxt
                        height: 30
                        text: qsTr("无")
                        font.pixelSize: 12
                        color: "black"
                    }
                    Text {
                        id: accountIdTxt
                        height: 30
                        text: qsTr("无")
                        font.pixelSize: 12
                        color: "black"
                    }
                }

            }
        }
    }

    Component.onCompleted: {
        updatePerson(null)
    }
}

