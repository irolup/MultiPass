//
// Created by irolup on 21/12/23.
//

#ifndef INSTAAPP_REDDITDIALOG_H
#define INSTAAPP_REDDITDIALOG_H

#include <QDialog>
#include <QShowEvent>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QPixmap>
#include <QDir>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>



class QLabel;

class RedditDialog : public QDialog
{
Q_OBJECT

public:
    explicit RedditDialog(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override;

private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QGridLayout *rightLayout;
    QLabel *SubRedditLabel;
    QLabel *ImageQuantitiesLabel;
    QLabel *PathFolderLabel;
    QLabel *ConfirmLabel;
    QLabel *DownloadedImagesLabel;
    QLineEdit *SubRedditLineEdit;
    QLineEdit *ImageQuantitiesLineEdit;
    QLineEdit *PathFolderLineEdit;
    QPushButton *ConfirmButton;
    QString folderPath;






};

#endif // REDDITDIALOG_H