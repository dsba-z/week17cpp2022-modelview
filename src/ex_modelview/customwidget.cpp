#include "customwidget.h"

#include <QPainter>

CustomWidget::CustomWidget(QWidget* parent)
    : QWidget(parent)
{
}

void CustomWidget::paintEvent(QPaintEvent* /* event */)
{
    QPainter painter(this);
    painter.setBrush(Qt::GlobalColor::gray);
    painter.drawRect(QRect(0, 0, this->width() - 1, this->height() - 1));
}
