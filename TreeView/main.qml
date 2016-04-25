import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480



    Item {
        id: root
        width: 600 // change to parent.width
        height: 500// change to parent.height

        ListView {
            id: rootView
            anchors.fill: parent
            delegate: groupsDelegate
            model: listModel

            Component {
                id: groupsDelegate

                Item {
                    id: container
                    width: 200
                    height: childrenRect.height
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                           container.ListView.view.currentIndex=index
                            console.log(index)
                        }
                    }

                    Column {
                        x: 14
                        id: mainColumn

                        Row {
                            id: mainRow
                            spacing: 3
                            property bool expanded: false

                            Image {
                                id: expander
                                source: "arrow_down_image.png"
                                rotation: mainRow.expanded ? -90 : 0
                                opacity: elements.count === 0 ? 0 : 1
                                Behavior on rotation {
                                    NumberAnimation {duration: 110}
                                }

                                MouseArea {
                                    visible: expander.opacity === 1 ? true : false
                                    id: expanderMouseArea
                                    anchors.fill: parent
                                    onClicked: {
                                        mainRow.expanded = !mainRow.expanded
                                    }
                                }
                            }

                            Text {
                                id: name
                                text: group
                            }
                        }

                        Item {
                            width: 200
                            height: childView.contentHeight
                            visible: mainRow.expanded

                            ListView {
                                id: childView
                                anchors.fill: parent
    //                            visible: mainRow.expanded
                                model: elements
                                delegate: groupsDelegate
                                highlight: Rectangle {color: "lightsteelblue"; radius: 5}
                                focus: true
                            }

                        }
                    }
                }
            }

            ListModel {
                id:listModel
                ListElement {
                    group: "first"
                    elements: [
                        ListElement {group: "first1"; elements: []},
                        ListElement {group: "first2"; elements: []}
                    ]
                }
            }
        }


    }
    }

