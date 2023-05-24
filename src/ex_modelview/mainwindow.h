#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "examplemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void openDataFile();
    void openAddRowDialog();
    void removeModelRow();
    void highlightDataItem(const QModelIndex& index);

private:
    Ui::MainWindow* ui;
    ExampleModel* _model;

    QString _currentFolder;
};
#endif// MAINWINDOW_H
