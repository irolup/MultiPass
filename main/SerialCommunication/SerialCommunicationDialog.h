#ifndef SERIALCOMMUNICATIONDIALOG_H
#define SERIALCOMMUNICATIONDIALOG_H

#include <QDialog>
#include <QShowEvent>
#include <QPushButton>

class QLabel;
class SerialCommunicationDialog : public QDialog
{
Q_OBJECT

public:
    explicit SerialCommunicationDialog(QWidget *parent = nullptr);

private slots:
    void chooseFile();
    void connectToSerialPort();

protected:
    void showEvent(QShowEvent *event) override;
private:
    QLabel *serialCommunication;
    QLabel *fileLabel;
    QPushButton *fileButton;
    QPushButton *connectButton;

};

#endif // SERIALCOMMUNICATIONDIALOG_H