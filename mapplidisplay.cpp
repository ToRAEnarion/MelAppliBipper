#include "mapplidisplay.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

MAppliDisplay::MAppliDisplay(QWidget* parent) : QFrame (parent), Values(nullptr), Seconds(nullptr)
{

}

void MAppliDisplay::setSeconds(int *value)
{
    Seconds = value;
}


void MAppliDisplay::setRange(int start, int length)
{
    Min = start;
    Length = length;
}

void MAppliDisplay::update()
{
    repaint();
}

void MAppliDisplay::paintEvent(QPaintEvent *e)
{
    if(Values == nullptr || Seconds == nullptr)
        return;

    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawLine(0,0,0,height());
    painter.drawLine(width(),0,width(),height());
    painter.drawLine(0, height()/2,width(),height()/2);

    float scale = 3;

    painter.save();
    for (int i=0;i<Values->size();i++)
    {
        for (int j=0;j<Values->at(i).N;j++)
        {
            QColor c = Constants::Colors[i%Constants::Colors.size()];
            c = QColor::fromHsv(c.hue(), 255, c.value()).darker(130);
            painter.setPen(c);
            int s = Values->at(i).getSeconds();
            painter.drawLine(s*scale*(j+1), 4, s*scale*(j+1), height()-4);
        }

    }
    painter.restore();
    painter.drawEllipse(QRect((*Seconds)*scale-4, height()/2-4, 8, 8));

  //  painter.end();
}

void MAppliDisplay::setValues(QList<Item> *value)
{
    Values = value;
}
