#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <check.h>
#include <aut.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("疯狂化学");
    connect(ui->tocheck,SIGNAL(clicked()),this,SLOT(showCheck()));
    connect(ui->toauto,SIGNAL(clicked()),this,SLOT(showAuto()));
    checkPage = new check();
    autoPage= new aut();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::putwidget(QWidget *widget)
{
    ui->horizontalLayout->addWidget(widget);
}
void MainWindow::delLayout()
{
    QLayoutItem *child;
    while ((child = ui->horizontalLayout->takeAt(0)) != 0)
    {
        //setParent为NULL，防止删除之后界面不消失
        if(child->widget())
        {
            child->widget()->setParent(NULL);
        }
        delete child;
    }
}
void MainWindow::showCheck()
{
    //qDebug()<<"SHOW!!!!\n";
    delLayout();
    putwidget(checkPage);
}
void MainWindow::showAuto()
{
    //qDebug()<<"SHOW2!!!!\n";
    delLayout();
    putwidget(autoPage);
}
