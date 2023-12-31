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
#include <QPoint>
#include <QSplitter>

SerialCommunicationDialog::SerialCommunicationDialog(QWidget *parent) : QDialog(parent)
{
    // Set the title of the dialog
    setWindowTitle("Serial communication");

    // Set the minimum and maximum sizes for the dialog
    setMinimumSize(1980, 1080); // Adjust the values according to your needs
    setMaximumSize(2560, 1440);

    //Set up the layout
    auto *mainSplitter = new QSplitter(Qt::Horizontal, this);
    auto *mainLayout = new QHBoxLayout(this);

    // Set up the labels and other objects
    serialCommunication = new QLabel("Serial communication<br> for smart screen", this);
    fileLabel = new QLabel("Choose a file to resize:", this);
    resizeImageLabel = new QLabel("Resize image. Left Mouse Click for resizing and Right Mouse Click for moving.", this);
    transparentCircleWidget = new TransparentCircleWidget(this);
    fileButton = new QPushButton("Choose File", this);
    fileButton->setFixedHeight(30);  // Set the desired height
    fileButton->setFixedWidth(100);  // Set the desired width
    connect(fileButton, &QPushButton::clicked, this, &SerialCommunicationDialog::chooseFile);
    upButton = new QPushButton("↑", this);
    upButton->setFixedSize(30,30);
    connect(upButton, &QPushButton::clicked, this, &SerialCommunicationDialog::moveUp);
    leftButton = new QPushButton("←", this);
    leftButton->setFixedSize(30,30);
    connect(leftButton, &QPushButton::clicked, this, &SerialCommunicationDialog::moveLeft);
    rightButton = new QPushButton("→", this);
    rightButton->setFixedSize(30,30);
    connect(rightButton, &QPushButton::clicked, this, &SerialCommunicationDialog::moveRight);
    downButton = new QPushButton("↓", this);
    connect(downButton, &QPushButton::clicked, this, &SerialCommunicationDialog::moveDown);
    downButton->setFixedSize(30,30);
    resetButton = new QPushButton("Reset to 0,0", this);
    connect(resetButton, &QPushButton::clicked, this, &SerialCommunicationDialog::reset);
    decreaseImageSizeButton = new QPushButton("-", this);
    decreaseImageSizeButton->setFixedSize(30,30);
    connect(decreaseImageSizeButton, &QPushButton::clicked, this, &SerialCommunicationDialog::decreaseImageSize);
    increaseImageSizeButton = new QPushButton("+", this);
    increaseImageSizeButton->setFixedSize(30,30);
    connect(increaseImageSizeButton, &QPushButton::clicked, this, &SerialCommunicationDialog::increaseImageSize);
    connectButton = new QPushButton("Connect to Serial Port", this);
    //connectButton->setFixedSize(30,150);  // Set the desired height
    connect(connectButton, &QPushButton::clicked, this, &SerialCommunicationDialog::connectToSerialPort);

    // Set up the QGraphicsView
    imageView = new QGraphicsView(this);
    imageView->setRenderHint(QPainter::Antialiasing);
    imageView->setRenderHint(QPainter::SmoothPixmapTransform);
    imageScene = new QGraphicsScene(this);
    imageScene->setBackgroundBrush(Qt::transparent);  // Add this line
    pixmapItem = new QGraphicsPixmapItem;
    imageScene->addItem(pixmapItem);
    imageView->setScene(imageScene);
    imageView->setMouseTracking(true);
    imageView->installEventFilter(this);
    transparentCircleWidget->hide();

    //Set up the left layout as a grid for better Ui
    auto *leftLayout = new QGridLayout;
    leftLayout->setRowMinimumHeight(0, 10);
    leftLayout->addWidget(serialCommunication, 0, 0);
    leftLayout->addWidget(fileLabel, 1,0);
    leftLayout->addWidget(fileButton, 2,0);
    leftLayout->addWidget(upButton, 3,0);
    leftLayout->setAlignment(upButton, Qt::AlignHCenter | Qt::AlignVCenter);
    leftLayout->addWidget(leftButton, 4,0);
    leftLayout->setAlignment(leftButton, Qt::AlignLeft);
    leftLayout->addWidget(rightButton, 4,0);
    leftLayout->setAlignment(rightButton, Qt::AlignRight);
    leftLayout->addWidget(downButton, 5,0);
    leftLayout->setAlignment(downButton, Qt::AlignHCenter | Qt::AlignVCenter);
    leftLayout->addWidget(resetButton, 6,0);
    leftLayout->setAlignment(resetButton, Qt::AlignLeft);
    leftLayout->addWidget(decreaseImageSizeButton, 7,0);
    leftLayout->setAlignment(decreaseImageSizeButton, Qt::AlignLeft);
    leftLayout->addWidget(increaseImageSizeButton, 7,0);
    leftLayout->setAlignment(increaseImageSizeButton, Qt::AlignRight);
    leftLayout->addWidget(connectButton, 10,0);
    leftLayout->setSpacing(-400);
    leftLayout->setSizeConstraint(QLayout::SetFixedSize);


    // Set up the left layout with a grid
    auto *rightLayout = new QGridLayout;
    rightLayout->setRowMinimumHeight(0, 10);
    rightLayout->addWidget(resizeImageLabel, 0, 0);
    rightLayout->addWidget(imageView,  1, 0);
    rightLayout->addWidget(transparentCircleWidget, 1, 0);
    rightLayout->setAlignment(transparentCircleWidget, Qt::AlignHCenter | Qt::AlignVCenter);
    rightLayout->setSizeConstraint(QLayout::SetFixedSize);

    mainSplitter->addWidget(leftLayoutWidget(leftLayout));
    mainSplitter->addWidget(rightLayoutWidget(rightLayout));


    // Add the mainSplitter to the mainLayout
    mainLayout->addWidget(mainSplitter);

    // Adjust alignment of the layout
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);


    // Set Layout
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    adjustSize();

}
QWidget *SerialCommunicationDialog::leftLayoutWidget(QLayout *leftLayout)
{
    auto *leftLayoutWidget = new QWidget;
    leftLayoutWidget->setLayout(leftLayout);
    return leftLayoutWidget;
}

