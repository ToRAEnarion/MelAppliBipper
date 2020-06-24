#ifndef MAPPLIDISPLAY_H
#define MAPPLIDISPLAY_H

#include <QFrame>
#include "struct.h"

class MAppliDisplay : public QFrame
{
public:
    MAppliDisplay(QWidget* parent = nullptr);
    void setSeconds(int *value);
    void setValues(QList<Item> *value);
    void setRange(int start, int length);
    void update();
protected:
    void paintEvent(QPaintEvent* e);

private:
    int* Seconds;
    QList<Item> *Values;

    int Min;
    int Length;
};

#endif // MAPPLIDISPLAY_H
