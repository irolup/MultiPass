#include "TransparentCircleWidget.h"
#include <QPainter>
#include <QPainterPath>

TransparentCircleWidget::TransparentCircleWidget(QWidget *parent) : QWidget(parent), opacity(0) {
    int diameter = 480;  // Set the diameter of the circular widget
    setFixedSize(diameter, diameter);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground, false);
    // Calculate the initial position based on the radius
    int radius = diameter / 2;
    int initialX = -radius;  // Adjust this based on your desired center
    int initialY = -radius;  // Adjust this based on your desired center

    // Set the initial position
    move(initialX, initialY);
}

void TransparentCircleWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Create a circular clipping path
    QPainterPath path;

    int radius = width() / 2;  // Set the radius to half of the widget width
    int centerX = width() / 2;
    int centerY = height() / 2;

    path.addEllipse(centerX - radius, centerY - radius, 2 * radius, 2 * radius);
    painter.setClipPath(path);

    painter.setOpacity(1);
// Draw the red perimeter square
    painter.setPen(QPen(Qt::red, 2));  // Set the pen color to red and width to 2
    painter.drawRect(centerX - radius, centerY - radius, 2 * radius, 2 * radius);

    painter.setBrush(Qt::transparent);
    painter.drawEllipse(centerX - radius, centerY - radius, 2 * radius, 2 * radius);

}



