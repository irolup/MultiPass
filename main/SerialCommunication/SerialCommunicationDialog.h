#ifndef SERIALCOMMUNICATIONDIALOG_H
#define SERIALCOMMUNICATIONDIALOG_H

#include <QDialog>
#include <QShowEvent>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QSlider>
#include <QPoint>
#include "TransparentCircleWidget.h"

class QLabel;
class SerialCommunicationDialog : public QDialog
{
Q_OBJECT

public:
    explicit SerialCommunicationDialog(QWidget *parent = nullptr);

private slots:
    void chooseFile();
    void connectToSerialPort();
    void updateImageSize(int value);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void handleMouseMove(QMouseEvent *event);
    void showEvent(QShowEvent *event) override;
private:
    QLabel *serialCommunication;
    QLabel *fileLabel;
    QLabel *resizeImageLabel;
    QPushButton *fileButton;
    QPushButton *connectButton;
    QGraphicsView *imageView;
    QGraphicsScene *imageScene;
    QGraphicsPixmapItem *pixmapItem;
    QPixmap originalPixmap;
    TransparentCircleWidget *transparentCircleWidget;
    QWidget *leftLayoutWidget(QLayout *leftLayout);
    QWidget *rightLayoutWidget(QLayout *rightLayout);


};

#endif // SERIALCOMMUNICATIONDIALOG_H