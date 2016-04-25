import QtQuick 2.0

import QtQuick.Controls 1.2

ScrollView {
    property int rectx
    property int recty
    property int currentmoux
    property int currentmouy
GridView {
    id: grid

    width: 800
    height: 600

    focus: true

    cellHeight: 100
    cellWidth: 100

    property bool shift_pressed: false



    function clearSelection()
    {
        var count = fruitModel.count;
        for (var i = 0; i < count; ++i)
        {
            var obj = fruitModel.get(i);
            obj.selected = false;
        }
    }

    function rectSelection(rect)
    {
        var ind = indexAt(rect.x, rect.y);
        if (ind !== -1)
        {
            var data = fruitModel.get(ind);
            data.selected = true;
        }

        var x2 = rect.x + rect.width;
        var y2 = rect.y + rect.height;

        x2 = Math.ceil(x2 / cellWidth) * cellWidth;
        y2 = Math.ceil(y2 / cellHeight) * cellWidth;

        console.log("x1:" +rect.x +" y1:" + rect.y + " x2:" + x2 + " y2:" + y2);

        for (var x = rect.x; x < x2; x += grid.cellWidth)
        {
            for (var y = rect.y; y < y2; y += grid.cellHeight)
            {
                ind = indexAt(x, y);
                if (ind !== -1)
                {
                    var data2 = fruitModel.get(ind);
                    data2.selected = true;
                }
            }
        }
    }
    delegate: Column {

        //anchors.centerIn: parent

        Rectangle {
            width: 50
            height: 50
            color: selected ?"blue" : "grey"
        }
        Text { text: name; anchors.horizontalCenter: parent.horizontalCenter }
    }

    model: fruitModel

    ListModel {
        id: fruitModel
    }

    Rectangle {
        id: selectRect
        color: "blue"
        opacity: .2
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {

            forceActiveFocus();

            if (!grid.shift_pressed)
            {
                grid.clearSelection();
            }

            selectRect.x = mouseX;
            selectRect.y = mouseY;

            selectRect.width = 0;
            selectRect.height = 0;
            selectRect.visible = true;
            rectx=selectRect.x;
            recty=selectRect.y;
            console.log("selectRect.x:"+selectRect.x)
            console.log("selectRect.y:"+selectRect.y)

            console.log("onPressAndHold, mouseX:" + mouseX + "mouseY:" + mouseY );
        }

        onPositionChanged: {
            if (selectRect.visible)
            {
                selectRect.x=rectx;
                selectRect.y=recty;
               if(mouseX-selectRect.x>0&&mouseY-selectRect.y>0)
               {
                selectRect.width = mouseX - selectRect.x;
                selectRect.height = mouseY - selectRect.y;
               }
               else if(mouseX-selectRect.x<0&&mouseY-selectRect.y>0)
               {

                   selectRect.width=-(mouseX-rectx);
                   console.log("selectRect.width:"+selectRect.width)
                   console.log("selectRect.x1:"+selectRect.x)
                   selectRect.x=rectx-selectRect.width;
                   console.log("rectx:"+rectx)
                   console.log("selectRect.x2:"+selectRect.x)
                   console.log("mouseX:"+mouseX)
                    selectRect.height=mouseY-selectRect.y;

               }
               else if(mouseX-selectRect.x>0&&mouseY-selectRect.y<0)
               {
                   selectRect.width = mouseX - selectRect.x;
                   selectRect.height=-(mouseY-selectRect.y);
                    selectRect.y=recty-selectRect.height;
               }
               else
               {
                  selectRect.width=selectRect.x-mouseX;
                   selectRect.x=rectx-(selectRect.width+1);

                  selectRect.height=selectRect.y-mouseY
                   selectRect.y=recty-(selectRect.height+1);
               }
            }
            console.log("onPositionChanged, mouseX:" + mouseX + "mouseY:" + mouseY );
        }

        onReleased: {
            if (selectRect.visible)
            {
                selectRect.x=rectx;
                selectRect.y=recty;

                if(mouseX-selectRect.x>0&&mouseY-selectRect.y>0)
                {
                 selectRect.width = mouseX - selectRect.x;
                 selectRect.height = mouseY - selectRect.y;
                }
                else if(mouseX-selectRect.x<0&&mouseY-selectRect.y>0)
                {
                    selectRect.width=selectRect.x-mouseX;
                     selectRect.x=rectx-selectRect.width;
                     selectRect.height=mouseY-selectRect.y;
                }
                else if(mouseX-selectRect.x>0&&mouseY-selectRect.y<0)
                {
                    selectRect.width = mouseX - selectRect.x;
                    selectRect.height=selectRect.y-mouseY;
                     selectRect.y=recty-selectRect.height;
                }
                else
                {
                   selectRect.width=selectRect.x-mouseX;
                    selectRect.x=rectx-selectRect.width;

                   selectRect.height=selectRect.y-mouseY
                    selectRect.y=recty-selectRect.height;
                }
            }
            grid.rectSelection(selectRect);
            if (selectRect.visible)
            {
                selectRect.visible = false;
            }
            console.log("onReleased");
        }
    }

    /*Keys.onPressed: {
        if (event.key == Qt.Key_Shift)
        {
            console.log("key shift");
            shift_pressed = true;
            event.accepted = true;
        }
    }*/

   /* Keys.onReleased: {
        if (event.key == Qt.Key_Shift)
        {
            console.log("key shift");
            shift_pressed = false;
            event.accepted = true;
        }
    }*/

    Component.onCompleted: {
        for (var i = 0 ; i < 10; i++)
        {
            fruitModel.append({name: "Apple", selected: false});
            fruitModel.append({name: "Orange", selected: false});
            fruitModel.append({name: "Banana", selected: false});
        }
    }
}

}

