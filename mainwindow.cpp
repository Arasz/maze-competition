#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "Types.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),socket(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket=new QTcpSocket(this);

    for(int i=0;i<7;i++)
        for(int j=0;j<4;j++)
            ui->robotVisionTable->setItem(j,i,new QTableWidgetItem("?"));
    for(int i=0;i<7;i++)
        ui->robotVisionTable->setColumnWidth(i,30);
    for(int i=0;i<4;i++)
        ui->robotVisionTable->setRowHeight(i,30);

}

MainWindow::~MainWindow()
{
    socket->close();
    delete ui;
    delete robot;
}

void MainWindow::on_pushButton_clicked()
{
    socket->abort();
    socket->connectToHost(ui->addressEdit->text(),ui->portEdit->text().toInt());
    if(socket->isWritable())
    {
        ui->pushButtonFastForward->setEnabled(true);
        ui->pushButtonForward->setEnabled(true);
        ui->pushButtonRush->setEnabled(true);
        ui->pushButtonWait->setEnabled(true);
        ui->pushButtonRotateLeft->setEnabled(true);
        ui->pushButtonRotateRight->setEnabled(true);
        socketStream.setDevice(socket);
        connect(socket,SIGNAL(readyRead()),this,SLOT(new_message()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(client_disconnected()));
        robot = new Robot();
    }
}

void MainWindow::on_pushButtonRush_clicked()
{
    if(socket->isWritable())
        socketStream<<"Rush"<<endl;

}

void MainWindow::on_pushButtonFastForward_clicked()
{
    if(socket->isWritable())
        socketStream<<"FastForward"<<endl;
}

void MainWindow::on_pushButtonForward_clicked()
{
    if(socket->isWritable())
        socketStream<<"Forward"<<endl;
}

void MainWindow::on_pushButtonWait_clicked()
{
    if(socket->isWritable())
        socketStream<<"Wait"<<endl;
}

void MainWindow::on_pushButtonRotateLeft_clicked()
{
    if(socket->isWritable())
        socketStream<<"RotateLeft"<<endl;
}

void MainWindow::on_pushButtonRotateRight_clicked()
{
    if(socket->isWritable())
        socketStream<<"RotateRight"<<endl;
}

void MainWindow::new_message()
{

    if(socket->isReadable())
    {
        QString localMap;
        localMap=socketStream.readLine();
        ui->rotationEdit->setText(localMap.mid(0,1));
        ui->translationEdit->setText(localMap.mid(2,1));
        for(int i=0;i<4;i++)
            for(int j=0;j<7;j++)
                ui->robotVisionTable->item(3-i,j)->setText(localMap.mid(4+i*7+j,1));
        //your code goes here
        robot->GetInformations(ui->rotationEdit->text(),
                ui->translationEdit->text(),localMap.mid(4));
        ActionsList actions = robot->MakeDecisions();

        for(auto action: actions)
        {
            if(socket->isWritable())
                socketStream<<action<<endl;
        }
    }

}

void MainWindow::client_disconnected()
{
    disconnect(socket,SIGNAL(readyRead()),this,SLOT(new_message()));
    disconnect(socket,SIGNAL(disconnected()),this,SLOT(client_disconnected()));
    socket->abort();
}
