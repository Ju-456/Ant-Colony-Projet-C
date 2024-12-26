#include "fourmi.h"
#include "menu.c"

#include <stdio.h>

int main()
{
    Colonie *colo = (Colonie *)malloc(sizeof(Colonie));
    if (!colo)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la colonie\n");
        return -1;
    }

    SystemeAgricole *agriculture = malloc(sizeof(SystemeAgricole));
    SystemeElevage *elevage = malloc(sizeof(SystemeElevage));

    int nbSaison = 4;
    int saisonActuel;

    EvenementExterne *EvnmtExt = malloc(sizeof(EvenementExterne));
    Pheromone *phero = malloc(sizeof(Pheromone));
    Hygiène *hyg = malloc(sizeof(Hygiène));
    Sécurité *secu = malloc(sizeof(Sécurité));
    Architecture archi;
    Environnement enviro;

    menu(colo, agriculture, elevage, nbSaison, &saisonActuel, EvnmtExt, phero, hyg, secu, archi, enviro);
    libererColonie(colo);
    free(colo);

    return 0;
}
