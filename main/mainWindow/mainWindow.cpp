//
// Created by irolup on 21/12/23.
//

#include "mainWindow.h"
#include <QPushButton>
#include <QApplication>
#include <QButtonGroup>


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

    //Insta button
    auto *instaButton = new QPushButton("Insta", this);
    buttonGroup->addButton(instaButton);
    instaButton->setGeometry(100, 10, 80, 30);

    //Queue button
    auto *queueButton = new QPushButton("Queue", this);
    buttonGroup->addButton(queueButton);
    queueButton->setGeometry(190, 10, 80, 30);

    auto *otherButton1 = new QPushButton("Other", this);
    buttonGroup->addButton(otherButton1);
    otherButton1->setGeometry(280, 10, 80, 30);





    //make connection
    //connect(this, SIGNAL(counterReached()), QApplication::instance(), SLOT(quit()));
    //connect(slider, SIGNAL(valueChanged(int)), progressBar, SLOT(setValue(int)));
}


//void Window::slotButtonClicked(bool checked)
//{
//    if (checked) {
//        m_button->setText("Checked");
//    } else {
//        m_button->setText("Hello World");
//    }
//    m_counter++;
//    if(m_counter == 10){
//        emit counterReached();
//    }
//}
