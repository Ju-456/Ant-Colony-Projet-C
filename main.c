#include "fourmi.h"
#include "fourmi.c"
#include <stdio.h>

int main() 
{
    int nbSaison;
    int saisonActuel;
    EvenementExterne EvnmtExt;
    Pheromone phero;
    Colonie *colonie = creerColonie(1, 5); // a changer prochainement avec le cycle de vie
    SystemeAgricole agriculture = {100, 50};
    SystemeElevage elevage = {10};
    Hygiène hygiene = {100, 0};
    Sécurité securite = {10, 0};
    Architecture architecture = {0};
    Environnement environnement = {0, 200};

    // Ajouter des fourmis à la colonie
    ajouterFourmi(&colonie->ouvrieres, 1, 0, ROLE_OUVRIERE);
    ajouterFourmiMale(&colonie->males, 2, 0, ROLE_MALE);

    // Gérer la colonie
    simulationSaisons(colonie, &agriculture, &elevage, nbSaison);
    cultiverChampignons(&agriculture);
    elevagePucerons(&elevage);
    gererHygiene(&hygiene);
    gererSecurite(&securite);
    construireSalle(&architecture);
    explorer(&environnement);

    // Affichage des résultats
    printf("La colonie a %d reines.\n", colonie->nombreReines);

    return 0;
}