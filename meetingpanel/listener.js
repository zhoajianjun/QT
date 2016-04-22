
var phoneStateColor = {
    "UNKNOWN": "#101010",
    "CONNECTED": "green",
    "CONNECTING": "yellow",
    "RINGING":  "lightgreen",
    "DISCONNECTING": "yellow",
    "DISCONNECTED": "grey",
}

function phoneColor(state)
{
    return phoneStateColor[state];
}

var chinesePhoneState = {
    "UNKNOWN": "未知",
    "CONNECTED": "已连接",
    "CONNECTING": "连接中",
    "RINGING":  "等待接通",
    "DISCONNECTING": "断开中",
    "DISCONNECTED": "已断开",
}


function getChinesePhoneState(state)
{
    return chinesePhoneState[state];
}

/*var phoneStateImages = {
    "UNKNOWN": "../images/user.svg",
    "CONNECTED": "../images/user_connected.svg",
    "CONNECTING": "../images/user_connecting.svg",
    "RINGING":  "../images/user_connecting.svg",
    "DISCONNECTING": "../images/user.svg",
    "DISCONNECTED": "../images/user.svg",
}*/
var phoneStateImages = {
    "UNKNOWN": "../images/offline.png",
    "CONNECTED": "../images/online.png",
    "CONNECTING": "../images/link.png",
    "RINGING":  "../images/link.png",
    "DISCONNECTING": "../images/offline.png",
    "DISCONNECTED": "../images/offline.png",
}

function getPhoneStateImage(state)
{
    return phoneStateImages[state];
}

var chineseOnlineState = {
    "OFFLINE": "离线",
    "AVAILABLE": "可用",
    "ON_THE_PHONE": "通话中",
    "AWAY": "离开",
    "BUSY": "忙",
    "UNAVAILABLE":  "不可用"
}

function getChineseOnlineState(state)
{
    return chineseOnlineState[state];
}

var userCustomConfig = {}

//.maintitle
//

function initializeUserCustomConfig(txt)
{
    //userConfig.
    userCustomConfig = JSON.parse(txt);
}

function getUserCustomConfig()
{
    return userCustomConfig;
}


function forceGC()
{
    gc();
}


/**
 *handlers = { onTimeout(), onRequestSuccess(req), onRequestError()}
 *
 */

function query(target, path, handlers)
{
    var req = new XMLHttpRequest();

    handlers.tick = function (){
        handlers.timeout--;
        return handlers.timeout <= 0;
    }

    var checkTimeout = function(){
        if (handlers.tick())
        {
            req.abort();
            handlers.onTimeout();
            disconnectTimer(handlers)
        }
    }

    setTimeout(handlers, checkTimeout);

    var url = "http://" + target.addr + "/" + path;
    console.log("query:", url, target.username, target.password)

    req.open("GET", url, true, target.username, target.password);
    if (target.logtime)
    {
        req.setRequestHeader("x-client-id", target.logtime);
    }

    req.onreadystatechange = function() {

        if (req.readyState === XMLHttpRequest.DONE && req.status == 200) {
            disconnectTimer(handlers)
            if (req.status == 200)
            {
                //console.log("respText:", req.responseText);
                var resp = JSON.parse(xjconvertor.convert(req.responseText))
                //console.log("response json:", serialize(obj, 5));
                handlers.onRequestSuccess(resp)
            }
            else {
                handlers.onRequestError(req)
            }
        }
    }

    req.send();
}


function disconnectTimer(handlers)
{
    try {
        timer.triggered.disconnect(handlers.checkTimeout);
    }
    catch(e)
    {
        //console.log("disconnectTimer err:", e);
    }
}

function post(target, path, xml, handlers)
{
    if (xml){
        var body = "<?xml version=\"1.0\" encoding=\"utf-8\"?>" + xml;
        return pushRequest(target, "POST", path, body, handlers);
    }
    else {
        return pushRequest(target, "POST", path, null, handlers);
    }
}

