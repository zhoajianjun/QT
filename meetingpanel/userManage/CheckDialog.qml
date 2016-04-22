import QtQuick 2.0
import QtQuick.Controls 1.4


Rectangle{
    id: rectDialog;
    z:10;
    width: parent.width/5 > 250 ? parent.width/5 : 300;
    height: 130;
    visible: false;
    //color:"#123863";
    color:"#a7b3bc";
    property string groupinfoString : "null";
    property int choiceFunc;
    property var object;
    function delGroupOrUser(choice ){
        if(choice == 1){
            //buttonCancle.visible = true;
            delGroups(groupUserView.model.get(groupUserView.currentIndex).name, groupUserView.currentIndex);
        }
        else if(choice == 2){
            //buttonCancle.visible = true;
            //var data = availableUserModel.get(avaiableUserView.currentIndex).id;
            if(choiceSipFlag == false && choiceVirFlag == false && choicePhyFlag == false && choiceConFlag == false)
                delUser(availableUserModel.get(avaiableUserView.currentIndex).id);
            else if(choiceSipFlag == true)
                delUser(availableUserModel.get(avaiableUserView.currentIndex).id);
            else if(choiceVirFlag == true)
                delVirUser(availableUserModel.get(avaiableUserView.currentIndex).id);
            else if(choicePhyFlag == true)
                delPhyUser(availableUserModel.get(avaiableUserView.currentIndex).id);
            else if(choiceConFlag == true)
                delConUser(availableUserModel.get(avaiableUserView.currentIndex).id);

            allUsersModel.remove(avaiableUserView.currentIndex);
            input1.text = "";
            input2.text = "";
            input3.text = "";
            //input4.text = "";
        }
        else if(choice == 4){
            //buttonCancle.visible = false;
            console.log("messageDialog function done nothing");
        }
        else if(choice == 5)
        {
            flagRootUserChoose = 0;
            var data = groupUserModel.get(groupUserView.currentIndex).id;
            addUserFunction(data, object, "role", 4);
        }

        else {
            //buttonCancle.visible = true;
            flagRootUserChoose = 1;
            //console.log("DEBUG:HHHHHHHHHHHHHH" + role);
            var dat = groupUserModel.get(groupUserView.currentIndex).id;
            addUserFunction(dat, object, "role", 1);
        }
    }

    Image{
        id:topleft;
        anchors.left: parent.left;
        anchors.top: parent.top;
        width: 10; height: 30;
        source: "../images/top_left.png";
    }
    Image{
        anchors.left: topleft.right; anchors.right: topright.left;
        width: parent.width; height: 30;
        source: "../images/top_mid.png";
    }
    Image{
        id: topright;
        anchors.right: parent.right; anchors.top: parent.top;
        width: 10; height: 30;
        source: "../images/top_right.png";
    }

    Text{
        anchors.top: parent.top; anchors.topMargin: 5;
        anchors.left: parent.left; anchors.leftMargin: 10;
        text:"操作提示信息:";
        font.pixelSize: 15;
        color:"red";
    }

    Image{
        anchors.bottom: parent.bottom; //anchors.bottomMargin: 50;
        width: parent.width ; height: parent.height -30;
        source: "../images/bg02.png";
        //fillMode: Image.PreserveAspectFit;


        Text{
            id: groupInfo;
            anchors.left : parent.left; anchors.leftMargin: 20;
            anchors.top: parent.top ;anchors.topMargin: 20;
            text:groupinfoString;
            //text:"确定删除组: " + (groupUserView.model.get(groupUserView.currentIndex).name) + " ?";
            color:"white";
            width: parent.width -10;
            font.pixelSize: 15;
            elide:Text.ElideMiddle;
        }
        Button{
            id: buttonSure;
            anchors.bottom: parent.bottom; anchors.bottomMargin: 10;
            anchors.right: parent.right; anchors.rightMargin: 20;
            width: 38; height: 20;
            text:"确定";
            onClicked:{
                delGroupOrUser(choiceFunc);
                rectDialog.visible = false;
            }
        }
        Button{
            id: buttonCancle;
            visible: choiceFunc == 4 ? false : true;
            anchors.bottom: parent.bottom; anchors.bottomMargin: 10;
            anchors.right: buttonSure.left; anchors.rightMargin: 10;
            width: 38; height: 20;
            text:"取消";
            onClicked: rectDialog.visible = false;

        }

    }
}
