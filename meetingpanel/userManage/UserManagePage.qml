import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.3
import QtQuick.Dialogs 1.2

import "../userManage"
import "../operating"
import "../listener.js" as Logic
//add

Rectangle{
    id: root;
    width:1300; height: 880;
    color:"#bbc5cc";
    property int flag: 0;
    property int  flagDelegateChoice: 0;
    property int  flagGroup1Id: 0; //the first group id is 1 or others.
    property int receiverCount: 0;
    property int  micGrantedCount: 0;
    property int  modeCount: 0;
    property int flagDropCtrl: 0;
    property int specialIntercomCount: 0;
    property int flagSpecialIntercom: 1;
    property int flagRootUserChoose: 0;
    property string groupNameString: "";

    property bool choiceSipFlag: false;
    property bool choiceVirFlag: false;
    property bool choicePhyFlag: false;
    property bool choiceConFlag: false;
    property int aIdFlag : 9999;
    MessageDialog {
        id: messageShow;
        modality: Qt.ApplicationModal;
        title: "消息提示！";
        standardButtons: StandardButton.Ok;
        onAccepted: {
            messageShow.close();
        }

    }
    function messageShowFunction(message){
        messageShow.text = message;
        messageShow.open();
    }



    CheckDialog{
        id: rectDialog;
        anchors.centerIn: parent;
        //timer:true;
        Timer {
                interval: 1200
                repeat: false;
                running: rectDialog.visible == true && rectDialog.choiceFunc == 4 ? true : false;
                onTriggered: {
                    rectDialog.visible = false;
                }
            }
        //anchors.bottom: column2.bottom; anchors.bottomMargin: 30;
        //anchors.horizontalCenter: column2.horizontalCenter;
        //groupinfoString: "确定删除群: " + (groupUserView.model.get(groupUserView.currentIndex).name) + " ?";
        //choiceFunc: 1;
    }

    function messageDialog(message, func, object){
        rectDialog.visible = true;
        rectDialog.groupinfoString = message;
        rectDialog.choiceFunc = func;
        rectDialog.object = object;
    }
    //property string userName;
    function load(){
        //if(flag === 0)
        queryGroup();
        queryAllUser(false);
        console.log("GroupView is Loading");
    }
    function addItems(item)
    {
        groupUserModel.append(item);
        //  console.log("hello1" + planets.count);
    }

    function queryGroup()
    {
        var path = "xnode/ws/groups/command?arg=browse id,realName"

        var handlers = {
            onTimeout: function (req){
                messageDialog("查询群:网络请求超时！", 4);
            },
            onRequestSuccess: function(resp) {
                //console.log("EEEEOresp:" + Logic.serialize(resp, 5));
                if(resp.result
                        && resp.result.detail
                        && resp.result.detail.command)
                {
                    var content = resp.result.detail.command;
                    //var grps = [];
                    if((typeof content) === "string")
                    {
                        var records = content.split("\n");
                        for (var i = 0; i < records.length; ++i)
                        {
                            var l = records[i].split("|");
                            var g = {
                                id : l[0],
                                name : l[1]
                            }
                            if(i == 0){
                                flagGroup1Id = l[0];
                                queryAddedGroup(flagGroup1Id);
                                if(menuListView.currentIndex == 0)
                                    queryGroupUser(flagGroup1Id);
                                else{
                                    if(choiceSipFlag == true || (choiceSipFlag == false && choiceVirFlag == false && choicePhyFlag == false && choiceConFlag == false))
                                        queryAllUser(true);
                                    else if(choiceVirFlag == true)
                                        queryVirAllUser(true);
                                    else if(choicePhyFlag ==true)
                                        queryPhyAllUser(true);
                                    else if(choiceConFlag == true)
                                        queryConUser(true);

                                }

                            }
                            addItems(g);//append({name: records[i]}
                        }
                    }
                }
            },
            onRequestError: function (req){
                messageDialog("查询群:网络请求数据失败！", 4);
            },
        }
        groupUserModel.clear();
        Logic.query(work.target, path, handlers);

    }

    function addGroups(groupName)
    {
        var path = "xnode/ws/groups/command"   //?arg=browse id,realName

        var handlers = {
            onTimeout: function (req){
                messageDialog("添加群:网络请求数据超时！", 4);
            },
            onRequestSuccess: function(resp) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(resp, 5));
                if(resp.result)
                {
                    //console.log("OOOOOOOOOO");
                    var overall = resp.result.overall;
                    //console.log("HHHHHHHHHHHHHHHHHH" + overall);
                    if(parseInt(overall) === 0)
                    {
                        groupUserModel.clear();
                        queryGroup();
                        //console.log("resquest onsuccess");
                        //planets.append({"name" : groupName});
                        /*
                             when delete group by groupName,we need id form sql.
                               here we didn't query form sql,but we record the count of sql by nLength;
                            */
                    }
                    else if(parseInt(overall) === 1)
                    {
                        console.log("addGroups " + groupName + " failed,code:" + result);
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                    }
                }
            },
            onRequestError: function (req){messageDialog("添加群:网络请求数据失败！", 4);},

        }
        var xml = "<set>" + "add NULL, '" + groupName +"'" + "</set>";
        //console.log("hello " + "add NULL, '" + groupName +"'" );
        Logic.post(work.target, path, xml, handlers);

    }

    function delGroups(groupName,index)
    {
        var path = "xnode/ws/groups/command"   //?arg=browse id,realName

        var handlers = {
            onTimeout: function (req){messageDialog("删除群:网络请求数据超时！", 4);},
            onRequestSuccess: function(req) {
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        console.log("delGroupsResquest onsuccess");
                        groupUserModel.remove(index);
                    }
                    else if(parseInt(overall) === 1)
                    {
                        //console.log("delGroups failed,code:" + result);
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //messageDialog("删除群:请求数据出错！", 4);
                    }

                }

            },
            onRequestError: function (req){
                messageDialog("删除群:网络请求数据失败！", 4);
            },

        }
        var xml = "<set>" + "delete where realName= '" + groupName +"'" + "</set>";
        console.log("hello " + "delete where realName= '"+ groupName +"'" );
        Logic.post(work.target, path, xml, handlers);
    }

    function queryAddedGroup(idNumber)
    {
        console.log("queryAttendees() idNumber is ", idNumber)

        var path = "xnode/ws/attendees/terminal_added?arg=" + idNumber;//group.toString();
        var handlers = {
            onTimeout: function (req){messageDialog("查询群用户:网络请求数据超时！", 4);},
            onRequestSuccess: function(req) {
                receiverCount = 0; micGrantedCount = 0; modeCount = 0; specialIntercomCount = 0;
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result
                        && req.result.detail
                        && req.result.detail.terminal_added)
                {
                    var content = req.result.detail.terminal_added;
                    if((typeof content) === "string")
                    {
                        var records = content.split("\n");
                        for (var i = 0; i < records.length; ++i)
                        {
                            var fields = records[i].split('|');

                            var attendee = {

                                accountId : fields[0],
                                fromId: fields[1],
                                realName : fields[2],
                                micGranted: fields[3],
                                receiver : fields[4],
                                userName: fields[5],
                                mode: fields[6],        //role, specialIntercom
                                role: fields[7],
                                specialIntercom: fields[8],
                                aId : fields[9],
                                fId : fields[10]
                                //flag : fields[9] + fields[10]
                            };
                            if(fields[7] == 1)
                                flagRootUserChoose = 1;
                            if(fields[4] == 1)
                                ++ receiverCount;
                            if(fields[3] == 1)
                                ++ micGrantedCount;
                            if(fields[6] == 1)
                                ++ modeCount;
                            if(fields[8] == 1)
                                ++specialIntercomCount;
                            attendeesModel.append(attendee);

                            //console.log("ZYZ:" + fields[0]+ ":"+ fields[1] + ":" + fields[2] + ":" + fields[9] + ":" + fields[10] + (fields[9] + fields[10]));

                        }


                    }
                }
            },
            onRequestError: function (req){messageDialog("查询群用户:网络请求数据失败！", 4);},
        }
        attendeesModel.clear();
        Logic.query(work.target, path, handlers);
    }

    function queryGroupUser(groupid)
    {
        console.log("queryGroupUser id is "+ groupid);
        var path = "xnode/ws/attendees/terminal_available?arg=" + groupid;
        //var path = "xnode/ws/account/command?arg=browse id,username,password,realname"
        var handlers = {
            onTimeout: function (req){console.log("timeout");
                messageDialog("查询可用用户:网络请求数据超时！", 4);
            },
            onRequestSuccess: function(req) {

                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result
                        && req.result.detail
                        && req.result.detail.terminal_available)
                {
                    var content = req.result.detail.terminal_available;
                    if ((typeof content) === "string")
                    {
                        var records = content.split("\n");
                        for (var i = 0; i < records.length; ++i)
                        {
                            var l = records[i].split("|");
                            var u = {
                                accountId : l[0],
                                fromId : l[1],
                                realName : l[2],
                                groupStatus : l[3],  //状态(1-已在组中,0-不在组中)
                                userName : l[4],
                                lopp : l [5],
                                lpp : l[6],
                            }

                            if(l[3] == 0)
                                availableUserModel.append(u);

                            // console.log("called alluserModel.append() and model.count= "+ allUserModel.count);
                        }
                        console.log("queryGroupUser is success!");
                        textShow.text = "可用用户[" + availableUserModel.count +"]";

                    }
                    else
                        console.log("failed");
                }
            },
            onRequestError: function (req){console.log("errored");messageDialog("查询可用用户:网络请求数据失败！", 4);},
        }
        //  if(indexFlag == 0){
        availableUserModel.clear();
        Logic.query(work.target, path, handlers);
        //     console.log("called queryallUser and posted");
        //     indexFlag = 1;
    }
    function queryAllUser(bool) // for Sip users;
    {
        var path = "xnode/ws/account/browse_only?arg=browse";
        //id,username,password,realname,state"
        //var path = "xnode/ws/account/command?arg=browse id,username,password,realname,email"
        //console.log("content is1 " );
        var handlers = {
            onTimeout: function (req){messageDialog("查询Sip全部用户:网络请求超时！", 4);},
            onRequestSuccess: function(req) {
                if(req.result
                        && req.result.detail
                        && req.result.detail.browse_only)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        var content = req.result.detail.browse_only;
                        if ((typeof content) === "string")
                        {
                            if(bool === true)
                                availableUserModel.clear();
                            allUsersModel.clear();
                            //var content = textNode.nodeValue
                            //console.log("content is " + content);
                            var records = content.split("\n");
                            for (var i = 0; i < records.length; ++i)
                            {
                                var l = records[i].split("|");
                                var u = {
                                    id : l[0],
                                    username : l[1],
                                    domain : l[2],
                                    password : l[3],
                                    realName : l[4],
                                    fromId : l[5],
                                }
                                if(bool == false)
                                    allUsersModel.append(u);
                                else
                                {
                                    //if(menuListView.currentIndex == 1)
                                    allUsersModel.append(u);
                                    availableUserModel.append(u);
                                }

                                //avaia(u);//append({name: records[i]});
                            }
                            //console.log("userName " + userName.toString());
                            if(menuListView.currentIndex == 1)
                                textShow.text = "全部用户["+ availableUserModel.count +"]";
                            else
                                textShow.text = "可用用户["+ availableUserModel.count +"]";

                        }

                    }
                    else
                    {
                        availableUserModel.clear();
                        allUsersModel.clear();
                    }

                }
            },
            onRequestError: function (req){messageDialog("查询Sip全部用户:网络请求失败！", 4);},
        }
        Logic.query(work.target, path, handlers);

    }

    function queryVirAllUser(bool) //for Vir users;
    {
        var path = "xnode/ws/csp/browse_only?arg=browse"      // id,username,serverIp,realname"
        var handlers = {
            onTimeout: function (req){ messageDialog("查询虚拟全部用户:网络请求超时！", 4);},
            onRequestSuccess: function(req) {

                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result
                        && req.result.detail
                        && req.result.detail.browse_only)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        var content = req.result.detail.browse_only;
                        if ((typeof content) === "string")
                        {
                            if(bool == true){
                                availableUserModel.clear();
                            }
                            allUsersModel.clear();
                            //var content = textNode.nodeValue
                            //console.log("content is " + content);
                            var records = content.split("\n");
                            for (var i = 0; i < records.length; ++i)
                            {
                                var l = records[i].split("|");  //id,username,serverIp,realname
                                var u = {
                                    id : l[0],
                                    username : l[1],
                                    serverIp: l[2],
                                    realName : l[3],
                                    fromId : l[4],
                                }
                                if(bool == false)
                                    allUsersModel.append(u);
                                else {
                                    allUsersModel.append(u);
                                    availableUserModel.append(u);
                                }

                            }
                            //console.log("userName " + userName.toString());

                            if(menuListView.currentIndex == 1)
                                textShow.text = "全部用户["+ availableUserModel.count +"]";
                            else
                                textShow.text = "可用用户["+ availableUserModel.count +"]";

                        }

                    }
                    else
                    {
                        if(menuListView.currentIndex == 1)
                            availableUserModel.clear();
                        allUsersModel.clear();
                        console.log("HHHHHHHHHHHHHHEEEEEEEEEEEEEEEEEEEE");
                    }

                }
            },
            onRequestError: function (req){messageDialog("查询虚拟全部用户:网络请求失败！", 4);},
        }
        Logic.query(work.target, path, handlers);


    }
    function queryPhyAllUser(bool) //for Phy users;
    { // <!--id,type/类型,audioAlgo/语音编码算法(5-G.711A, 7-G.729A),userName/用户名,realName/姓名-->
        var path = "xnode/ws/csp_real/browse_only?arg=browse" //" id,type,audioAlgo,username,realname"
        var handlers = {
            onTimeout: function (req){messageDialog("查询物理全部用户:网络请求超时！", 4);},
            onRequestSuccess: function(req) {

                if(req.result
                        && req.result.detail
                        && req.result.detail.browse_only)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        var content = req.result.detail.browse_only;
                        if ((typeof content) === "string")
                        {
                            if(bool == true)
                                availableUserModel.clear();
                            allUsersModel.clear();
                            //var content = textNode.nodeValue
                            //console.log("content is " + content);
                            var records = content.split("\n");
                            for (var i = 0; i < records.length; ++i)
                            {
                                var l = records[i].split("|");  //id,username,serverIp,realname
                                var u = {
                                    id : l[0],
                                    type: l[1],
                                    audioAlgo: l[2],
                                    username : l[3],
                                    realName : l[4],
                                    fromId : l[5],
                                }
                                if(bool == false)
                                    allUsersModel.append(u);
                                else{
                                    allUsersModel.append(u);
                                    availableUserModel.append(u);
                                }

                            }
                            //console.log("userName " + userName.toString());

                            if(menuListView.currentIndex == 1)
                                textShow.text = "全部用户["+ availableUserModel.count +"]";
                            else
                                textShow.text = "可用用户["+ availableUserModel.count +"]";

                        }
                    }
                    else
                    {
                        if(menuListView.currentIndex == 1)
                            availableUserModel.clear();
                        allUsersModel.clear();
                    }
                }
            },
            onRequestError: function (req){messageDialog("查询物理全部用户:网络请求失败！", 4);},
        }
        Logic.query(work.target, path, handlers);
    }

    function queryConUser(bool) //for contact users
    {
        var path = "xnode/ws/contact/browse_only?arg=browse" //" id,userName,domain,realName
        var handlers = {
            onTimeout: function (req){messageDialog("查询联系人全部用户:网络请求超时！", 4);},
            onRequestSuccess: function(req) {

                if(req.result
                        && req.result.detail
                        && req.result.detail.browse_only)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        var content = req.result.detail.browse_only;
                        if ((typeof content) === "string")
                        {
                            if(bool == true)
                                availableUserModel.clear();
                            allUsersModel.clear();
                            //var content = textNode.nodeValue
                            //console.log("content is " + content);
                            var records = content.split("\n");
                            for (var i = 0; i < records.length; ++i)
                            {
                                var l = records[i].split("|");  //id,username,serverIp,realname
                                var u = {
                                    id : l[0],
                                    username: l[1],
                                    domain: l[2],
                                    realName : l[3],
                                    fromId : l[4],
                                }
                                if(bool == false)
                                    allUsersModel.append(u);
                                else{
                                    allUsersModel.append(u);
                                    availableUserModel.append(u);
                                }

                            }
                            //console.log("userName " + userName.toString());

                            if(menuListView.currentIndex == 1)
                                textShow.text = "全部用户["+ availableUserModel.count +"]";
                            else
                                textShow.text = "可用用户["+ availableUserModel.count +"]";

                        }
                    }
                    else
                    {
                        if(menuListView.currentIndex == 1)
                            availableUserModel.clear();
                        allUsersModel.clear();
                    }
                }

                //flag=true
            },
            onRequestError: function (req){messageDialog("查询联系人全部用户:网络请求失败！", 4);},
        }
        Logic.query(work.target, path, handlers);

    }

    function modifyUserInfo(newUsername,newPassword,newRealname,newEmail,userId){  //for Sip users;
        var path = "xnode/ws/account/command/";
        var handlers = {
            onTimeout: function (req){
                messageDialog("修改Sip用户信息:网络请求超时！", 4);
            },
            onRequestSuccess: function(req) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        console.log("HHHHHHHHHHHHHEEEEEEEEEEEEEEEEEEEE");
                        var index= avaiableUserView.currentIndex;
                        queryAllUser(true);
                        messageDialog("用户信息修改成功!",4);
                    }
                    else if(parseInt(overall) === 1)
                    {
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //messageDialog("修改Sip用户信息:数据请求失败！", 4);
                    }
                }
            },
            onRequestError: function (req){
                messageDialog("修改Sip用户信息:网络请求失败！", 4);
            },
        }
        var xml="<set>"+"change  userName='" +newUsername+"',"+"password='"+newPassword+"',"+ "realName='"+
                newRealname+"',"+"email='"+newEmail+"' "+"where id="+"'"+userId+"'"+"</set>";
        console.log("change  userName='" +newUsername+"',"+"password='"+newPassword+"',"+ "realName='"+
                    newRealname+"',"+"email='"+newEmail+"' "+"where id="+"'"+userId+"'");
        Logic.post(work.target, path, xml, handlers);
    }


    function modifyVirUserInfo(newUserName,newServerIp, newRealName,userId)
    {
        var path = "xnode/ws/csp/command/";
        var handlers = {
            onTimeout: function (req){
                messageDialog("修改虚拟用户信息:网络请求超时！", 4);
            },
            onRequestSuccess: function(req) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        if(menuListView.currentIndex == 1)
                            queryVirAllUser(true);
                        else
                            queryGroupUser(groupUserModel.get(groupUserView.currentIndex).id);
                        messageDialog("用户信息修改成功!",4);
                    }
                    else if(parseInt(overall) === 1)
                    {
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //messageDialog("修改虚拟用户信息:数据请求失败！", 4);
                    }

                }

            },
            onRequestError: function (req){
                messageDialog("修改虚拟用户信息:网络请求失败！", 4);
            },
        }
        var xml="<set>"+"change  userName='" +newUserName+"',"+"server_addr='"+newServerIp+"',"+ "realName='"+
                newRealName+"' "+"where id="+"'"+userId+"'"+"</set>";
        console.log("change  userName='" +newUserName+"',"+"server_addr='"+newServerIp+"',"+ "realName='"+
                    newRealName+"' "+"where id="+"'"+userId+"'");
        Logic.post(work.target, path, xml, handlers);
    }

    function modifyPhyUserInfo(newType, newAudioAlgo, newUserName, newRealName,userId) // for Phy users
    {
        var path = "xnode/ws/csp_real/command/";
        var handlers = {
            onTimeout: function (req){
                messageDialog("修改物理用户信息:网络请求超时！", 4);
            },
            onRequestSuccess: function(req) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        if(menuListView.currentIndex == 1)
                            queryPhyAllUser(true);
                        else
                            queryGroupUser(groupUserModel.get(groupUserView.currentIndex).id);
                        messageDialog("用户信息修改成功!",4);
                    }
                    else if(parseInt(overall) === 1)
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //messageDialog("修改物理用户信息:数据请求超时！", 4);
                }

            },
            onRequestError: function (req){
                messageDialog("修改物理用户信息:网络请求失败！", 4);

            },
        }
        var xml="<set>"+"change  type='" +newType+"',"+"audioAlgo='"+newAudioAlgo+"',"+"userName='" +newUserName+"',"+ "realName='"+
                newRealName+"' "+"where id="+"'"+userId+"'"+"</set>";
        console.log("change  type='" +newType+"',"+"audioAlgo='"+newAudioAlgo+"',"+"userName='" +newUserName+"',"+ "realName='"+
                    newRealName+"' "+"where id="+"'"+userId+"'");
        Logic.post(work.target, path, xml, handlers);

    }

    function modifyConUserInfo(newUsername, newDomain, newRealName, userId) //for Contacts users
    {
        var path = "xnode/ws/contact/command/";
        var handlers = {
            onTimeout: function (req){
                messageDialog("修改联系人用户信息:网络请求超时！", 4);
            },
            onRequestSuccess: function(req) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        if(menuListView.currentIndex == 1)
                            queryConUser(true);
                        else
                            queryGroupUser(groupUserModel.get(groupUserView.currentIndex).id);
                        messageDialog("用户信息修改成功!",4);
                    }
                    else if(parseInt(overall) === 1)
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //messageDialog("修改联系人用户信息:数据请求失败！", 4);
                }

            },
            onRequestError: function (req){
                messageDialog("修改联系人用户信息:网络请求失败！", 4);
            },
        }
        var xml="<set>"+"change  userName='" +newUsername+"',"+"domain='"+newDomain+"',"+ "realName='"+
                newRealName+"' "+"where id="+"'"+userId+"'"+"</set>";
        console.log("change  userName='" +newUsername+"',"+"domain='"+newDomain+"',"+ "realName='"+
                    newRealName+"' "+"where id="+"'"+userId+"'");
        Logic.post(work.target, path, xml, handlers);

    }

    function delUser(userId) //for Sip users;
    {
        var path="xnode/ws/account/command"
        var handlers = {
            onTimeout: function (req){
                messageDialog("删除Sip用户:网络请求超时！", 4);
            },
            onRequestSuccess: function(req) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        var index=avaiableUserView.currentIndex
                        // console.log(index);
                        availableUserModel.remove(index);
                    }
                    else if(parseInt(overall) === 1)
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //messageDialog("删除Sip用户:数据请求失败！", 4);

                }

            },
            onRequestError: function (req){
                messageDialog("删除Sip用户:网络请求失败！", 4);

            },
        }
        var xml="<set>"+"delete where id='"+userId+"'"+"</set>";
        Logic.post(work.target, path, xml, handlers);
    }

    function delVirUser(userId)//for Vir users;
    {
        var path = "xnode/ws/csp/command/";
        var handlers = {
            onTimeout: function (req){
                messageDialog("删除虚拟用户:网络请求超时！", 4);
            },
            onRequestSuccess: function(req) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        var index=avaiableUserView.currentIndex
                        // console.log(index);
                        availableUserModel.remove(index);
                    }
                    else if(parseInt(overall) === 1)
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //messageDialog("删除虚拟用户:数据请求失败！", 4);
                }

            },
            onRequestError: function (req){
                messageDialog("删除虚拟用户:网络请求失败！", 4);
            },
        }
        var xml="<set>"+"delete where id='"+userId+"'"+"</set>";
        Logic.post(work.target, path, xml, handlers);
    }

    function delPhyUser(userId) // for Phy users;
    {
        var path = "xnode/ws/csp_real/command/";
        var handlers = {
            onTimeout: function (req){
                messageDialog("删除物理用户:网络请求超时！", 4);
            },
            onRequestSuccess: function(req) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        var index=avaiableUserView.currentIndex
                        // console.log(index);
                        availableUserModel.remove(index);
                    }
                    else if(parseInt(overall) === 1)
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //messageDialog("删除虚拟用户:数据请求失败！", 4);
                }

            },
            onRequestError: function (req){
                messageDialog("删除虚拟用户:网络请求失败！", 4);

            },
        }
        var xml="<set>"+"delete where id='"+userId+"'"+"</set>";
        Logic.post(work.target, path, xml, handlers);
    }

    function delConUser(userId) //for Contact users;
    {
        var path = "xnode/ws/contact/command/";
        var handlers = {
            onTimeout: function (req){
                messageDialog("删除联系人用户:网络请求超时！", 4);
            },
            onRequestSuccess: function(req) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        var index=avaiableUserView.currentIndex
                        // console.log(index);
                        availableUserModel.remove(index);
                    }
                    else if (parseInt(overall) === 1)
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //messageDialog("删除联系人用户:请求数据失败！", 4);
                }
            },
            onRequestError: function (req){
                messageDialog("删除联系人用户:网络请求数据失败！", 4);
            },
        }
        var xml="<set>"+"delete where id='"+userId+"'"+"</set>";
        Logic.post(work.target, path, xml, handlers);
    }

    function addUserFunction(idNumber, object, option, value){

        console.log("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH" + object);
        var path = "xnode/ws/attendees/command";
        var handlers = {
            onTimeout: function (req){messageDialog("添加用户权限:网络请求超时！", 4);},
            onRequestSuccess: function(req) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        if(option.toString() == "receiver"){
                            if(value == 0)
                            {
                                 -- receiverCount;
                                if(receiverCount == 0)
                                    receiverCount = 0;
                            }
                            else
                                ++ receiverCount;
                        }
                        else if (option.toString() == "micGranted"){
                            if(value == 0)
                            {
                                -- micGrantedCount;
                                if(micGrantedCount == 0)
                                    micGrantedCount = 0;
                            }
                            else
                                ++ micGrantedCount;
                        }
                        else if (option.toString() == "mode"){
                            if(value == 0)
                            {
                                 -- modeCount;
                                if(modeCount == 0)
                                    modeCount = 0;
                            }
                            else
                                ++modeCount;
                        }
                        else if (option.toString() == "specialIntercom"){
                            if(value == 0)
                            {
                                --specialIntercomCount;
                                if(specialIntercomCount == 0)
                                    specialIntercomCount = 0;
                            }
                            else
                                ++specialIntercomCount;
                        }

                        else if(option.toString() == "role"){
                            if(value == 1)
                                flagRootUserChoose = 1;
                            else
                                flagRootUserChoose = 0;
                            queryAddedGroup(idNumber);
                        }

                        // console.log("resquest onsuccess");
                        //groupUserModel.append(object);
                        //queryAddedGroup(idNumber);
                    }
                    else if(parseInt(overall) === 1)
                    {
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //console.log("addUsertoGroup " + idNumber + " failed,code:" + result);
//                        if(flagRootUserChoose == 1)
//                        {
//                            console.log("i Entered! NOONONONO");
//                            messageDialog("失败，不允许对指挥员进行此操作！", 4);
//                        }
//                        else
//                            messageDialog("添加用户权限：请求数据失败！", 4);
                        console.log("failed request!")

                    }
                }

            },
            onRequestError: function (req){messageDialog("添加用户权限:网络请求失败！", 4);},
            //<!--id,accountId,micGranted/发言权,groupId,receiver/监听权,fromId(0-account,1-contact,2-csp,3-csp_real),mode/连接模式(0-被动,1-主动) -->
        }
        var xml = "<set>" + "change "+option.toString()+"='"+value+"' "+"where accountId='"+object.accountId+"' "+"and "+"fromId='"+object.fromId+"'"+"</set>";
        console.log("hello " + "change "+option.toString()+"='"+value+"' "+"where accountId='"+object.accountId+"' "+"and "+"fromId='"+object.fromId+"'");
        Logic.post(work.target, path, xml, handlers);


    }

    function addUsertoGroup(idNumber, object, value){

        //console.log("addUsertoGroup " + idNumber + object.accountId + object.fromId + object.realName + object.groupStatus + object.userName);
        var path = "xnode/ws/attendees/command";

        var handlers = {
            onTimeout: function (req){messageDialog("添加用户到群:网络请求超时！", 4);},
            onRequestSuccess: function(req) {
                console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        // console.log("resquest onsuccess");
                        //groupUserModel.append(object);
                        if(value == 1)
                            queryAddedGroup(idNumber);
                        if(value == 0)
                            queryGroupUser(idNumber);
                    }
                    else if(parseInt(overall) === 1)
                    {
                        //console.log("DEBUG:HHHHHHHHHHHH" + req.result.detail.command["@reason"]);
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //console.log("addUsertoGroup " + idNumber + " failed,code:" + overall);
                        //if(value == 1)
                        queryAddedGroup(idNumber);
                        //if(value == 0)
                        queryGroupUser(idNumber);
                        //onNotify(req);

                    }
                }

            },
            onRequestError: function (req){messageDialog("添加用户到群:网络请求失败！", 4);},
            //<!--id,accountId,micGranted/发言权,groupId,receiver/监听权,fromId(0-account,1-contact,2-csp,3-csp_real),mode/连接模式(0-被动,1-主动) -->
        }
        var xml;
        if(value == 1){
            xml = "<set>" + "add NULL,'"+ object.accountId+"','"+"1','"+idNumber+"',"+"'1','"+object.fromId +"',"+"'1'" + "</set>";
            console.log("hello " + "add NULL,'"+ object.accountId+"','"+"1','"+idNumber+"',"+"'1','"+object.fromId +"',"+"'1'");
        }
        else{
            xml = "<set>" + "delete "+ "where accountId='"+object.accountId+"' "+"and "+"fromId='"+object.fromId+ "'" + "</set>";
            console.log("hello1 " + "delete "+ "where accountId='"+object.accountId+"' "+"and "+"fromId='"+object.fromId+ "'" );
        }
        //groupStatus : l[3],  //状态(1-已在组中,0-不在组中)
        Logic.post(work.target, path, xml, handlers);

    }

    function addUsers(username,password,realname,email)   //for Sip users;
    {

        var path = "xnode/ws/account/command/";
        //  var path = "xnode/ws/account";
        var handlers = {
            onTimeout: function (req){console.log("addUsers request  time out! ");
                messageDialog("增加sip用户失败: " + realname+ "网络超时！", 4);
            },
            onRequestSuccess: function(req) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        console.log("sucess! ");
                        if(menuListView.currentIndex == 1)
                            queryAllUser(true);
                        else

                            queryGroupUser(groupUserModel.get(groupUserView.currentIndex).id);
                        allUsersModel.append({"username":username,"password":password,"realName":realname,"email":email})
                        //  messageShowFunction("增加用户: " + realname+ "成功!");
                        messageDialog("增加用户: " + realname+ "成功!", 4);
                    }
                    else if(parseInt(overall) === 1)
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //messageDialog("添加Sip用户:数据请求失败！", 4);
                }

            },
            onRequestError: function (req){messageDialog("增加sip用户失败: " + realname+ "数据出错！", 4);

            },
        }

        var xml = "<set>" +"add NULL,'" +username+"'"+", "+"NULL,"+"'"+password+"'"+", "+"'"+realname+"'"+", "+"'"+email+"'" + "</set>";
        console.log("add NULL,'" +username+"'"+", "+"NULL,"+"'"+password+"'"+", "+"'"+realname+"'"+", "+"'"+email+"'" );
        Logic.post(work.target, path, xml, handlers);

    }

    function addVirUsers(username, serverIp, realName) //for Vir users;
    {
        var path = "xnode/ws/csp/command/";
        var handlers = {
            onTimeout: function (req){console.log("addVirUsers request  time out! ");
                messageDialog("增加虚拟用户失败: " + realName+ "网络超时！", 4);
            },
            onRequestSuccess: function(req) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        console.log("sucess! ");
                        if(menuListView.currentIndex == 1)
                            queryVirAllUser(true);
                        else
                            queryGroupUser(groupUserModel.get(groupUserView.currentIndex).id);
                        allUsersModel.append({"username":username,"serverIP":serverIp,"realName":realName})
                        //  messageShowFunction("增加用户: " + realname+ "成功!");
                        messageDialog("增加用户: " + realName+ "成功!", 4);
                        //console.log("hello+++++++++++++++++++++++++add vir users");
                    }
                    else if(parseInt(overall) === 1)
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //messageDialog("增加虚拟用户失败: " + realName+ "数据错误！", 4);
                }

            },
            onRequestError: function (req){messageDialog("增加虚拟用户失败: " + realName+ "数据出错！", 4);

            },
        }

        var xml = "<set>" +"add NULL,'" +username+"'"+", "+"'"+serverIp+"'"+", "+"'"+realName+"'"+ "</set>";
        console.log("add NULL,'" +username+"'"+", "+"'"+serverIp+"'"+", "+"'"+realName+"'" );
        Logic.post(work.target, path, xml, handlers);

    }

    function addPhyUsers(type,audioAlgo,userName,realName) //for Phy users;
    {
        var path = "xnode/ws/csp_real/command/";
        var handlers = {
            onTimeout: function (req){console.log("addPhyUsers request  time out! ");
                messageDialog("增加物理用户失败: " + realName+ "网络超时！", 4);
            },
            onRequestSuccess: function(req) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        console.log("sucess! ");
                        if(menuListView.currentIndex == 1)
                            queryPhyAllUser(true);
                        else
                            queryGroupUser(groupUserModel.get(groupUserView.currentIndex).id);
                        //allUsersModel.append({"username":username,"serverIP":serverIp,"realName":realName})
                        //  messageShowFunction("增加用户: " + realname+ "成功!");
                        messageDialog("增加用户: " + realName+ "成功!", 4);
                        console.log("hello+++++++++++++++++++++++++add vir users");
                    }
                    else if(parseInt(overall) === 1)
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //messageDialog("增加物理用户失败: " + realName+ "数据出错！", 4);
                }

            },
            onRequestError: function (req){messageDialog("增加物理用户失败: " + realName+ "网络请求出错！", 4);

            },
        }

        var xml = "<set>" +"add NULL,'" +type+"'"+", "+"'"+audioAlgo+"'"+", "+"'"+userName+"'"+", "+"'"+realName+"'"+ "</set>";
        console.log("add NULL,'" +type+"'"+", "+"'"+audioAlgo+"'"+", "+"'"+userName+"'"+", "+"'"+realName+"'");
        Logic.post(work.target, path, xml, handlers);
    }

    function addConUsers(userName, domain, realName)
    {
        var path = "xnode/ws/contact/command/";
        var handlers = {
            onTimeout: function (req){console.log("addConUsers request  time out! ");
                messageDialog("增加联系人用户失败: " + realName+ "网络超时！", 4);
            },
            onRequestSuccess: function(req) {
                //console.log("HHHHHHHHHHHHHHHHHHHHHHEEEEOresp:" + Logic.serialize(req, 5));
                if(req.result)
                {
                    var overall = req.result.overall;
                    if(parseInt(overall) === 0)
                    {
                        console.log("sucess! ");
                        if(menuListView.currentIndex == 1)
                            queryConUser(true);
                        else
                            queryGroupUser(groupUserModel.get(groupUserView.currentIndex).id);
                        //allUsersModel.append({"username":username,"serverIP":serverIp,"realName":realName})
                        //  messageShowFunction("增加用户: " + realname+ "成功!");
                        messageDialog("增加用户: " + realName+ "成功!", 4);
                        console.log("hello+++++++++++++++++++++++++add vir users");
                    }
                    else if(parseInt(overall) === 1)
                        messageDialog(req.result.detail.command["@reason"] + "!", 4);
                        //messageDialog("增加联系人用户失败: " + realName+ "数据错误！", 4);
                }

            },
            onRequestError: function (req){messageDialog("增加联系人用户失败: " + realName+ "数据出错！", 4);

            },
        }

        var xml = "<set>" +"add NULL,'" +userName+"'"+", "+"'"+domain+"'"+", "+"'"+realName+"'"+ "</set>";
        console.log("add NULL,'" +userName+"'"+", "+"'"+domain+"'"+", "+"'"+realName+"'");
        Logic.post(work.target, path, xml, handlers);
    }

    function checkUserName(strings)
    {
        for(var i = 0; i < allUsersModel.count ; i++)
        {
            var userData = allUsersModel.get(i);
            if(userData.username == strings)
                return false;
        }
        return true;
    }

    function checkVirUserName(strings)
    {
        //console.log("DEBUG:HHHHHHHHHHHHHHHHH" + parseInt(strings));
        if(parseInt(strings) >= 1002 && parseInt(strings) <= 9999) //[1002-9999]
            return true;
        else
            return false;
    }



    Image{ //the first rect

        id:rect1;
        x:0; y:0;
        width: parent.width; height: 90;
        source:"../images/top.png"
        //fillMode: Image.PreserveAspectCrop;
        //fillMode: Image.PreserveAspectFit
        //color:"#123868"
        MessageDialog {
            id: exitDialog
            modality: Qt.ApplicationModal
            title: "退出"
            text: "确定要退出此程序吗?"
            standardButtons: StandardButton.Ok | StandardButton.No
            onAccepted: {
                console.log("And of course you could only agree.")
                Qt.quit()
            }
            onRejected: {
                exitDialog.close()
            }
        }

        Image{
            id:bqpic;
            anchors.right: parent.right;
            anchors.rightMargin: 250;
            anchors.top: parent.top;
            anchors.topMargin: 30;
            width: 82; height: 30;
            source:"../images/return01.png";
            fillMode: Image.PreserveAspectFit;
            //fillMode: Image.PreserveAspectCrop;

            MouseArea{
                anchors.fill: parent;
                hoverEnabled: true;
                onEntered: bqpic.source = "../images/return02.png";
                onExited:  bqpic.source = "../images/return01.png";
                onPressed: bqpic.source = "../images/return03.png";
                onClicked: {
                    work.showOperateView();
                }
            }
        }

        Image{
            id:quitBut;
            //color:"#123868"
            anchors.left: bqpic.right;
            anchors.leftMargin: 30;
            anchors.top: bqpic.top;
            width: 110; height: 30;
            fillMode: Image.PreserveAspectFit;
            source: "../images/exit01.png";
            //fillMode: Image.PreserveAspectCrop;

            MouseArea{
                anchors.fill: parent;
                hoverEnabled: true;
                onEntered: quitBut.source = "../images/exit02.png";
                onExited: quitBut.source = "../images/exit01.png";
                onPressed: quitBut.source = "../images/exit03.png";
                onClicked: {
                    exitDialog.open();
                }
            }
        }

        Text{
            id:label01;
            anchors.left: parent.left;
            anchors.leftMargin: 40;
            anchors.top: parent.top; anchors.topMargin: 5;
            text: qsTr("指挥调度系统");
            font.pixelSize: 28;
            color: "white";
        }
        Text{
            anchors.top: label01.bottom; anchors.topMargin: 8;
            anchors.left: label01.right; anchors.leftMargin: -55;
            text: qsTr("——用户管理界面");
            font.pixelSize: 20;
            color:"white";
        }
    }

    Rectangle {
        id: rect2;
        anchors.top: rect1.bottom;
        width: parent.width;
        height: parent.height-rect1.height -30 ; //30 for the third rect, rect3;
        SplitView {
            anchors.fill: parent
            orientation: Qt.Vertical;
            SplitView{
                handleDelegate: Rectangle{

                }
                id:row1;
                Layout.fillWidth: true;
                height: parent.height /5 *3;
                //height: parent.height - 350;
                //height: parent.height /20 *11;
                Layout.minimumHeight: 300;
                Rectangle {
                    id: column1;
                    width: 230
                    Layout.minimumWidth: 230;
                    Layout.maximumWidth: 500;
                    //color:"#123868";
                    color:"#bbc5cc";
                    Image{
                        id:rect21;
                        anchors.left: parent.left;
                        anchors.leftMargin: 3;
                        anchors.top: parent.top; anchors.topMargin: 1;
                        width: parent.width -3 ; height: 51;
                        //radius: 6;
                        //Image {
                        //  anchors.fill: parent;
                        source: "../images/grouplist.png";
                        //fillMode: Image.PreserveAspectCrop;
                        fillMode: Image.PreserveAspectFit;
                        //}

                        Text{
                            anchors.horizontalCenter: parent.horizontalCenter;
                            anchors.verticalCenter: parent.verticalCenter;
                            text:"用户群共["+ groupUserModel.count+"]群";
                            font.pixelSize: 20;
                            color:"white";
                        }
                    }


                    Rectangle{
                        id:rect23;
                        anchors.bottom: parent.bottom; anchors.bottomMargin:1;
                        anchors.left: parent.left; anchors.leftMargin: 2;
                        width: parent.width;
                        height: 26;
                        //color:"#123868";
                        color:"#bbc5cc";
                        TextField{
                            id:textinput;
                            anchors.left: parent.left; anchors.leftMargin: 3;
                            width: parent.width-65 ;height: parent.height -2;
                            anchors.top: parent.top; anchors.topMargin: 0;
                            placeholderText: "输入添加的群名";
                            font.pixelSize: 13;
                            style: TextFieldStyle {
                                background: Rectangle {
                                    radius: 6
                                    implicitWidth: parent.width-60
                                    implicitHeight: parent.height -2
                                    border.color: "lightblue"
                                    border.width: 2
                                }
                            }
                        }
                        Image{
                            id:addGroup;
                            anchors.left: textinput.right; anchors.leftMargin: 10;
                            //anchors.right: parent.right; //anchors.rightMargin: 1;
                            //width:50;
                            height: 22 ;
                            anchors.top: parent.top; anchors.topMargin: 1;
                            //text:"添加组";
                            source: "../images/creatGroup.png";
                            fillMode: Image.PreserveAspectFit;
                            MouseArea{
                                anchors.fill: parent;
                                hoverEnabled: true;
                                onEntered: addGroup.source = "../images/creatGroup2.png";
                                onExited: addGroup.source = "../images/creatGroup.png";
                                onClicked: {
                                    //console.log("HHHHHHHHHHHHHHHHH " + rect2.height);

                                    if(textinput.text)
                                        addGroups(textinput.text);
                                    textinput.text = "";
                                }
                            }
                        }

                    }

                    Rectangle{
                        id: rect22;
                        anchors.top: rect21.bottom;
                        anchors.bottom: rect23.top;
                        anchors.bottomMargin: 3;
                        //anchors.topMargin: 1;
                        anchors.left: parent.left; anchors.leftMargin: 5;
                        width: parent.width - 10; height: parent.height;
                        //color:"#006c8e";
                        //color:"#315980";
                        color:"#7d8f9c";
                        radius: 8;
                        border.color: "lightgray";
                        border.width: 1;

                        ListModel{
                            id:groupUserModel;
                            /*
                            ListElement { name: "嵌入式"; }
                            ListElement { name: "平台组"; }
                            ListElement { name: "安卓董"; }
                            ListElement { name: "测试组"; }
                            ListElement { name: "嵌入式"; }
                            ListElement { name: "平台组"; }
                            ListElement { name: "安卓董"; }
                            ListElement { name: "测试组"; }
                            ListElement { name: "嵌入式"; }
                            ListElement { name: "平台组"; }
                            ListElement { name: "安卓董"; }
                            ListElement { name: "测试组"; }
                            ListElement { name: "嵌入式"; }
                            ListElement { name: "平台组"; }
                            ListElement { name: "安卓董"; }
                            ListElement { name: "测试组"; }*/
                        }
                        ScrollView{
                            anchors.fill: parent;

                            style:ScrollViewStyle{
                                handle: Item{
                                    implicitHeight: 7;
                                    implicitWidth: 7;
                                    Rectangle{color:"#123868";
                                        anchors.fill: parent;
                                        visible: true;
                                    }

                                }
                                decrementControl: Image{
                                    width: 7; height: 7;
                                    source: "../images/arrow_up.png";
                                }
                                incrementControl: Image{
                                    width: 7; height: 7;
                                    source: "../images/arrow_down.png";
                                }
                                scrollBarBackground: Item{
                                    implicitHeight: 7;
                                    implicitWidth: 7;
                                }

                            }

                            ListView{
                                id: groupUserView;
                                anchors.fill: parent
                                spacing: 2;
                                delegate: groupUserDelegate;
                                model: groupUserModel;
                                highlight: Rectangle{
                                    //width: rect22.width - 16;
                                    // height: ListView.view.height;
                                    color:"#00394f";
                                    radius: 6;
                                    //width: parent.width -20;
                                    y: groupUserView.currentItem.y
                                    Behavior on y {
                                        SpringAnimation {
                                            spring: 3
                                            damping: 0.2
                                        }
                                    }
                                    Button{
                                        //opacity: 0;
                                        z:20;
                                        anchors.right:parent.right; anchors.rightMargin: 30;
                                        //anchors.horizontalCenter: parent.horizontalCenter;
                                        anchors.verticalCenter: parent.verticalCenter;
                                        width: 20; height: 20;
                                        //border.width: control.pressed ? 1 : 0;
                                        //border.color: (control.hovered || control.pressed ? "red" : "white");
                                        //radius: 9;
                                        Image{
                                            //z:20;
                                            //opacity: 0;
                                            anchors.fill: parent;
                                            anchors.margins: 2;

                                            //source: "../images/delGroupBut.svg"
                                            source: "../images/delGroupBut.svg";

                                        }

                                        style:ButtonStyle{
                                            background:Rectangle{
                                                radius:9;
                                                opacity: 0.5;
                                                color:(control.hovered || control.pressed ? "red" : "gray");
                                                border.width: control.pressed ? 2 : 0;
                                                border.color: (control.hovered || control.pressed ? "red" : "white");
                                            }
                                        }

                                        onClicked: {
                                            //groupUserView.currentIndex = index;
                                            var data = groupUserView.model.get(groupUserView.currentIndex).id;
                                            console.log("delGroupBut onclicked! id: " + data);
                                            messageDialog("确定删除群: " + (groupUserView.model.get(groupUserView.currentIndex).name) + " ?" ,1);

                                        }
                                    }


                                }
                                onCurrentIndexChanged: {
                                    flagRootUserChoose = 0;
                                    flagSpecialIntercom = 1;
                                    groupNameString = groupUserModel.get(groupUserView.currentIndex).name;
                                }

                            }



                        }
                        Component{
                            id: groupUserDelegate;

                            Item{
                                id:wrapper1;
                                width: parent.width;  height:32;
                                Rectangle{
                                    anchors.left: parent.left; anchors.leftMargin: 3;
                                    anchors.bottom: parent.bottom;
                                    width: parent.width -6; height: 2;
                                    color:"#123863";
                                    //opacity: 0;
                                }

                                Image {
                                    id: pic4;
                                    anchors.top: parent.top;
                                    anchors.topMargin: -5;
                                    anchors.left: parent.left;
                                    anchors.leftMargin: 15;
                                    width: 32; height: 32;
                                    source:"../images/pic5.png";
                                    fillMode: Image.PreserveAspectFit;
                                }
                                Text{
                                    text:name;
                                    anchors.top: parent.top;
                                    anchors.topMargin: 6; anchors.left: pic4.right; anchors.rightMargin: 5;
                                    font.pixelSize: 15;
                                    color:"white";

                                    width:parent.width -95;
                                    height: parent.height;
                                    elide:Text.ElideMiddle;
                                }

                                // }
                                MouseArea{
                                    //TODO
                                    //anchors.fill: parent;
                                    anchors.right: parent.right; anchors.rightMargin: 50;
                                    anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.left: parent.left;
                                    //acceptedButtons: Qt.MiddleButton;
                                    onClicked: {
                                        wrapper1.ListView.view.currentIndex = index;
                                        //console.log(groupUserView.model.get(index).name);
                                        var data = groupUserView.model.get(index).id;
                                        queryAddedGroup(data);
                                        //queryGroupUser(data);
                                    }

                                }

                            }

                        }

                    }
                }
                Rectangle{
                    id: column2;
                    //color:"#123868";
                    //color:"#a7b3bc"
                    color:"#bbc5cc";
                    anchors.left: column1.right;
                    width: parent.width;
                    height: parent.height;
                    ListModel{
                        id: attendeesModel;
                        /*
                        ListElement { name: "李一"; }
                        ListElement { name: "李二"; }
                        ListElement { name: "李三三"; }
                        ListElement { name: "李四五"; }
                        ListElement { name: "董怀志"; }
                        //ListElement { name: "}
                        ListElement { name: "平台组"; }
                        ListElement { name: "安卓董"; }
                        ListElement { name: "测试组"; }
                        ListElement { name: "嵌入式"; }
                        ListElement { name: "平台组"; }
                        ListElement { name: "安卓董"; }
                        ListElement { name: "测试组"; }
                        ListElement { name: "嵌入式"; }
                        ListElement { name: "平台组"; }
                        ListElement { name: "安卓董"; }
                        ListElement { name: "测试组"; }*/
                    }
                    Rectangle{
                        //anchors.fill: parent;
                        //width: parent.width;
                        anchors.top: rect24.bottom;
                        anchors.bottom: parent.bottom; anchors.bottomMargin: 7;
                        width: parent.width;
                        //height: parent.height -77;
                        //height: parent.height -7;
                        radius: 10;
                        color:"#a7b3bc";

                        ScrollView{
                            anchors.fill: parent;

                            style:ScrollViewStyle{
                                handle: Item{
                                    implicitHeight: 25;
                                    implicitWidth: 12;
                                    Rectangle{
                                        color:"#315980";
                                        anchors.fill: parent;
                                        visible: true;
                                    }

                                }
                                decrementControl: Image{
                                    width: 12; height: 12;
                                    source: "../images/arrow_up02.png";
                                }
                                incrementControl: Image{
                                    width: 12; height: 12;
                                    source: "../images/arrow_down01.png";
                                }
                                scrollBarBackground: Item{
                                    implicitHeight: 25;
                                    implicitWidth: 16;
                                }

                            }

                            GridView{
                                property int dragItemIndex: -1; //[2]-----------------added!
                                id:attendeesListView;
                                anchors.left: parent.left; anchors.leftMargin: 70;
                                anchors.fill: parent;
                                model:attendeesModel;
                                delegate: attendeesDelegate;
                                anchors.margins: 20

                                cellWidth: 150
                                cellHeight:100

                            }
                        }
                    }

                    Component{
                        id: attendeesDelegate;

                        Item {
                            id: wrapper2;
                            //width: 90; height: 60;
                            Image{
                                id: dragRect;
                                width: 118; height: 62;
                                source: role == 4 ? "../images/xjUserBack.png" : role == 2 ? "../images/yjBack.png" : role == 3 ?
                                                                                                 "../images/speakerBac.png" : "../images/zHYBack.png";
                                //fillMode: Image.PreserveAspectFit;

                                Image {
                                    id: pic6;
                                    //z:12;
                                    anchors.left: parent.left; anchors.leftMargin: 2;
                                    anchors.top: parent.top; anchors.topMargin: 3;//anchors.topMargin: 3;
                                    width: 32; height: 32;
                                    source:  "../images/pic6.png";
                                    //source: (role == 1) ? "../images/rootuser.png" : "../images/pic6.png";
                                    //fillMode: Image.PreserveAspectFit;

                                    MouseArea{
                                        //messageDialog("确定用户#" + (attendeesModel.get(index).realName) + "#为指挥员?", attendeesModel.get(index));
                                        //messageDialog("失败,禁止对专向用户进行此操作!", 4);
                                        anchors.fill: parent;
                                        //propagateComposedEvents: true
                                        onClicked: {
                                            if(aIdFlag == 9999)
                                            {
                                                aIdFlag = attendeesModel.get(index).accountId;
                                            }
                                            if(aIdFlag != attendeesModel.get(index).accountId)
                                            {
                                                flagSpecialIntercom = 1;
                                            }
                                            if(role != 1)
                                            {
                                                //console.log("DEBUG:HHHHHHHHHHHHHH" + specialIntercom);//"此操作会取消用户已有的专向和转接功能！"
                                                if(flagRootUserChoose == 1)
                                                {
                                                    messageDialog("失败,一个群只能有一个指挥员!", 4);
                                                }
                                                else if(aId > 0)
                                                {
                                                    messageDialog("确定用户#" + (attendeesModel.get(index).realName) + "#为指挥员?" + "\n" + "此操作会取消用户的转接功能！",
                                                              6, attendeesModel.get(index));
                                                }
                                                else if(specialIntercom == 1 && flagSpecialIntercom != 3)
                                                {
                                                    messageDialog("确定用户#" + (attendeesModel.get(index).realName) + "#为指挥员?" + "\n" + "此操作会取消用户已有的专向功能！",
                                                              6, attendeesModel.get(index));
                                                }
                                                else if(specialIntercom == 0 && flagSpecialIntercom == 2)
                                                {
                                                    messageDialog("确定用户#" + (attendeesModel.get(index).realName) + "#为指挥员?" + "\n" + "此操作会取消用户已有的专向功能！",
                                                              6, attendeesModel.get(index));
                                                }
//                                                else if(flagRootUserChoose == 1)
//                                                {
//                                                    messageDialog("失败,一个群只能有一个指挥员!", 4);
//                                                }
                                                else
                                                    messageDialog("确定用户#" + (attendeesModel.get(index).realName) + "#为指挥员?",
                                                              6, attendeesModel.get(index));
                                            }
                                            else
                                                messageDialog("取消用户#" + (attendeesModel.get(index).realName) + "#为指挥员?",
                                                              5, attendeesModel.get(index));

                                            mouse.accepted = false
                                            //mouse.accepted = false
                                        }
                                    }
                                }

                                Text{
                                    //z:12;
                                    id: realNameid;
                                    text:realName;
                                    anchors.top: parent.top;
                                    anchors.topMargin: 6;
                                    //anchors.horizontalCenter: parent.horizontalCenter;
                                    //height: 20;
                                    anchors.left: pic6.right; anchors.leftMargin: -10;
                                    anchors.right: shift.left;
                                    height: 20; width:parent.width - 20;
                                    horizontalAlignment :Text.AlignHCenter ;
                                    font.pixelSize: 15;
                                    color:"white";
                                    elide: Text.ElideRight;

                                    ToolTip{
                                        //z:15;
                                        space: 30;
                                        toolTip: parent.text;
                                    }
                                }

                                CheckBox{
                                    id:shift;
                                    z:10;
                                    //anchors.left: realNameid.right; anchors.leftMargin: 4;
                                    anchors.right: parent.right; anchors.rightMargin: 2;
                                    //anchors.verticalCenter: realNameid.verticalCenter;
                                    anchors.top: parent.top; anchors.topMargin: 6;
                                    checked: specialIntercom == 1 ? true : false;
                                    style: CheckBoxStyle {
                                        indicator: Image{
                                            width: 10
                                            height: 10
                                            source: "../images/speShift01.png";
                                            fillMode: Image.PreserveAspectFit;
                                            Image {
                                                visible: control.checked
                                                source: "../images/speShift02.png";
                                                anchors.margins: 0
                                                anchors.fill: parent
                                            }
                                        }
                                    }

                                    onClicked: {

                                        var data = groupUserModel.get(groupUserView.currentIndex).id;
                                        var dat = attendeesModel.get(index);
                                        aIdFlag = dat.accountId;
                                        if(aId == "" && role != 3 && role != 2 && role != 1)
                                        //if(aId > 0 && role != 3 && role != 2 && role != 1)
                                        {
                                            if(shift.checkedState == 2){

                                                addUserFunction(data, dat, "specialIntercom", 1);
                                                flagSpecialIntercom = 2;
                                            }
                                            else{
                                                //console.log("shift not onclicked!");
                                                addUserFunction(data, dat, "specialIntercom", 0);
                                                flagSpecialIntercom = 3;
                                            }

                                        }
                                        else
                                        {
                                            shift.checked = false;
                                            if(role == 3 )
                                                messageDialog("失败,禁止对广播员进行此操作!", 4);
                                            else if(role == 2)
                                                messageDialog("失败,禁止对越级用户进行此操作!", 4);
                                            else if(role ==1 )
                                                messageDialog("失败，禁止对指挥员进行此操作!", 4);
                                            else
                                            {
                                                messageDialog("失败,禁止对转接用户用此操作！", 4);
                                            }

                                        }

                                    }
                                }

                                CheckBox{
                                    id: check1;
                                    z: 10;
                                    anchors.bottom: parent.bottom; anchors.bottomMargin: 5;
                                    anchors.left: parent.left; anchors.leftMargin: 14;
                                    checked: receiver == 1 ? false : true;
                                    style: CheckBoxStyle {
                                        indicator: Image{
                                            width: 18
                                            height: 20
                                            source: "../images/icon_1.png";
                                            fillMode: Image.PreserveAspectFit;
                                            Image {
                                                visible: control.checked
                                                source: "../images/icon_01.png";
                                                anchors.margins: 0
                                                anchors.fill: parent
                                            }
                                        }
                                    }
                                    onClicked: {

                                        if(role != 1)
                                        {
                                            //console.log("check1.state " + check1.checkedState);
                                            var value; var data = groupUserModel.get(groupUserView.currentIndex).id;
                                            if(check1.checkedState == 2){
                                                value = 0;
                                            }
                                            else{
                                                value = 1;
                                            }
                                            console.log("index " + index);
                                            addUserFunction(data, attendeesModel.get(index), "receiver", value); //1: valueof receiver;
                                        }else //role =1
                                        {
                                            check1.checked = false;
                                            messageDialog("失败，不允许对指挥员进行此操作！", 4);
                                        }


                                    }
                                }
                                CheckBox{
                                    id: check2;
                                    z: 10;
                                    anchors.bottom: parent.bottom; anchors.bottomMargin: 5;
                                    anchors.left: check1.right; anchors.leftMargin: 9;
                                    //checked: true;

                                    checked: micGranted == 1 ? false : true;
                                    style: CheckBoxStyle {
                                        indicator: Image{
                                            width: 18
                                            height: 20
                                            source: "../images/icon_2.png";
                                            fillMode: Image.PreserveAspectFit;
                                            Image {
                                                visible: control.checked
                                                source: "../images/icon_5.png";
                                                anchors.margins: 0
                                                anchors.fill: parent
                                            }
                                        }
                                    }

                                    onClicked: {
                                        if(role != 1)
                                        {
                                            var value;
                                            var data = groupUserModel.get(groupUserView.currentIndex).id;
                                            if(check2.checkedState == 2){
                                                value = 0;
                                            }
                                            else{
                                                value =1;
                                            }
                                            addUserFunction(data, attendeesModel.get(index), "micGranted", value);
                                        }else //role =1
                                        {
                                            check2.checked = false;
                                            messageDialog("失败，不允许对指挥员进行此操作！", 4);
                                        }

                                    }
                                }
                                CheckBox{
                                    id: check3;
                                    z: 10;
                                    anchors.bottom: parent.bottom; anchors.bottomMargin: 5;
                                    anchors.left: check2.right; anchors.leftMargin: 11;
                                    checked: mode == 1 ? false : true;
                                    style: CheckBoxStyle {
                                        indicator: Image{
                                            width: 18
                                            height: 20
                                            source: "../images/icon_3.png";
                                            fillMode: Image.PreserveAspectFit;
                                            Image {
                                                visible: control.checked
                                                source: "../images/icon_6.png";
                                                anchors.margins: 0
                                                anchors.fill: parent
                                            }
                                        }
                                    }
                                    onClicked: {
                                        if(role != 1)
                                        {
                                            var value;
                                            var data = groupUserModel.get(groupUserView.currentIndex).id;
                                            if(check3.checkedState == 2){
                                                value = 0;
                                            }
                                            else{
                                                value = 1;
                                            }

                                            addUserFunction(data, attendeesModel.get(index), "mode", value);
                                        }else //role = 1
                                        {
                                            check3.checked = false;
                                            messageDialog("失败，不允许对指挥员进行此操作！", 4);
                                        }
                                    }
                                }

                                Text{
                                    id: partText;
                                    visible: false;
                                    anchors.bottom: parent.bottom; anchors.bottomMargin: -20;
                                    anchors.horizontalCenter: dragRect.horizontalCenter;
                                    text: role == 1 ?  userName + " 指挥员" : role == 2 ?  userName + " 越级" : role == 3 ? userName +" 广播员" : userName;
                                    color:"black"; font.pixelSize: 13;
                                }

                                Text{
                                    anchors.bottom: parent.bottom; anchors.bottomMargin: -20;
                                    anchors.horizontalCenter: dragRect.horizontalCenter;
                                    //text: role == 1 ?  userName + " 指挥员" : role == 2 ?  userName + " 越级" : role == 3 ? userName +" 广播员" : userName;
                                    color:"black"; font.pixelSize: 13;
                                    text: fromId == 2 ? partText.text + "-虚拟" : fromId == 3 ? partText.text + "-物理" : fromId == 1 ? partText.text + "-联系人" : partText.text;
                                }

                                //[1].....................changed!
                                MouseArea{
                                    id: mouseArea;
                                    //z:1;
                                    propagateComposedEvents: true
                                    anchors.fill: parent;
                                    drag.target: dragRect;
                                    drag.onActiveChanged: {
                                        if(mouseArea.drag.active){
                                            attendeesListView.dragItemIndex = index;
                                        }
                                        flagDropCtrl = 1;
                                        dragRect.Drag.drop();

                                    }

                                }

                                states: [
                                    State{
                                        when: dragRect.Drag.active
                                        ParentChange{
                                            target: dragRect;
                                            parent: root;
                                        }
                                        AnchorChanges {
                                            target: dragRect
                                            anchors.horizontalCenter: undefined
                                            anchors.verticalCenter: undefined
                                        }

                                    }

                                ]
                                Drag.active: mouseArea.drag.active
                                Drag.hotSpot.x: dragRect.width/3
                                Drag.hotSpot.y: dragRect.height/3

                            }


                        }

                    }

                    Rectangle{
                        id: rect24;
                        anchors.top: showGroup.bottom;
                        anchors.topMargin: 0;
                        width: parent.width;
                        height: 35;
                        //border.color: "black";
                        //border.width: 1;
                        //color:"#123868";
                        color:"#213c59";

                        Rectangle{
                            id: rect241;
                            anchors.top: parent.top; width: 40;
                            anchors.left: parent.left; anchors.leftMargin: parent.width/7;
                            Image{
                                id: pic8;
                                source:"../images/icon_1.png";
                                anchors.top:parent.top; anchors.topMargin: 7;
                                width: 18;
                                anchors.left: parent.left;
                                fillMode: Image.PreserveAspectFit;
                            }

                            Text{
                                id:tex2;
                                anchors.left: pic8.right; anchors.leftMargin: 6;
                                anchors.top: parent.top; anchors.topMargin: 5;
                                text:"监听权["+ receiverCount +"/32]";
                                color:"white";
                            }
                        }
                        Rectangle{
                            id: rect242;
                            anchors.top: parent.top; width:40 ;
                            anchors.left: rect241.right; anchors.leftMargin: parent.width /6;
                            Image{
                                id: pic9;
                                source:"../images/icon_2.png";
                                anchors.top:parent.top; anchors.topMargin: 7;
                                width: 21;
                                anchors.left: parent.left;
                                fillMode: Image.PreserveAspectFit;
                            }
                            Text{
                                id: tex3;
                                anchors.left: pic9.right; anchors.leftMargin: 5;
                                anchors.top: parent.top; anchors.topMargin: 5;
                                text:"发言权["+ micGrantedCount +"/32]";
                                color:"white";
                            }
                        }
                        Rectangle{
                            id: rect243;
                            anchors.top: parent.top; width:40 ;
                            anchors.left: rect242.right; anchors.leftMargin: parent.width /6;
                            Image{
                                id: pic10;
                                source:"../images/icon_3.png";
                                anchors.top:parent.top; anchors.topMargin: 7;
                                width: 21;
                                anchors.left: parent.left;
                                fillMode: Image.PreserveAspectFit;
                            }
                            Text{
                                id:tex4;
                                anchors.left: pic10.right; anchors.leftMargin: 5;
                                anchors.top: parent.top; anchors.topMargin: 5;
                                text:"主动呼叫[" + modeCount +"/32]";
                                color:"white";
                            }
                        }
                        Rectangle{
                            id: rect244;
                            anchors.top: parent.top; width:40 ;
                            anchors.left: rect243.right; anchors.leftMargin: parent.width /6;
                            Image{
                                id: pic11;
                                source:"../images/speShift02.png";
                                anchors.top:parent.top; anchors.topMargin: 9;
                                width: 15; height:15
                                anchors.left: parent.left;
                                fillMode: Image.PreserveAspectFit;
                            }
                            Text{
                                id:tex5;
                                anchors.left: pic11.right; anchors.leftMargin: 5;
                                anchors.top: parent.top; anchors.topMargin: 5;
                                text:"专向开关[" + specialIntercomCount +"/32]";
                                color:"white";
                            }
                        }

                    }
                    Rectangle{
                        id:showGroup;
                        anchors.top: parent.top; anchors.topMargin: 7;
                        width: parent.width; height: 45;
                        color:"#bbc5cc";
                        //radius:8;

                        Image{
                            id:showGroupRight;
                            anchors.right: parent.right;
                            height: parent.height;
                            width: 11;
                            //source: "../images/yonghuzu_right.png";
                            source: "../images/list02_right.png";
                            //fillMode: Image.PreserveAspectFit;
                        }

                        Image{
                            //id:showGroup;
                            anchors.left: showGroupLeft.right;
                            //anchors.right: parent.right; //anchors.rightMargin: 11;
                            anchors.right: showGroupRight.left; //anchors.rightMargin:0;
                            height: parent.height; width: parent.width ;
                            //source: "../images/yonghuzu_mid.png";
                            source: "../images/list02_mid.png";
                            //fillMode: Image.PreserveAspectCrop;
                        }
                        Image{
                            id:showGroupLeft;
                            anchors.left: parent.left;
                            height: parent.height; width: 11;
                            //source: "../images/yonghuzu_left.png";
                            source: "../images/list02_left.png";
                            //fillMode: Image.PreserveAspectFit;
                        }

                        Text{
                            id: tex1;
                            anchors.centerIn: parent;
                            //anchors.top: parent.top; anchors.topMargin: 7;
                            //anchors.left: parent.left; anchors.leftMargin: parent.width/12;
                            //text:"[" + attendeesModel.count + "/32]用户在 "+ groupUserModel.get(groupUserView.currentIndex).name + " 群";
                            text:"[" + attendeesModel.count + "/32]用户在 "+ groupNameString + " 群";
                            font.pixelSize: 22;
                            color:"white";
                        }
                    }



                    DropArea{
                        id: dropArea1;
                        anchors.fill: parent;
                        onDropped: {
                            //console.log("hello1111111111111");
                            console.log(avaiableUserView.drag1ItemIndex +" "+  attendeesListView.dragItemIndex);
                            if(avaiableUserView.drag1ItemIndex !== -1 && flagDropCtrl == 2){
                                var dat = avaiableUserView.model.get(avaiableUserView.drag1ItemIndex);
                                var data = groupUserModel.get(groupUserView.currentIndex).id;
                                console.log("groupid 000" + data);
                                addUsertoGroup(data, dat, 1);
                                //attendeesModel.append(dat);
                                avaiableUserView.model.remove(avaiableUserView.drag1ItemIndex);
                                avaiableUserView.drag1ItemIndex = -1;
                                flagDropCtrl = 0;
                            }
                            else if (flagDropCtrl == 1){
                                //var da = attendeesListView.model.get(attendeesListView.dragItemIndex);
                                queryAddedGroup(groupUserModel.get(groupUserView.currentIndex).id);
                                //attendeesModel.append(da);
                                //attendeesModel.remove(attendeesListView.dragItemIndex);
                                flagDropCtrl = 0;

                            }
                        }
                    }

                }

            }

            SplitView {
                handleDelegate: Rectangle{

                }
                id: row2;
                Layout.fillWidth: true
                //height: 350;
                height: parent.height/5 * 2 ;
                Layout.minimumHeight:250;

                Rectangle {
                    id: column3;
                    width: 230; //---3
                    //color: "#315980";
                    color:"#BBC5CC";
                    Layout.minimumWidth: 90;
                    Layout.maximumWidth: 230;
                    height: parent.height;
                    /*
                    ReComboBox{
                        id: rect27;

                        anchors.top: parent.top; anchors.topMargin: 2;
                        anchors.horizontalCenter: parent.horizontalCenter;
                        //width: 228; height: 138;
                    }*/

                    Image{
                        id: rect27;
                        anchors.top: parent.top; anchors.topMargin: 2;
                        //anchors.horizontalCenter: parent.horizontalCenter;
                        //anchors.verticalCenter: parent.verticalCenter;
                        anchors.left: parent.left; anchors.leftMargin: 4;
                        width: 230;
                        height: 38;
                        //source: "../images/showUserInfo.png";
                        source:"../images/grouplist.png";
                        //fillMode: Image.PreserveAspectFit;
                        fillMode: Image.PreserveAspectCrop;
                        Text{
                            anchors.centerIn: parent;
                            text:"用户信息";
                            font.pixelSize: 20;
                            color:"white";
                        }

                    }

                    Rectangle{
                        x: 0; y: 42;
                        height: parent.height - 60;//30
                        width:parent.width;
                        color:"#7D8F9C";
                        // }

                        ScrollView{

                            anchors.fill: parent;
                            //width:Math.min(content.width , parent.width);
                            // height: Math.min(content.height, parent.height);
                            //height: Math.min(345, parent.height);
                            //frameVisible :true;
                            style:ScrollViewStyle{
                                handle: Item{
                                    implicitHeight: 7;
                                    implicitWidth: 7;
                                    Rectangle{
                                        color:"#123868"
                                        anchors.fill: parent;
                                        visible: true;
                                    }

                                }
                                decrementControl: Image{
                                    width: 7; height: 7;
                                    source: "../images/arrow_up02.png";
                                }
                                incrementControl: Image{
                                    width: 7; height: 7;
                                    source: "../images/arrow_down01.png";
                                }
                                scrollBarBackground: Item{
                                    implicitHeight: 7;
                                    implicitWidth: 7;
                                }

                            }

                            Rectangle{
                                id:content;
                                //color: "#315980";
                                color:"#7d8f9c";
                                //anchors.top: parent.top;
                                //anchors.bottom: parent.bottom;
                                //anchors.top: rect27.bottom; anchors.topMargin: 5;
                                //anchors.bottom: rect26.top; anchors.bottomMargin: 5;
                                width: column3.width;
                                height: 310;
                                //height: column3.height //- 82;
                                //height:  200;
                                //RegExpValidator { id: regexpValidator;regExp: "000.000.000.000"}
                                IntValidator {id:input2TextValidator; bottom: 1002; top:9999}
                                ReComboBox{
                                    id:choiceClient;
                                    anchors.top: parent.top;
                                    //anchors.top: parent.bottom; anchors.topMargin: 10;
                                    //anchors.top: rect27.bottom; anchors.topMargin: 10;
                                    //anchors.horizontalCenter: parent.horizontalCenter;
                                    anchors.left: parent.left; anchors.leftMargin: 3;
                                    width: parent.width; height: 30;

                                    onChoiceSip: {
                                        audioAlg.visible = false;
                                        phyType.visible = false;
                                        userPassWord.visible = true;
                                        input1.placeholderText = "用户名";
                                        inputPWText.text = "密   码";
                                        inputPWText.font.pixelSize = 17;
                                        input2.inputMask = "";
                                        input2.placeholderText = "输入密码";
                                        choiceSipFlag = true;
                                        choiceVirFlag = false;
                                        choicePhyFlag = false;
                                        if(menuListView.currentIndex == 1)
                                            queryAllUser(true);
                                        else
                                            queryAllUser(false);

                                        input1.text = "";
                                        input2.text = "";
                                        input3.text = "";

                                    }
                                    //console.log("hello ++++++++++++++++++ choiceSip called!");
                                    onChoiceVir: {
                                        phyType.visible = false;
                                        audioAlg.visible = false;
                                        userPassWord.visible = true;
                                        //input1.validator = regexpValidator
                                        input1.placeholderText = "用户名[1002,9999]";
                                        inputPWText.text = "服务器地址";
                                        inputPWText.font.pixelSize = 12;
                                        input2.placeholderText = "服务器地址";
                                        //input1.validator = input2TextValidator;
                                        input2.inputMask = "000.000.000.00";
                                        choiceSipFlag = false;
                                        choiceVirFlag = true;
                                        choicePhyFlag = false;
                                        choiceConFlag = false;
                                        if(menuListView.currentIndex == 1)
                                            queryVirAllUser(true);
                                        else
                                            queryVirAllUser(false);
                                        input1.text = "";
                                        input2.text = "";
                                        input3.text = "";

                                    }
                                    onChoicePhy: {
                                        audioAlg.visible = true;
                                        phyType.visible = true;
                                        userPassWord.visible = false;
                                        input1.placeholderText = "用户名";
                                        inputPWText.text = "类   型";
                                        inputPWText.font.pixelSize = 17;
                                        //input2.validator = regexpValidator;
                                        input2.placeholderText = "0-指挥单机 1-扬声单机";
                                        choiceSipFlag = false;
                                        choiceVirFlag = false;
                                        choicePhyFlag = true;
                                        choiceConFlag = false;
                                        if(menuListView.currentIndex == 1)
                                            queryPhyAllUser(true);
                                        else
                                            queryPhyAllUser(false);
                                        input1.text = "";
                                        input2.text = "";
                                        input3.text = "";
                                        //input4.text = "";
                                    }

                                    onChoiceCon: {
                                        audioAlg.visible = false;
                                        phyType.visible = false;
                                        userPassWord.visible = true;
                                        input1.placeholderText = "用户名";
                                        inputPWText.text = "域      ";
                                        inputPWText.font.pixelSize = 17;
                                        input2.placeholderText = "输入域名";
                                        input2.inputMask = "";
                                        choiceSipFlag = false;
                                        choiceVirFlag = false;
                                        choicePhyFlag = false;
                                        choiceConFlag = true;
                                        if(menuListView.currentIndex == 1)
                                            queryConUser(true);
                                        else
                                            queryConUser(false);

                                        input1.text = "";
                                        input2.text = "";
                                        input3.text = "";
                                        //input4.text = "";

                                    }
                                }


                                Rectangle{
                                    id: rect28;
                                    //anchors.top: rect27.bottom; anchors.topMargin: 30;
                                    anchors.top: choiceClient.bottom; anchors.topMargin: 13;
                                    anchors.left: parent.left; anchors.leftMargin: 16;
                                    width: parent.width; height: 40;
                                    //color:"#315980";
                                    color:"#7d8f9c";
                                    TextField{
                                        id: userNameSearch;
                                        anchors.left: parent.left; anchors.leftMargin: 3;
                                        anchors.top: parent.top; anchors.topMargin: 4;
                                        width: parent.width -90; height: 26;
                                        placeholderText: "输用户姓名/用户名";
                                        font.pixelSize: 13;
                                        style: TextFieldStyle {
                                            background: Rectangle {
                                                radius: 8
                                                implicitWidth: parent.width-60
                                                implicitHeight: 26;
                                                border.color: "lightblue";
                                                border.width: 2;
                                            }
                                        }
                                    }

                                    Image{
                                        id: searchBut;
                                        anchors.left: userNameSearch.right; anchors.leftMargin: 5;
                                        anchors.top: parent.top; anchors.topMargin: 2;
                                        //
                                        width: 50; height: 32;
                                        source: "../images/buttn_t01.png";
                                        fillMode: Image.PreserveAspectFit;
                                        Text{
                                            anchors.centerIn: parent;
                                            text:"搜索";
                                            color:"white";
                                            font.pixelSize: 15;
                                        }

                                        MouseArea{
                                            anchors.fill: parent;
                                            hoverEnabled: true;
                                            onEntered: searchBut.source = "../images/buttn_t02.png";
                                            onExited: searchBut.source = "../images/buttn_t01.png";
                                            onClicked: {
                                                console.log("search clicked! " + userNameSearch.text + allUsersModel.count);
                                                if(userNameSearch.text){
                                                    var dat = userNameSearch.text;
                                                    for(var i = 0; i < allUsersModel.count ; i ++){
                                                        var userData = allUsersModel.get(i);
                                                        //console.log("realName " + allUsersModel.get(i).realName);
                                                        if(userData.realName === dat || userData.username === dat)
                                                        {
                                                            console.log("search entered! " + allUsersModel.count);
                                                            var data = allUsersModel.get(i);
                                                            input1.text = data.username;
                                                            if(choiceSipFlag == false && choiceVirFlag == false && choicePhyFlag == false && choiceConFlag == false)
                                                                input2.text = data.password;
                                                            else if(choiceSipFlag == true)
                                                                input2.text = data.password;
                                                            else if(choiceVirFlag == true)
                                                                input2.text = data.serverIp;
                                                            else if(choicePhyFlag == true){
                                                                input2.text = data.type;
                                                                console.log("HHHHHHHHHHHHHHHHHHHHH" + data.audioAlgo);
                                                                if(data.audioAlgo == 5)
                                                                {
                                                                    radioButton01.checked = true;
                                                                }
                                                                else{
                                                                    radioButton02.checked = true;
                                                                }
                                                                //input4.text = data.audioAlgo;
                                                            }
                                                            else if(choiceConFlag == true)
                                                                input2.text = data.domain;

                                                            input3.text = data.realName;

                                                            break;
                                                        }

                                                    }
                                                    if(i == allUsersModel.count)
                                                        if( (choiceSipFlag == false && choiceVirFlag == false && choicePhyFlag == false && choiceConFlag == false) || choiceSipFlag == true)
                                                            messageDialog("Sip单机中没有该用户！", 4);
                                                        else if(choiceVirFlag == true)
                                                            messageDialog("虚拟单机中没有该用户！", 4);
                                                        else if(choicePhyFlag == true)
                                                            messageDialog("物理单机中没有该用户！", 4);
                                                        else if(choiceConFlag == true)
                                                            messageDialog("联系人中没有该用户！", 4);
                                                    // dataRequestError("此系统没有该用户！");

                                                }

                                            }
                                        }
                                    }
                                }

                                Column{
                                    id: userInformation;
                                    anchors.top: rect28.bottom; anchors.topMargin: 2;
                                    //anchors.top: rect27.bottom; anchors.topMargin: 80;
                                    anchors.left: parent.left; anchors.leftMargin: 5;
                                    width: parent.width; height: 140;
                                    spacing: 8;

                                    Rectangle{
                                        //color:"#315980";
                                        color:"#7d8f9c";
                                        width: parent.width;
                                        height: 30;
                                        Rectangle{
                                            id: inputUserName;
                                            //color:"#315980";
                                            color:"#7d8f9c";
                                            width: 40; height: parent.height;
                                            anchors.left: parent.left; anchors.leftMargin: 15;
                                            Text{
                                                anchors.centerIn: parent;
                                                text:"用户名";
                                                font.pixelSize: 17
                                                color:"white";
                                            }
                                        }


                                        TextField{
                                            id: input1;
                                            anchors.left:inputUserName.right; anchors.leftMargin: 20;
                                            anchors.verticalCenter: inputUserName.verticalCenter;
                                            width: 135; height: 24;
                                            font.pixelSize: 12;
                                            //text:""
                                            placeholderText: "用户名";
                                            text:availableUserModel.get(avaiableUserView.currentIndex).username;
                                            validator: RegExpValidator { regExp: /[0-9]+/ }
                                            //validator: IntValidator { bottom: 1002; top:9999}
                                            style: TextFieldStyle {
                                                background: Rectangle {
                                                    radius: 8
                                                    color:"#c6d1e0"
                                                    //color:"#7d8f9c";
                                                    implicitWidth: 135
                                                    implicitHeight: 24
                                                    border.color: "lightblue"
                                                    border.width: 2
                                                }
                                            }
                                        }
                                    }

                                    Rectangle{
                                        id:userPassWord;
                                        //color:"#315980";
                                        color:"#7d8f9c";
                                        width: parent.width;
                                        height: 30;
                                        Rectangle{
                                            id: inputPassword;
                                            //color:"#315980";
                                            color:"#7d8f9c";
                                            width: 40; height: parent.height;
                                            anchors.left: parent.left; anchors.leftMargin: 15;
                                            Text{
                                                id:inputPWText;
                                                anchors.centerIn: parent;
                                                text:"密   码";
                                                font.pixelSize: 17
                                                color:"white";
                                            }
                                        }


                                        TextField{
                                            id: input2;
                                            anchors.left:inputPassword.right; anchors.leftMargin: 20;
                                            anchors.verticalCenter: inputPassword.verticalCenter;
                                            width: 135; height: 24;
                                            font.pixelSize: 12;
                                            placeholderText: "密码";
                                            text:availableUserModel.get(avaiableUserView.currentIndex).password;
                                            validator: RegExpValidator { regExp: /[0-9A-Za-z.]+/ }
                                            style: TextFieldStyle {
                                                background: Rectangle {
                                                    radius: 8
                                                    color:"#c6d1e0"
                                                    implicitWidth: 135
                                                    implicitHeight: 24
                                                    border.color: "lightblue"
                                                    border.width: 2
                                                }
                                            }
                                        }
                                    }

                                    Rectangle{
                                        //color:"#315980";
                                        color:"#7d8f9c";
                                        width: parent.width;
                                        height: 30;
                                        Rectangle{
                                            id: inputName;
                                            //color:"#315980";
                                            color:"#7d8f9c";
                                            width: 40; height: parent.height;
                                            anchors.left: parent.left; anchors.leftMargin: 15;
                                            Text{
                                                anchors.centerIn: parent;
                                                text:"姓   名";
                                                font.pixelSize: 17;
                                                color:"white";
                                            }
                                        }


                                        TextField{
                                            id: input3;
                                            anchors.left:inputName.right; anchors.leftMargin: 20;
                                            anchors.verticalCenter: inputName.verticalCenter;
                                            width: 135; height: 24;
                                            font.pixelSize: 12;
                                            placeholderText: "姓名";
                                            text:availableUserModel.get(avaiableUserView.currentIndex).realName;
                                            style: TextFieldStyle {
                                                background: Rectangle {
                                                    radius: 8
                                                    color:"#c6d1e0"
                                                    implicitWidth: 135
                                                    implicitHeight: 24
                                                    border.color: "lightblue"
                                                    border.width: 2
                                                }
                                            }
                                        }
                                    }

                                    Rectangle{
                                        id: audioAlg;
                                        visible: false;
                                        //color:"#315980";
                                        color:"#7d8f9c";
                                        width: parent.width;
                                        height: 30;
                                        Rectangle{
                                            id: inputAudioAlg;
                                            //color:"#315980";
                                            color:"#7d8f9c";
                                            width: 40; height: parent.height;
                                            anchors.left: parent.left; anchors.leftMargin: 15;
                                            Text{
                                                anchors.centerIn: parent;
                                                text:"语音算法";
                                                font.pixelSize: 13;
                                                color:"white";
                                            }
                                        }
                                        //GroupBox {

                                        RowLayout {
                                            id:input4;
                                            //anchors.right: parent.right; anchors.rightMargin: 15;
                                            anchors.left:inputAudioAlg.right; anchors.leftMargin: 13;
                                            anchors.verticalCenter: inputAudioAlg.verticalCenter;
                                            width: 135; height: 24;
                                            ExclusiveGroup { id: tabPositionGroup }
                                            RadioButton {
                                                id:radioButton01;
                                                checked: true;
                                                //text:"5";
                                                text: qsTr("5-G.711A")
                                                style: RadioButtonStyle{
                                                        label: Text{
                                                        text: control.text
                                                        font.pixelSize: 10
                                                        font.family: "DejaVu Sans"
                                                        anchors.margins: 0
                                                        horizontalAlignment: Text.left
                                                    }
                                                indicator: Rectangle{
                                                    implicitWidth: 14
                                                    implicitHeight: 14
                                                    radius: 9
                                                    border.color: control.activeFocus ? "darkblue" : "gray"
                                                    border.width: 1

                                                    Rectangle {
                                                        anchors.fill: parent
                                                        visible: control.checked
                                                        color: "#555"
                                                        radius: 9
                                                        anchors.margins: 4
                                                    }
                                                }
                                            }
                                                exclusiveGroup: tabPositionGroup
                                            }
                                            RadioButton {
                                                id:radioButton02;
                                                anchors.left: radioButton01.right; anchors.leftMargin: 5;
                                                text: qsTr("7-G.711A")
                                                style: RadioButtonStyle{
                                                        label: Text{
                                                        text: control.text
                                                        font.pixelSize: 10
                                                        font.family: "DejaVu Sans"
                                                        anchors.margins: 0
                                                        horizontalAlignment: Text.left
                                                    }
                                                indicator: Rectangle{
                                                    implicitWidth: 14
                                                    implicitHeight: 14
                                                    radius: 9
                                                    border.color: control.activeFocus ? "darkblue" : "gray"
                                                    border.width: 1

                                                    Rectangle {
                                                        anchors.fill: parent
                                                        visible: control.checked
                                                        color: "#555"
                                                        radius: 9
                                                        anchors.margins: 4
                                                    }
                                                }
                                            }
                                                exclusiveGroup: tabPositionGroup
                                            }
                                        }
                                    }

                                    Rectangle{
                                        id: phyType;
                                        visible: false;
                                        //color:"#315980";
                                        color:"#7d8f9c";
                                        width: parent.width;
                                        height: 30;
                                        Rectangle{
                                            id: inputPhyType;
                                            //color:"#315980";
                                            color:"#7d8f9c";
                                            width: 40; height: parent.height;
                                            anchors.left: parent.left; anchors.leftMargin: 15;
                                            Text{
                                                anchors.centerIn: parent;
                                                text:"单机类型";
                                                font.pixelSize: 13;
                                                color:"white";
                                            }
                                        }
                                        //GroupBox {

                                        RowLayout {
                                            id:input5;
                                            //anchors.right: parent.right; anchors.rightMargin: 8;
                                            anchors.left:inputPhyType.right; anchors.leftMargin: 13;
                                            anchors.verticalCenter: inputPhyType.verticalCenter;
                                            width: 135; height: 24;
                                            ExclusiveGroup { id: tabPositionGroup01 }
                                            RadioButton {
                                                id:radioButton11;
                                                checked: true;
                                                //text:"指挥";
                                                text: qsTr("指挥")
                                                style: RadioButtonStyle{
                                                        label: Text{
                                                        text: control.text
                                                        font.pixelSize: 13
                                                        font.family: "DejaVu Sans"
                                                        anchors.margins: 0
                                                        horizontalAlignment: Text.left
                                                    }
                                                indicator: Rectangle{
                                                    implicitWidth: 14
                                                    implicitHeight: 14
                                                    radius: 9
                                                    border.color: control.activeFocus ? "darkblue" : "gray"
                                                    border.width: 1

                                                    Rectangle {
                                                        anchors.fill: parent
                                                        visible: control.checked
                                                        color: "#555"
                                                        radius: 9
                                                        anchors.margins: 4
                                                    }
                                                }
                                            }
                                                exclusiveGroup: tabPositionGroup01
                                            }
                                            RadioButton {
                                                id:radioButton22;
                                                //anchors.left: radioButton11.right; anchors.leftMargin: 23;
                                                //anchors.left: radioButton02.left;
                                                //text:"扬声";
                                                text: qsTr("扬声")
                                                style: RadioButtonStyle{
                                                        label: Text{
                                                        text: control.text
                                                        font.pixelSize: 13
                                                        font.family: "DejaVu Sans"
                                                        anchors.margins: 0
                                                        horizontalAlignment: Text.left
                                                    }
                                                indicator: Rectangle{
                                                    implicitWidth: 14
                                                    implicitHeight: 14
                                                    radius: 9
                                                    border.color: control.activeFocus ? "darkblue" : "gray"
                                                    border.width: 1

                                                    Rectangle {
                                                        anchors.fill: parent
                                                        visible: control.checked
                                                        color: "#555"
                                                        radius: 9
                                                        anchors.margins: 4
                                                    }
                                                }
                                            }
                                                exclusiveGroup: tabPositionGroup01
                                            }
                                        }
                                    }
                                }

                                Row{
                                    id: butArea;
                                    anchors.top: userInformation.bottom; anchors.topMargin: 20;
                                    //anchors.bottom: rect26.top; //anchors.bottomMargin: parent.height/10;
                                    //anchors.bottomMargin: 0;
                                    //z:10;
                                    //anchors.top: userInformation.bottom; anchors.topMargin: 30;
                                    anchors.left: parent.left; anchors.leftMargin: 20;
                                    width: parent.width; height: 40;
                                    spacing: 18;
                                    Image{
                                        id: addUserBut;
                                        //anchors.left: parent.left; anchors.leftMargin: 20;
                                        width:50; height: 26;
                                        source: "../images/tj.png";
                                        fillMode: Image.PreserveAspectFit;
                                        Text{
                                            anchors.centerIn: parent;
                                            text:"添加";
                                            font.pixelSize: 15;
                                            color:"white";
                                        }

                                        MouseArea{
                                            anchors.fill: parent;
                                            hoverEnabled: true;
                                            onEntered: addUserBut.source = "../images/tj02.png";
                                            onExited: addUserBut.source = "../images/tj.png";
                                            onClicked: {
                                                if(input1.text == "" || input3.text == "")
                                                {
                                                    messageDialog("添加用户失败：用户信息不能为空!", 4);
                                                }
                                                else{
                                                    var strings;
                                                    if(choiceSipFlag == false && choiceVirFlag == false && choicePhyFlag == false && choiceConFlag == false)
                                                    {
                                                        strings = checkUserName(input1.text);
                                                        if(strings == true)
                                                            addUsers(input1.text, input2.text, input3.text, null);
                                                        else
                                                            messageDialog("增加用户失败：用户名"+ input1.text +"重复!", 4);
                                                    }
                                                    else if(choiceSipFlag == true)
                                                    {
                                                        strings = checkUserName(input1.text);
                                                        if(strings == true)
                                                            addUsers(input1.text, input2.text, input3.text, null);
                                                        else
                                                            messageDialog("增加用户失败：用户名"+ input1.text +"重复!", 4);
                                                    }

                                                    else if(choiceVirFlag == true)
                                                    {
//                                                        strings = checkUserName(input1.text);
//                                                        if(strings == true)
//                                                        {
                                                            if(checkVirUserName(input1.text))
                                                                addVirUsers(input1.text, input2.text, input3.text);
                                                            else
                                                                messageDialog("增加用户失败：用户名"+ input1.text +"错误[1002-9999]!", 4);
//                                                        }else
//                                                            messageDialog("增加用户失败：用户名"+ input1.text +"重复!", 4);
                                                    }

                                                    else if(choicePhyFlag == true)
                                                    {
                                                        var audio, type;
                                                        if(radioButton01.checked == true)
                                                            audio = 5;
                                                        else
                                                            audio = 7;
                                                        if(radioButton11.checked == true)
                                                            type = 0;
                                                        else
                                                            type = 1;
                                                        strings = checkUserName(input1.text);
                                                        if(strings == true)
                                                            addPhyUsers(type, audio, input1.text, input3.text);
                                                        else
                                                            messageDialog("增加用户失败：用户名"+ input1.text +"重复!", 4);
                                                        //                                            }
                                                    }

                                                    else if(choiceConFlag == true)
                                                    {
//                                                        strings = checkUserName(input1.text);
//                                                        if(strings == true)
                                                            addConUsers(input1.text,input2.text,input3.text);
/*                                                        else
                                                            messageDialog("增加用户失败：用户名"+ input1.text +"重复!", 4)*/;
                                                    }

                                                }

                                            }
                                        }
                                    }

                                    Image{
                                        id: modifhButton;
                                        //anchors.left: parent.left; anchors.leftMargin: 20;
                                        width:50; height: 26;
                                        source: "../images/butttn_x01.png";
                                        fillMode: Image.PreserveAspectFit;
                                        Text{
                                            anchors.centerIn: parent;
                                            text:"修改";
                                            font.pixelSize: 15;
                                            color:"white";
                                        }

                                        MouseArea{
                                            anchors.fill: parent;
                                            hoverEnabled: true;
                                            onEntered: modifhButton.source = "../images/buttn_x02.png";
                                            onExited: modifhButton.source = "../images/butttn_x01.png";
                                            onClicked: {
                                                if(input1.text == "" || input3.text == ""){
                                                    messageDialog("修改用户失败：用户信息不能为空!", 4);
                                                }
                                                else{
                                                    console.log("modify entered!");
                                                    var data = availableUserModel.get(avaiableUserView.currentIndex);
                                                    if(choiceSipFlag == false && choiceVirFlag == false && choicePhyFlag == false && choiceConFlag == false)
                                                        modifyUserInfo(input1.text, input2.text, input3.text, null, data.id);
                                                    else if(choiceSipFlag == true)
                                                        modifyUserInfo(input1.text, input2.text, input3.text, null, data.id);
                                                    else if(choiceVirFlag == true)
                                                        modifyVirUserInfo(input1.text, input2.text, input3.text, data.id);
                                                    else if(choicePhyFlag == true){
                                                        console.log("hello++++++++++++++++ Phy called!");
                                                        var audio, type;
                                                        if(radioButton01.checked == true)
                                                            audio = 5;
                                                        else
                                                            audio = 7;
                                                        if(radioButton11.checked == true)
                                                            type = 0;
                                                        else
                                                            type = 1;
                                                        modifyPhyUserInfo(type, audio, input1.text, input3.text, data.id);
                                                    }
                                                    else if(choiceConFlag == true)
                                                        modifyConUserInfo(input1.text, input2.text, input3.text, data.id);
                                                    input1.text = "";
                                                    input2.text = "";
                                                    input3.text = "";
                                                    //input4.text = "";
                                                }

                                            }
                                        }
                                    }
                                    Image{
                                        id: delUserBut;
                                        //anchors.left: parent.left; anchors.leftMargin: 20;
                                        width:50; height: 26;
                                        source: "../images/buttn_s01.png";
                                        fillMode: Image.PreserveAspectFit;
                                        Text{
                                            anchors.centerIn: parent;
                                            text:"删除";
                                            font.pixelSize: 15;
                                            color:"white";
                                        }

                                        MouseArea{
                                            anchors.fill: parent;
                                            hoverEnabled: true;
                                            onEntered: delUserBut.source = "../images/buttn_s02.png";
                                            onExited: delUserBut.source = "../images/buttn_s01.png";
                                            onClicked: {
                                                if(menuListView.currentIndex == 1)
                                                    messageDialog("确定删除用户: " + (availableUserModel.get(avaiableUserView.currentIndex).realName) + " ?", 2);
                                                else{
                                                    console.log("DONE nothing!");
                                                }
                                            }
                                        }
                                    }

                                }

                            }//rect end;

                        } //ScrollView end;
                    }

                    Rectangle{
                        id: rect26;
                        anchors.bottom: parent.bottom; anchors.bottomMargin: 0;
                        anchors.left: parent.left; anchors.leftMargin: 2;
                        width: parent.width-4;
                        height: 28;
                        radius:5;
                        color:"white";
                        Text{
                            id: textShow;
                            anchors.centerIn: parent;
                            text:"群可用用户["+ availableUserModel.count+"]";
                            color: "#00394f";
                        }
                    }

                }




                Rectangle {
                    id: column4;
                    //color: "#123868"
                    color:"#bbc5cc";
                    anchors.left: column3.right;
                    width: parent.width;
                    height: parent.height;
                    //radius: 18;
                    ListModel{
                        id:allUsersModel;
                    }

                    ListModel{
                        id:availableUserModel;
                        /*
                        ListElement { name: "平台"; }
                        ListElement { name: "安卓董董"; }
                        ListElement { name: "测试组"; }
                        ListElement { name: "嵌入式"; }
                        ListElement { name: "平台组"; }
                        ListElement { name: "安卓董"; }
                        ListElement { name: "测试组"; }
                        ListElement { name: "嵌入式"; }
                        ListElement { name: "平台组"; }
                        ListElement { name: "安卓董"; }
                        ListElement { name: "测试组"; }
                        ListElement { name: "安卓董"; }
                        ListElement { name: "测试组"; }
                        ListElement { name: "嵌入式"; }
                        ListElement { name: "平台组"; }
                        ListElement { name: "安卓董"; }
                        ListElement { name: "测试组"; }*/
                    }

                    Rectangle{
                        anchors.top: rect25.bottom;
                        width: parent.width;
                        anchors.bottom: parent.bottom; anchors.bottomMargin: 7;
                        //height: parent.height -50;
                        color:"#a7b3bc"
                        radius:10;
                        //}

                        ScrollView{
                            anchors.fill: parent;
                            //width: parent.width;
                            //height: parent.height -50;

                            style:ScrollViewStyle{
                                handle: Item{
                                    implicitHeight: 25;
                                    implicitWidth: 12;
                                    Rectangle{
                                        color:"#315980";
                                        anchors.fill: parent;
                                        visible: true;
                                    }

                                }
                                decrementControl: Image{
                                    width: 12; height: 12;
                                    source: "../images/arrow_up02.png";
                                }
                                incrementControl: Image{
                                    width: 12; height: 12;
                                    source: "../images/arrow_down01.png";
                                }
                                scrollBarBackground: Item{
                                    implicitHeight: 25;
                                    implicitWidth: 16;
                                }

                            }

                            GridView{
                                property int drag1ItemIndex: -1;
                                //id: view;
                                //anchors.left: parent.left; anchors.leftMargin: 10;
                                anchors.fill: parent;
                                id: avaiableUserView;
                                cellHeight: 95;
                                cellWidth: 100;
                                model: availableUserModel;
                                delegate: flagDelegateChoice == 0 ? avaiableUserDelegate : allUserViewDelegate;
                                //delegate: allUserViewDelegate;

                                highlight: Image {
                                    visible: flagDelegateChoice == 1;
                                    z:10;
                                    //opacity: 0.3;
                                    width: 72; height: 72;
                                    //border.color: "blue"; border.width: 5;
                                    //color: "lightgreen";
                                    //radius: 5
                                    source: "../images/dq.png";
                                    x: avaiableUserView.currentItem.x
                                    y: avaiableUserView.currentItem.y
                                    Behavior on x { SpringAnimation { spring: 3; damping: 0.2 } }
                                    Behavior on y { SpringAnimation { spring: 3; damping: 0.2 } }
                                }
                                anchors.margins: 20;
                                highlightFollowsCurrentItem: false
                                focus: true

                                onCurrentIndexChanged: {
                                    //textDialog.text = "";
                                }

                            }
                        }
                    }

                    Component{
                        id: allUserViewDelegate;
                        Item{
                            id: wrapper5;
                            Image{
                                id: rect;
                                width: 72; height: 72;
                                source: "../images/aviUserBac.png";
                                fillMode: Image.PreserveAspectFit;

                                Image {
                                    //id: pic7;
                                    source:"../images/aviUserPer.png";
                                    anchors.top:parent.top; anchors.topMargin: 4;
                                    //anchors.left: parent.left; anchors.leftMargin: 5;
                                    anchors.horizontalCenter: parent.horizontalCenter;
                                    fillMode: Image.PreserveAspectFit;
                                }

                                Text {
                                    text: realName ;
                                    //text:domain;
                                    anchors.bottom: parent.bottom; anchors.bottomMargin: 1;
                                    //anchors.left: parent.left; anchors.leftMargin: 7;
                                    //anchors.horizontalCenter: parent.horizontalCenter;
                                    // anchors.centerIn: parent;
                                    //anchors.verticalCenter: parent.verticalCenter;
                                    horizontalAlignment : Text.AlignHCenter;
                                    font.pixelSize: 14;
                                    width: parent.width;
                                    height: 20;
                                    color:"white";
                                    elide:Text.ElideRight;

                                    ToolTip{
                                        space: 0;
                                        toolTip: parent.text;
                                    }
                                }
                                Text{
                                    anchors.bottom: parent.bottom; anchors.bottomMargin: -20;
                                    anchors.horizontalCenter: parent.horizontalCenter;
                                    //text:fromId;
                                    text: fromId === "OFFLINE" ? "离线" : fromId === "AVAILABLE" ? "可用" : fromId === "ON_THE_PHONE" ? "通话中" :
                                                                                                                                    fromId === "AWAY" ? "离开" : fromId === "BUSY" ? "忙" : "不可用";
                                    color:"black"; font.pixelSize: 13;

                                }
                                MouseArea{
                                    anchors.fill:  parent;
                                    onClicked: {
                                        wrapper5.GridView.view.currentIndex = index;
                                        console.log("0000 " + index);
                                        var data = availableUserModel.get(avaiableUserView.currentIndex);
                                        input1.text = data.username;
                                        if(choiceSipFlag == false && choiceVirFlag == false && choicePhyFlag == false && choiceConFlag == false)
                                            input2.text = data.password;
                                        else if(choiceSipFlag == true)
                                            input2.text = data.password;
                                        else if(choiceVirFlag == true)
                                            input2.text = data.serverIp;
                                        else if(choicePhyFlag == true)
                                            input2.text = data.type;
                                        else if(choiceConFlag == true)
                                            input2.text = data.domain;

                                        input3.text = data.realName;

                                        if(choicePhyFlag == true)
                                        {
                                            if(data.audioAlgo == 5)
                                                radioButton01.checked = true;
                                            else
                                                radioButton02.checked = true;
                                        }

                                        //input4.text = data.audioAlgo;
                                        //input4.text = data.email;

                                    }
                                }
                            }
                        }
                    }

                    Component{
                        id:avaiableUserDelegate;
                        Item{
                            id: wrapper3;
                            Image{
                                id: rect;
                                width: 72; height: 72;
                                source: "../images/aviUserBac.png";
                                fillMode: Image.PreserveAspectFit;
                                Image {
                                    id: pic7;
                                    source:"../images/aviUserPer.png";
                                    anchors.top:parent.top; anchors.topMargin: 4;
                                    //anchors.left: parent.left; anchors.leftMargin: 5;
                                    anchors.horizontalCenter: parent.horizontalCenter;
                                    fillMode: Image.PreserveAspectFit;
                                }

                                Text {
                                    text:realName;
                                    anchors.bottom: parent.bottom; anchors.bottomMargin: 1;
                                    horizontalAlignment : Text.AlignHCenter;
                                    font.pixelSize: 14;
                                    width: parent.width;
                                    height: 20;
                                    color:"white";
                                    elide:Text.ElideRight;

                                    ToolTip{
                                        space: 0;
                                        toolTip: parent.text;
                                    }
                                }
                                Text{
                                    id:partOne;
                                    visible: false;
                                    anchors.bottom: parent.bottom; anchors.bottomMargin: -20;
                                    anchors.horizontalCenter: parent.horizontalCenter;
                                    text: fromId == 2 ? "虚拟单机" : fromId == 3 ? "物理单机" : fromId == 1 ? "联系人" : "Sip";
                                    color:"black"; font.pixelSize: 13;

                                }
                                Text{
                                    //id:partOne;
                                    anchors.bottom: parent.bottom; anchors.bottomMargin: -20;
                                    anchors.horizontalCenter: parent.horizontalCenter;
                                    text: lopp === "OFFLINE" ? partOne.text +"-离线" : lopp === "AVAILABLE" ? partOne.text +"-可用" : lopp === "ON_THE_PHONE" ? partOne.text +"-通话中" :
                                                                                                                                                            lopp === "AWAY" ? partOne.text +"-离开" : lopp === "BUSY" ? partOne.text +"-忙" : partOne.text +"-不可用";
                                    color:"black"; font.pixelSize: 13;

                                }


                                MouseArea{
                                    id: mouseArea1;
                                    anchors.fill: parent;
                                    drag.target: rect;
                                    drag.onActiveChanged: {
                                        if (mouseArea1.drag.active) {
                                            avaiableUserView.drag1ItemIndex = index;
                                        }
                                        flagDropCtrl = 2;
                                        rect.Drag.drop();
                                    }

                                }
                                states: [
                                    State {
                                        when: rect.Drag.active
                                        ParentChange {
                                            target: rect
                                            parent: root
                                        }

                                        AnchorChanges {
                                            target: rect
                                            anchors.horizontalCenter: undefined
                                            anchors.verticalCenter: undefined
                                        }
                                    }
                                ]

                                Drag.active: mouseArea1.drag.active
                                Drag.hotSpot.x: rect.width/3
                                Drag.hotSpot.y: rect.height/3

                            }
                        }
                    }


                    Rectangle{
                        id: rect25;
                        anchors.top: parent.top; anchors.topMargin: 1;
                        anchors.left: parent.left;// anchors.leftMargin: 0;
                        //anchors.right: parent.right;//anchors.rightMargin: 2;
                        width: parent.width -2;
                        height: 38;
                        //color:"#123868";
                        color:"#7d8f9c";

                        radius: 6;
                        //border.color: "lightgray"; border.width: 2;
                        ListModel{
                            id: menuModel;
                            ListElement { name: "可用用户"; }
                            ListElement { name: "全部用户"; }
                        }
                        Component{
                            id: menuDelegate;
                            Item{
                                id: wrapper4;
                                width: parent.width/2;
                                height: 38;

                                Rectangle{
                                    anchors.fill: parent;
                                    //color: "#216297";
                                    color:"#7d8f9c";
                                    radius:8;
                                }

                                Text{
                                    anchors.horizontalCenter: parent.horizontalCenter;
                                    anchors.verticalCenter: parent.verticalCenter;
                                    text:name;
                                    color:"white";
                                    font.pixelSize: 18;

                                }
                                MouseArea{
                                    anchors.fill: parent;
                                    onClicked: {
                                        wrapper4.GridView.view.currentIndex = index;
                                        if(index ==1)//all user choice
                                        {
                                            //rect29.visible = true;
                                            flagDelegateChoice = 1;// choose allUserViewDelegate for GridView ;
                                            if(choiceSipFlag == false && choiceVirFlag == false && choicePhyFlag == false && choiceConFlag == false){
                                                //availableUserModel.clear();
                                                queryAllUser(true);
                                            }
                                            else if(choiceVirFlag == true)
                                                queryVirAllUser(true);
                                            else if(choicePhyFlag == true)
                                                queryPhyAllUser(true);
                                            else if(choiceSipFlag == true)
                                                queryAllUser(true);
                                            else if(choiceConFlag == true)
                                                queryConUser(true);

                                        }
                                        else
                                        {
                                            //rect29.visible = false;
                                            //delUserDialog.visible = false; // del user's dialogo rectangle;
                                            flagDelegateChoice = 0; //choice different Delegate;
                                            //console.log("currentIndex " + groupUserView.currentIndex);
                                            queryGroupUser((groupUserView.model.get(groupUserView.currentIndex).id));
                                            //textShow.text = "可用用户[" + availableUserModel.count +"]";
                                        }
                                    }
                                }
                            }
                        }
                        GridView{
                            id: menuListView;
                            cellHeight: 38;
                            cellWidth:parent.width/2;
                            anchors.fill: parent;
                            model: menuModel;
                            delegate:menuDelegate;

                            //orientation: ListView.Horizontal;
                            highlight: Rectangle{
                                z:10;
                                width: GridView.view.width ;
                                height: GridView.view.height;
                                border.color: "black";
                                border.width: 2;
                                //color:"#00394f";
                                radius: 8;
                                x: menuListView.currentItem.x
                                y: menuListView.currentItem.y
                                Behavior on x { SpringAnimation { spring: 3; damping: 0.2 } }
                                Behavior on y { SpringAnimation { spring: 3; damping: 0.2 } }


                                Image{
                                    id: menuLeft;
                                    anchors.left: parent.left;
                                    width: 10; height: parent.height;
                                    //source: "../images/kyyh_left.png";
                                    source:"../images/list02_left.png";
                                    //fillMode: Image.PreserveAspectFit;
                                }

                                Image{
                                    anchors.left:menuLeft.right; //anchors.right: menuRight.right;
                                    width: parent.width -18; height: parent.height;
                                    //source:"../images/kyyh_mid.png";
                                    source:"../images/list02_mid.png";
                                    //fillMode: Image.PreserveAspectCrop;
                                }
                                Image{
                                    anchors.right: parent.right; //anchors.rightMargin: 8;
                                    height: parent.height; width: 10;
                                    //source: "../images/kyyh_rihgt.png";
                                    source:"../images/list02_right.png";
                                    //fillMode: Image.PreserveAspectFit;
                                }

                                Text{
                                    anchors.centerIn: parent;
                                    text:menuModel.get(menuListView.currentIndex).name;
                                    font.pixelSize: 20;
                                    color:"white";
                                }
                            }

                            onCurrentIndexChanged: {
                                input1.text = "";
                                input2.text = "";
                                input3.text = "";
                                //input4.text = "";
                            }
                        }



                    }
                    DropArea{
                        id: dropArea;
                        anchors.fill: parent;
                        onDropped: {
                            console.log("hello22222222222222  "  + attendeesListView.dragItemIndex);
                            if(attendeesListView.dragItemIndex !== -1 && flagDropCtrl == 1 ){
                                var data = attendeesListView.model.get(attendeesListView.dragItemIndex);
                                console.log("data.receiver : " + data.receiver);
                                if(data.role == 1)
                                    flagRootUserChoose = 0;
                                //availableUserModel.append(data);
                                var dat = groupUserModel.get(groupUserView.currentIndex).id;
                                addUsertoGroup(dat, data, 0);
                                if(data.receiver == 1)
                                {
                                    receiverCount--;
                                    if(receiverCount == 0)
                                        receiverCount = 0;
                                }
                                if(data.micGranted == 1)
                                {
                                    micGrantedCount--;
                                    if(micGrantedCount == 0)
                                        micGrantedCount = 0;
                                }
                                if(data.mode == 1)
                                {
                                    modeCount--;
                                    if(modeCount == 0)
                                        modeCount = 0;
                                }
                                if(data.specialIntercom == 1)
                                {
                                    specialIntercomCount--;
                                    if(specialIntercomCount == 0)
                                        specialIntercomCount = 0;
                                }
                                //queryGroupUser(dat);
                                attendeesListView.model.remove(attendeesListView.dragItemIndex);
                                //queryAddedGroup(dat);
                                attendeesListView.dragItemIndex = -1;
                                flagDropCtrl = 0;
                            }
                            else if (flagDropCtrl == 2){
                                //console.log("HHH" + attendeesListView.dragItemIndex)
                                //var da2 = avaiableUserView.drag1ItemIndex;
                                //var da = availableUserModel.get(avaiableUserView.drag1ItemIndex);
                                //var da1 = avaiableUserView.drag1ItemIndex ;
                                //queryGroupUser()
                                queryGroupUser(groupUserModel.get(groupUserView.currentIndex).id);
                                //availableUserModel.insert(da2, da);
                                //availableUserModel.append(da);
                                //availableUserModel.remove(avaiableUserView.drag1ItemIndex);
                                flagDropCtrl = 0;
                            }
                        }
                    }


                }
            }
        }
    }

    Image {
        id: rect3;
        anchors.top: rect2.bottom;
        anchors.topMargin: 0;
        height: 30;
        width: parent.width ;
        //fillMode: Image.PreserveAspectCrop
        source:"../images/top.png"
        //clip: true
        //color: "#195586";
        Text{
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter: parent.verticalCenter;
            text:"北京北清视通信息技术有限公司";
            font.family: "楷体";
            font.pixelSize: 18;
            color: "white";
        }
    }

}
