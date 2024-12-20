#include "fourmi.h"
#include "menu.c"

#include <stdio.h>
// Fonction pour libérer la mémoire de la colonie
void libererColonie(Colonie *colo) {
    // Implémentez la libération de chaque liste de fourmis
    // Exemple :
    while (colo->ouvrieres) {
        supprimerFourmi(&colo->ouvrieres, colo->ouvrieres);
    }
    while (colo->soldats) {
        supprimerFourmi(&colo->soldats, colo->soldats);
    }
    while (colo->males) {
        supprimerFourmiMale(&colo->males);
    }
}

int main() 
{
    int nbSaison = 4;
    int saisonActuel = 0;        
    EvenementExterne EvnmtExt;
    Pheromone phero;
    Architecture archi;

    Colonie *colo = (Colonie *)malloc(sizeof(Colonie)); 
    if (!colo) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la colonie\n");
        return -1;
    }
/*
    SystemeAgricole agriculture;
    SystemeElevage elevage;
    Hygiène hyg;
    Sécurité secu;
    
    Environnement enviro;
*/
    menu(colo, nbSaison, saisonActuel, EvnmtExt, phero, archi);// Libération de la mémoire
    libererColonie(colo);
    free(colo);
    
    return 0;
}
