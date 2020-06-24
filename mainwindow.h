#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QStandardItemModel>
#include <QSound>
#include "struct.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setIsPlaying(bool b);

    void updateTable();
    void playSound(int i);

private slots:
    void onDataChanged();
    void onAddTriggered();
    void onDeleteTriggered();

    void on_playButton_pressed();
    void on_previousButton_pressed();

    void onTick();

private:
    Ui::MainWindow *ui;
    QList<Item> Items;
    QStandardItemModel *Model;
    QSound* CurrentSound;

    QTimer* Timer;
    int Elapsed;

    bool IsPlaying;
};

#endif // MAINWINDOW_H
