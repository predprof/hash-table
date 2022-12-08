#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include <QTableWidget>

#include "htable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createTable(Ui::MainWindow *ui, HTable<std::string, int> col);

private slots:
    void on_btn_load_clicked();

    void on_btn_save_clicked();

    void on_btn_insert_clicked();

    void on_btn_delete_clicked();

    void on_btn_clear_clicked();

private:
    Ui::MainWindow *ui;

    HTable<std::string, int> col;
};
#endif // MAINWINDOW_H
