import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4


Button{
    id:root
    style: ButtonStyle{
        id:bstyle
        Image {
            id: normalImage
            source: control.pressed?"../images/buttn_press_image1.png":"../images/buttn_image.png"
        }
        Image {
            id: disableImage
            source: "../images/buttn_enable_iamge.png"
        }
        background: Image {
            id: name
            source: root.enabled?normalImage.source:disableImage.source;
            Component.onCompleted: {
                root.onEnabledChanged.connect(updateStyle)
            }

            function updateStyle()
            {
                if(root)
                {
                if (root.enabled)
                {
                    name.source= normalImage.source;
                }
                else
                {
                    name.source = disableImage.source;
                }
                }
            }
        }

    label:Text {
       anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        text: control.text
        color: "#eeeeee"
    }

}
}



/*Button {
    id:root

    style: ButtonStyle {
        id: bstyle

        Gradient {
            id: normalGrad

            GradientStop { position: 0 ; color: control.pressed ? "#061d1b" : "#075c5b" }
            GradientStop {position:  0.5;color:control.pressed ? "#012b12" : "#014848"  }
            GradientStop { position: 1 ; color: control.pressed ? "#015252" : "#015a5a" }
        }

        Gradient {
            id: disableGrad

            GradientStop { position: 0 ; color: "gray" }
            GradientStop { position: 0.5 ; color: "gray" }
            GradientStop { position: 1 ; color: "gray" }
        }


        background: Rectangle {
            id: bgRect
            implicitWidth: 100
            implicitHeight: 25
            border.width: control.activeFocus ? 2 : 1
            border.color: "#888"
            //radius: 20
            gradient: root.enabled ? normalGrad :disableGrad

            Component.onCompleted: {
                root.onEnabledChanged.connect(updateStyle)
            }

            function updateStyle()
            {
                if (root.enabled)
                {
                    bgRect.gradient = normalGrad;
                }
                else
                {
                    bgRect.gradient = disableGrad;
                }
            }
        }

        label: Text {

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            text: control.text
            color: "#eeeeee"
        }
    }
}*/



