#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

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



void MainWindow::on_bu_search_clicked()
{
    QString db_file=this->ui->tb_db_name->text();
    QString name=this->ui->tb_name->text();
    QMessageBox mb;
    QString age="";

    if(db_file==""){
        mb.setText("Error: Database not selected.");
        mb.exec();
        return;
    }

    else if(name==""){
        mb.setText("Error: No lookup name provided.");
        mb.exec();
        return;
    }

    QSqlDatabase db;

    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_file);

    if( !db.open() ){
        printf("%s: open result fail\n",__PRETTY_FUNCTION__);
        mb.setText(db.lastError().text());
        mb.exec();
        return;
    }

    printf("%s: open result success\n",__PRETTY_FUNCTION__);

    QSqlQuery query("select age from data where name=?");
    query.bindValue(0,name);
    if(!query.exec()){

        printf("%s: query fail\n",__PRETTY_FUNCTION__);
        mb.setText(query.lastError().text());
        mb.exec();
        return;
    }

    printf("%s: query succeed\n",__PRETTY_FUNCTION__);

    while (query.next()){
        age=query.value(0).toString();
        printf("%s: query result: %s\n",__PRETTY_FUNCTION__,age.toStdString().c_str());
    }

    this->ui->tb_age->setText(age);
}
