#include "binarydata.h"


QModelIndex BinaryData::lastIdx;
QStringList BinaryData::lastResult;

BinaryData::BinaryData(QAbstractListModel*parent) :
    QAbstractListModel(parent)
{
    insertSampleData();
}

QHash<int, QByteArray> BinaryData::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Line] = "lineData";
    return roles;
}

QVariant BinaryData::data(const QModelIndex &index, int role) const
{
    (void)role;

    if ((index == lastIdx) && !lastResult.isEmpty())
        return lastResult;

    lastResult.clear();
    lastResult.reserve(LineSize);
    lastIdx = index;

    int offset = index.row() * LineSize;
    QString addr = QString("%1").arg(offset, 4, 16, QChar('0')).toUpper();
    lastResult.append(addr);
    const QByteArray& lineData = mData.mid(offset, LineSize);
    foreach (char c, lineData) {
        QString byte = QString("%1").arg((quint8)c, 2, 16, QChar('0')).toUpper();
        lastResult.append(byte);
    }
    return lastResult;
}

int BinaryData::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return mData.count() / LineSize;
}

void BinaryData::insertSampleData()
{
    for (int i = 0; i < 4096; ++i ) {
        mData.append(i);
    }
}

void BinaryData::keyPress(int keyCode, const QString& keyText)
{
    if (((keyCode >= Qt::Key_0) && (keyCode <= Qt::Key_9)) || ((keyCode >= Qt::Key_A) && (keyCode <= Qt::Key_F))) {
        editCell(keyText);
        return;
    }

    mEntered.clear();
    switch (keyCode) {
    case Qt::Key_Up:
        if (mAddress >= LineSize)
            mAddress -= LineSize;
        break;
    case Qt::Key_Down:
        if (mAddress + LineSize < mData.length())
            mAddress += LineSize;
        break;
    case Qt::Key_Left:
        if (mOffset > 1)
            mOffset--;
        else {
            if (mAddress >= LineSize) {
                mAddress -= LineSize;
                mOffset = LineSize;
            }
        }
        emit offsetChange();
        break;
    case Qt::Key_Right:
        if (mOffset < LineSize) {
            mOffset++;
        } else {
            mOffset = 1;
            if (mAddress + LineSize < mData.length())
                mAddress += LineSize;
        }
        emit offsetChange();
        break;
    }
    emit addressChange();
}

void BinaryData::editCell(const QString& keyText)
{
    mEntered += keyText.toUpper();
    int addr = mAddress + mOffset - 1;
    mData[addr] = mEntered.toInt(0, 16);

    QModelIndex row = index(addr / LineSize);
    QModelIndex rowEnd = index(addr / LineSize + 1);
    lastResult.clear();

    emit dataChanged(row, rowEnd);

    if (mEntered.length() == 2) {
        mOffset = (mOffset + 1) % 16;
        mEntered.clear();
        emit offsetChange();
    }

}

