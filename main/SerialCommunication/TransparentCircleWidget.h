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

protected:
    void paintEvent(QPaintEvent *event) override;
    //void mousePressEvent(QMouseEvent *event);

private:
    qreal opacity;

    signals:


};

#endif // TRANSPARENTCIRCLEWIDGET_H