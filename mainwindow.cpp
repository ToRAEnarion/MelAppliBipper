#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Qt>
#include <QTimer>
#include <QSound>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Manager = new BipperManager(this);
    connect(Manager, SIGNAL(isPlayingChanged()), this, SLOT(updateButtons()));
    connect(Manager, SIGNAL(currentTimeChanged()), this, SLOT(updateClock()));

    Constants::init();

    Model = new BipperModel(Manager, this);
    connect(Model, SIGNAL(itemChanged(QStandardItem *)), this, SLOT(onDataChanged()));

    Clock = new QLabel();
    Clock->setText("00:00");

    // Attach the model to the view
    ui->table->setModel(Model);

    ui->display->setRange(0,3600);

    connect(
        ui->mainToolBar->addAction(QIcon(":/icons/add"), "add"), SIGNAL(triggered()),
        this, SLOT(onAddTriggered()));
    ui->mainToolBar->addSeparator();

    connect(
        ui->mainToolBar->addAction(QIcon(":/icons/delete"), "delete"), SIGNAL(triggered()),
        this, SLOT(onDeleteTriggered()));


    ui->mainToolBar->addWidget(Clock);

//    ui->display->setValues(&Items);
 //   ui->display->setSeconds(&Elapsed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTable()
{
    QList<BipperItem*> items = Manager->getItems();
    Model->setRowCount(items.size());
    for(int row = 0; row < items.size(); row++)
    {
        QModelIndex index = Model->index(row,0,QModelIndex());
        Model->setData(index, items[row]->seconds());
        Model->setData(index, Constants::Colors[row%Constants::Colors.size()], Qt::BackgroundRole);
        index = Model->index(row,1,QModelIndex());
        Model->setData(index, Constants::Colors[row%Constants::Colors.size()], Qt::BackgroundRole);
        Model->setData(index, items[row]->occurences());
        index = Model->index(row,2,QModelIndex());
        Model->setData(index, Constants::Colors[row%Constants::Colors.size()], Qt::BackgroundRole);
        Model->setData(index, "--");
    }

    ui->display->repaint();
}

void MainWindow::onDataChanged()
{
    QList<BipperItem*> items = Manager->getItems();
   /* while(items.size() <Model->rowCount())
        items.append(Item());

    while(Items.size()>Model->rowCount())
        Items.removeLast();*/

    for (int i= 0;i<Model->rowCount();i++)
    {
   /*     QModelIndex idx = Model->index(i,0);
        items[i].Time = Model->data(idx, Qt::EditRole).toTime();

        idx = Model->index(i,1);
        items[i].N = Model->data(idx, Qt::EditRole).toInt();*/
    }

    updateTable();
    ui->display->update();
}

void MainWindow::onAddTriggered()
{
    Manager->onAddTriggered();
    updateTable();
}

void MainWindow::onDeleteTriggered()
{

}

void MainWindow::on_playButton_pressed()
{
    Manager->switchIsPlaying();
}

void MainWindow::on_previousButton_pressed()
{
    Manager->onResetTriggered();
    ui->display->repaint();
}

void MainWindow::on_timeMax_valueChanged(int k)
{
    Manager->setMaxTime(k);
}

void MainWindow::updateButtons()
{
    ui->playButton->setIcon(Manager->isPlaying() ? QIcon(":/icons/pause") : QIcon(":/icons/play"));
    ui->mainToolBar->setEnabled(!Manager->isPlaying());
    ui->timeMax->setEnabled(!Manager->isPlaying());
}

void MainWindow::updateClock()
{
    Clock->setText(QTime(Manager->currentTime()/60, Manager->currentTime()%60).toString("hh:mm"));
}
