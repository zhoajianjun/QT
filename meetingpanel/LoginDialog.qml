import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4
import readfile 1.0


import "listener.js" as Logic


Item{
    id: root
    anchors.centerIn: parent

    signal loginSuccess(var tgt)

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
        };
        var dateString = new Date().toLocaleDateString(Qt.locale("C"), "yyMMdd");
        var timeString = new Date().toLocaleTimeString(Qt.locale("C"), "hhmmss");
        root.target.logtime = dateString + "-" + timeString + Math.random();
        console.log("logtime", root.target.logtime);
        var handlers = {
         onTimeout : onLoginTimeout,
         onRequestSuccess: function (resp) {

             myFile.clear();
             myFile.write(addrRect.text);
             myFile.write(userRect.text);
             myFile.write(passwordRect.text);

             root.loginSuccess(root.target);


            },
         onRequestError: onLoginError

        }


        Logic.query(root.target, "xnode", handlers)
        statusTxt.text = "登录中,请稍候";
    }

    function onLoginTimeout()
    {
        loginning = false
        statusTxt.text = "网络超时，请重试......"
        checkLoginable()
    }

    function onLoginError(req)
    {
        loginning = false
        statusTxt.text = "Error:" + req.status.toString()
        console.log("onLoginError")
    }
    function getlogintitle(){
        var loginTitle=mainWin.readjson()
          return loginTitle.mainTitle;

    }

        FileIo {
            id: myFile
            source: "user.txt"
            onError: console.log(msg)
        }


        Image {
            id: name
            sourceSize.width: 406
            source: "../images/loginback.png"
            Text {
                id: logintitle

                //text: qsTr("指挥调度系统")
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.top: parent.top
                anchors.topMargin: 30
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 25
                color: "white"
            }

        Column {
            id: column
            height: 150
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.top: parent.top
            anchors.topMargin: 100

            spacing: 10

            Row {
                id: row1
                height: 40

                Text {
                    id: text1
                    width: 100
                    height: 40
                    color: "white"
                    text: qsTr("服务器地址:")
                    verticalAlignment: Text.AlignVCenter
                    //horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 16
                }

                TextField {
                    id: addrRect
                    width: 200
                    height: 40
                    placeholderText: qsTr("请输入服务器地址")
                    KeyNavigation.down: userRect
                }
            }

            Row {
                id: row2
                height: 40
                Text {
                    id: text2
                    width: 100
                    height: 40
                    color: "white"
                    text: qsTr("用户名:   ")
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    //horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 16
                }

                TextField {
                    id: userRect
                    width: 200
                    height: 40
                    placeholderText: qsTr("请输入用户名")
                    KeyNavigation.down: passwordRect
                    KeyNavigation.up: addrRect

                }
            }

            Row {
                id: row3
                height: 40
                Text {
                    id: text3
                    width: 100
                    height: 40
                    text: qsTr("密   码:   ")
                    color: "white"
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 16
                }

                TextField {
                    id: passwordRect
                    width: 200
                    height: 40
                    placeholderText: qsTr("请输入密码")
                    echoMode: TextInput.Password
                    KeyNavigation.up: userRect

                    onAccepted: {
                        if (isLoginable())
                        {
                            login();
                        }
                    }
                }
            }
        }

        Button{
            id:loginBtn
            anchors.top: column.bottom
            anchors.topMargin: 20

            anchors.left: parent.left
            anchors.leftMargin: 100
            style: ButtonStyle{
                id:bstyle
                background: Image {
                    id: backimage
                    source: control.pressed?"../images/loginbnt.png":"../images/loginbnt1.png"
                }
                label:Text {
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "登录"
                    color: "#eeeeee"
                }

            }
            onClicked: {
                 login();
            }
        }
        Button{
            id:cancleBtn
            anchors.top: column.bottom
            anchors.topMargin: 20

            anchors.right: parent.right
            anchors.rightMargin: 100
            style: ButtonStyle{
                id:bstyle1
                background: Image {
                    id:canclebackimage
                    source: control.pressed?"../images/loginbnt.png":"../images/loginbnt1.png"
                }
                label:Text {
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "退出"
                    color: "#eeeeee"
                }

            }
            onClicked: {
                Qt.quit();
            }
        }
        Text {
            id: statusTxt
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            color: "red"
            text: ""
            font.pixelSize: 15
        }

        Component.onCompleted: {
            //addrRect.text = "192.168.5.103"
            // userRect.text = "admin"
            //passwordRect.text = "111111"

            var mm=myFile.read();
            var records= mm.split("\n");
            for (var i = 0; i < records.length; ++i)
            {
                var l = records[i].split(" ");
                console.log(l[0]);
                console.log(l[1]);
                console.log(l[2]);

                addrRect.text=l[0];
                userRect.text=l[1];
               // passwordRect.text=l[2];
            }
            logintitle.text=getlogintitle();
        }

}
}

