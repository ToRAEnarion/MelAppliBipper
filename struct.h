#ifndef STRUCT_H
#define STRUCT_H

#include <QTime>
#include <QColor>
#include <QList>


struct Constants
{
    static QList<QColor> Colors;
    static QList<QString> Sounds;
};

struct Item
{
    Item(): Time(1,0),N(1)
    {}

    int getSeconds() const
    {
        return Time.hour()*60 +Time.minute();
    }

    QTime Time;
    int N;
    char Mode;
};

#endif // STRUCT_H
