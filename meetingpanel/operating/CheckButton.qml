import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.4

Button{
    id:root
    checkable:true
    style: ButtonStyle{
        id:bstyle
        background: Image {
            id: name1
            source:
            {
               control.checked?"../images/buttn_press_image1.png":"../images/buttn_image.png"
            }

//            Component.onCompleted: {
//                root.onEnabledChanged.connect(updateStyle);
//            }

//            function updateStyle()
//            {
//                if (root.enabled)
//                {
//                    name1.source = control.checked?"../images/button2.png":"../images/button0.png"
//                }
//                else
//                {
//                    name1.source=" ../images/buttn3.png";
//                }
//            }
//            states: [
//                State {
//                    name: "clicked"
//                    PropertyChanges { target: name1;source:"../images/quitsystem01.png"}
//                },
//                State {
//                    name: "unclicked"
//                    when: root.pressed
//                    PropertyChanges { target: name1;source:"../images/quitsystem03.png" }
//                }
//            ]
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

    checkable: true

    style: ButtonStyle {
        id: bstyle

        Gradient {
            id: normalGrad

            GradientStop { position: 0 ; color: control.checked ? "#061d1b" : "#075c5b" }
            GradientStop {position:  0.5;color:control.checked ? "#012b12" : "#014848"  }
            GradientStop { position: 1 ; color: control.checked? "#015252" : "#015a5a" }
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
           // radius: 20
            gradient: normalGrad

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
