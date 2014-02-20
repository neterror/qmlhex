#ifndef BINARYDATA_H
#define BINARYDATA_H

#include <QtCore>
#include <QStandardItemModel>

class BinaryData : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(Param)
public:
    enum Roles {
        Line = Qt::UserRole + 1
    };

    enum Param {
        LineSize = 16
    };

    explicit BinaryData(QAbstractListModel *parent = 0);
    Q_PROPERTY (QString address READ address WRITE setAddress NOTIFY addressChange);
    Q_PROPERTY (int offset READ offset WRITE setOffset NOTIFY offsetChange);

    Q_INVOKABLE void keyPress(int keyCode, const QString& keyText);

    QString address() const {return QString("%1").arg(mAddress, 4, 16, QChar('0')).toUpper();}
    void setAddress(const QString& addr) {mAddress = addr.toInt(0, 16); addressChange();}

    int offset() const {return mOffset;}
    void setOffset(int off) {mOffset = off; offsetChange();}

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
private:
    QByteArray mData;

    static QModelIndex lastIdx;
    static QStringList lastResult;


protected:
    virtual QHash<int, QByteArray> roleNames() const;

private:
    int mAddress;
    int mOffset;
    QString mEntered;
    QStringList mLastResponse;
    QModelIndex mLastRequest;

    void insertSampleData();
    void editCell(const QString& keyText);
signals:
    void addressChange();
    void offsetChange();
};

#endif // BINARYDATA_H
