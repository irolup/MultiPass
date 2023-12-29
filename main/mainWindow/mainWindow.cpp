//
// Created by irolup on 21/12/23.
//

#include "mainWindow.h"
#include <QPushButton>
#include <QApplication>
#include <QButtonGroup>
#include "redditDialog.h"
#include "SerialCommunication.h"
#include "SerialCommunicationDialog.h"


Window::Window(QWidget *parent) :
        QWidget(parent)
{
    // Set size of the window
    setFixedSize(900, 700);


    // Create and position the buttons
    QButtonGroup *buttonGroup = new QButtonGroup(this);

    //Reddit button
    auto *redditButton = new QPushButton("Reddit", this); // New Reddit button
    buttonGroup->addButton(redditButton);
    redditButton->setGeometry(10, 10, 80, 30); // Set coordinates and size for Reddit button
    connect(redditButton, &QPushButton::clicked, this, &Window::openRedditSubWindow);

    //Insta button
    auto *instaButton = new QPushButton("Insta", this);
    buttonGroup->addButton(instaButton);
    instaButton->setGeometry(100, 10, 80, 30);

    //Queue button
    auto *queueButton = new QPushButton("Queue", this);
    buttonGroup->addButton(queueButton);
    queueButton->setGeometry(190, 10, 80, 30);

    auto *serialCommButton = new QPushButton("Serial Communication", this);
    buttonGroup->addButton(serialCommButton);
    serialCommButton->setGeometry(280, 10, 80, 30);
    connect(serialCommButton, &QPushButton::clicked, this, &Window::openSerialCommunicationDialog);



}

    //Open the Dialog
    void Window::openRedditSubWindow(){
        redditDialog = new RedditDialog(this);
        redditDialog->exec();
    }
    void Window::openSerialCommunicationDialog()
    {
        serialCommDialog = new SerialCommunicationDialog(this);
        serialCommDialog->exec();
    }

