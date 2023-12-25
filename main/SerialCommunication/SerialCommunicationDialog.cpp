#include "SerialCommunicationDialog.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>

SerialCommunicationDialog::SerialCommunicationDialog(QWidget *parent) : QDialog(parent)
{
    // Set up the labels for left layout
    serialCommunication = new QLabel("Serial communication<br> for smart screen", this);

    fileLabel = new QLabel("Choose a file to resize:", this);

    fileButton = new QPushButton("Choose File", this);
    fileButton->setFixedHeight(30);  // Set the desired height
    fileButton->setFixedWidth(100);  // Set the desired width
    connect(fileButton, &QPushButton::clicked, this, &SerialCommunicationDialog::chooseFile);

    connectButton = new QPushButton("Connect to Serial Port", this);
    connectButton->setFixedHeight(30);  // Set the desired height
    connectButton->setFixedWidth(150);  // Set the desired width
    connect(connectButton, &QPushButton::clicked, this, &SerialCommunicationDialog::connectToSerialPort);

    sizeSlider = nullptr;

    // Set up the left layout
    // Set up the left layout
    auto *leftContainer = new QVBoxLayout;  // Create a container for the widgets that should be resized
    leftContainer->addWidget(serialCommunication);
    leftContainer->addWidget(fileLabel);
    leftContainer->addWidget(fileButton);
    leftContainer->addWidget(connectButton);

    if (!sizeSlider)
    {
        // Add a slider to the left container
        sizeSlider = new QSlider(Qt::Horizontal);
        sizeSlider->setMinimum(10);  // Minimum size percentage
        sizeSlider->setMaximum(100); // Maximum size percentage
        sizeSlider->setValue(10);   // Initial size percentage
        connect(sizeSlider, &QSlider::valueChanged, this, &SerialCommunicationDialog::updateImageSize);
        leftContainer->addWidget(sizeSlider);
    }

    leftContainer->addSpacing(1);

// Set up the right layout with QGraphicsView
    imageView = new QGraphicsView(this);
    imageScene = new QGraphicsScene(this);
    pixmapItem = new QGraphicsPixmapItem;

    imageScene->addItem(pixmapItem);
    imageView->setScene(imageScene);
    imageView->setMouseTracking(true);
    imageView->installEventFilter(this);
    leftContainer->addWidget(imageView);

    transparentCircleWidget = new TransparentCircleWidget(this);
    leftContainer->addWidget(transparentCircleWidget);

// Set up the left layout with a grid
    auto *rightLayout = new QGridLayout;

    // Set the flags to make the dialog resizable from the corner
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);

    // Set the minimum and maximum sizes for the dialog
    setMinimumSize(800, 700); // Adjust the values according to your needs
    setMaximumSize(3000, 1300); // Adjust the values according to your needs

    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftContainer);  // Use the leftContainer instead of leftLayout
    mainLayout->addLayout(rightLayout);
// Adjust aligment of the layout
    mainLayout->setAlignment(leftContainer, Qt::AlignTop);
    mainLayout->setAlignment(rightLayout, Qt::AlignTop);
