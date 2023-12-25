#include "TransparentCircleWidget.h"
#include <QPainter>

TransparentCircleWidget::TransparentCircleWidget(QWidget *parent) : QWidget(parent)
{
}

void TransparentCircleWidget::updateSize(int width, int height)
{
    setFixedSize(width, height);
}
void TransparentCircleWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Dessiner un fond blanc
    painter.fillRect(rect(), Qt::white);

    // Dessiner un cercle transparent
    int circleSize = 480;
    int x = (width() - circleSize) / 2;
    int y = (height() - circleSize) / 2;

    painter.setBrush(QBrush(Qt::transparent));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(x, y, circleSize, circleSize);
}