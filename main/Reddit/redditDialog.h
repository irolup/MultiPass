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
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>

class QLabel;

class RedditDialog : public QDialog
{
Q_OBJECT

public:
    explicit RedditDialog(QWidget *parent = nullptr);

private slots:
    void chooseDownloadFolder();

protected:
    void showEvent(QShowEvent *event) override;

private:
    QHBoxLayout *mainLayout;
    QGridLayout *leftLayout;
    QGridLayout *rightLayout;
    QLabel *SubRedditLabel;
    QLabel *ImageQuantitiesLabel;
    QLabel *PathFolderLabel;
    QLabel *ConfirmLabel;
    QLabel *DownloadedImagesLabel;
    QLabel *SelectPathFolder;
    QLabel *SelecDownloadFolderLabel;
    QLineEdit *SubRedditLineEdit;
    QLineEdit *ImageQuantitiesLineEdit;
    QLineEdit *PathFolderLineEdit;
    QPushButton *ConfirmURLButton;
    QPushButton *ConfirmAllButton;
    QPushButton *DownloadPathButton;
    QString LoadFolderPath;
    QString chosenDownloadFolderPath;
    QString SelectedDownloadedPath;






};

#endif // REDDITDIALOG_H