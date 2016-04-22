import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2
import SortFilterProxyModel 0.1

import "../listener.js" as Logic

Rectangle {
    id: root
    width: 600
    height: 500
    signal addtransferid(string accounta,string froma,string accountb,string fromb)
    signal deltransferid(string usera,string userb)
    property int  accountid
    property string groupId
    property var attendees : []

    function load()
    {
        //return;
        if (groupId)
        {
            Logic.queryTransferTable(groupId, onGetTransferTables);
        }
    }

    function extractAttendee(atts, accountId, fromId)
    {
        //console.log("extractAttendee, accoutId:", accountId, " fromId: ", fromId)
        for (var i = 0 ; i < atts.length; i++)
        {
            //console.log("check att ", atts[i].accountId, ":", atts[i].fromId)
            if (atts[i].accountId === accountId
                    && atts[i].fromId === fromId  )
            {
                var att = atts[i];
                atts.splice(i, 1);

                return att;
            }
        }
        return null;
    }

    function cloneAttendee()
    {
        var clone = [];
        for (var i = 0 ; i < attendees.length; i++)
        {
            if (attendees[i].role === Logic.getRoleValue("COMMANDER")
                    ||attendees[i].role === Logic.getRoleValue("SUPERIOR")
                    ||attendees[i].role === Logic.getRoleValue("ANNOUNCER")
                    ||attendees[i].specialIntercom==="1")
            {
                if (attendees[i].oppositeAccountId == null || attendees[i].oppositeAccountId == "") // if attendee already have peer, we need to show them.
                    continue;
            }
            clone.push(attendees[i]);
        }
        return clone;
    }

    function onGetTransferTables(grpId, transfers)
    {
        var pairs = [];
        var backup = cloneAttendee();

        for (var i = 0; i < transfers.length; i++)
        {
            var t = transfers[i];
            //var at_id1 = t.accountId1 + t.fromId1;
            //var at_id2 = t.accountId2 + t.fromId2;


            var attA = extractAttendee(backup, t.accountId1, t.fromId1);
            if (!attA)
            {
                console.log("invalid transfer accountId1: " + t.accountId1
                            + ", fromId1: " + t.fromId1);
                continue;
            }
            var attB = extractAttendee(backup, t.accountId2, t.fromId2);;
            if (!attB)
            {
                console.log("invalid transfer accountId2: " + t.accountId2
                            + ", fromId2: " + t.fromId2);
                continue;
            }

            var pair = {
                tid: t.id,
                interpose: t.interpose,
                userNameA: attA.realName,
                userNameB: attB.realName,
                userA: attA,
                userB: attB,
            };

            pairs.push(pair)

        }

        resetTables(pairs, backup)
    }

    function resetTables(pairs, singles)
    {
        pairModel.clear();
        aModel.clear();
        bModel.clear();

        for (var i = 0; i < pairs.length; i++)
        {
            pairModel.append(pairs[i]);
        }


        for (var i = 0; i < singles.length; i++)
        {
            aModel.append(singles[i]);
            bModel.append(singles[i]);
        }

    }

    function addItem(a, b)
    {
        if (a.accountId === b.accountId &&
                a.fromId === b.fromId)
        {
            return;
        }

        var tf = {
            accountId1: a.accountId,
            fromId1: a.fromId,
            accountId2: b.accountId,
            fromId2: b.fromId,
            interpose: 0
        };

        Logic.addTransfer(groupId, tf,
                          function(grpId, transfer)
                          {
                              load();
                              root.addtransferid(a.accountId,a.fromId,b.accountId,b.fromId);
                          },
                          function(grpId, transfer, msg)
                          {
                              console.log("addTransfer failed: " + msg);
                          }

                          )
    }

    function deleteItem(t)
    {
        var tid = t.tid;

        Logic.deleteTransfer(groupId, tid,
                             function(grpId, t_id)
                             {
                                 load();
                                 root.deltransferid(t.userNameA,t.userNameB)
                             },
                             function(grpId, t_id, msg)
                             {
                                 console.log("deleteTransfer failed: " + msg);
                             }

                             )
    }

    function changeInterpose(pair, bChecked)
    {
        Logic.changeTransferInterpose(groupId, pair.tid, bChecked,
                                      function(grpId, t_id)
                                      {
                                          load();
                                      },
                                      function(grpId, t_id, msg)
                                      {
                                          console.log("changeTransferInterpose failed: " + msg);
                                      }
                                      )

    }

    ListModel {
        id: pairModel

        //        ListElement {
        //            userNameA: "Eddard Stark"
        //            userNameB :"Catelyn Tully"
        //            interpose: true
        //        }
    }

    ListModel {
        id: aModel
    }

    ListModel {
        id: bModel
    }

    ColumnLayout {
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            //bottom: bottomBar.top
            //leftMargin: 12
        }

        spacing: 8
        Item { Layout.preferredHeight: 4 } // padding

        Text {
            font.bold: true
            text: "已组成转接列表:"
            color: "black"
        }

        TableView {
            id: tableView

            width: 600
            height: 200
            implicitHeight: 200
            implicitWidth: 600
            frameVisible: true
            sortIndicatorVisible: true
            currentRow: rowCount ? 0 : -1
            backgroundVisible: true
            itemDelegate: Item {
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    color: "white"
                    text: styleData.value
                    anchors.left: parent.left
                    anchors.leftMargin: 12
                }
            }
            rowDelegate: Rectangle{
                height: 25
                color: styleData.alternate? "#7d8f9c" : "#a7b3bc"
                BorderImage{
                    id: selected
                    anchors.fill: parent
                    source: "../images/selectedrow.png"
                    visible: styleData.selected
                    border{left:2; right:2; top:2; bottom:2}
                    SequentialAnimation {
                        running: true; loops: Animation.Infinite
                        NumberAnimation { target:selected; property: "opacity"; to: 1.0; duration: 900}
                        NumberAnimation { target:selected; property: "opacity"; to: 0.5; duration: 900}
                    }
                }
            }

            TableViewColumn {
                role: "userNameA";
                title: qsTr("用户A")
                width: tableView.viewport.width / 3
            }
            TableViewColumn {
                role: "userNameB";
                title: qsTr("用户B");
                width: tableView.viewport.width / 3

            }
            TableViewColumn {
                role: "interpose";
                title: qsTr("插话")
                width: tableView.viewport.width / 3

                delegate: CheckBox{
                    //  anchors.left: usernameb.right
                    //anchors.leftMargin: 12
                    checked: styleData.value === "1"

                    onClicked: {
                        //console.log("dump value :" + Logic.serialize(styleData.value, 3))
                        changeInterpose(proxyModel.get(styleData.row), checked);
                    }
                }
            }
            style: TableViewStyle {
                headerDelegate: BorderImage {
                    id: name
                    source: "../images/meeting_back_image.png"
                    height: 25
                    width: tableView.width
                    Text {
                        id: textItem
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: styleData.textAlignment
                        anchors.leftMargin: 12
                        text: styleData.value
                        color: "white"
                    }
                }
                handle: Item{
                    implicitWidth: 12
                    implicitHeight: 12
                    Rectangle {
                        color: "#7d8f9c"
                        anchors.fill: parent
                        visible: true
                    }
                }
                decrementControl:Image{
                    width:12
                    height: 12
                    source:
                    {
                        if(styleData.horizontal)
                        {
                            return "../images/arrow_left.png"
                        }
                        else
                        {
                            return "../images/arrow_up.png"
                        }
                    }
                }
                incrementControl:
                    Image{
                    width:12
                    height: 12
                    source:
                    {
                        if(styleData.horizontal)
                        {
                            "../images/arrow_right.png"
                        }
                        else
                        {
                            "../images/arrow_down.png"
                        }
                    }
                }
                scrollBarBackground: Rectangle {
                    implicitWidth: 12
                    implicitHeight: 12
                    color: "#a7b3bc"
                }

            }

            model: SortFilterProxyModel {
                id: proxyModel
                source: pairModel

                sortOrder: tableView.sortIndicatorOrder
                sortCaseSensitivity: Qt.CaseInsensitive
                sortRole: pairModel.count > 0 ? tableView.getColumn(tableView.sortIndicatorColumn).role : ""

                filterString: ""
                filterSyntax: SortFilterProxyModel.Wildcard
                filterCaseSensitivity: Qt.CaseInsensitive
            }
        }
        FancyButton{
            id: deleteBtn
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            text: "删除"
            enabled: tableView.selection.count > 0
            onClicked: {
                tableView.selection.forEach(function(rowIndex)
                {
                    deleteItem(proxyModel.get(rowIndex));
                });
            }
        }

        Text {
            font.bold: true
            text: "候选转接列表:"
            color: "black"
        }

        Row {

            TableView {
                id: aList
                implicitHeight: 200
                implicitWidth: 300

                frameVisible: true
                sortIndicatorVisible: true
                currentRow: rowCount ? 0 : -1
                backgroundVisible: true
                style: TableViewStyle {
                    headerDelegate: BorderImage {
                        id: useraheaderImages
                        source: "../images/meeting_back_image.png"
                        height: 25
                        width: aList.width

                        // color: "#123863"
                        Text {
                            id: useratext
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: styleData.textAlignment
                            anchors.leftMargin: 12
                            text: styleData.value
                            elide: Text.ElideRight
                            color: "white"

                        }
                    }
                    handle: Item{
                        implicitWidth: 12
                        implicitHeight: 12
                        Rectangle {
                            color: "#7d8f9c"
                            anchors.fill: parent
                            visible: true
                        }
                    }
                    decrementControl:
                        Image{
                        width:12
                        height: 12
                        source:
                        {
                            if(styleData.horizontal)
                            {
                                return "../images/arrow_left.png"
                            }
                            else
                            {
                                return "../images/arrow_up.png"
                            }
                        }
                    }
                    incrementControl:
                        Image{
                        width:12
                        height: 12
                        source:
                        {
                            if(styleData.horizontal)
                            {
                                "../images/arrow_right.png"
                            }
                            else
                            {
                                "../images/arrow_down.png"
                            }
                        }

                    }
                    scrollBarBackground: Rectangle {
                        implicitWidth: 12
                        implicitHeight: 12
                        color: "#a7b3bc"
                    }
                }



                itemDelegate: Item {
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        color: "black"
                        text: styleData.value
                        anchors.left: parent.left
                        anchors.leftMargin: 12
                    }
                }
                rowDelegate: Rectangle{
                    height: 25
                    color: styleData.alternate? "#7d8f9c" : "#a7b3bc"

                    BorderImage{
                        id:selecteda
                        anchors.fill: parent
                        source: "../images/selectedrow.png"
                        visible: styleData.selected
                        border{left:2; right:2; top:2; bottom:2}
                        SequentialAnimation {
                            running: true; loops: Animation.Infinite
                            NumberAnimation { target:selecteda; property: "opacity"; to: 1.0; duration: 900}
                            NumberAnimation { target:selecteda; property: "opacity"; to: 0.5; duration: 900}
                        }
                    }
                }

                TableViewColumn { role: "realName"; title: qsTr("用户A") }

                model: SortFilterProxyModel {
                    id: aProxyModel
                    source: aModel


                    sortOrder: aList.sortIndicatorOrder
                    sortCaseSensitivity: Qt.CaseInsensitive
                    sortRole: aModel.count > 0 ? aList.getColumn(aList.sortIndicatorColumn).role : ""

                    filterString: ""
                    filterSyntax: SortFilterProxyModel.Wildcard
                    filterCaseSensitivity: Qt.CaseInsensitive
                }

            }

            TableView {
                id: bList
                implicitHeight: 200
                implicitWidth: 300

                frameVisible: true
                sortIndicatorVisible: true
                currentRow: rowCount ? 0 : -1
                style: TableViewStyle {
                    headerDelegate: BorderImage {
                        id: userbheaderImages
                        source: "../images/meeting_back_image.png"
                        height: 25
                        width: bList.width

                        // color: "#123863"
                        Text {
                            id: userbtext
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: styleData.textAlignment
                            anchors.leftMargin: 12
                            text: styleData.value
                            elide: Text.ElideRight
                            color: "white"

                        }
                    }
                    handle: Item{
                        implicitWidth: 12
                        implicitHeight: 12
                        Rectangle {
                            color: "#7d8f9c"
                            anchors.fill: parent
                            visible: true
                        }
                    }
                    decrementControl:Image{
                        width:
                        {
                            return 12
                        }
                        height:
                        {
                            return 12
                        }

                        source:
                        {
                            if(styleData.horizontal)
                            {
                                return "../images/arrow_left.png"
                            }
                            else
                            {
                                return "../images/arrow_up.png"
                            }
                        }
                    }
                    incrementControl:
                        Image{
                        width:
                        {
                            return 12
                        }
                        height:
                        {
                            return 12
                        }
                        source:
                        {
                            if(styleData.horizontal)
                            {
                                "../images/arrow_right.png"
                            }
                            else
                            {
                                "../images/arrow_down.png"
                            }
                        }
                    }
                    scrollBarBackground: Rectangle {
                        implicitWidth: 12
                        implicitHeight: 12
                        color: "#a7b3bc"
                    }
                }


                itemDelegate: Item {
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        color: "black"
                        text: styleData.value
                        anchors.left: parent.left
                        anchors.leftMargin: 12
                    }
                }
                rowDelegate: Rectangle{
                    height: 25
                    color: styleData.alternate? "#7d8f9c" : "#a7b3bc"
                    BorderImage{
                        id: selectedb
                        anchors.fill: parent
                        source: "../images/selectedrow.png"
                        visible: styleData.selected
                        border{left:2; right:2; top:2; bottom:2}
                        SequentialAnimation {
                            running: true; loops: Animation.Infinite
                            NumberAnimation { target:selectedb; property: "opacity"; to: 1.0; duration: 900}
                            NumberAnimation { target:selectedb; property: "opacity"; to: 0.5; duration: 900}
                        }
                    }
                }

                TableViewColumn { role: "realName"; title: qsTr("用户B") }

                model: SortFilterProxyModel {
                    id: bProxyModel
                    source: bModel

                    sortOrder: bList.sortIndicatorOrder
                    sortCaseSensitivity: Qt.CaseInsensitive
                    sortRole: bModel.count > 0 ? bList.getColumn(bList.sortIndicatorColumn).role : ""

                    filterString: ""
                    filterSyntax: SortFilterProxyModel.Wildcard
                    filterCaseSensitivity: Qt.CaseInsensitive
                }
            }
        }

        FancyButton{
            id: addBtn
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            text: "增加"

            enabled: {

                return aList.selection.count > 0 && bList.selection.count > 0;

            }
            onClicked: {
                var aindex = -1;
                var bindex = -1;
                aList.selection.forEach(function (rowIndex)
                {
                    aindex = rowIndex;
                    console.log("A select " + rowIndex);
                    console.log(Logic.serialize(aProxyModel.get(aindex)));
                })

                bList.selection.forEach(function (rowIndex)
                {
                    bindex = rowIndex;
                    console.log("B select " + rowIndex);
                    console.log(Logic.serialize(bProxyModel.get(bindex)));
                })
                if (aindex >= 0 && bindex >= 0)
                {
                    addItem(aProxyModel.get(aindex), bProxyModel.get(bindex));
                }
            }

        }
        FancyButton{
            id: closeBtn

            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            text: "关闭"

            onClicked: {

                transferDlg.close();
            }
        }


    }

}

