#include "fourmi.h"
#include "fourmi.c"
#include <stdio.h>

int main() 
{
    int nbSaison;
    int saisonActuel;
    int climat;            // le climat qui regne dans la fourmilliere
    EvenementExterne EvnmtExt;
    Pheromone phero;
    Colonie *colo = creerColonie(1, 5); // a changer prochainement avec le cycle de vie
    SystemeAgricole agriculture = {100, 50};
    SystemeElevage elevage = {10};
    Hygiène hyg = {100, 0};
    Sécurité secu = {10, 0};
    Architecture archi = {0};
    Environnement enviro = {0, 200};

    // Ajouter des fourmis à la colonie
    ajouterFourmi(&colo->ouvrieres, 1, 0, ROLE_OUVRIERE);
    ajouterFourmiMale(&colo->males, 2, 0, ROLE_MALE);

    // Gérer la colonie
    simuleUneSaison(colo, &agriculture, &elevage, nbSaison, saisonActuel, EvnmtExt, phero, climat);
    //simuleUneSaison (appeler une saison) -> ex : hiver -> GestionEvenementExterne -> reproduction -> affichageCycleSaison
    
    cultiverChampignons(&agriculture);
    elevagePucerons(&elevage);
    gererHygiene(&hyg);
    gererSecurite(&secu);
    construireSalle(&archi);
    explorer(&enviro);

    // Affichage des résultats
    printf("La colonie a %d reines.\n", colo->nombreReines);

    return 0;
}