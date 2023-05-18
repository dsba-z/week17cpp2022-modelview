#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    _model = new ExampleModel();
    ui->setupUi(this);

    ui->tableView->setModel(_model);

    // ui->actionOpen;

    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);

}

// on_actionOpen_triggered

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".");
    // _model->getDataFromFile(fileName);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _model;
}

