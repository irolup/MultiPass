// SerialCommunication.h
#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QImage>

class SerialCommunication : public QObject
{
Q_OBJECT

public:
    explicit SerialCommunication(QObject *parent = nullptr);
    ~SerialCommunication();

    void openSerialPort(const QString &portName);
    void closeSerialPort();
    void writeToSerialPort(const QString &imagePath);

private:
    QSerialPort serialPort;

    signals:
        void imageSentSuccessfully();
        void errorOccurred(const QString &errorMessage);
};

#endif // SERIALCOMMUNICATION_H