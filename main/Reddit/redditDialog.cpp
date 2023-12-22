//
// Created by irolup on 21/12/23.
//

#include "redditDialog.h"
#include <QVBoxLayout>
#include <QLabel>

RedditDialog::RedditDialog(QWidget *parent) :
        QDialog(parent)
{
    // Set up the user interface components
    label = new QLabel("Reddit Dialog Content", this);

    // Set up the layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);

    // You can add more widgets to the layout if needed

    setLayout(layout);

    // Set the size of the dialog
    setFixedSize(300, 200);

    // Set any other properties or configurations as needed
}