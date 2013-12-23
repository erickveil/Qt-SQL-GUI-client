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
    QString name=this->ui->tb_name->text();
    queryAge(name);
}

QString MainWindow::getDBFile()
{
    QMessageBox mb;
    QString db_file=this->ui->tb_db_name->text();

    if(db_file==""){
        mb.setText("Error: Database not selected.");
        mb.exec();
    }
    return db_file;
}

void MainWindow::setDB()
{
    QMessageBox mb;
    QString db_file=getDBFile();
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
}

void MainWindow::queryAge(QString name)
{
    setDB();
    QMessageBox mb;
    QString age="";

    if(name==""){
        mb.setText("Error: No lookup name provided.");
        mb.exec();
        return;
    }

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
    this->ui->tb_mod_age->setText(age);
    this->ui->tb_mod_name->setText(name);
}

void MainWindow::on_bu_add_record_clicked()
{
    QString name=this->ui->tb_add_name->text();
    QString age=this->ui->tb_add_age->text();
    setDB();
    QMessageBox mb;

    if(name==""){
        mb.setText("Error: No insert name provided.");
        mb.exec();
        return;
    }

    if(age==""){
        mb.setText("Error: No insert age provided.");
        mb.exec();
        return;
    }

    QSqlQuery query("insert into data (name, age) values(?, ?)");
    query.bindValue(0,name);
    query.bindValue(1,age);

    if(!query.exec()){
        printf("%s: insert fail\n",__PRETTY_FUNCTION__);
        mb.setText(query.lastError().text());
        mb.exec();
        return;
    }

    printf("%s: insert succeed\n",__PRETTY_FUNCTION__);
    mb.setText("Insert successful!");
    mb.exec();
}

void MainWindow::on_bu_mod_record_clicked()
{
    QString name=this->ui->tb_mod_name->text();
    QString age=this->ui->tb_mod_age->text();
    setDB();
    QMessageBox mb;

    if(name==""){
        mb.setText("Error: No modification name queried.");
        mb.exec();
        return;
    }

    if(age==""){
        mb.setText("Error: No modification age provided.");
        mb.exec();
        return;
    }

    QSqlQuery query("update data set age=? where name=?");
    query.bindValue(0,age);
    query.bindValue(1,name);

    if(!query.exec()){
        printf("%s: modify fail\n",__PRETTY_FUNCTION__);
        mb.setText(query.lastError().text());
        mb.exec();
        return;
    }

    printf("%s: modify succeed\n",__PRETTY_FUNCTION__);
    mb.setText("Redord modification successful!");
    mb.exec();
}
