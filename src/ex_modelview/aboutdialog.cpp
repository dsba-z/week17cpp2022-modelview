#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    _logo = new CustomWidget(ui->widgetLogoContainer);

    ui->horizontalLayout->addWidget(_logo);

    
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
    delete ui;
}