function post2(target, path, xml, handlers)
{
    var body = "<?xml version=\"1.0\" encoding=\"utf-8\"?>" + xml;
    var req = new XMLHttpRequest();

    handlers.tick = function (){
        handlers.timeout--;
        return handlers.timeout <= 0;
    }

    var checkTimeout = function(){
        if (handlers.tick())
        {
            req.abort();
            handlers.onTimeout();
            disconnectTimer(handlers)
        }
    }

    setTimeout(handlers, checkTimeout);

    var url = "http://" + target.addr + "/" + path;
    console.log("post:", url, target.username, target.password)

    req.open("POST", url, true, target.username, target.password);
    req.setRequestHeader("Content-Type", "application/xml");
    req.setRequestHeader("Content-length", body.length)
    if (target.logtime)
    {
        req.setRequestHeader("x-client-id", target.logtime);
    }

    req.onreadystatechange = function() {
        if (req.readyState === XMLHttpRequest.DONE && req.status == 200) {
            disconnectTimer(handlers)
            if (req.status == 200)
            {
                var resp = JSON.parse(xjconvertor.convert(req.responseText))
                handlers.onRequestSuccess(resp)
            }
            else {
                handlers.onRequestError(req)
            }
        }
    }

    req.send(body);
}

function setTimeout(handlers, checkTimeout)
{
    handlers.timeout = 7;
    handlers.checkTimeout = checkTimeout;
    timer.triggered.connect(handlers.checkTimeout);
}

var singleRequest = null;

var waitRequests = [];
var MAX_REQUESTS = 1;
var processingRequest = null;

function pushRequest(target, method, path, body, handlers)
{
    if (waitRequests.length > MAX_REQUESTS)
    {
        console.log("pending post overflow!")
        return false;
    }

    var req = {};
    req.target = target;
    req.method = method;
    req.path = path;
    req.body = body;
    req.handlers = handlers;
    waitRequests.push(req);

    if (processingRequest == null)
    {
        sendNextRequest();
    }

    return true;
}

function sendNextRequest()
{
    if (waitRequests.length > 0 && processingRequest == null)
    {
        processingRequest = waitRequests.pop();
        doSendRequest(processingRequest);
    }
}

function doSendRequest(request)
{
    var handlers = request.handlers;
    var req = new XMLHttpRequest();
    var target = request.target;
    var body = request.body;
    var method = request.method;

    handlers.tick = function (){
        handlers.timeout--;
        return handlers.timeout <= 0;
    }

    var checkTimeout = function(){
        if (handlers.tick())
        {
            req.abort();
            handlers.onTimeout();
            disconnectTimer(handlers);
            processingRequest = null;
            sendNextRequest();
        }
    }

    setTimeout(handlers, checkTimeout);

    var url = "http://" + target.addr + "/" + request.path;
    console.log(method, url, target.username, target.password)

    req.open(method, url, true, target.username, target.password);
    if (body)
    {
        req.setRequestHeader("Content-Type", "application/xml");
        req.setRequestHeader("Content-length", body.length)
    }

    if (target.logtime)
    {
        req.setRequestHeader("x-client-id", target.logtime);
    }

    req.onreadystatechange = function() {
        if (req.readyState === XMLHttpRequest.DONE && req.status == 200) {
            disconnectTimer(handlers)
            processingRequest = null;
            sendNextRequest();
            if (req.status == 200)
            {
                var resp = JSON.parse(xjconvertor.convert(req.responseText))
                handlers.onRequestSuccess(resp)
            }
            else {
                handlers.onRequestError(req)
            }
        }
    }

    req.send(body);
}

function continuousQuery(target, path, handlers)
{
    if (!singleRequest)
    {
        singleRequest = new XMLHttpRequest();

        handlers.tick = function (){
            handlers.timeout--;
            return handlers.timeout <= 0;
        }

        var checkTimeout = function(){
            if (handlers.tick())
            {
                singleRequest.abort();
                handlers.onTimeout();
                singleRequest = null;
                disconnectTimer(handlers)
                if (handlers.isWorkRunning())
                {
                    continuousQuery(target, path, handlers)
                }
            }
        }

        setTimeout(handlers, checkTimeout)

        var url = "http://" + target.addr + "/" + path;
        //console.log("continuousQuery:", url, target.username, target.password)

        singleRequest.open("GET",url, true, target.username, target.password);
        singleRequest.setRequestHeader("x-client-id", target.logtime);

        singleRequest.onreadystatechange = function() {

            //console.log("onreadystate:", singleRequest.readyState, singleRequest.status);

            if (singleRequest.readyState === XMLHttpRequest.DONE && singleRequest.status == 200) {
                disconnectTimer(handlers)
                if (singleRequest.status == 200)
                {
                    //console.log("respText:", req.responseText);
                    //console.log("response json:", serialize(obj, 5));
                    try
                    {
                        var resp = JSON.parse(xjconvertor.convert(singleRequest.responseText))
                        handlers.onRequestSuccess(resp)
                    }
                    catch (e)
                    {
                        console.log("handle resp error", e);
                    }
                    finally {
                        singleRequest = null;
                    }
                }
                else {
                    try
                    {
                        handlers.onRequestError(singleRequest);
                    }
                    catch (e)
                    {
                        console.log("request error", e);
                    }
                    finally
                    {
                        singleRequest = null;
                    }
                }
                if (handlers.isWorkRunning())
                {
                    continuousQuery(target, path, handlers)
                }
            }
        }

        singleRequest.send();
    }
}

