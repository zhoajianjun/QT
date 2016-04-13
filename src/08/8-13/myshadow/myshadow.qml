import QtQuick 2.2
import QtGraphicalEffects 1.0

Item {
    width: 300; height: 300

    Image {
        id: butterfly; source: "images/butterfly.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true; visible: false
    }

    DropShadow {
        anchors.fill: butterfly; source: butterfly
        horizontalOffset: 4; verticalOffset: 4
        radius: 8.0; samples: 16; color: "#80000000";
    }
}
