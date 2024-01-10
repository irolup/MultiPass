#ifndef SERIALCOMMUNICATIONDIALOG_H
#define SERIALCOMMUNICATIONDIALOG_H

#include <QDialog>
#include <QShowEvent>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsPixmapItem>
#include <QComboBox>
#include <QSlider>
#include <QPoint>
#include "TransparentCircleWidget.h"
#include "ConnectionSettingsDialog.h"

class QLabel;
class TransparentCircleWidget;
class ConnectionSettingsDialog; // Forward declaration
class SerialCommunicationDialog : public QDialog
{
Q_OBJECT

public:
    explicit SerialCommunicationDialog(QWidget *parent = nullptr);
    QString getSelectedComPort() const;
    QString selectedComPort;
private slots:
    void chooseFile();
    void connectToSerialPort();
    void moveUp();
    void moveLeft();
    void moveRight();
    void reset();
    void moveDown();
    void decreaseImageSize();
    void increaseImageSize();
    void exportImage();
    void openExportedImagesFolder();
    void selectFileToSend();
    // Add a new slot to update the selectedComPort variable when the combo box selection changes
    void updateSelectedComPort(int index);
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void handleMouseMove(QMouseEvent *event);
    void showEvent(QShowEvent *event) override;
private:
    QLabel *serialCommunication;
    QLabel *fileLabel;
    QLabel *resizeImageLabel;
    QLabel *comPortSelectorLabel;
    QComboBox *comPortComboBox;
    QPushButton *fileButton;
    QPushButton *connectButton;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *resetButton;
    QPushButton *exportImageButton;
    QPushButton *decreaseImageSizeButton;
    QPushButton *increaseImageSizeButton;
    QPushButton *imagePathFolderButton;
    QPushButton *selectFileToSendButton;
    QGraphicsView *imageView;
    QGraphicsScene *imageScene;
    QGraphicsPixmapItem *pixmapItem;
    QPixmap originalPixmap;
    QPixmap currentPixmap;
    TransparentCircleWidget *transparentCircleWidget;
    ConnectionSettingsDialog *connectionSettingsDialog;
    QGraphicsRectItem *markerItem;
    QWidget *leftLayoutWidget(QLayout *leftLayout);
    QWidget *rightLayoutWidget(QLayout *rightLayout);



};

#endif // SERIALCOMMUNICATIONDIALOG_H