function startListen(target, handlers) {

    continuousQuery(target, "sync", handlers)
}

function getElementsByTagName(rootElement, tagName, elements) {
    var childNodes = rootElement.childNodes;
    for(var i = 0; i < childNodes.length; i++) {
        if(childNodes[i].nodeName === tagName) {
            elements.push(childNodes[i]);
            //console.log("find tagName " + tagName);
        }
        else {
            getElementsByTagName(childNodes[i], tagName, elements)
        }
    }
}

function getDirectElementsByTagName(rootElement, tagName, elements) {
    //if (!rootElement.childNodes)
    //{
    //    console.log("root:" + rootElement.nodeName + "tagname:", tagName);
    //}

    var childNodes = rootElement.childNodes;
    for(var i = 0; i < childNodes.length; i++) {
        if(childNodes[i].nodeName === tagName) {
            elements.push(childNodes[i]);
        }
    }
}

function findFirstChildByTagName(rootElement, tagName) {
    if(rootElement)
    {
        var childNodes = rootElement.childNodes;
        for(var i = 0; i < childNodes.length; i++) {
            if(childNodes[i].nodeName === tagName) {
                return childNodes[i];
            }
        }
    }
    return null;
}


function parseXmlToJson(whereNode)
{
    var where = {};
    if(whereNode)
    {
        var childNodes = whereNode.childNodes;
        for(var i = 0; i < childNodes.length; i++)
        {
            where[childNodes[i].nodeName] = childNodes[i].firstChild.nodeValue;
        }
    }
    return where;
}

function parseAttendeeJsonObject(o, objectNodes)
{
    if (o.length)
    {
        for (var i = 0; i < o.length; ++i)
        {
            var object = {};
            object.type = o[i].type;
            object.class = o[i].class;
            object.where = o[i].w;
            object.value = o[i].v;
            objectNodes.push(object);
        }
    }
    else
    {
        var obj = {};
        obj.type = o.type;
        obj.class = o.class;
        obj.where = o.w;
        obj.value = o.v;
        objectNodes.push(obj);
    }
}
function parseSystemNoticeJsonObject(n,objectNodes)
{
    if (n.length)
    {
        for (var i = 0; i < n.length; ++i)
        {
            var object = {};
            object.time = n[i].time;
            object.type = n[i].type;
            object.code = n[i].code;
            object.module = n[i].module;
            object.text=n[i].text;
            objectNodes.push(object);
        }
    }
    else
    {
        var obj = {};
        obj.time = n.time;
        obj.type = n.type;
        obj.code = n.code;
        obj.module = n.module;
        obj.text=n.text;
        objectNodes.push(obj);
    }
}

function parseVoiceJsonObject(r, objectNodes)
{
    if (r.length)
    {
        for (var i = 0; i < r.length; ++i)
        {
            var object = {};
            object.type = r[i].type;
            object.class = r[i].class;
            object.app = r[i].app;
            object.data = r[i].data;
            objectNodes.push(object);
        }
    }
    else
    {
        var obj = {};
        obj.type = r.type;
        obj.class = r.class;
        obj.app = r.app;
        obj.data = r.data;
        objectNodes.push(obj);
    }
}


