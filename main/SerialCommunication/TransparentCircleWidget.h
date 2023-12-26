#ifndef TRANSPARENTCIRCLEWIDGET_H
#define TRANSPARENTCIRCLEWIDGET_H

#include <QWidget>
#include <QPainterPath>

class TransparentCircleWidget : public QWidget
{
Q_OBJECT

public:
    TransparentCircleWidget(QWidget *parent = nullptr);

public slots:
    void updateSize(int width, int height);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    qreal opacity;

};

#endif // TRANSPARENTCIRCLEWIDGET_H