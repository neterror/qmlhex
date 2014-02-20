#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "binarydata.h"
#include <QtQuick>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;

    qmlRegisterType<BinaryData>("Abrites", 1, 0, "BinaryData");

    viewer.setMainQmlFile(QStringLiteral("qml/HexEdit/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
