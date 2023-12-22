//
// Created by irolup on 21/12/23.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QPushButton;
class RedditDialog;
class Window : public QWidget
{
Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    signals:

private slots:

private:
    int m_counter;
    QPushButton *redditButton;
    QPushButton *instaButton;
    QPushButton *queueButton;
    QPushButton *otherButton1;
    RedditDialog *redditDialog;

};
#endif // WINDOW_H