// SetLayout
    setLayout(mainLayout);
    // Set the distance between the left layout and the window's border
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Set the size of the dialog

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

        // Load the image into the QGraphicsView
        originalPixmap.load(filePath);

        // Calculate the available space in the layout
        int maxWidth = imageView->maximumWidth();
        int maxHeight = imageView->maximumHeight();

        // Resize the image to fit within the available space
        int newWidth = originalPixmap.width();
        int newHeight = originalPixmap.height();

        if (newWidth > maxWidth || newHeight > maxHeight)
        {
            // Calculate the aspect ratio
            qreal aspectRatio = qreal(newWidth) / qreal(newHeight);

            // Adjust width or height to fit within the available space
            if (newWidth > maxWidth)
            {
                newWidth = maxWidth;
                newHeight = int(newWidth / aspectRatio);
            }

            if (newHeight > maxHeight)
            {
                newHeight = maxHeight;
                newWidth = int(newHeight * aspectRatio);
            }
        }

        // Resize the image
        pixmapItem->setPixmap(originalPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio));
        imageScene->setSceneRect(pixmapItem->pixmap().rect());

        // Resize the QGraphicsView
        imageView->setFixedSize(newWidth, newHeight);

        // Position the QGraphicsView above the "Connect to Serial Port" button
        auto *leftLayout = dynamic_cast<QVBoxLayout *>(layout());
        if (leftLayout)
        {
            leftLayout->addWidget(imageView);
            leftLayout->addWidget(connectButton);
        }

        int initialCircleSizePercentage = 10;  // Adjust the percentage as needed
        int initialCircleWidth = newWidth * initialCircleSizePercentage / 100;
        int initialCircleHeight = newHeight * initialCircleSizePercentage / 100;

        // Set the maximum size for the transparent circle based on a percentage of the image size
        int maxCircleSizePercentage = 30;  // Adjust the percentage as needed
        int maxCircleWidth = newWidth * maxCircleSizePercentage / 100;
        int maxCircleHeight = newHeight * maxCircleSizePercentage / 100;

        if (initialCircleWidth > maxCircleWidth || initialCircleHeight > maxCircleHeight)
        {
            // Adjust initial circle size if it exceeds the maximum size
            initialCircleWidth = maxCircleWidth;
            initialCircleHeight = maxCircleHeight;
        }

        // Set the fixed size for the transparent circle
        transparentCircleWidget->setFixedSize(initialCircleWidth, initialCircleHeight);

        // Calculate the offset to center the circle within the image
        int xOffset = (newWidth - initialCircleWidth) / 2;
        int yOffset = (newHeight - initialCircleHeight) / 2;

        // Move and show the transparent circle
        transparentCircleWidget->move(imageView->pos() + QPoint(xOffset, yOffset));
        transparentCircleWidget->show();
    }
}

void SerialCommunicationDialog::connectToSerialPort()
{
    // Implement the connection to the serial port here
}

bool SerialCommunicationDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == imageView)
    {
        if (event->type() == QEvent::MouseMove)
        {
            // Handle mouse move event for selection or resizing
            handleMouseMove(static_cast<QMouseEvent*>(event));
        }
        else if (event->type() == QEvent::MouseButtonPress)
        {
            // Handle mouse press event for selection or resizing
            handleMouseMove(static_cast<QMouseEvent*>(event));
        }
    }

    return QObject::eventFilter(obj, event);
}

void SerialCommunicationDialog::handleMouseMove(QMouseEvent *event)
{
    // Check if the left mouse button is pressed
    if (event->buttons() & Qt::LeftButton)
    {
        // Resize the image and transparent circle based on mouse movement
        int newWidth = event->pos().x() - pixmapItem->pos().x();
        int newHeight = event->pos().y() - pixmapItem->pos().y();

        // Update the size of the image and transparent circle
        pixmapItem->setPixmap(originalPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio));
        transparentCircleWidget->updateSize(newWidth, newHeight);
    }
}
void SerialCommunicationDialog::updateImageSize(int value)
{
    if (!originalPixmap.isNull())
    {
        // Update the size of the image and transparent circle based on the slider value
        int newWidth = originalPixmap.width() * value / 100;
        int newHeight = originalPixmap.height() * value / 100;

        // Resize the image
        pixmapItem->setPixmap(originalPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio));
        imageScene->setSceneRect(pixmapItem->pixmap().rect());

        // Resize the QGraphicsView
        imageView->setFixedSize(newWidth, newHeight);

        // Update the position of the transparent circle
        int xOffset = (newWidth - transparentCircleWidget->width()) / 2;
        int yOffset = (newHeight - transparentCircleWidget->height()) / 2;

        transparentCircleWidget->updateSize(newWidth, newHeight);
        transparentCircleWidget->move(imageView->pos() + QPoint(xOffset, yOffset));
    }
}

void SerialCommunicationDialog::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw a white background
    painter.fillRect(rect(), Qt::white);

    // Draw a transparent circle
    painter.setBrush(QBrush(Qt::transparent));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(rect());
}





void SerialCommunicationDialog::showEvent(QShowEvent *event) {
    // Call the base class implementation
    QDialog::showEvent(event);

    // Set the position of the layout when the dialog is shown
    layout()->setGeometry(QRect(0, 5, 200, 100));
}