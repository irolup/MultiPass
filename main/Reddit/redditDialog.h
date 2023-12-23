//
// Created by irolup on 21/12/23.
//

#ifndef INSTAAPP_REDDITDIALOG_H
#define INSTAAPP_REDDITDIALOG_H

#include <QDialog>
#include <QShowEvent>

class QLabel;

class RedditDialog : public QDialog
{
Q_OBJECT

public:
    explicit RedditDialog(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override;

private:
    QLabel *label; // Example label to show content
};

#endif // REDDITDIALOG_H