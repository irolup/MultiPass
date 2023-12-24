#include "Autre.h"
#include <QPushButton>
#include <QVBoxLayout>

Autre::Autre(QWidget *parent) : QWidget(parent) {
    // Créer un bouton
    QPushButton *bouton = new QPushButton("Ouvrir Serial Communication", this);

    // Connecter le clic du bouton à la méthode onBoutonClique
    connect(bouton, &QPushButton::clicked, this, &Autre::onBoutonClique);

    // Créer une mise en page
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(bouton);
    setLayout(layout);
}

void Autre::onBoutonClique() {
    // Vous pouvez ajouter ici des opérations supplémentaires lors du clic sur le bouton
    // Par exemple, ouvrir une nouvelle fenêtre, etc.

    // Créer une nouvelle instance de la classe Autre (fenêtre)
    Autre *nouvelleFenetre = new Autre;
    nouvelleFenetre->show();
}