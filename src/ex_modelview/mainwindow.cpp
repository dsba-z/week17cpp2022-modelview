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
    _aboutDialog = new AboutDialog(this);
    _proxy = new MyProxy(this);
    _proxy->setSourceModel(_model);

    ui->tableView->setModel(_proxy);
    ui->tableView->setSortingEnabled(true);

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
    QObject::connect(ui->minAgeButton, &QPushButton::clicked, this, &MainWindow::setMinFilterAge);

    _currentFolder = loadCurrentFolderFromFile();
}


void MainWindow::setMinFilterAge()
{
    int newMinAge = ui->lineEdit->text().toInt();
    _proxy->setMinAge(newMinAge);
}
// bool MySortFilterProxyModel::lessThan(const QModelIndex &left,
//                                       const QModelIndex &right) const
// {
//     QVariant leftData = sourceModel()->data(left);
//     QVariant rightData = sourceModel()->data(right);
//     return leftData < rightData;
// }

// bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow,
//                                               const QModelIndex &sourceParent) const
// {
//     QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
//     QModelIndex index1 = sourceModel()->index(sourceRow, 1, sourceParent);
//     QModelIndex index2 = sourceModel()->index(sourceRow, 2, sourceParent);

//     return (sourceModel()->data(index0).toString().contains(filterRegularExpression())
//             || sourceModel()->data(index1).toString().contains(filterRegularExpression()))
//             && dateInRange(sourceModel()->data(index2).toDate());
// }
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
