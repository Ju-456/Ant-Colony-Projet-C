#include "fourmi.h"
#include "fourmi.c"
#include <stdio.h>

int main() 
{
    int nbSaison;
    int saisonActuel;        // le climat qui regne dans la fourmilliere
    EvenementExterne EvnmtExt;
    Pheromone phero;

    Colonie *colo = (Colonie *)malloc(sizeof(Colonie)); // = creerColonie(0, 5); creation de colonie aleatoir à la place

    SystemeAgricole agriculture;
    SystemeElevage elevage;
    Hygiène hyg;
    Sécurité secu;
    Architecture archi;
    Environnement enviro;

    menu(colo, nbSaison, saisonActuel, EvnmtExt, phero);
    return 0;
}