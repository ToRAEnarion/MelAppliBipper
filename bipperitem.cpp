#include "bipperitem.h"

BipperItem::BipperItem(QObject *parent) : QObject(parent), Seconds(60), Occurences(1)
{

}

int BipperItem::occurences() const
{
    return Occurences;
}

void BipperItem::setOccurences(int value)
{
    Occurences = value;
}

int BipperItem::seconds() const
{
    return Seconds;
}


void BipperItem::setSeconds(int value)
{
    if(Seconds != value)
    {
        Seconds = value;
        emit secondsChanged();
    }
}
