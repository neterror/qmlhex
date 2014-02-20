import QtQuick 2.0
import QtQuick.Controls 1.0

Rectangle {
    width: 1024
    height: 768

    TextField {
        anchors.top: parent.top
        width: parent.width
        height: 50
        onAccepted: {
            editor.setAddr(text)
        }
    }

    HexEdit {
        id: editor
        width: parent.width * 2/3
        height: parent.height * 2/3
        visibleLines: 16
        anchors.centerIn: parent
    }
}
