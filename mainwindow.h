#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bu_select_file_clicked();

    void on_bu_search_clicked();

    void on_bu_add_record_clicked();

private:
    QSqlDatabase db;
    Ui::MainWindow *ui;
    //void fillList();
    void setDB();
    void queryAge(QString name);
    QString getDBFile();
};

#endif // MAINWINDOW_H
