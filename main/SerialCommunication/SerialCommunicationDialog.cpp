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
    setMinimumSize(1280, 960); // Adjust the values according to your needs
    setMaximumSize(3000, 1300);

    //Set up the layout
    auto *mainSplitter = new QSplitter(Qt::Horizontal, this);
    auto *mainLayout = new QHBoxLayout(this);

    // Set up the labels and other objects
    serialCommunication = new QLabel("Serial communication<br> for smart screen", this);
    fileLabel = new QLabel("Choose a file to resize:", this);
    resizeImageLabel = new QLabel("Resize image", this);
    transparentCircleWidget = new TransparentCircleWidget(this);
    fileButton = new QPushButton("Choose File", this);
    fileButton->setFixedHeight(30);  // Set the desired height
    fileButton->setFixedWidth(100);  // Set the desired width
    connectButton = new QPushButton("Connect to Serial Port", this);
    connectButton->setFixedHeight(30);  // Set the desired height
    connectButton->setFixedWidth(150);  // Set the desired width
    connect(fileButton, &QPushButton::clicked, this, &SerialCommunicationDialog::chooseFile);
    connect(connectButton, &QPushButton::clicked, this, &SerialCommunicationDialog::connectToSerialPort);

    // Set up the QGraphicsView
    imageView = new QGraphicsView(this);
    imageView->setViewport(new QWidget);
    imageView->setRenderHint(QPainter::Antialiasing);
    imageView->setRenderHint(QPainter::SmoothPixmapTransform);
    imageScene = new QGraphicsScene(this);
    imageScene->setBackgroundBrush(Qt::transparent);  // Add this line
    pixmapItem = new QGraphicsPixmapItem;
    imageScene->addItem(pixmapItem);
    imageView->setScene(imageScene);
    imageView->setMouseTracking(true);
    imageView->installEventFilter(this);

    //Set up the left layout as a grid for better Ui
    auto *leftLayout = new QGridLayout;
    leftLayout->setRowMinimumHeight(0, 10);
    leftLayout->addWidget(serialCommunication, 0, 0);
    leftLayout->addWidget(fileLabel, 1,0);
    leftLayout->addWidget(fileButton, 2,0);
    leftLayout->addWidget(connectButton, 3,0);
    leftLayout->setSpacing(-10);
    leftLayout->setSizeConstraint(QLayout::SetFixedSize);


    // Set up the left layout with a grid
    auto *rightLayout = new QGridLayout;
    rightLayout->setRowMinimumHeight(0, 10);
    rightLayout->addWidget(resizeImageLabel, 0, 0);
    rightLayout->addWidget(imageView,  1, 0);
    rightLayout->addWidget(transparentCircleWidget, 1, 0);
    rightLayout->setSpacing(-10);
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

        // Set initial position in the center of the grid
        int xOffset = (maxWidth - newWidth) / 2;
        int yOffset = (maxHeight - newHeight) / 2;
        pixmapItem->setPos(xOffset, yOffset);

        // Resize the QGraphicsView
        imageView->setFixedSize(newWidth, newHeight);

        // Show the TransparentCircleWidget after loading the image
        if (!transparentCircleWidget->isVisible())
        {
            // Set the fixed size for the transparent circle
            int initialCircleWidth = 50;  // Adjust the width as needed
            int initialCircleHeight = 50; // Adjust the height as needed

            transparentCircleWidget->setFixedSize(initialCircleWidth, initialCircleHeight);

            // Set a static position for the transparent circle
            int xOffset = 100;  // Adjust the x-coordinate as needed
            int yOffset = 100;  // Adjust the y-coordinate as needed

            // Move and show the transparent circle
            //transparentCircleWidget->move(xOffset, yOffset);
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
        // Resize the image based on mouse movement
        int newWidth = event->pos().x() - pixmapItem->pos().x();
        int newHeight = event->pos().y() - pixmapItem->pos().y();

        pixmapItem->setPixmap(originalPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio));


    }
    else if (event->buttons() & Qt::RightButton)
    {
        // Move the image within the grid
        QPoint newPos = event->pos().toPointF().toPoint();
        int maxX = 900 - pixmapItem->pixmap().width();
        int maxY = 900 - pixmapItem->pixmap().height();
        newPos.setX(qBound(0, newPos.x(), maxX));
        newPos.setY(qBound(0, newPos.y(), maxY));
        pixmapItem->setPos(newPos);
    }
}
void SerialCommunicationDialog::updateImageSize(int value)
{
    if (!originalPixmap.isNull())
    {
        // Calculate the new size based on the slider value
        int newWidth = originalPixmap.width() * value / 100;
        int newHeight = originalPixmap.height() * value / 100;

        // Resize the pixmapItem
        pixmapItem->setPixmap(originalPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio));

        // Update the scene rect
        imageScene->setSceneRect(QRectF(0, 0, newWidth, newHeight));

        // Update the position of the transparent circle
        int xOffset = (newWidth - transparentCircleWidget->width()) / 2;
        int yOffset = (newHeight - transparentCircleWidget->height()) / 2;

        transparentCircleWidget->updateSize(newWidth, newHeight);
        transparentCircleWidget->move(imageView->pos() + QPoint(xOffset, yOffset));

        // Resize the QGraphicsView
        imageView->setFixedSize(newWidth, newHeight);
    }
}

//void SerialCommunicationDialog::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event);
//
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//
//    // Draw a white background
//
//    // Draw a transparent circle
//    painter.setBrush(QBrush(Qt::transparent));
//    painter.setPen(Qt::NoPen);
//    painter.drawEllipse(rect());
//}


void SerialCommunicationDialog::showEvent(QShowEvent *event)
{
    // Call the base class implementation
    QDialog::showEvent(event);

    // Set the position of the layout when the dialog is shown
    layout()->setGeometry(QRect(0, 5, 200, 100));


}