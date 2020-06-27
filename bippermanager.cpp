#include "bippermanager.h"


BipperManager::BipperManager(QObject *parent) : QObject(parent),
    CurrentSound(nullptr),
    CurrentTime(0),
    MaxTime(0)
{
    Constants::init();
}

QList<BipperItem *> BipperManager::getItems() const
{
    return Items;
}

int BipperManager::currentTime() const
{
    return CurrentTime;
}


void BipperManager::onDataChanged()
{
/*    while(Items.size() <Model->rowCount())
        Items.append(Item());

    while(Items.size()>Model->rowCount())
        Items.removeLast();

    for (int i= 0;i<Model->rowCount();i++)
    {
        QModelIndex idx = Model->index(i,0);
        Items[i].Time = Model->data(idx, Qt::EditRole).toTime();

        idx = Model->index(i,1);
        Items[i].N = Model->data(idx, Qt::EditRole).toInt();
    }

    updateTable();
    ui->display->update();
    */
}


void BipperManager::setIsPlaying(bool b)
{
    if(IsPlaying == b)
        return;
    IsPlaying = b;
    if(b)
    {
        Timer->start(1000);
    }
    else
    {
        Timer->stop();
    }
    emit isPlayingChanged();
}

bool BipperManager::isPlaying() const
{
    return IsPlaying;
}


void BipperManager::onAddTriggered()
{
    Items.append(new BipperItem(this));
    emit itemsChanged();
}

void BipperManager::onDeleteTriggered()
{
    emit itemsChanged();
}

void BipperManager::onResetTriggered()
{
    setIsPlaying(false);
    CurrentTime = 0;
    emit currentTimeChanged();
}


void BipperManager::onTick()
{
    CurrentTime++;
    int offset = 0;
    for(int i=0;i<Items.size();i++)
    {
        int s = Items[i]->seconds();
        int t = s + offset;
        if(((CurrentTime-offset) % s) == 0 &&
                ((CurrentTime-offset) /s) <= Items[i]->occurences())
        {
            playSound(0);
        }
        offset += s*Items[i]->occurences();
    }

    emit currentTimeChanged();
}

int BipperManager::maxTime() const
{
    return MaxTime;
}

void BipperManager::setMaxTime(int value)
{
    if(MaxTime != value)
    {
        MaxTime = value;
        maxTimeChanged();
    }
}

void BipperManager::playSound(int i)
{
    if(CurrentSound)
    {
        CurrentSound->stop();
        CurrentSound->deleteLater();
    }

    CurrentSound = new QSound(Constants::Sounds[i%Constants::Sounds.size()]);
    CurrentSound->play();
}

