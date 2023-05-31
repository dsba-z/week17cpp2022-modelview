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
    // QFileDialog* fdialog = new QFileDialog(this);
    // fdialog.open();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", "*.csv");
    _model->loadDataFromFile("../data/titanic.csv");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _model;
}

