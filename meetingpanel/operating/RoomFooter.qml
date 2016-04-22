import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import "../listener.js" as Logic

Item {
    id: root
    width: parent.width
    height: 50
    //color: "#123863"

    property alias status: meetingStatusText.text
    property alias nameText: groupNameTxt.text
    property bool broadcast: false
    property bool special: false

    signal load()
    signal start()
    signal stop()
    signal changeMode(bool broadCast)
    signal changeSpecial(bool spec)
    signal openTransferPage()
    function updateMode(mode)
    {
        broadcast = (mode === 1);
        broadcastSwch.checked = broadcast;
        console.log("broadcastSwitch.checked is " + broadcastSwch.checked);
    }
    function updateSpecial(spec)
    {
        console.log("spec:"+spec)
        special = (spec === 1);
        specialIntercomBtn.checked = special;
    }
    function updateStatus(st)
    {
        if (st == "running")
        {
            status = "进行中";
            startBtn.enabled = false;
            stopBtn.enabled = true;
        }
        else
        {
            status = "空闲";
            startBtn.enabled = true;
            stopBtn.enabled = false;
        }
    }
    BorderImage {
        id: footerimage
        height: parent.height-5
        anchors.left: parent.left
        anchors.right: parent.right
        source: "../images/meeting_footer_image.png"
        Rectangle {
            id:grouprect
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            width: 80
            Text {
                anchors.fill: parent
                id: groupNameTxt
                text:  ""
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 16
                color: "white"
            }
        }
        Rectangle {
            id:meetrect
            width: 80
            anchors.left: grouprect.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            Text {
                id: meetingStatusText
                anchors.fill: parent
                text: qsTr("Unknown")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 16
                color: "white"
            }
        }
        Row
        {
            id: rowLayout1
            anchors.right: parent.right
            anchors.rightMargin: 42
            anchors.verticalCenter: parent.verticalCenter
            spacing: 15


            FancyButton {
                id: startBtn
                text: qsTr("开始")
                width: 80
                height: 30
                onClicked: {
                    root.start()
                }
            }

            FancyButton {
                id: stopBtn
                width: 80
                height: 30
                text: qsTr("关闭")
                onClicked: {
                    root.stop()
                }
            }

            TwoStateSwitch {
                id: broadcastSwch
                width: 110
                height: 30
                onClicked: {
                    root.changeMode(!broadcast);
                }
            }

            CheckButton {
                id: specialIntercomBtn
                width: 80
                height: 30
                text: qsTr("专向")
                visible: {
                    if(broadcast)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                onClicked: {
                    root.changeSpecial(!special);
                }
            }

            FancyButton {
                id: transferBtn
                width: 80
                height: 30
                text: qsTr("转接管理")
                visible: {
                    if(broadcast)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                onClicked: {
                    root.openTransferPage();
                }
            }
            FancyButton{
                id: refreshBtn
                text: qsTr("刷新")
                width: 80
                height: 30
                onClicked: {
                    root.load()
                }
            }
        }
    }


    Component.onCompleted: {
        broadcastSwch.checked = broadcast;
    }

    onBroadcastChanged: {
        broadcastSwch.checked = broadcast;
        console.log("broadcastSwitch.checked is " + broadcastSwch.checked);
    }

    onSpecialChanged: {
        specialIntercomBtn.checked = special;
    }

}

