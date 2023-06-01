#include "addrowdialog.h"
#include "ui_addrowdialog.h"

AddRowDialog::AddRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRowDialog)
{

    // if (!existingRow.isEmpty())
    // {
    //     if (existingRow[1].toBool())
    //     {
    //         ui->checkBoxSurvived->setCheckState(Qt::Checked);

    //     }
    //     else
    //     {

    //         ui->checkBoxSurvived->setCheckState(Qt::Unchecked);
    //     }

    //     ui->lineEditName->setText(existingRow[3].toString());
    // }
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
    dataRow.append(QString());
    dataRow.append(QString());
    dataRow.append(QString());
    dataRow.append(QString());
    dataRow.append(QString());
    dataRow.append(QString());
    // additional data checks
    // return success / failure
    // throw an exception

    return dataRow;
}
