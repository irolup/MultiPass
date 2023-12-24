#include "SerialCommunicationDialog.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFileDialog>

SerialCommunicationDialog::SerialCommunicationDialog(QWidget *parent) : QDialog(parent)
{
    // Set up the labels for left layout
    serialCommunication = new QLabel("Serial communication<br> for smart screen", this);

    fileLabel = new QLabel("Choose a file to resize:", this);

    fileButton = new QPushButton("Choose File", this);
    connect(fileButton, &QPushButton::clicked, this, &SerialCommunicationDialog::chooseFile);

    connectButton = new QPushButton("Connect to Serial Port", this);
    connect(connectButton, &QPushButton::clicked, this, &SerialCommunicationDialog::connectToSerialPort);



    // Set up the left layout
    auto *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(serialCommunication);
    leftLayout->addWidget(fileLabel);
    leftLayout->addWidget(fileButton);
    leftLayout->addWidget(connectButton);

    leftLayout->addSpacing(1);

    // Set up the left layout with a grid
    auto *rightLayout = new QGridLayout;

    // Set up the main layout
    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    //Ajust aligment of the layout
    mainLayout->setAlignment(leftLayout, Qt::AlignTop);
    mainLayout->setAlignment(rightLayout, Qt::AlignTop);
    //SetLayout
    setLayout(mainLayout);
    // Set the distance between the left layout and the window's border
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Set the size of the dialog
    setFixedSize(1000, 700);
    // Set the title of the dialog
    setWindowTitle("Serial communication");
}

void SerialCommunicationDialog::chooseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Choose a file", "", "All Files (*.*);;Text Files (*.txt)");
    if (!filePath.isEmpty())
    {
        // You can use filePath as needed
        fileLabel->setText("Selected file: " + filePath);
    }
}

void SerialCommunicationDialog::connectToSerialPort()
{
    // Implement the connection to the serial port here
}




void SerialCommunicationDialog::showEvent(QShowEvent *event) {
    // Call the base class implementation
    QDialog::showEvent(event);

    // Set the position of the layout when the dialog is shown
    layout()->setGeometry(QRect(0, 5, 200, 100));
}