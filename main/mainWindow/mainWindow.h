//
// Created by irolup on 21/12/23.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QShowEvent>

class QPushButton;
class RedditDialog;
class SerialCommunicationDialog;
class Window : public QWidget
{
Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    signals:

private slots:
    void openRedditSubWindow();
    void openSerialCommunicationDialog();

private:
    int m_counter;
    QPushButton *redditButton;
    QPushButton *instaButton;
    QPushButton *queueButton;
    QPushButton *otherButton1;
    RedditDialog *redditDialog;
    SerialCommunicationDialog *serialCommDialog;

};
#endif // WINDOW_H