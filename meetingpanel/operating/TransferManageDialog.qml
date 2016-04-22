import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2

import "../listener.js" as Logic


Dialog {
    property alias groupId: transPage.groupId
    property alias attendees: transPage.attendees

    id: root
    width: 650
    height: 630
    visible: false
    signal update(string accounta,string froma,string accountb,string fromb)
    signal deltransfer(string usera,string userb)

    function load()
    {
        transPage.load();
    }

    title: qsTr("转接管理")

    contentItem:

        Rectangle {
        anchors.fill: parent

        color: "#bbc5cc"
        border.color: "#585556"
        border.width: 3

        TransferPage {
            id: transPage

            width: 600
            color: "#bbc5cc"
            anchors.top : parent.top
            anchors.topMargin: 5
            anchors.bottom: parent.bottom

            anchors.bottomMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 24
            anchors.right: parent.right
            anchors.rightMargin: 24
            onAddtransferid: {
                root.update(accounta, froma, accountb, fromb);

            }
            onDeltransferid: {
                root.deltransfer(usera,userb);
            }


            //color: "white"
        }
    }
}

