//
// Created by charlie on 04/01/24.
//

#ifndef MULTIPASS_SERIALCOMMUNICATIONCONTROLER_H
#define MULTIPASS_SERIALCOMMUNICATIONCONTROLER_H
#include "SerialCommunication.h"
#include "SerialCommunicationDialog.h"
#include <QObject>

class Controller : public QObject
{
Q_OBJECT

public:
    Controller(QObject *parent = nullptr);
    ~Controller();

    void processImage(const QString &imagePath);

private:
    SerialCommunication imageSender;
    SerialCommunicationDialog selectedImagePath;
    QString currentImagePath;

signals:
    void processingFinished();
    void processingError(const QString &errorMessage);
};

#endif // MULTIPASS_SERIALCOMMUNICATIONCONTROLER_H