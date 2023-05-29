#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    _logo = new QLabel(ui->widgetLogoContainer);
    _logo->setText("Logo text");
}

AboutDialog::~AboutDialog()
{
    // delete ui;
}


// QList<QVariant> AboutDialog::getDataRow()
// {
//     // QList<QVariant> dataRow;
//     // dataRow.append(1);
//     // dataRow.append(bool(ui->checkBoxSurvived->checkState()));
//     // dataRow.append(ui->comboBoxPClass->currentText().toInt());
//     // dataRow.append(ui->lineEditName->text());
//     // dataRow.append(ui->spinBoxAge->value());
//     // additional data checks
//     // return success / failure
//     // throw an exception

//     return dataRow;
// }
