#include "loader.h"

Loader::Loader(QObject *parent) :
    QObject(parent)
{
}

void Loader::loadFile(const QString& file, BinaryData* display)
{
    QFile f(file);
    f.open(QIODevice::ReadOnly);
    display->load(f.readAll());
}
