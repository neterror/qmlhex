#ifndef LOADER_H
#define LOADER_H

#include <QtCore>
#include <QtQuick>
#include "binarydata.h"

class Loader : public QObject
{
    Q_OBJECT
public:
    explicit Loader(QObject *parent = 0);

    Q_INVOKABLE void loadFile(const QString& file, BinaryData* display);
signals:

public slots:

};

#endif // LOADER_H
