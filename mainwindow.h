#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QStandardItemModel>
#include "struct.h"
#include "bippermanager.h"
#include "bippermodel.h"
#include <QLabel>

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
private slots:
    void onDataChanged();
    void onAddTriggered();
    void onDeleteTriggered();

    void on_playButton_pressed();
    void on_previousButton_pressed();
    void on_timeMax_valueChanged(int k);

    void updateButtons();
    void updateClock();
private:
    Ui::MainWindow *ui;
    BipperManager* Manager;
    BipperModel *Model;
    QLabel* Clock;
};

#endif // MAINWINDOW_H
