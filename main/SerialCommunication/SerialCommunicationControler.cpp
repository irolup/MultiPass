//
// Created by charlie on 04/01/24.
//

#include "SerialCommunicationControler.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    // Connect the signals from ImageSender to Controller
    connect(&imageSender, &SerialCommunication::imageSentSuccessfully, this, &Controller::processingFinished);
    connect(&imageSender, &SerialCommunication::errorOccurred, this, &Controller::processingError);
    // Connect the button click signal to the slot in Controller

}

Controller::~Controller()
{
    // Disconnect signals if needed
}

void Controller::processImage(const QString &imagePath)
{
    // Optionally, perform additional processing on imagePath

    // Call ImageSender to send the image
    imageSender.writeToSerialPort(imagePath);
}
