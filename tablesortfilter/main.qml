/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1
//import QtQuick.XmlListModel 2.0
import SortFilterProxyModel 0.1

ApplicationWindow {
    id: window

    width: 640
    height: 360
    visible: true
    title: qsTr("Flickr: %1").arg(comboBox.currentText)

    toolBar: ToolBar {
        ComboBox {
            id: comboBox

            model: [qsTr("Dogs"), qsTr("Cats")]
            anchors.verticalCenter: parent.verticalCenter
        }

        TextField {
            id: searchBox

            width: window.width / 3
            placeholderText: qsTr("Search...")
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
        }
    }

    XmlListModel {
        id: sourceModel

        source: "file:///home/backup/tmp/dogs.xml"
        query: "/rss/channel/item"
        namespaceDeclarations: "declare namespace media=\"http://search.yahoo.com/mrss/\";"

        XmlRole { name: "title"; query: "media:title/string()" }
        XmlRole { name: "credit"; query: "media:credit/string()" }
        XmlRole { name: "image"; query: "media:content/@url/string()" }
        XmlRole { name: "link"; query: "link/string()" }
    }

    SplitView {
        anchors.fill: parent

        ListModel {
            id: pairModel

            ListElement {
                title: "Brilliance"
                name :"xxxx"
                author: "Jens"
                credit: "credit1"

            }

            ListElement {
                title: "A Masterpiece"
                name :"xxxx"
                author: "Gabriel"
                credit: "credit2"

            }

            ListElement {
                title: "Outstanding"
                name :"xxxx"

                author: "Frederik"
                credit: "credit3"
            }
        }

        TableView {
            id: tableView

            width: parent.width / 2
            frameVisible: false
            sortIndicatorVisible: true
            currentRow: rowCount ? 0 : -1

            TableViewColumn { role: "title"; title: qsTr("Title") }
            TableViewColumn { role: "credit"; title: qsTr("Credit") }

            //onDoubleClicked: Qt.openUrlExternally(proxyModel.get(tableView.currentRow).link)

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

       Image {
            id: image

            width: parent.width / 2
            fillMode: Image.PreserveAspectFit
            source: tableView.currentRow !== -1 ? proxyModel.get(tableView.currentRow).image : ""

            BusyIndicator {
                running: image.status === Image.Loading
                anchors.centerIn: parent
            }
        }
    }
}
