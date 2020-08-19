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
    Q_PROPERTY(bool IsPlaying READ isPlaying WRITE setIsPlaying NOTIFY isPlayingChanged)

    Q_PROPERTY(int MaxTime READ maxTime WRITE setMaxTime NOTIFY maxTimeChanged)
    Q_PROPERTY(int CompleteCycleTime READ completeCycleTime NOTIFY completeCycleTimeChanged)
public:
    BipperManager(QObject* parent = nullptr);

    int itemsCount()const;
    QList<BipperItem*> getItems() const;
    BipperItem* item(int i);

    int currentTime() const;

    bool isPlaying() const;
    void setIsPlaying(bool b);

    int maxTime() const;
    void setMaxTime(int value);

    int getSequenceTotalTime() const;

    int completeCycleTime() const;

public slots:
    void onDataChanged();
    void playSound(int i);
    void onAddTriggered();
    void onDeleteTriggered();

    void onResetTriggered();
    void switchIsPlaying();
private slots:
    void onTick();
signals:
    void currentTimeChanged();
    void isPlayingChanged();
    void itemsChanged();
    void maxTimeChanged();
    void completeCycleTimeChanged();
private:
    QList<BipperItem*> Items;

    QSound* CurrentSound;

    QTimer* Timer;
    int CurrentTime;

    bool IsPlaying;

    int MaxTime;
};

#endif // BIPPERMANAGER_H
