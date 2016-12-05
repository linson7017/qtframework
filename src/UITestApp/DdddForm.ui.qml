import QtQuick 2.4
import QtQuick.Layouts 1.2

Item {
    width: 400
    height: 400

    Flickable {
        id: flickable1
        x: 39
        y: 132
        width: 220
        height: 218
    }

    Text {
        id: text1
        x: 109
        y: 49
        width: 155
        height: 65
        color: "#000000"
        text: qsTr("Text")
        style: Text.Raised
        font.bold: true
        font.family: "Courier"
        textFormat: Text.RichText
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 30
    }
}

