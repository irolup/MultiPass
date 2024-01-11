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
#include <QStandardPaths>
#include <QMessageBox>
#include <QInputDialog>

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
    transparentCircleWidget->setFixedSize(480, 480);
    markerItem = nullptr;
    // Create a red square marker in the top-left corner of the circle widget
    markerItem = new QGraphicsRectItem(transparentCircleWidget->pos().x() - 5,
                                       transparentCircleWidget->pos().y() - 5,
                                       10, 10);
    markerItem->setPen(QPen(Qt::red));

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
    exportImageButton = new QPushButton("Export image", this);
    connect(exportImageButton, &QPushButton::clicked, this, &SerialCommunicationDialog::exportImage);
    imagePathFolderButton = new QPushButton("Open exported images path", this);
    connect(imagePathFolderButton, &QPushButton::clicked, this, &SerialCommunicationDialog::openExportedImagesFolder);
    selectFileToSendButton = new QPushButton("Select file to send", this);
    connect(selectFileToSendButton, &QPushButton::clicked, this, &SerialCommunicationDialog::selectFileToSend);
    comPortSelectorLabel = new QLabel("Please select the port you want to connect : ");
    comPortComboBox = new QComboBox(this);
    comPortComboBox->addItem("Automatic");
    comPortComboBox->addItem("COM port 1");
    comPortComboBox->addItem("COM port 2");
    comPortComboBox->addItem("COM port 3");
    comPortComboBox->addItem("COM port 4");
    comPortComboBox->addItem("ttyACM0");
    connectButton = new QPushButton("Connect to Serial Port", this);
    connect(comPortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SerialCommunicationDialog::updateSelectedComPort);
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
    imageScene->addItem(markerItem);
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
    leftLayout->addWidget(exportImageButton, 9,0);
    leftLayout->setAlignment(exportImageButton,Qt::AlignLeft);
    leftLayout->addWidget(imagePathFolderButton, 10,0);
    leftLayout->setAlignment(imagePathFolderButton,Qt::AlignLeft);
    leftLayout->addWidget(selectFileToSendButton,11,0);
    leftLayout->setAlignment(selectFileToSendButton, Qt::AlignLeft);
    leftLayout->addWidget(comPortSelectorLabel, 12,0);
    leftLayout->addWidget(comPortComboBox,13,0);
    leftLayout->addWidget(connectButton, 14,0);
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

            // Resize the QGraphicsView
            imageView->setFixedSize(1500, 1000);

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




            // If the position hasn't been set yet, set it to the top-left corner of the circle widget
            if (pixmapItem->pos() == QPointF(0, 0))
            {
                qreal width = pixmapItem->pixmap().width();
                qreal height = pixmapItem->pixmap().height();

                pixmapItem->setPos(transparentCircleWidget->pos().x() + width/2, transparentCircleWidget->pos().y() + height/2);
                markerItem->setRect(transparentCircleWidget->pos().x(), transparentCircleWidget->pos().y() + transparentCircleWidget->height() - markerItem->rect().height(), markerItem->rect().width(), markerItem->rect().height());

                qDebug() << "pixmapItem position: " << pixmapItem->pos();
                qDebug() << transparentCircleWidget->pos();
            }

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

