#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("List of traveling salesman");

    col.loadFromFile("C:/Qt/MyProjects/oop-lab-work-2/output.txt");

    createTable(ui, col);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTable(Ui::MainWindow *ui, HTable<std::string, int> col) {
    ui->tableWidget->setRowCount(col.getSize());
    ui->tableWidget->setColumnCount(2);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Number" << "Key" << "Max value");
    for (int i = 0; i < col.getSize(); i++) {
        int number = i + 1;
        auto k = col.getKey(number);
        auto v = col.getValue(k);
        QTableWidgetItem *key = new QTableWidgetItem(QString::fromStdString(k));
        QTableWidgetItem *value = new QTableWidgetItem(QString::number(v));
        ui->tableWidget->setItem(i, 0, key);
        ui->tableWidget->item(i,0)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
        ui->tableWidget->setItem(i, 1, value);
        ui->tableWidget->item(i,1)->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    }

    auto size = col.getSize();
    auto cost = col.getSum();
    ui->label_size->setText("Total items: " + QString::number(size));
    ui->label_sum->setText("Total cost: " + QString::number(cost));
}

void MainWindow::on_btn_load_clicked()
{
    if (ui->LineEdit_loadFromFile->text().isEmpty()) {
        QMessageBox msg;
        msg.setText("Input path to loaded file.");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        return;
    }

    QString path = ui->LineEdit_loadFromFile->text();
    col.loadFromFile(path.toStdString());

    this->createTable(ui, col);

    QMessageBox msg;
    msg.setText("Data from file was loaded.");
    msg.setIcon(QMessageBox::Information);
    msg.exec();
    return;
}


void MainWindow::on_btn_save_clicked()
{
    if (ui->lineEdit_writeToFile->text().isEmpty()) {
        QMessageBox msg;
        msg.setText("Input path to saved file.");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        return;
    }

    QString path = ui->lineEdit_writeToFile->text();
    col.writeToFile(path.toStdString());
    this->createTable(ui, col);

    QMessageBox msg;
    msg.setText("Data was saved to file.");
    msg.setIcon(QMessageBox::Information);
    msg.exec();
    return;
}


void MainWindow::on_btn_insert_clicked()
{
    if (ui->lineEdit_key->text().isEmpty()) {
        QMessageBox msg;
        msg.setText("Input key.");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        return;
    }
    if (ui->lineEdit_value->text().isEmpty()) {
        QMessageBox msg;
        msg.setText("Input value.");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        return;
    }

    if (!ui->lineEdit_value->text().toInt()) {
        QMessageBox msg;
        msg.setText("Value must be integer.");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        return;
    }

    QString newKey = ui->lineEdit_key->text();
    int newValue = ui->lineEdit_value->text().toInt();
    col.insert(newKey.toStdString(), newValue);
    this->createTable(ui, col);

    ui->lineEdit_key->clear();
    ui->lineEdit_value->clear();
}


void MainWindow::on_btn_delete_clicked()
{
    if (ui->lineEdit_key->text().isEmpty()) {
        QMessageBox msg;
        msg.setText("Input key.");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        return;
    }

    QString newKey = ui->lineEdit_key->text();

    if (col.isKey(newKey.toStdString())) {
        col.remove(newKey.toStdString());
        this->createTable(ui, col);
    }
    else {
        QMessageBox msg;
        msg.setText("Input existing key.");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        return;
    }

    ui->lineEdit_key->clear();
}


void MainWindow::on_btn_clear_clicked()
{
    col.clear();
    this->createTable(ui, col);
}

