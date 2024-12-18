#include "fourmi.h"
#include "menu.c"

#include <stdio.h>

int main() 
{
    int nbSaison = 4;
    int saisonActuel;        
    EvenementExterne EvnmtExt;
    Pheromone phero;
    int saisonChoice;

    Colonie *colo = (Colonie *)malloc(sizeof(Colonie)); // = creerColonie(0, 5); creation de colonie aleatoir à la place

    SystemeAgricole agriculture;
    SystemeElevage elevage;
    Hygiène hyg;
    Sécurité secu;
    Architecture archi;
    Environnement enviro;

    menu(colo, nbSaison, saisonActuel, EvnmtExt, phero, archi, saisonChoice);
    return 0;
}