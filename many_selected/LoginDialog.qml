import QtQuick 2.0
import QtQuick.Dialogs 1.2

Dialog {
    id: root
    title: qsTr("Login")

//    contentItem: Rectangle {
//        color: "lightskyblue"
//        implicitWidth: 400
//        implicitHeight: 100
//        Text {
//            text: "Hello blue sky!"
//            color: "navy"
//            anchors.centerIn: parent
//        }
//    }

        contentItem: LoginUI {
            implicitWidth: 403
            implicitHeight: 350
        }

}

