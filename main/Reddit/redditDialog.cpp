//
// Created by irolup on 21/12/23.
//

#include "redditDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QPixmap>
#include <QDir>

RedditDialog::RedditDialog(QWidget *parent) :
        QDialog(parent)
{
    // Set up the labels for left layout
    auto SubRedditLabel = new QLabel("Please enter a sub-reddit URL:", this);
    auto ImageQuantitiesLabel = new QLabel("Please enter the image quantities you<br> want to download (default = 10):", this);
    auto PathFolderLabel = new QLabel("Please enter the path for downloads:", this);
    auto ConfirmLabel = new QLabel("Confirm all:", this);



    // Set up the LineEdit for left layout

    // Set up the LineEdit for right layout
    auto *SubRedditLineEdit = new QLineEdit(this);
    auto *ImageQuantitiesLineEdit = new QLineEdit(this);
    auto *PathFolderLineEdit = new QLineEdit(this);
    // Adjusting the max size
    SubRedditLineEdit->setMaximumSize(200, 20);
    ImageQuantitiesLineEdit->setMaximumSize(200, 20);
    PathFolderLineEdit->setMaximumSize(200, 20);

    // Set up the buttons for left layout
    auto *ConfirmButton = new QPushButton("Confirm", this);
    // Adjusting the max size
    ConfirmButton->setMaximumSize(200, 20);

    // Set up the buttons for right layout

    // Set up the left layout
    auto *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(SubRedditLabel);
    leftLayout->addWidget(SubRedditLineEdit);
    leftLayout->addWidget(ImageQuantitiesLabel);
    leftLayout->addWidget(ImageQuantitiesLineEdit);
    leftLayout->addWidget(PathFolderLabel);
    leftLayout->addWidget(PathFolderLineEdit);
    leftLayout->addWidget(ConfirmLabel);
    leftLayout->addWidget(ConfirmButton);
    leftLayout->addSpacing(1);

    // Set up the right layout



    // Set up the left layout with a grid
    auto *rightLayout = new QGridLayout;

    // Set up the labels for right layout
    auto *infoLabel = new QLabel("Downloaded images", this);
    rightLayout->addWidget(infoLabel, 0, 0, 1, 5, Qt::AlignTop);


    //Load an image on the left layout
    QString folderPath = "/home/irolup/CLionProjects/images";

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
    setWindowTitle("Reddit");
}


void RedditDialog::showEvent(QShowEvent *event) {
    // Call the base class implementation
    QDialog::showEvent(event);

    // Set the position of the layout when the dialog is shown
    layout()->setGeometry(QRect(0, 5, 200, 100));
}