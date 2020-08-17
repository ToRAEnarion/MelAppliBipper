#include "bippermanager.h"
#include <QDebug>

BipperManager::BipperManager(QObject *parent) : QObject(parent),
    CurrentSound(nullptr),
    CurrentTime(0),
    IsPlaying(false),
    MaxTime(0)
{
    Constants::init();
    Timer = new QTimer(this);
    connect(Timer, &QTimer::timeout, this, &BipperManager::onTick);

    onAddTriggered();
}

int BipperManager::itemsCount() const
{
    return Items.size();
}

QList<BipperItem *> BipperManager::getItems() const
{
    return Items;
}

BipperItem *BipperManager::item(int i)
{
    return Items[i];
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

void BipperManager::switchIsPlaying()
{
    setIsPlaying(!IsPlaying);
}


void BipperManager::onTick()
{
    CurrentTime++;

    if(MaxTime>0 && CurrentTime >= MaxTime)
    {
        playSound(-1);
        onResetTriggered();
        return;
    }

    int workingTime = CurrentTime;
    if(MaxTime>0)
    {
        int seq = getSequenceTotalTime();
        workingTime = CurrentTime % seq;
    }

    int offset = 0;
    for(int i=0;i<Items.size();i++)
    {
        int s = Items[i]->seconds();
        int t = s + offset;
        if(((workingTime - offset) % s) == 0 &&
                ((workingTime - offset) /s) <= Items[i]->occurences())
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
        qDebug()<<"set mx time "<<value;
        MaxTime = value;
        emit maxTimeChanged();
        emit completeCycleTimeChanged();
    }
}

int BipperManager::getSequenceTotalTime() const
{
    int t = 0;
    for (int i=0;i<Items.size();i++)
    {
        t += Items[i]->seconds() * Items[i]->occurences();
    }
    return t;
}

int BipperManager::completeCycleTime() const
{
    if(MaxTime<1)
        return 60;
    return MaxTime;
}

void BipperManager::playSound(int i)
{
    if(CurrentSound)
    {
        CurrentSound->stop();
        CurrentSound->deleteLater();
    }


    if(i<0)
    {
        CurrentSound = new QSound(Constants::SoundEnd);
        CurrentSound->play();
        return;
    }

    CurrentSound = new QSound(Constants::Sounds[i%Constants::Sounds.size()]);
    CurrentSound->play();
}

