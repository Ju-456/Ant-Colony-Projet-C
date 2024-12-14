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
    RandomColonie(colo);

    SystemeAgricole agriculture = {100, 50};
    SystemeElevage elevage = {10};
    Hygiène hyg = {100, 0};
    Sécurité secu = {10, 0};
    Architecture archi = {0};
    Environnement enviro = {0, 200};

    // Fonctionnement de la colonie
    //FourmiliereEnEvolution(colo);
    simuleUneSaison(colo, &agriculture, &elevage, nbSaison, saisonActuel, EvnmtExt, phero);
    //simuleUneSaison (appeler une saison) -> ex : hiver -> GestionEvenementExterne -> ReproductionEtMortalite -> affichageCycleSaison
    
    cultiverGraines(&agriculture);
    elevagePucerons(&elevage);
    gererHygiene(&hyg);
    gererSecurite(&secu);
    construireSalle(&archi);
    explorer(&enviro);

    return 0;
}