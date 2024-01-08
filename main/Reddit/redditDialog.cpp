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
    SubRedditLabel = new QLabel("Please enter a sub-reddit name:", this);
    EnteredNameLabel = new QLabel("URL: ", this);
    EnteredNameLabel->setWordWrap(true);
    SelectPathFolder = new QLabel("Please select an empty <br> path for downloads");
    ImageQuantitiesLabel = new QLabel("Please enter the image quantities you<br> want to download (Max = 50):", this);
    ConfirmLabel = new QLabel("Confirm all:", this);
    SelecDownloadFolderLabel = new QLabel("Path : ",this);
    SelecDownloadFolderLabel->setWordWrap(true);
    SubRedditLineEdit = new QLineEdit(this);
    SubRedditLineEdit->setMaximumSize(200, 20);
    ImageQuantitiesLineEdit = new QLineEdit(this);
    ImageQuantitiesLineEdit->setMaximumSize(200, 20);
    ConfirmNameButton = new QPushButton("Confirm name", this);
    connect(ConfirmNameButton, &QPushButton::clicked, this, &RedditDialog::confirmName);
    DownloadPathButton = new QPushButton("Select folder path", this);
    connect(DownloadPathButton, &QPushButton::clicked, this, &RedditDialog::chooseDownloadFolder);
    ConfirmQuantitiesButton = new QPushButton("Confirm quantities", this);
    ConfirmAllButton = new QPushButton("Confirm", this);
    ConfirmAllButton->setMaximumSize(200, 20);

    //Right layout objects
    DownloadedImagesLabel = new QLabel("Downloaded images", this);
    //Add connect function

    // Set up the left layout

    leftLayout->setColumnMinimumWidth(0,50);
    leftLayout->addWidget(SubRedditLabel,0,0);
    leftLayout->addWidget(SubRedditLineEdit,1,0);
    leftLayout->addWidget(EnteredNameLabel, 2,0);
    leftLayout->addWidget(ConfirmNameButton, 3, 0 );
    leftLayout->addWidget(SelectPathFolder,4,0);
    leftLayout->addWidget(DownloadPathButton,5,0);
    leftLayout->addWidget(SelecDownloadFolderLabel,6,0);
    leftLayout->addWidget(ImageQuantitiesLabel,7,0);
    leftLayout->addWidget(ImageQuantitiesLineEdit,8,0);
    leftLayout->addWidget(ConfirmQuantitiesButton,11,0);
    leftLayout->addWidget(ConfirmLabel,12,0);
    leftLayout->addWidget(ConfirmAllButton, 13, 0);


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

    // Check if the "MultiDownloadPath" folder exists
    QString initialPath = documentsPath + "/MultiDownloadPath";
    QDir initialDir(initialPath);

    // If the folder exists, set the initial path to that folder; otherwise, use the documents directory
    SelectedDownloadedPath = initialDir.exists() ? initialPath : documentsPath;

    // Ask the user to choose a directory
    SelectedDownloadedPath = QFileDialog::getExistingDirectory(this, tr("Choose Download Folder"), SelectedDownloadedPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    // Check if the user selected a valid directory
    if (!SelectedDownloadedPath.isEmpty()) {
        // Update the path variable for later use
        chosenDownloadFolderPath = SelectedDownloadedPath;

        // Create the "MultiDownloadPath" folder
        QString multiDownloadPath = chosenDownloadFolderPath + "/MultiDownloadPath";
        QDir multiDownloadDir(multiDownloadPath);

        if (!multiDownloadDir.exists()) {
            if (!multiDownloadDir.mkpath(multiDownloadPath)) {
                qDebug() << "Error creating folder.";
                return;
            }
        }

        // Create the "DownloadedImagesMultiPass" subfolder
        downloadedImagesPath = multiDownloadPath + "/DownloadedImagesMultiPass";
        QDir downloadedImagesDir(downloadedImagesPath);

        SelecDownloadFolderLabel->setText("Path: <br>" + downloadedImagesPath);
        if (!downloadedImagesDir.exists()) {
            if (!downloadedImagesDir.mkpath(downloadedImagesPath)) {
                qDebug() << "Error creating folder.";
                return;
            }
        }

        // Indicate to the user the chosen path
        QMessageBox::information(this, tr("Folder Chosen"), tr("Download folder chosen: %1").arg(downloadedImagesPath));
    } else {
        // User canceled the dialog or chose an invalid directory
        qDebug() << "User canceled or chose an invalid directory.";
    }
    qDebug() << downloadedImagesPath;
}

void RedditDialog::confirmName(){
    // Get the entered name from the QLineEdit
    QString subredditName = SubRedditLineEdit->text();

    // Check if the entered name contains spaces or invalid symbols
    QRegularExpression validSubredditName("^[A-Za-z0-9_]+$");
    if (!subredditName.isEmpty() && validSubredditName.match(subredditName).hasMatch()) {
        // Valid name, construct the URL
        enteredName = "https://www.reddit.com/r/" + subredditName;

        // Update the QLabel to display the entered name
        EnteredNameLabel->setText("URL: " + enteredName);

        // You can use 'enteredName' in other parts of your code as needed
    } else {
        // Invalid name, indicate an error
        QMessageBox::warning(this, tr("Error"), tr("Invalid subreddit name. Please avoid spaces and special characters."));
    }
}

QString RedditDialog::getSubredditName() {
    return SubRedditLineEdit->text();
}

QString RedditDialog::getDownloadedImagesPath() {
    return downloadedImagesPath;
}
