#include "TransparentCircleWidget.h"
#include <QPainter>
#include <QPainterPath>

TransparentCircleWidget::TransparentCircleWidget(QWidget *parent) : QWidget(parent), opacity(0) {
    setFixedSize(480, 480);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground, false);
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

    // Draw a white background
    painter.fillRect(rect(), Qt::white);

    // Create a circular clipping path
    QPainterPath path;


    int radius = qMin(width(), height()) / 4;
    int centerX = width() / 2;
    int centerY = height() / 2;

    path.addEllipse(centerX - radius, centerY - radius, 2 * radius, 2 * radius);
    painter.setClipPath(path);

    painter.setOpacity(1);

    painter.setBrush(Qt::transparent);
    painter.drawEllipse(centerX - radius, centerY - radius, 2 * radius, 2 * radius);
}

void TransparentCircleWidget::mousePressEvent(QMouseEvent *event){
    //Emit a signal to notify the click event
    emit widgetClicked(event->pos());
}

