//
// Created by irolup on 21/12/23.
//

#include "redditDialog.h"
#include <QVBoxLayout>


RedditDialog::RedditDialog(QWidget *parent) :
        QDialog(parent)
{
    // Set the title of the dialog
    setWindowTitle("Reddit");

    // Set the minimum and maximum sizes for the dialog
    setMinimumSize(1280, 960); // Adjust the values according to your needs
    setMaximumSize(3000, 1300);

    // Set up the main layout
    mainLayout = new QHBoxLayout(this);
    leftLayout = new QVBoxLayout;
    rightLayout = new QGridLayout;

    // Set up the labels and other objects
    //Left Layout objects
    SubRedditLabel = new QLabel("Please enter a sub-reddit URL:", this);
    ImageQuantitiesLabel = new QLabel("Please enter the image quantities you<br> want to download (default = 10):", this);
    PathFolderLabel = new QLabel("Please enter the path for downloads:", this);
    ConfirmLabel = new QLabel("Confirm all:", this);
    SubRedditLineEdit = new QLineEdit(this);
    SubRedditLineEdit->setMaximumSize(200, 20);
    ImageQuantitiesLineEdit = new QLineEdit(this);
    ImageQuantitiesLineEdit->setMaximumSize(200, 20);
    PathFolderLineEdit = new QLineEdit(this);
    PathFolderLineEdit->setMaximumSize(200, 20);
    ConfirmButton = new QPushButton("Confirm", this);
    ConfirmButton->setMaximumSize(200, 20);
    //Right layout objects
    DownloadedImagesLabel = new QLabel("Downloaded images", this);
    //Add connect function

    // Set up the left layout
    leftLayout->addWidget(SubRedditLabel);
    leftLayout->addWidget(SubRedditLineEdit);
    leftLayout->addWidget(ImageQuantitiesLabel);
    leftLayout->addWidget(ImageQuantitiesLineEdit);
    leftLayout->addWidget(PathFolderLabel);
    leftLayout->addWidget(PathFolderLineEdit);
    leftLayout->addWidget(ConfirmLabel);
    leftLayout->addWidget(ConfirmButton);
    leftLayout->addSpacing(1);

    // Set up the labels for right layout
    rightLayout->addWidget(DownloadedImagesLabel, 0, 0, 1, 5, Qt::AlignTop);


    //Load an image on the left layout
    folderPath = "/home/irolup/CLionProjects/images";
    // Create a QDir object for the folder
    QDir imageDir(folderPath);
    // Filter the files to include only image files
    QStringList nameFilters;
    nameFilters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp"; // Add more extensions if needed
    QStringList imageFiles = imageDir.entryList(nameFilters, QDir::Files);

    // Loop through the image files and add them to the layout
    int row = 1;
    int col = 0;
    for (const QString &imageFile : imageFiles) {
        auto *imageLabel = new QLabel(this);

        // Construct the full path to the image
        QString imagePath = imageDir.filePath(imageFile);

        // Load the image
        QPixmap image(imagePath);

        // Resize the image to fit the available space in the grid (adjust the size as needed)
        image = image.scaledToWidth(150, Qt::SmoothTransformation);

        // Set the image to the QLabel
        imageLabel->setPixmap(image);

        // Add the QLabel to the layout at the specified row and column
        rightLayout->addWidget(imageLabel, row, col, 1, 1, Qt::AlignTop);

        // Increment the column, and move to the next row if necessary
        col++;
        if (col == 5) {
            col = 0;
            row++;
        }
    }

    //Set up the mainLayout
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    //Ajust aligment of the layout
    mainLayout->setAlignment(leftLayout, Qt::AlignTop);
    mainLayout->setAlignment(rightLayout, Qt::AlignTop);
    //SetLayout
    setLayout(mainLayout);
    // Set the distance between the left layout and the window's border
    mainLayout->setContentsMargins(10, 10, 10, 10);
}


void RedditDialog::showEvent(QShowEvent *event) {
    // Call the base class implementation
    QDialog::showEvent(event);

    // Set the position of the layout when the dialog is shown
    layout()->setGeometry(QRect(0, 5, 200, 100));
}

