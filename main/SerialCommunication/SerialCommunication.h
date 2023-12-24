// SerialCommunication.h
#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SerialCommunication : public QObject
{
Q_OBJECT

public:
    explicit SerialCommunication(QObject *parent = nullptr);
    ~SerialCommunication();

    void openSerialPort(const QString &portName);
    void closeSerialPort();
    qint64 writeToSerialPort(const QByteArray &data);

private:
    QSerialPort serialPort;
};

#endif // SERIALCOMMUNICATION_H