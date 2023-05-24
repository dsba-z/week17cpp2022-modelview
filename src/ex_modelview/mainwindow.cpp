#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addrowdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>


QString loadCurrentFolderFromFile()
{
    QFile inputFile("./settings_file.txt");
    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        return QString("");
    }
    QTextStream inputStream(&inputFile);

    return inputStream.readLine(); 
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new ExampleModel(this);
    ui->tableView->setModel(_model);
    ui->listView->setModel(_model);
    ui->listView->setModelColumn(3);



    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openDataFile);
    QObject::connect(ui->pushButtonAddRow, &QPushButton::clicked, this, &MainWindow::openAddRowDialog);
    QObject::connect(ui->pushButtonRemoveRow, &QPushButton::clicked, this, &MainWindow::removeModelRow);
    QObject::connect(ui->listView, &QAbstractItemView::clicked, this, &MainWindow::highlightDataItem);
    QObject::connect(ui->tableView, &QAbstractItemView::clicked, this, &MainWindow::highlightDataItem);

    _currentFolder = loadCurrentFolderFromFile();
}

QString extractDir(QString file)
{
    return file;
}

void saveCurrentFolderToFile(QString _currentFolder)
{
    QFile outputFile("./settings_file.txt");
    if (!outputFile.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    QTextStream outputStream(&outputFile);
    outputStream << _currentFolder;
}

void MainWindow::openDataFile()
{
    if (_currentFolder.isEmpty())
    {
        _currentFolder = ".";
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Open data file", _currentFolder, "*.csv");
    QMessageBox::warning(this, "Error", fileName, QMessageBox::Ok);

    _currentFolder = extractDir(fileName);
    saveCurrentFolderToFile(_currentFolder);


    if (!_model->reloadDataFromFile(fileName))
    {
        QMessageBox::warning(this, "Error", "Cannot open file", QMessageBox::Ok);
    }
}

void MainWindow::highlightDataItem(const QModelIndex& clickIndex)
{
    int row = clickIndex.row();
    QModelIndex index = _model->index(row, 3);
    ui->labelNameData->setText(_model->data(index).toString());
    index = _model->index(row, 1);
    ui->labelSurvivedData->setText(_model->data(index).toString());
}


void MainWindow::openAddRowDialog()
{
    AddRowDialog dialog;
    if (dialog.exec())
    {
        QList<QVariant> dataRow = dialog.getDataRow();
        _model->appendRow(dataRow);
    }
}

void MainWindow::removeModelRow()
{
    int rowIndex = ui->spinBoxRemove->value();
    // QModelIndex removeIndex = ui->listView->currentIndex();
    // int rowToRemove = removeIndex.row();
    
    if (!_model->removeRow(rowIndex))
    {
        QMessageBox::warning(this, "Error", "Incorrect index (doesn't exist)", QMessageBox::Ok);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
