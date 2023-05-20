#include "addrowdialog.h"
#include "ui_addrowdialog.h"

AddRowDialog::AddRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRowDialog)
{
    ui->setupUi(this);
}

AddRowDialog::~AddRowDialog()
{
    delete ui;
}


QList<QVariant> AddRowDialog::getDataRow()
{
    QList<QVariant> dataRow;
    dataRow.append(1);
    dataRow.append(bool(ui->checkBoxSurvived->checkState()));
    dataRow.append(ui->comboBoxPClass->currentText().toInt());
    dataRow.append(ui->lineEditName->text());
    dataRow.append(ui->spinBoxAge->value());
    // additional data checks
    // return success / failure
    // throw an exception

    return dataRow;
}
