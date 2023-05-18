#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    _model = new ExampleModel();
    ui->setupUi(this);

    ui->tableView->setModel(_model);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete _model;
}

