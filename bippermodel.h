#ifndef BIPPERMODEL_H
#define BIPPERMODEL_H

#include <QStandardItemModel>
#include "bippermanager.h"

class BipperModel : public QStandardItemModel
{
    Q_OBJECT
public:
    BipperModel(BipperManager* manager, QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
private slots:
    void onItemChanged();
private:
    BipperManager* Manager;
};

#endif // BIPPERMODEL_H