function parseNoticeObject(objectNode)
{
    var object = {};
    if(objectNode)
    {
        object.type = findFirstChildByTagName(objectNode, "type").firstChild.nodeValue;
        object.class = findFirstChildByTagName(objectNode, "class").firstChild.nodeValue;

        var whereNode = findFirstChildByTagName(objectNode, "w");
        var valueNode = findFirstChildByTagName(objectNode, "v");

        object.where = parseXmlToJson(whereNode);
        object.value = parseXmlToJson(valueNode);
    }
    return object;
}
function parseVoiceNoticeObject(objectNode)
{
    var object={};
    if(objectNode)
    {
        object.app=findFirstChildByTagName(objectNode,"app").firstChild.nodeValue;
        object.data=findFirstChildByTagName(objectNode,"data").firstChild.nodeValue;
    }
    return object;
}

function updatePerson(att, notice)
{
    if (notice.value.onlineState)
        att.onlineStatus = notice.value.onlineState;
    if (notice.value.micGranted)
        att.speakable = notice.value.micGrandted;
    if (notice.value.receiver)
        att.listenable = notice.value.receiver;
    if (notice.value.callState)
        att.phoneStatus = notice.value.callState;
}
function updateAttendeePerson(att,notice)
{
    if (notice.value.micGranted)
        att.speakable = notice.value.micGranted;
    if (notice.value.receiver)
        att.listenable = notice.value.receiver;
    if(notice.value.role)
        att.role=notice.value.role
    if (notice.value.specialIntercom)
        att.specialIntercom = notice.value.specialIntercom;
}
function updateTransfer(att,notice)
{
     if (notice.where.accountId1&&notice.where.fromId1)
     {
         att.oppositeAccountId=""
         att.oppositeFromId=""
     }
     if(notice.where.accountId2&&notice.where.fromId2)
     {
         att.oppositeAccountId=""
         att.oppositeFromId=""
     }
}

function serialize(object, maxDepth) {
    function _processObject(object, maxDepth, level) {
        var output = new Array();
        var pad = "  "
        if (maxDepth == undefined) {
            maxDepth = -1
        }
        if (level == undefined) {
            level = 0
        }
        var padding = new Array(level + 1).join(pad)

        output.push((Array.isArray(object) ? "[" : "{"))
        var fields = new Array()
        for (var key in object) {
            var keyText = Array.isArray(object) ? "" : ("\"" + key + "\": ")
            if (typeof (object[key]) == "object" && key != "parent" && maxDepth != 0) {
                var res = _processObject(object[key], maxDepth > 0 ? maxDepth - 1 : -1, level + 1)
                fields.push(padding + pad + keyText + res)
            } else {
                fields.push(padding + pad + keyText + "\"" + object[key] + "\"")
            }
        }
        output.push(fields.join(",\n"))
        output.push(padding + (Array.isArray(object) ? "]" : "}"))

        return output.join("\n")
    }

    return _processObject(object, maxDepth)
}

function test_dump()
{
    var a = {id: 1,
        name: "time",
        w: {x: "10",
            y: "20"}}
    var output = serialize(a, 3);

    console.log("test dump:" + output);
}


function queryRooms(func_onGetRooms, post_handler)
{
    var handlers = {
        onTimeout: function (req){
            //showErrorMessage("网络超时，请重试......");
        },
        onRequestSuccess: function(resp) {

            var rooms = [];
            var roomnodes = [];
            if(parseInt(resp.result.overall)===0)
            {
                if (resp.result
                        && resp.result.detail
                        && resp.result.detail.conferences
                        && resp.result.detail.conferences.conference)
                {
                    var conf = resp.result.detail.conferences.conference;
                    if (conf.length)
                    {
                        for (var j = 0; j < conf.length; ++j)
                        {
                            var room = {};
                            room.groupId = conf[j].group;
                            room.status = conf[j].state;
                            room.mode = (conf[j].mode === "DISPATCHING") ? 1 : 0;
                            room.specialIntercom = (conf[j].specialIntercom === "on") ? 1 : 0;
                            rooms.push(room);
                        }
                    }
                    else
                    {
                        var roo = {};
                        roo.groupId = conf.group;
                        roo.status = conf.status;
                        roo.mode = (conf.mode === "DISPATCHING") ? 1 : 0;
                        roo.specialIntercom = (conf.specialIntercom === "on") ? 1 : 0;
                        rooms.push(roo);
                    }
                }
            }
            else
            {

            }


            console.log("rooms: " + rooms.length, serialize(rooms, 5));
//            for (var i = 0; i < roomnodes.length; i++)
//            {
//                console.log("create room :" + i +" total:"+ rooms.length)
//                var room = {};
//                var roomnode = roomnodes[i];
//                var node = findFirstChildByTagName(roomnode, "group");
//                if (node.firstChild)
//                    room.groupId = node.firstChild.nodeValue;

//                room.status = findFirstChildByTagName(roomnode, "state").firstChild.nodeValue;
//                var modestr = findFirstChildByTagName(roomnode, "mode").firstChild.nodeValue;
//                room.mode = (modestr === "DISPATCHING") ? 1 : 0;
//                modestr = findFirstChildByTagName(roomnode, "specialIntercom").firstChild.nodeValue;
//                room.specialIntercom = (modestr === "on") ? 1 : 0;
//                rooms.push(room);
//            }
            func_onGetRooms(rooms, post_handler);
            showErrorMessage("");
        },
        onRequestError: function (req){
            //showErrorMessage("网络连接异常，请重试......");
        },
    }
    query(work.target, "xnode/ws/conferences?opt=lr", handlers);
}

