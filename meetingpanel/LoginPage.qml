import QtQuick 2.0
import QtQuick.Controls 1.2

import "listener.js" as Logic

Rectangle {

    id: root

    signal loginSuccess(var tgt)
    color: "lightgreen"

    property bool loginning: false
    property var target

    function isLoginable()
    {
        if (loginning)
            return false;
        if (!addrRect.text)
            return false
        if (!userRect.text)
            return false
        if (!passwordRect.text)
            return false

        return true
    }

    function checkLoginable()
    {
        if (isLoginable())
            loginBtn.enabled = true
        else
            loginBtn.enabled = false
    }

    function login()
    {
        root.target = {
            addr : addrRect.text,
            username : userRect.text,
            password : passwordRect.text
        }
        var handlers = {
         onTimeout : onLoginTimeout,
         onRequestSuccess: function (req) {
                root.loginSuccess(root.target);
            },
         onRequestError: onLoginError

        }


        Logic.query(root.target, "xnode", handlers)
    }

    function onLoginTimeout()
    {
        loginning = false
        statusTxt.text = "login time out!"
        checkLoginable()
    }

    function onLoginError(req)
    {
        loginning = false
        statusTxt.text = "Error:" + req.status.toString()
        console.log("onLoginError")
    }

    Text {
        id: title
        y: 100
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter

        text: qsTr("音频调度控制面板")
        font.pixelSize: 40
    }

    Column {
        id: col

        width: 400
        y: title.y + title.height + 200

        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 3

        Rectangle {
            height: 50
            width: 500
            color: "red"
            Rectangle {
                id: addrText

                width: 200
                height: parent.height
                anchors.left: parent.left
                color: root.color

                Text {

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left

                    color: "blue"
                    text: "服务器地址:"
                    font.pixelSize: 20
                }

            }

            TextField {
                id: addrRect

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left

                anchors.leftMargin: addrText.width
                height: addrText.height

                focus: true

                placeholderText: qsTr("Enter addr")
                font.pixelSize: 20

                onTextChanged: {
                    checkLoginable()
                }
            }
        }

        Rectangle {
            height: 50
            width: 500
            Rectangle {
                id: userText

                width: 200
                height: parent.height
                anchors.left: parent.left
                color: root.color

                Text {

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left

                    color: "blue"
                    text: "用户名:"
                    font.pixelSize: 20
                }

            }

            TextField {
                id: userRect

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left

                anchors.leftMargin: userText.width
                height: userText.height

                focus: true

                placeholderText: qsTr("Enter name")
                font.pixelSize: 20

                onTextChanged: {
                    checkLoginable()
                }
            }
        }

        Rectangle {
            height: 50
            width: 500
            Rectangle {
                id: passwordText

                width: 200
                height: parent.height
                anchors.left: parent.left
                color: root.color

                Text {

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left

                    color: "blue"
                    text: "密码:"
                    font.pixelSize: 20
                }

            }

            TextField {
                id: passwordRect

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left

                anchors.leftMargin: passwordText.width
                height: passwordText.height

                focus: true

                placeholderText: qsTr("Enter password")
                font.pixelSize: 20

                onTextChanged: {
                    checkLoginable()
                }
            }
        }
    }


    Rectangle {
        id: buttonRect
        width: 600
        height: 50

        //anchors.left: col.left

        color: parent.color

        y: 600
        anchors.horizontalCenter: parent.horizontalCenter

        Button {
            id: cancel

            width: 200
            height: parent.height

            anchors.left: parent.left
            anchors.leftMargin: 10

            text: "退出"

            onClicked: {
                Qt.quit();
            }
        }

        Button {
            id: loginBtn

            width: 200
            height: parent.height
            anchors.right: parent.right
            anchors.rightMargin: 10

            text: "登录"
            onClicked: {
                login();
            }
        }

    }

    Text {
        id: statusTxt
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100

        color: "red"
        text: "goooooooooooooooooooo"
        font.pixelSize: 15
    }

    Component.onCompleted: {
        addrRect.text = "192.168.5.103"
        userRect.text = "admin"
        passwordRect.text = "111111"
        //checkLoginable()
    }
}
