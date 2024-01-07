#ifndef CONNECTIONSETTINGSDIALOG_H
#define CONNECTIONSETTINGSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "SerialCommunicationDialog.h"
#include "SerialCommunication.h"
#include <QSerialPortInfo>

class SerialCommunicationDialog;

class ConnectionSettingsDialog : public QDialog
{
Q_OBJECT

public:
    explicit ConnectionSettingsDialog(SerialCommunicationDialog *parentDialog);

private slots:
    // Add any slots or functions relevant to your connection settings dialog

private:
    SerialCommunicationDialog *serialCommunicationDialogInstance;
    SerialCommunication *serialCommunicationInstance;
    QString selectedcomPortString;
    QString serialPortName;
    QLabel *selectedcomPortLabel;
    QVBoxLayout *layout;
};

#endif // CONNECTIONSETTINGSDIALOG_H