void SerialCommunicationDialog::exportImage()
{
    // Check if a file is selected
    if (pixmapItem->pixmap().isNull())
        return;

    // Get the current position and size of the image item
    QPointF currentItemPos = pixmapItem->pos();
    QSizeF currentItemSize = pixmapItem->pixmap().size();

    // Get the user's documents directory
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    // Create the "exportedImages" folder in the documents directory if it doesn't exist
    QString folderPath = documentsPath + "/exportedImagesMultiPass";
    QDir folderDir(folderPath);
    if (!folderDir.exists()) {
        if (!folderDir.mkpath(folderPath)) {
            qDebug() << "Error creating folder.";
            return;
        }
    }

    // Prompt the user for the image name
    QString imageName = QInputDialog::getText(this, "Image Name", "Enter the image name:", QLineEdit::Normal, "exported_image");
    if (imageName.isEmpty())
        return;  // Return early if the user cancels or provides an empty name

    // Get the offset of the transparent circle widget
    QPoint widgetOffset = transparentCircleWidget->pos();

    // Calculate the position and size relative to the transparent circle widget
    qreal relativeX = std::max(currentItemPos.x(), currentItemPos.x() - transparentCircleWidget->pos().x());

    qreal relativeY = std::max(currentItemPos.y(), qAbs(currentItemPos.y() - transparentCircleWidget->pos().y()));
    qreal relativeWidth = std::min(static_cast<qreal>(currentItemSize.width()), static_cast<qreal>(transparentCircleWidget->width()));
    qreal relativeHeight = std::min(static_cast<qreal>(currentItemSize.height()), static_cast<qreal>(transparentCircleWidget->height()));
    qDebug() << "Current Item Pos: " << currentItemPos;
    qDebug() << "Widget Offset: " << widgetOffset;
    qDebug() << "New RelativeX: " << relativeX;
    qDebug() << "transparentCircleWidget Parent Widget Pos: " << transparentCircleWidget->parentWidget()->pos();

    // Create a new pixmap with the size of the transparent circle widget (480x480)
    QPixmap exportPixmap(480, 480);
    exportPixmap.fill(Qt::transparent);

    // Create a QPainter to draw the portion of the current image that fits within the transparent circle widget
    QPainter painter(&exportPixmap);

    // Draw the pixmap, aligning it with the left corner of the transparent circle widget
    painter.drawPixmap(0, 0, pixmapItem->pixmap(), relativeX, relativeY, relativeWidth, relativeHeight);

    // Save the exported image to the "exportedImages" folder in the documents directory
    QString exportFilePath = folderPath + "/" + imageName + ".jpg";

    if (!exportFilePath.isEmpty())
    {
        if (!exportPixmap.save(exportFilePath, "JPEG"))
        {
            qDebug() << "Error saving image.";
        }
    }
    QMessageBox::information(this, "Image Exported", imageName + exportFilePath);
    qDebug() << "Export File Path: " << exportFilePath;
}

void SerialCommunicationDialog::openExportedImagesFolder() {
    // Get the user's documents directory
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    // Create the "exportedImages" folder in the documents directory if it doesn't exist
    QString folderPath = documentsPath + "/MultiPass/exportedImagesMultiPass";
    QDir folderDir(folderPath);
    if (!folderDir.exists()) {
        if (!folderDir.mkpath(folderPath)) {
            qDebug() << "Error creating folder.";
            return;
        }
    }

    // Open the folder dialog for viewing exported images
    QFileDialog::getExistingDirectory(this, "Open Exported Images Folder", folderPath, QFileDialog::ReadOnly);
}

void SerialCommunicationDialog::selectFileToSend() {
// Set the initial directory for the file dialog
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString initialDir = documentsPath + "/exportedImagesMultiPass";

    // Open a file dialog for selecting a PNG file
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select PNG File"), initialDir, tr("PNG Files (*.png);;All Files (*)"));

    // Check if the user selected a file
    if (!filePath.isEmpty())
    {
        // Do something with the selected file path, for example, store it in a member variable
        QString selectedFilePath = filePath;
        qDebug() << "Selected File Path: " << selectedFilePath;
    }
    else
    {
        qDebug() << "No file selected.";
    }
}

void SerialCommunicationDialog::connectToSerialPort()
{
    // Instantiate the ConnectionSettingsDialog and pass the parent (this)
    connectionSettingsDialog = new ConnectionSettingsDialog(this);

    // Show the ConnectionSettingsDialog
    connectionSettingsDialog->exec();
}

void SerialCommunicationDialog::updateSelectedComPort(int index) {
// Update the selectedComPort variable with the current choice
    selectedComPort = comPortComboBox->itemText(index);
    qDebug() << "Selected COM Port: " << selectedComPort;
}

QString SerialCommunicationDialog::getSelectedComPort() const {
    if (selectedComPort.isNull() || selectedComPort.isEmpty()) {
        // Return the default value (e.g., "Automatic")
        return "Automatic";
    }
    return selectedComPort;
}




