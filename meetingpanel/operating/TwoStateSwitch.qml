import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4
Switch{
    id:root
    width: 111
    height: 30
style: SwitchStyle{
    groove: Image {
        id: name
        source: "../images/th_back_image.png"
    }
    handle: Image {
        id: name2
        source: "../images/th_image.png"
        Text {
            id: title
            width: root.width/2
            height: root.height
            font.pointSize: 14
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "#999999"
            text: checked ? "会议":"通播"
        }
    }
}
onClicked: {

}
}


