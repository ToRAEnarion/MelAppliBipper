#ifndef BIPPERMANAGER_H
#define BIPPERMANAGER_H

#include <QObject>
#include "bipperitem.h"
#include <QSound>
#include <QTimer>
#include "struct.h"

class BipperManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int CurrentTime READ currentTime NOTIFY currentTimeChanged)
    Q_PROPERTY(int IsPlaying READ isPlaying WRITE setIsPlaying NOTIFY currentTimeChanged)

    Q_PROPERTY(int MaxTime READ maxTime WRITE setMaxTime NOTIFY maxTimeChanged)
public:
    BipperManager(QObject* parent);
    QList<BipperItem*> getItems() const;

    int currentTime() const;

    bool isPlaying() const;
    void setIsPlaying(bool b);

    int maxTime() const;
    void setMaxTime(int value);

private:
    void playSound(int i);
public slots:
    void onDataChanged();

    void onAddTriggered();
    void onDeleteTriggered();

    void onResetTriggered();
private slots:
    void onTick();
signals:
    void currentTimeChanged();
    void isPlayingChanged();
    void itemsChanged();
    void maxTimeChanged();
private:
    QList<BipperItem*> Items;

    QSound* CurrentSound;

    QTimer* Timer;
    int CurrentTime;

    bool IsPlaying;

    int MaxTime;
};

#endif // BIPPERMANAGER_H
