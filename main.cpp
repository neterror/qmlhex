#include <QApplication>
#include "binarydata.h"
#include "loader.h"
#include <QtQuick>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<BinaryData>("HexEditor", 1, 0, "HexModel");
    qmlRegisterType<Loader>("HexEditor", 1, 0, "LoadData");

    QQmlApplicationEngine engine(QUrl("qrc:/qml/HexEdit/main.qml"));
    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    if ( !window ) {
        qWarning("Error: Your root item has to be a Window.");
        return -1;
    }

    window->show();
    window->update();

    return app.exec();
}
