import QtQuick 2.0
import Abrites 1.0

Item {
    BinaryData { id: bin }
    property int visibleLines : 16

    function setAddr(address) {
        console.log("address = " +  address + ", bin.offset = " + bin.offset + ", bin.address = " + bin.address + ", lineSize: " + BinaryData.LineSize)
        bin.address = address
        bin.offset = address % BinaryData.LineSize
        console.log("address = " +  address + ", bin.offset = " + bin.offset + ", bin.address = " + bin.address)
    }

    Component {
        id: drawLine
        ListView {
            id: line
            property int normalWidth : line.width / (BinaryData.LineSize + 2)
            property int addressWidth : normalWidth * 2

            height: hexViewer.height / visibleLines
            width: hexViewer.width
            orientation: ListView.Horizontal
            interactive: false
            model: lineData
            delegate: Rectangle {
                property bool addressField : index % (BinaryData.LineSize + 1) === 0
                property bool selected : (index === bin.offset) && (lineData[0] === bin.address)

                color: addressField ? "#BBBBBB" : selected ? "darkgray" : "white"
                border.width: 1
                border.color: "#EEEEEE"
                width: addressField ?  addressWidth : normalWidth
                height: line.height

                Text {
                    anchors.centerIn: parent
                    text: lineData[index]
                    font.pixelSize: Math.min(parent.height / 2, parent.width / 2)
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked : {
                        bin.address = lineData[0]
                        bin.offset = index
                        hexViewer.forceActiveFocus()
                    }
                }
            }
        }
    }


    ListView {
        id: hexViewer
        width: parent.width
        height: parent.height
        model: bin
        clip: true
        delegate : drawLine
        focus: true

        Keys.onPressed: {
            bin.keyPress(event.key, event.text)
        }
    }
}
