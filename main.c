#include "fourmi.h"
#include "menu.c"

#include <stdio.h>

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

    menu(colo, nbSaison, saisonActuel, EvnmtExt, phero, archi);// Libération de la mémoire
    libererColonie(colo);
    free(colo);
    
    return 0;
}
