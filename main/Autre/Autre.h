#ifndef AUTRE_H
#define AUTRE_H

#include <QWidget>

class Autre : public QWidget {
Q_OBJECT

public:
    Autre(QWidget *parent = nullptr);

private slots:
    void onBoutonClique();
};

#endif // AUTRE_H