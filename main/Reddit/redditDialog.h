//
// Created by irolup on 21/12/23.
//

#ifndef INSTAAPP_REDDITDIALOG_H
#define INSTAAPP_REDDITDIALOG_H

#include <qregularexpression.h>
#include <QDialog>
#include <QShowEvent>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <string>
#include <QPushButton>
#include <QPixmap>
#include <QDir>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextBrowser>
#include <QComboBox>

class QLabel;

class RedditDialog : public QDialog
{
Q_OBJECT

public:
    explicit RedditDialog(QWidget *parent = nullptr);
    std::string getSubredditURL();
    std::string getDownloadedImagesPath();
    const int& getImageQuantities() const;
private slots:
    void chooseDownloadFolder();
    void confirmName();
    void confirmQuantities();
    void confirmAll();
    void updateUrlWithCategory();
protected:
    void showEvent(QShowEvent *event) override;

private:
    int imageQuantities;
    QHBoxLayout *mainLayout;
    QGridLayout *leftLayout;
    QGridLayout *rightLayout;
    QLabel *SubRedditLabel;
    QLabel *ImageQuantitiesLabel;
    QLabel *ConfirmLabel;
    QLabel *DownloadedImagesLabel;
    QLabel *SelectPathFolder;
    QLabel *SelecDownloadFolderLabel;
    QLabel *EnteredNameLabel;
    QLabel *ImageQuantitiesLabelNumber;
    QLabel *RedditChoiceLabel;
    QLineEdit *SubRedditLineEdit;
    QLineEdit *ImageQuantitiesLineEdit;
    QPushButton *ConfirmNameButton;
    QPushButton *ConfirmAllButton;
    QPushButton *DownloadPathButton;
    QPushButton *ConfirmQuantitiesButton;
    QString enteredName;
    QString LoadFolderPath;
    QString chosenDownloadFolderPath;
    QString SelectedDownloadedPath;
    QString downloadedImagesPath;
    QString updatedUrl;
    QComboBox *RedditChoiceComboBox;
};

#endif // REDDITDIALOG_H