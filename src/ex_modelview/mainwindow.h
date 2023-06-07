#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "examplemodel.h"
#include <QMainWindow>
#include <QSortFilterProxyModel>

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

private:
    Ui::MainWindow* ui;

    ExampleModel* _model;
    QSortFilterProxyModel* _proxy;

private slots:
    void openFile();
    void on_addNewRowButton_clicked();

};
#endif// MAINWINDOW_H