function queryGroups(func_onGetGroups, post_handler)
{
    var path = "xnode/ws/groups/command?arg=browse id,realName"

    var handlers = {
        onTimeout: function (req){},
        onRequestSuccess: function(resp) {

            if (resp.result
                    && resp.result.detail
                    && resp.result.detail.command)
            {
                var content = resp.result.detail.command;
                var grps = [];
                if ((typeof content) === "string")
                {
                    console.log("content is " + content);
                    var records = content.split("\n");
                    for (var i = 0; i < records.length; ++i)
                    {
                        var l = records[i].split("|");
                        var g = {
                            groupId : l[0],
                            name : l[1]
                        }

                        grps.push(g);
                    }
                }

                func_onGetGroups(grps, post_handler);
            }
            showErrorMessage("");
        },
        onRequestError: function (req){ },
    }
    query(work.target, path, handlers);
}

var attendeeLocalFieldMap =
        {
    "receiver":"listenable",
    "micGranted":"speakable"
}

function getAttendeeLocalField(remote_field)
{
    return attendeeLocalFieldMap[remote_field];
}

var ChineseRoleName =
        {
    "0" : "未知",
    "1" : "指挥员",
    "2" : "越级用户",
    "3" : "广播员",
    "4" : "下级用户"
}
var ChineseRoleImage=
        {
    "0":"../images/user_unknow_off_image.png",
    "1":"../images/user_commander_off_image.png",
    "2":"../images/user_special_off_image.png",
    "3":"../images/user_broadcast_off_image.png",
    "4":"../images/user_normal_off_image.png"
}
var RoleImage={
    "0":"../images/user_unknow_image.png",
    "1":"../images/user_commander_image.png",
    "2":"../images/user_special_image.png",
    "3":"../images/user_broadcast_image.png",
    "4":"../images/user_normal_image.png"
}
function getRoleImage(role)
{
    return RoleImage[role];
}

function getChineseRoleImage(role)
{
    return ChineseRoleImage[role];
}

function getChineseRoleName(role)
{
    return ChineseRoleName[role];
}

var roleValueMap =
        {
    "UNKNOWN"   : "0",
    "COMMANDER" : "1",
    "SUPERIOR"  : "2",
    "ANNOUNCER" : "3",
    "SUBORDINATE" :"4",
}
var specialImage={
    "0":"../images/zhuanxiang.png",
    "1":"../images/zhuanxiang1.png"
}
function getspecialImage(specialIntercom){
    return specialImage[specialIntercom];
}

function getRoleValue(name)
{
    return roleValueMap[name];
}

function recordToAttendee(record)
{
    var fields = record.split('|');

    var attendee = {

        accountId : fields[0],
        tu_type : fields[1],
        realName : fields[2],
        speakable: fields[3],
        listenable: fields[4],
        phoneStatus: fields[5],
        onlineStatus: fields[6],
        fromId:     fields[7],
        userName:   fields[8],
        role:      fields[9],
        specialIntercom: fields[10],
        oppositeAccountId:fields[11],
        oppositeFromId:fields[12],
        selected: false,
        voiceLevelPerson: "0",
    };
    //console.log("attendee.realName:"+attendee.realName)
    return attendee;
}

