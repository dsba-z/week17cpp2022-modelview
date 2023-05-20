#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include "addrowdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new ExampleModel(this);
    ui->tableView->setModel(_model);
    ui->listView->setModel(_model);
    ui->listView->setModelColumn(3);

    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openDataFile);
    QObject::connect(ui->pushButtonAddRow, &QPushButton::clicked, this, &MainWindow::openAddRowDialog);
    QObject::connect(ui->pushButtonRemoveRow, &QPushButton::clicked, this, &MainWindow::removeModelRow);
}

void MainWindow::openDataFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open data file", ".", "*.csv");
    if(!_model->reloadDataFromFile(fileName))
    {
        QMessageBox::warning(this, "Error", "Cannot open file", QMessageBox::Ok);
    }
}

void MainWindow::openAddRowDialog()
{
    AddRowDialog dialog;
    if(dialog.exec())
    {
        QList<QVariant> dataRow = dialog.getDataRow();
        _model->appendRow(dataRow);

    }
}

void MainWindow::removeModelRow()
{
    int rowIndex = ui->spinBoxRemove->value();
    _model->removeRow(rowIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

