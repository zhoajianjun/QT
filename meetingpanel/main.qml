import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import readfile 1.0
import XmlToJsonConvertor 1.0

Window {
    id: mainWin
    title: qsTr("音频调度")

    width: 800
    height: 600

    color: "grey"

    visible: true
    //visibility: Window.FullScreen
    visibility: Window.Maximized

    function showWorkGround(value)
    {
        if (value)
        {
            console.log("show mainwin");
            mainWin.show();
            //loginPage.hide();
            //loginPage.close();
            loginPage.visible=true;
            //work.visible = true
            work.start();
            work.load();
        }
        else
        {
            //work.visible = false
            mainWin.hide();
            loginPage.show();
            work.stop()

        }
    }
    function dataRequestError(string){
        requestErrorDialog.text = string;
        requestErrorDialog.open();
    }
    function readjson()
    {
        var config=myFile.read();
        var json = JSON.parse(config);
        var count = json.titles.length;
        for (var i in json.titles) {
            var config1 = json.titles[i];
            var userconfig={
                mainTitle:config1.maintitle
            }
            //TODO: populate other configs.
        }
        return userconfig;
    }

    Timer {
        id: timer;
        interval: 1000;
        repeat: true;
        running: true;

        onTriggered: {
            //gc();
        }
    }

    Image {
        id: backimage
        anchors.fill: parent
        source: "../images/mainback.png"
        Image {
            id: leftimage
            x:-20
            y:0
            source: "../images/leftback.png"
        }
        Image {
            id: rightimage
            anchors.right: parent.right
            sourceSize.width: parent.width*0.3
            anchors.top:parent.top
            anchors.topMargin: parent.height*0.4
            source: "../images/rightback.png"
        }
        Image {
            id: bottomimage
            anchors.left: parent.left
            anchors.right: parent.right
            source: "../images/bottomback.png"
        }
    FileIo {
        id: myFile
        source: "userCustomConfig.json"
        onError: console.log(msg)
    }

    XmlToJsonConvertor {
        id: xjconvertor
    }

    LoginDialog {
        id: loginPage
        visible: true
        width: 406
        height: 350
        onLoginSuccess: {
            work.visible = true;
            work.setTarget(tgt)
            showWorkGround(true);
            mainWin.visibility = Window.FullScreen
            mainWin.visibility = Window.Maximized
        }
    }
    MessageDialog {
        id: requestErrorDialog;
        modality: Qt.ApplicationModal;
        title: "Data Request Error!";
        //text: "请求数据失败！";
        standardButtons: StandardButton.Ok;
        onAccepted: {
            requestErrorDialog.close();
        }
    }

    WorkGround {
        id: work
        anchors.fill: parent
        visible: true
        onLogout: {
            showWorkGround(false)
        }
        onVisibleChanged: {
            console.log("work is visible " + visible);
        }
    }

    Component.onCompleted: {
        work.visible = false;
        loginPage.visible=true;
        readjson();
    }
    }
}
