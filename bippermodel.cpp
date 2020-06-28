#include "bippermodel.h"
#include <QDebug>

BipperModel::BipperModel(BipperManager *manager, QObject *parent) : QStandardItemModel (parent), Manager(manager)
{
    setColumnCount(3);
    connect(Manager, SIGNAL(itemsChanged()), this, SLOT(onItemChanged()));
}

QVariant BipperModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::BackgroundRole)
        return Constants::Colors[index.row()%Constants::Colors.size()];

    if(role == Qt::EditRole || role == Qt::DisplayRole)
    {
        if(index.column() == 0)
        {
            int s = Manager->item(index.row())->seconds();
            return QTime(s/60, s%60);
        }
        if(index.column() == 1)
        {
            return Manager->item(index.row())->occurences();
        }
    }
    return QVariant();
}

bool BipperModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole || index.row()>=Manager->itemsCount())
        return false;

    if(index.column() == 0)
    {
        int k = -value.toTime().secsTo(QTime(0,0));
        k/=60;
        qDebug()<<k;
        Manager->item(index.row())->setSeconds(k);
    }

}

Qt::ItemFlags BipperModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void BipperModel::onItemChanged()
{
    setRowCount(Manager->itemsCount());
    emit dataChanged(index(0,0), index(rowCount(), 3));
}
