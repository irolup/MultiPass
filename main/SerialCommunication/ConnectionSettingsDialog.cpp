#include "ConnectionSettingsDialog.h"

ConnectionSettingsDialog::ConnectionSettingsDialog(SerialCommunicationDialog *parentDialog)
        : QDialog(parentDialog), serialCommunicationDialogInstance(parentDialog)
{
    // Access the selected COM Port from the parentDialog
    selectedcomPortString = serialCommunicationDialogInstance->getSelectedComPort();

    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : serialPorts) {
        qDebug() << "Detected port:" << port.portName();
    }

    for (const QSerialPortInfo &port : serialPorts) {
        #ifdef Q_OS_LINUX
        if (port.portName().startsWith("tty")) {
            serialPortName = port.portName();
            break;
        }
        #elif defined(Q_OS_WIN)
        if (port.portName().startsWith("COM")) {
            serialPortName = port.portName();
            break;
        }
        #endif
    }

    if (serialPortName.isEmpty()) {
        qDebug() << "No suitable serial port found.";
    }

    selectedcomPortLabel = new QLabel("Available com port: " + serialPortName, this);

    layout = new QVBoxLayout(this);
    layout->addWidget(selectedcomPortLabel);

    setLayout(layout);
    setWindowTitle("Connection Settings");
}