
var rooms = null;
var username = null;
var password = null;

username = "admin"
password = "111111"

function query(handers)
{
    var doc = new XMLHttpRequest()
    doc.onreadystatechange = function (){
        if (doc.readyState == XMLHttpRequest.DONE) {
//            var a = doc.responseXML.documentElement;
//            for (var ii = 0; ii < a.childNodes.length; ++ii) {
//                showRequestInfo(a.childNodes[ii].nodeName);
//            }
//            showRequestInfo("Headers -->");
//            showRequestInfo(doc.getAllResponseHeaders ());
//            showRequestInfo("Last modified -->");
//            showRequestInfo(doc.getResponseHeader ("Last-Modified"));
            handers.onSuccess(doc)
        }

    }

    doc.open("GET", "http://192.168.5.181/xnode/suApp", true, "admin", "111111");
    doc.send();

}