function queryAttendees(grpId, func_onGetAttendees)
{
    console.log("queryAttendees() group is ", grpId)
    if (grpId)
    {
        var path = "xnode/ws/attendees/terminal_added_with_state?arg=" + grpId;
        var handlers = {
            onTimeout: function (req){},
            onRequestSuccess: function(resp) {

                if (resp.result
                        && resp.result.detail
                        && resp.result.detail.terminal_added_with_state)
                {
                    var content = resp.result.detail.terminal_added_with_state;
                    var attendees = [];

                    console.log("content is " + content);
                    if ((typeof content) === "string")
                    {

                        var records = content.split("\n");
                        for (var i = 0; i < records.length; ++i)
                        {
                            //console.log(records[i]);
                            attendees.push(recordToAttendee(records[i]));
                        }
                    }

                    func_onGetAttendees(grpId, attendees);
                }
            },
            onRequestError: function (req){},
        }
        query(work.target, path, handlers);
    }
}

function recordToTransfer(record)
{
    var fields = record.split('|');

    var transfer = {
        id:         fields[0],
        accountId1 : fields[1],
        fromId1 : fields[2],
        accountId2 : fields[3],
        fromId2: fields[4],
        interpose: fields[5],
    };
    return transfer;
}

function queryTransferTable(grpId, func_onGetTable)
{
    console.log("queryTransferTable() group is ", grpId)
    if (grpId)
    {
        var path = "xnode/ws/transfer/command?arg=browse id,accountId1,fromId1,accountId2,fromId2,interpose where groupId=" + grpId;
        var handlers = {
            onTimeout: function (req){showErrorMessage("网络超时，请重试......");},
            onRequestSuccess: function(resp) {

                var transfers = [];

                if (resp.result
                        && resp.result.detail
                        && resp.result.detail.command)
                {
                    var content = resp.result.detail.command;
                    if ((typeof content) === "string")
                    {
                        console.log("content is " + content);
                        var records = content.split("\n");
                        for (var i = 0; i < records.length; ++i)
                        {
                            console.log("content is " + content);
                            transfers.push(recordToTransfer(records[i]));
                        }
                    }
                }

                func_onGetTable(grpId, transfers);
                showErrorMessage("");

            },
            onRequestError: function (req){},
        }
        query(work.target, path, handlers);
    }
}


function transferEdit(grpId, transfer, path, func_onSuccess, func_onFailure)
{
    console.log("addTransfer() group is ", grpId)
    if (grpId)
    {
        var handlers = {
            onTimeout: function (req){ },
            onRequestSuccess: function(resp) {

                //console.log("resp:" + req.responseText);

                var result = -1;
                if (resp.result
                        && resp.result.overall)
                {
                    result = parseInt(resp.result.overall);
                }

                if (result == 0)
                {
                    //queryAttendees(grpId);
                    //reQueryAttendees();
                    if (func_onSuccess)
                        func_onSuccess(grpId, transfer);
                }
                else
                {
                    if (func_onFailure)
                        func_onFailure(grpId, transfer, "result is "+result);
                    console.log("transferEdit " + "failed,code:" + result);
                }
            },
            onRequestError: function (req){
                if (func_onFailure)
                    func_onFailure(grpId, transfer, "request error");
            },
        }
        query(work.target, path, handlers);
    }
}

function addTransfer(grpId, transfer, func_onSuccess, func_onFailure)
{
    console.log("addTransfer() group is ", grpId)
    var path = "xnode/ws/transfer/command?arg=add NULL," + grpId + ","
            + transfer.accountId1 + "," + transfer.fromId1 +","
            + transfer.accountId2 + "," + transfer.fromId2 +","
            + transfer.interpose;

    transferEdit(grpId, transfer, path, func_onSuccess, func_onFailure);
}

function deleteTransfer(grpId, tid, func_onSuccess, func_onFailure)
{
    console.log("addTransfer() group is ", grpId)
    var path = "xnode/ws/transfer/command?arg=delete where id='" + tid + "'";

    transferEdit(grpId, tid, path, func_onSuccess, func_onFailure);
}

