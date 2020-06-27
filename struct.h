#ifndef STRUCT_H
#define STRUCT_H

#include <QTime>
#include <QColor>
#include <QList>


struct Constants
{
    static QList<QColor> Colors;
    static QList<QString> Sounds;

    static void init()
    {
        if(!IsInit)
        {
            IsInit = true;

            Constants::Colors.append(QColor::fromRgb(255,175,175));
            Constants::Colors.append(QColor::fromRgb(175,255,175));
            Constants::Colors.append(QColor::fromRgb(175,175,255));
            Constants::Colors.append(QColor::fromRgb(255,150,255));
            Constants::Colors.append(QColor::fromRgb(150,255,255));

            Constants::Sounds.append(":/sounds/bip1");
        }
    }

private:
    static bool IsInit;
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
