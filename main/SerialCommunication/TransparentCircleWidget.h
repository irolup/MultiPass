#ifndef TRANSPARENTCIRCLEWIDGET_H
#define TRANSPARENTCIRCLEWIDGET_H

#include <QWidget>
#include <QPainterPath>
#include <QMouseEvent>

class TransparentCircleWidget : public QWidget
{
Q_OBJECT

public:
    TransparentCircleWidget(QWidget *parent = nullptr);

public slots:
    void updateSize(int width, int height);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event);

private:
    qreal opacity;

    signals:
    void widgetClicked(const QPoint);

};

#endif // TRANSPARENTCIRCLEWIDGET_H