function changeTransferInterpose(grpId, tid, bChecked, func_onSuccess, func_onFailure)
{
    console.log("changeTransferInterpose() group is ", grpId);
    var value = "0";
    if (bChecked)
        value = "1";

    var path = "xnode/ws/transfer/command?arg=change interpose='" + value + "' where id='" + tid + "'";

    transferEdit(grpId, tid, path, func_onSuccess, func_onFailure);
}
function queryLog(startTime,endTime,func_onGetLogList)
{
    var path = "xnode/ws/recording/logconf/command?arg=browse * where event="+"'会议开始'"+" and time >"+startTime+" and time <"+endTime;
    var handlers = {

        onTimeout: function (req){
        console.log("query log timeout")
        },
        onRequestSuccess: function(resp) {
            var result=-1;
            if (resp.result
                    && resp.result.overall)
            {
                result = parseInt(resp.result.overall);
            }

            if (result==0)
            {
                var logs=resp.result.detail.command
                var logtext=[];
                if ((typeof logs) === "string")
                {
                    var records = logs.split("\n");
                    for (var i = 0; i < records.length; ++i)
                    {
                        logtext.push(recordToLog(records[i]));
                    }
                }
            }
            func_onGetLogList(logtext)
        },
        onRequestError: function (req){},
    }
    query(work.target, path, handlers);

}
function recordToLog(record)
{
    var logtext = record.split('|');

    var log = {
        id:logtext[0],
        uuid:logtext[1],
        event:logtext[2],
        time:logtext[3],
        type:logtext[4],
        describe:logtext[5]
    };
    return log;
}
function quaryloglist(meetingId,func_onGetLogListView)
{
    var path = "xnode/ws/recording/logconf/command?arg=browse * where uuid='"+meetingId+"'";
    var handlers = {

        onTimeout: function (req){
        console.log("query log list timeout")
        },
        onRequestSuccess: function(resp) {
            var result=-1;
            if (resp.result
                    && resp.result.overall)
            {
                result = parseInt(resp.result.overall);
            }

            if (result==0)
            {
                var logs=resp.result.detail.command
                var logtext=[];
                if ((typeof logs) === "string")
                {
                    var records = logs.split("\n");
                    for (var i = 0; i < records.length; ++i)
                    {
                        logtext.push(recordToLogListView(records[i]));
                    }
                }
            }
            func_onGetLogListView(logtext)
        },
        onRequestError: function (req){},
    }
    query(work.target, path, handlers);
}

function recordToLogListView(record)
{
    var logtext = record.split('|');

    var logs = {
        meetId:logtext[0],
        meetUuid:logtext[1],
        meetEvent:logtext[2],
        meetTime:logtext[3],
        meetType:logtext[4],
        meetDescribe:logtext[5]
    };
    return logs;
}
function quaryEquipmentLog(startTime,endTime,func_onGetEquipmentLog)
{
    var path = "xnode/ws/recording/log_online/command?arg=browse * where  time >"+startTime+" and time <"+endTime;
    var handlers = {
        onTimeout: function (req){
        console.log("query Equipmentlog timeout ")
        },
        onRequestSuccess: function(resp) {
            var result=-1;
            if (resp.result
                    && resp.result.overall)
            {
                result = parseInt(resp.result.overall);
            }

            if (result==0)
            {
                var logs=resp.result.detail.command
                var logtext=[];
                if ((typeof logs) === "string")
                {
                    var records = logs.split("\n");
                    for (var i = 0; i < records.length; ++i)
                    {
                        logtext.push(recordToOnline(records[i]));
                    }
                }
            }
            func_onGetEquipmentLog(logtext)
        },
        onRequestError: function (req){},
    }
    query(work.target, path, handlers);
}
function recordToOnline(record)
{
    var logtext = record.split('|');

    var equipmentLog = {
        equipmentId:logtext[0],
        equipmentEvent:logtext[1],
        equipmentUsername:logtext[2],
        equipmentType:logtext[3],
        equipmentTime:timeToLocalTime(logtext[4]),
    };
    return equipmentLog;
}

function standardOutput(value){
    return value < 10 ? ("0" + value) : value
}

function timeToLocalTime(time)
{
    var today = new Date(time*1000);
    var year=today.getFullYear()
    var month=standardOutput(today.getMonth()+1)
    var days=standardOutput(today.getDate())
    var hours=standardOutput(today.getHours())
    var minutes=standardOutput(today.getMinutes())
    var seconds=standardOutput(today.getSeconds())
    time=year+'-'+month+'-'+days+' '+hours+':'+minutes+':'+seconds
    return time
}
