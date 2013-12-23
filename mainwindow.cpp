#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bu_select_file_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Select Database"), "/home/");
    this->ui->tb_db_name->setText(fileName);
}


