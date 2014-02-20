TARGET = hexedit
QT += qml quick widgets

SOURCES += main.cpp binarydata.cpp loader.cpp
HEADERS += binarydata.h loader.h
OTHER_FILES += qml/HexEdit/main.qml qml/HexEdit/HexEdit.qml

RESOURCES += resources.qrc
