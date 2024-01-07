// ConnectionSettingsDialog.cpp

#include "ConnectionSettingsDialog.h"

ConnectionSettingsDialog::ConnectionSettingsDialog(SerialCommunicationDialog *parentDialog)
        : QDialog(parentDialog), serialCommunicationDialogInstance(parentDialog)
{
    // Access the selected COM Port from the parentDialog
    selectedcomPortString = serialCommunicationDialogInstance->getSelectedComPort();

    selectedcomPortLabel = new QLabel("Selected COM Port: " + selectedcomPortString, this);

    layout = new QVBoxLayout(this);
    layout->addWidget(selectedcomPortLabel);

    setLayout(layout);
    setWindowTitle("Connection Settings");
}