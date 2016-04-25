import QtQuick 2.4
import QtQuick.Controls 1.3

Item {
    id: item1
    width: 403
    height: 350

    Image {
        id: logo
        width: 403
        height: 81
        sourceSize.height: 81
        sourceSize.width: 403
        fillMode: Image.Stretch
        source: "mc_pro.bmp"
    }

    Column {
        id: column1
        height: 180
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: parent.top
        anchors.topMargin: 100

        Row {
            id: row1
            height: 50

            Text {
                id: text1
                width: 100
                height: 40
                text: "Server:"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
            }

            TextField {
                id: textField1
                width: 200
                height: 40
                placeholderText: qsTr("Text Field")
            }
        }

        Row {
            id: row2
            height: 50
            Text {
                id: text2
                width: 100
                height: 40
                text: "Server:"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
            }

            TextField {
                id: textField2
                width: 200
                height: 40
                placeholderText: qsTr("Text Field")
            }
        }
    }
}

