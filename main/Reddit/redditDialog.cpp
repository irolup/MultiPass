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
    leftLayout = new QGridLayout;
    rightLayout = new QGridLayout;

    // Set up the labels and other objects
    //Left Layout objects
    SubRedditLabel = new QLabel("Please enter a sub-reddit URL:", this);
    SelectPathFolder = new QLabel("Please select an empty <br>folder path for downloads");
    ImageQuantitiesLabel = new QLabel("Please enter the image quantities you<br> want to download (default = 10):", this);
    PathFolderLabel = new QLabel("Please enter the path for downloads:", this);
    ConfirmLabel = new QLabel("Confirm all:", this);
    SelecDownloadFolderLabel = new QLabel("Path : ",this);
    SubRedditLineEdit = new QLineEdit(this);
    SubRedditLineEdit->setMaximumSize(200, 20);
    ImageQuantitiesLineEdit = new QLineEdit(this);
    ImageQuantitiesLineEdit->setMaximumSize(200, 20);
    PathFolderLineEdit = new QLineEdit(this);
    PathFolderLineEdit->setMaximumSize(200, 20);
    ConfirmURLButton = new QPushButton("Confirm URL", this);
    DownloadPathButton = new QPushButton("Select file", this);
    ConfirmAllButton = new QPushButton("Confirm", this);
    ConfirmAllButton->setMaximumSize(200, 20);

    //Right layout objects
    DownloadedImagesLabel = new QLabel("Downloaded images", this);
    //Add connect function

    // Set up the left layout

    leftLayout->setColumnMinimumWidth(0,50);
    leftLayout->addWidget(SubRedditLabel,0,0);
    leftLayout->addWidget(SubRedditLineEdit,1,0);
    leftLayout->addWidget(ConfirmURLButton,2,0 );
    leftLayout->addWidget(SelectPathFolder,3,0);
    leftLayout->addWidget(DownloadPathButton,4,0);
    connect(DownloadPathButton, &QPushButton::clicked, this, &RedditDialog::chooseDownloadFolder);
    leftLayout->addWidget(SelecDownloadFolderLabel,5,0);
    leftLayout->addWidget(ImageQuantitiesLabel,6,0);
    leftLayout->addWidget(ImageQuantitiesLineEdit,7,0);
    leftLayout->addWidget(PathFolderLabel,8,0);
    leftLayout->addWidget(PathFolderLineEdit,9,0);
    leftLayout->addWidget(ConfirmLabel,10,0);
    leftLayout->addWidget(ConfirmAllButton, 11, 0);


    // Set up the labels for right layout
    rightLayout->addWidget(DownloadedImagesLabel, 0, 0, 1, 5, Qt::AlignTop);


    //Load an image on the left layout
    LoadFolderPath = "/home/irolup/CLionProjects/images";
    // Create a QDir object for the folder
    QDir imageDir(LoadFolderPath);
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

void RedditDialog::chooseDownloadFolder() {
    // Get the user's documents directory
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    // Check if the "MultiPass/DownloadedImagesMultiPass" folder exists
    QString initialPath = documentsPath + "/MultiPassMemory/DownloadedImagesMultiPass";
    QDir initialDir(initialPath);

    // If the folder exists, set the initial path to that folder; otherwise, use the documents directory
    SelectedDownloadedPath = initialDir.exists() ? initialPath : documentsPath;

    // Ask the user to choose a directory
    SelectedDownloadedPath = QFileDialog::getExistingDirectory(this, tr("Choose Download Folder"), SelectedDownloadedPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    // Check if the user selected a valid directory
    if (!SelectedDownloadedPath.isEmpty()) {
        // Update the path variable for later use
        chosenDownloadFolderPath = SelectedDownloadedPath;

        // Create the "MultiPass" folder and "DownloadedImagesMultiPass" subfolder
        QString folderPath = chosenDownloadFolderPath + "/MultiPass/DownloadedImagesMultiPass";
        QDir folderDir(folderPath);

        SelecDownloadFolderLabel->setText("Path: <br>" + chosenDownloadFolderPath);
        if (!folderDir.exists()) {
            if (!folderDir.mkpath(folderPath)) {
                qDebug() << "Error creating folder.";
                return;
            }
        }

        // Indicate to the user the chosen path
        QMessageBox::information(this, tr("Folder Chosen"), tr("Download folder chosen: %1").arg(chosenDownloadFolderPath));
    } else {
        // User canceled the dialog or chose an invalid directory
        qDebug() << "User canceled or chose an invalid directory.";
    }
}

