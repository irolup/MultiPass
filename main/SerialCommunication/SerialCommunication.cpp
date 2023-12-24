// SerialCommunication.cpp
#include "SerialCommunication.h"
#include <QDebug>

SerialCommunication::SerialCommunication(QObject *parent) : QObject(parent)
{
    // Set other default serial port settings if needed
    serialPort.setBaudRate(QSerialPort::Baud9600);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
}

SerialCommunication::~SerialCommunication()
{
    if (serialPort.isOpen()) {
        serialPort.close();
        qDebug() << "Serial port closed.";
    }
}

void SerialCommunication::openSerialPort(const QString &portName)
{
    serialPort.setPortName(portName);

    if (serialPort.open(QIODevice::ReadWrite)) {
        qDebug() << "Serial port opened successfully.";
    } else {
        qDebug() << "Error opening serial port: " << serialPort.errorString();
    }
}

void SerialCommunication::closeSerialPort()
{
    if (serialPort.isOpen()) {
        serialPort.close();
        qDebug() << "Serial port closed.";
    }
}

qint64 SerialCommunication::writeToSerialPort(const QByteArray &data)
{
    if (serialPort.isOpen()) {
        qint64 bytesWritten = serialPort.write(data);
        qDebug() << bytesWritten << " bytes written.";
        return bytesWritten;
    } else {
        qDebug() << "Serial port is not open.";
        return -1;
    }
}