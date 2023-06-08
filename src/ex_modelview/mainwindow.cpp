#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    _model = new ExampleModel();
    _proxy = new MyProxy();
    ui->setupUi(this);

    _proxy->setSourceModel(_model);
    ui->tableView->setModel(_proxy);
    ui->tableView->setSortingEnabled(true);

    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    // QObject::connect(ui->slider, &QSlider::valueChanged, this, &MainWindow::changeMaxFilter);

}

// on_actionOpen_triggered

void MainWindow::openFile()
{
    // QFileDialog* fdialog = new QFileDialog(this);
    // fdialog.open();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", "*.csv");
    _model->loadDataFromFile(fileName);
}

// void setFilterSlot(int value)
// {
//     _proxy->setFilter(value);
// }


void MainWindow::on_addNewRowButton_clicked()
{
    QMessageBox::warning(this, "Success", "Button clicked", QMessageBox::Ok);
}



MainWindow::~MainWindow()
{
    delete ui;
}

