#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    _logo = new CustomWidget(ui->widgetLogoContainer);

    QHBoxLayout* hboxLayout;
    hboxLayout = new QHBoxLayout(ui->widgetLogoContainer);
    ui->widgetLogoContainer->setLayout(hboxLayout);
    hboxLayout->addWidget(_logo);

    
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(_logo->sizePolicy().hasHeightForWidth());
    _logo->setSizePolicy(sizePolicy);

    // ui->horizontalLayout->addWidget(_logo);
    // ui->horizontalLayout->removeWidget(ui->label);


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