QWidget *SerialCommunicationDialog::rightLayoutWidget(QLayout *rightLayout)
{
    auto *rightLayoutWidget = new QWidget;
    rightLayoutWidget->setLayout(rightLayout);
    return rightLayoutWidget;
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
        if (!originalPixmap.isNull()) {

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
        imageView->setFixedSize(1500, 1000);
        pixmapItem->setPos(0, 0);

        // Ensure that the transparent circle is on top of the loaded image
        transparentCircleWidget->raise();
        transparentCircleWidget->show();
    }
    }
    else
    {
        // No file selected, hide the TransparentCircleWidget
        transparentCircleWidget->hide();
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
            handleMouseMove(static_cast<QMouseEvent*>(event));
        }
        else if (event->type() == QEvent::MouseButtonPress)
        {
            handleMouseMove(static_cast<QMouseEvent*>(event));
        }
    }

    return QObject::eventFilter(obj, event);
}

void SerialCommunicationDialog::handleMouseMove(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        // Resize the image based on mouse movement from the bottom right corner
        int newWidth = event->pos().x() - pixmapItem->pos().x();
        int newHeight = event->pos().y() - pixmapItem->pos().y();

        pixmapItem->setPixmap(originalPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio));
    }
    else if (event->buttons() & Qt::RightButton)
    {
        // Move the image within the grid
        int imageWidth = pixmapItem->pixmap().width();
        int imageHeight = pixmapItem->pixmap().height();

        int offSetX = imageWidth/2;

        // Calculate the new position of the top-left corner of the image
        int newX = (event->pos().x()) - (imageHeight) ;
        int newY = (event->pos().y() ) - (imageWidth/2);

        // Set the new position of the image without bounds checking
        pixmapItem->setPos(newX, newY);

    }
}

void SerialCommunicationDialog::showEvent(QShowEvent *event)
{
    // Call the base class implementation
    QDialog::showEvent(event);

    // Set the position of the layout when the dialog is shown
    layout()->setGeometry(QRect(0, 5, 200, 100));
}

void SerialCommunicationDialog::moveUp() {
    int newWidth = pixmapItem->pos().x();
    int newHeight = pixmapItem->pos().y() - 5;
    pixmapItem->setPos(newWidth, newHeight);
}

void SerialCommunicationDialog::reset() {
    pixmapItem->setPos(0, 0);
}

void SerialCommunicationDialog::moveDown() {
    int newWidth = pixmapItem->pos().x();
    int newHeight = pixmapItem->pos().y() + 5;
    pixmapItem->setPos(newWidth, newHeight);
}

void SerialCommunicationDialog::moveLeft() {
    int newWidth = pixmapItem->pos().x() - 5;
    pixmapItem->setPos(newWidth, pixmapItem->pos().y());
}

void SerialCommunicationDialog::moveRight() {
    int newWidth = pixmapItem->pos().x() + 5;
    pixmapItem->setPos(newWidth, pixmapItem->pos().y());
}

void SerialCommunicationDialog::decreaseImageSize() {
    int newWidth = pixmapItem->pixmap().width() - 5;
    int newHeight = pixmapItem->pixmap().height() - 5;
    pixmapItem->setPixmap(originalPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio));
}

void SerialCommunicationDialog::increaseImageSize() {
    int newWidth = pixmapItem->pixmap().width() + 5;
    int newHeight = pixmapItem->pixmap().height() + 5;
    pixmapItem->setPixmap(originalPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio));
}




