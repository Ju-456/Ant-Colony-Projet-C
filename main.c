#include "fourmi.h"
#include "menu.c"

#include <stdio.h>

int main() 
{
    Colonie *colo = (Colonie *)malloc(sizeof(Colonie)); 
    if (!colo) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la colonie\n");
        return -1;
    }

    SystemeAgricole *agriculture = malloc(sizeof(SystemeAgricole));
    SystemeElevage *elevage = malloc(sizeof(SystemeElevage));

    int nbSaison = 4;
    int saisonActuel = 0;

    EvenementExterne EvnmtExt;
    Pheromone phero;
    Hygiène hyg;
    Sécurité secu;
    Architecture archi;
    Environnement enviro;

    int nOuvrieres, nSoldats, nMales;

    menu(colo, nOuvrieres, nSoldats, agriculture, elevage, nMales, nbSaison, saisonActuel, EvnmtExt, phero, &hyg, &secu, archi, enviro);
    libererColonie(colo);
    free(colo);
    
    return 0;
}
