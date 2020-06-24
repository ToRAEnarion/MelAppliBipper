#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Qt>
#include <QTimer>
#include <QSound>
#include <QDebug>


QList<QColor> Constants::Colors = QList<QColor>() ;
QList<QString> Constants::Sounds = QList<QString>();


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    CurrentSound(nullptr),
    Elapsed(0)
{
    ui->setupUi(this);
    Timer = new QTimer(this);
    connect(Timer, &QTimer::timeout, this, &MainWindow::onTick);
    setIsPlaying(false);

    Constants::Colors.append(QColor::fromRgb(255,175,175));
    Constants::Colors.append(QColor::fromRgb(175,255,175));
    Constants::Colors.append(QColor::fromRgb(175,175,255));
    Constants::Colors.append(QColor::fromRgb(255,150,255));
    Constants::Colors.append(QColor::fromRgb(150,255,255));

    Constants::Sounds.append(":/sounds/bip1");

    Model = new QStandardItemModel(0,3,this);
    connect(Model, SIGNAL(itemChanged(QStandardItem *)), this, SLOT(onDataChanged()));

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

    ui->display->setValues(&Items);
    ui->display->setSeconds(&Elapsed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setIsPlaying(bool b)
{
    IsPlaying = b;
    if(b)
    {
        ui->playButton->setIcon(QIcon(":/icons/pause"));
        Timer->start(1000);
    }
    else
    {
        ui->playButton->setIcon(QIcon(":/icons/play"));
        Timer->stop();
    }

    ui->mainToolBar->setEnabled(!b);
}

void MainWindow::updateTable()
{
    Model->setRowCount(Items.size());
    for(int row = 0; row < Items.size(); row++)
    {
        QModelIndex index = Model->index(row,0,QModelIndex());
        Model->setData(index, Items[row].Time);
        Model->setData(index, Constants::Colors[row%Constants::Colors.size()], Qt::BackgroundRole);
        index = Model->index(row,1,QModelIndex());
        Model->setData(index, Constants::Colors[row%Constants::Colors.size()], Qt::BackgroundRole);
        Model->setData(index, Items[row].N);
        index = Model->index(row,2,QModelIndex());
        Model->setData(index, Constants::Colors[row%Constants::Colors.size()], Qt::BackgroundRole);
        Model->setData(index, "--");
    }

    ui->display->repaint();
}

void MainWindow::playSound(int i)
{
    if(CurrentSound)
    {
        CurrentSound->stop();
        CurrentSound->deleteLater();
    }

    CurrentSound = new QSound(Constants::Sounds[i%Constants::Sounds.size()]);
    CurrentSound->play();
}

void MainWindow::onDataChanged()
{
    while(Items.size() <Model->rowCount())
        Items.append(Item());

    while(Items.size()>Model->rowCount())
        Items.removeLast();

    for (int i= 0;i<Model->rowCount();i++)
    {
        QModelIndex idx = Model->index(i,0);
        Items[i].Time = Model->data(idx, Qt::EditRole).toTime();

        idx = Model->index(i,1);
        Items[i].N = Model->data(idx, Qt::EditRole).toInt();
    }

    updateTable();
    ui->display->update();
}

void MainWindow::onAddTriggered()
{
    Items.append(Item());
    updateTable();
}

void MainWindow::onDeleteTriggered()
{

}

void MainWindow::on_playButton_pressed()
{
    setIsPlaying(!IsPlaying);
}

void MainWindow::on_previousButton_pressed()
{
    Elapsed = 0;
    setIsPlaying(!IsPlaying);
    ui->display->repaint();
}

void MainWindow::onTick()
{
    Elapsed++;
    int offset = 0;
    for(int i=0;i<Items.size();i++)
    {
        int s = Items[i].getSeconds();
        int t = s + offset;
        if(((Elapsed-offset) % s) == 0 &&
                ((Elapsed-offset) /s) <= Items[i].N)
        {
            playSound(0);
        }
        offset += s*Items[i].N;
    }

    ui->display->update();
}
