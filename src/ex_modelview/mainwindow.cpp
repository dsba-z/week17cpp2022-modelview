#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addrowdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSlider>

const int NAME_COLUMN = 3;

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
    _aboutDialog = new AboutDialog(this);
    _proxy = new MyProxy(this);
    _proxy->setSourceModel(_model);

    ui->tableView->setModel(_proxy);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(1);
    ui->tableView->hideColumn(2);
    ui->tableView->hideColumn(6);
    ui->tableView->hideColumn(7);
    ui->tableView->hideColumn(8);
    ui->tableView->hideColumn(9);
    ui->tableView->hideColumn(10);
    ui->tableView->hideColumn(11);

    ui->listView->setModel(_model);
    ui->listView->setModelColumn(3);

    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openDataFile);
    QObject::connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::showAboutDialog);
    QObject::connect(ui->pushButtonAddRow, &QPushButton::clicked, this, &MainWindow::openAddRowDialog);
    QObject::connect(ui->pushButtonRemoveRow, &QPushButton::clicked, this, &MainWindow::removeModelRow);
    QObject::connect(ui->listView, &QAbstractItemView::clicked, this, &MainWindow::highlightDataItem);
    QObject::connect(ui->tableView, &QAbstractItemView::clicked, this, &MainWindow::highlightDataItem);

    QObject::connect(ui->minAgeSlider, &QSlider::valueChanged, this, &MainWindow::setMinFilterAge);
    QObject::connect(ui->minAgeLineEdit, &QLineEdit::textChanged, this, &MainWindow::setMinFilterAgeString);

    QObject::connect(ui->lineEditName, &QLineEdit::textChanged, this, &MainWindow::setName);

    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    QObject::connect(selectionModel, &QItemSelectionModel::currentRowChanged, this, &MainWindow::rowChangedSlot);


    QObject::connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addButtonSlot);

    _currentFolder = loadCurrentFolderFromFile();
}

void MainWindow::addButtonSlot()
{
    QPushButton* newButton = new QPushButton(ui->scrollArea);

    _extraButtons.append(newButton); 
    newButton->setText(QString::number(_extraButtons.size()));

    ui->scrollAreaWidgetContents->layout()->addWidget(newButton);
    QObject::connect(newButton, &QPushButton::clicked, this, &MainWindow::addButtonSlot);
}

void MainWindow::rowChangedSlot(QModelIndex current, QModelIndex previous)
{
    highlightDataItem(current);
}

void MainWindow::setMinFilterAge(int value)
{
    // int newMinAge = ui->lineEdit->text().toInt();
    
    ui->minAgeLineEdit->setText(QString::number(value));
    _proxy->setMinAge(value);
}

void MainWindow::setMinFilterAgeString(QString value)
{    
    // ui->minAgeLineEdit->setText(value);
    ui->minAgeSlider->setValue(value.toInt());
    _proxy->setMinAge(value.toInt());
}

QString extractDir(const QString& file)
{
    return file;
}

void saveCurrentFolderToFile(const QString& _currentFolder)
{
    QFile outputFile("./settings_file.txt");
    if (!outputFile.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    QTextStream outputStream(&outputFile);
    outputStream << _currentFolder;
}

void MainWindow::showAboutDialog()
{
    _aboutDialog->show();
}

void MainWindow::openDataFile()
{
    if (_currentFolder.isEmpty())
    {
        _currentFolder = ".";
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Open data file", _currentFolder, "*.csv");
    // QMessageBox::warning(this, "Error", fileName, QMessageBox::Ok);

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
    QModelIndex index = _proxy->index(row, 3);
    ui->lineEditName->setText(_proxy->data(index).toString());
    index = _proxy->index(row, 1);
    ui->labelSurvivedData->setText(_proxy->data(index).toString());
}


void MainWindow::openAddRowDialog()
{
    AddRowDialog dialog;
    if (dialog.exec())
    {
        QList<QVariant> dataRow = dialog.getDataRow();
        // _model->setData(row, 0, dataRow[0]);
        // _model->setData(row, 1, dataRow[1]);
        _model->appendRow(dataRow);
    }
}

void MainWindow::removeModelRow()
{
    // int rowIndex = ui->spinBoxRemove->value();
    QModelIndex removeIndex = ui->listView->currentIndex();
    int rowToRemove = removeIndex.row();

    
    
    if (!_model->removeRow(rowToRemove))
    {
        QMessageBox::warning(this, "Error", "Incorrect index (doesn't exist)", QMessageBox::Ok);
    }
}


// void MainWindow::setName(QString newText)
// {
//     QModelIndex currentItemProxy = ui->tableView->currentIndex();
//     QModelIndex currentItem = _proxy->mapToSource(currentItemProxy);
//     _model->setData(currentItem, newText);
// }

void MainWindow::setName(QString newText)
{
    QModelIndex currentItem = ui->tableView->currentIndex();
    int row = currentItem.row();

    QModelIndex nameItemProxy = _proxy->index(row, NAME_COLUMN);
    // _proxy->setData(nameItemProxy, newText);

    QModelIndex nameItemOriginal = _proxy->mapToSource(nameItemProxy);

    _model->setData(nameItemOriginal, newText);
}


MainWindow::~MainWindow()
{
    delete ui;
}
