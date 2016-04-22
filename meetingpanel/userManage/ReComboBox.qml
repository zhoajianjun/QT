import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
Item {

    signal choiceSip();
    signal choiceVir();
    signal choicePhy();
    signal choiceCon();
    RowLayout {
        //anchors.centerIn: parent;
        spacing: -2;
        ExclusiveGroup { id: tabPositionGroup }
        RadioButton {
            id:choice1;
            width: 52; height: 28;
            checked: true
            exclusiveGroup: tabPositionGroup

            style: RadioButtonStyle{

                indicator: Image{
                    width: 52;height: 28;
                    visible: true;
                    //anchors.fill: parent;
                    source:  "../images/button2.png" ;//"../images/button2.png";

                    Text {
                        anchors.centerIn: parent;
                        text: qsTr("SIP单机");
                        color:"white";
                        font.pixelSize: 12;
                    }
                    Image{
                        width: 52;height: 28;
                        visible: control.checked;
                        //anchors.fill: parent;
                        source:"../images/button0.png";

                        Text {
                            anchors.centerIn: parent;
                            text: qsTr("SIP单机");
                            color:"white";
                            font.pixelSize: 13;
                        }
                    }
                }

            }
            onClicked: choiceSip();
        }
        RadioButton {
            id:choice2;
            exclusiveGroup: tabPositionGroup

            width: 52; height: 28;
            style: RadioButtonStyle{

                indicator: Image{
                    width: 52;height: 28;
                    visible: true;
                    //anchors.fill: parent;
                    source:  "../images/button2.png" ;//"../images/button2.png";

                    Text {
                        anchors.centerIn: parent;
                        text: qsTr("虚拟单机");
                        color:"white";
                        font.pixelSize: 12;
                    }
                    Image{
                        width: 52;height: 28;
                        visible: control.checked;
                        //anchors.fill: parent;
                        source:"../images/button0.png";

                        Text {
                            anchors.centerIn: parent;
                            text: qsTr("虚拟单机");
                            color:"white";
                            font.pixelSize: 13;
                        }
                    }
                }

            }

            onClicked: choiceVir();
        }

        RadioButton {
            id:choice3;
            exclusiveGroup: tabPositionGroup;
            //checked: true;
            width: 52; height: 28;
            style: RadioButtonStyle{

                indicator: Image{
                    width: 52;height: 28;
                    visible: true;
                    //anchors.fill: parent;
                    source:  "../images/button2.png" ;//"../images/button2.png";

                    Text {
                        anchors.centerIn: parent;
                        text: qsTr("物理单机");
                        color:"white";
                        font.pixelSize: 12;
                    }
                    Image{
                        width: 52;height: 28;
                        visible: control.checked;
                        //anchors.fill: parent;
                        source:"../images/button0.png";

                        Text {
                            anchors.centerIn: parent;
                            text: qsTr("物理单机");
                            color:"white";
                            font.pixelSize: 13;
                        }
                    }
                }

            }

            onClicked: choicePhy();

        }

        RadioButton {
            id:choice4;
            exclusiveGroup: tabPositionGroup;
            //checked: true;
            width: 52; height: 28;
            style: RadioButtonStyle{

                indicator: Image{
                    width: 52;height: 28;
                    visible: true;
                    //anchors.fill: parent;
                    source:  "../images/button2.png" ;//"../images/button2.png";

                    Text {
                        anchors.centerIn: parent;
                        text: qsTr("联系人");
                        color:"white";
                        font.pixelSize: 12;
                    }
                    Image{
                        width: 52;height: 28;
                        visible: control.checked;
                        //anchors.fill: parent;
                        source:"../images/button0.png";

                        Text {
                            anchors.centerIn: parent;
                            text: qsTr("联系人");
                            color:"white";
                            font.pixelSize: 13;
                        }
                    }
                }

            }

            onClicked: choiceCon();

        }
    }

}

