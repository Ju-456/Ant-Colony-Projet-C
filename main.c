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

    // Allocation de mémoire pour les systèmes agricoles et d'élevage
    SystemeAgricole *agriculture = malloc(sizeof(SystemeAgricole));
    SystemeElevage *elevage = malloc(sizeof(SystemeElevage));

    int nbSaison = 4;
    int saisonActuel = 0;

    // Initialisation des structures nécessaires pour la simulation
    EvenementExterne EvnmtExt; // Gestion des événements externes
    Pheromone *phero = malloc(sizeof(Pheromone)); // Gestion des phéromones
    Hygiène *hyg = malloc(sizeof(Hygiène)); // Gestion de l'hygiène
    Sécurité *secu = malloc(sizeof(Sécurité)); // Gestion de la sécurité
    Architecture archi; // Gestion de l'architecture interne
    Environnement enviro; // Gestion des paramètres environnementaux

    menu(colo, agriculture, elevage, nbSaison, saisonActuel, EvnmtExt, phero, hyg, secu, archi, enviro);
    libererColonie(colo);
    free(colo);
    
    return 0;
}