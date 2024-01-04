// SerialCommunication.cpp
#include "SerialCommunication.h"
#include <QDebug>
#include <QBuffer>

SerialCommunication::SerialCommunication(QObject *parent) : QObject(parent)
{
    // Set other default serial port settings if needed
    serialPort.setPortName("/dev/ttyUSB0");
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

void SerialCommunication::writeToSerialPort(const QString &imagePath)
{
    QImage image(imagePath);
    if (image.isNull()) {
        emit errorOccurred("Failed to load image");
        return;
    }

    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    if (!serialPort.open(QIODevice::ReadWrite)) {
        emit errorOccurred("Failed to open serial port");
        return;
    }

    qint64 bytesWritten = serialPort.write(imageData);
    if (bytesWritten == -1) {
        emit errorOccurred("Failed to write image data to serial port");
        return;
    }

    emit imageSentSuccessfully();
    serialPort.close();
}