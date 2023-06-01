#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include "customwidget.h"

namespace Ui
{
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget* parent = nullptr);
    ~AboutDialog();

    // QList<QVariant> getDataRow();

private:
    Ui::AboutDialog* ui;
    CustomWidget* _logo;
};

#endif// ABOUTDIALOG_H
