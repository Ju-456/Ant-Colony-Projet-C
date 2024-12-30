#include "fourmi.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h> // Pour le "sleep(3)"
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour srand(time(NULL));

// Initialisation aléatoire de la colonie
int RandomColonie(Colonie *colo, Hygiène *hyg, Sécurité *secu, SystemeElevage *elevage, SystemeAgricole *agriculture)
{
    if (!colo)
    {
        fprintf(stderr, "Erreur : pointeur de colonie invalide.\n");
        return -1;
    }

    // Initialisation des champs de la colonie
    colo->ouvrieres = NULL;
    colo->males = NULL;
    colo->soldats = NULL;
    colo->nombreReines = 5;

    // Genere aleaatoirement des valeurs entre 1 à 3
    hyg->niveauProprete = rand() % 3 + 1;
    hyg->niveauMaladie = rand() % 3 + 1;
    secu->niveauProtection = rand() % 3 + 1;
    secu->attaquesReçues = rand() % 3 + 1;

    // Ajout fixe de reines
    int nReines = 5; // Nombre de reines
    for (int i = 0; i < nReines; ++i)
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_REINE); // les reines sont dans la même liste chainée que les ouvrières mais elles sont en tête de listes
    }

    // Ajout aléatoire d'ouvrières
    int nOuvrieres = rand() % 201 + 500; // Nombre entre 500 et 700
    for (int i = 0; i < nOuvrieres; ++i)
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    nOuvrieres = compterFourmis(colo->ouvrieres);

    // Ajout aléatoire de soldats
    int nSoldats = nOuvrieres * (5 + rand() % 6) / 100; // les soldats representent 5 - 10% de la fourmilière
    for (int i = 0; i < nSoldats; ++i)
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    elevage->nombrePucerons = nOuvrieres * (20 + rand() % 6) / 100;    // 20 - 25% de la proportion d'ouvrières
    agriculture->quantitéDeNourriture = nOuvrieres * (2 + rand() % 2); // 2 - 3 * proportion d'ouvrières
    agriculture->quantitéGraines = nOuvrieres * (3 + rand() % 3);      // 3 - 5 * proportion d'ouvrières

    return 0; // Succès
}

void simuleUneSaisonRandom(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int *saisonActuel, Hygiène *hyg, Sécurité *secu, EvenementExterne *EvnmtExt, Pheromone *phero, Architecture archi)
{
    for (int i = 0; i < nbSaison; ++i) // nbSaison = 4, on aurait pu mettre <= nbSaison ssi nbSaison = 3
    {
        switch (i % 4)
        { // Répartition des saisons : 0 = HIVER, 1 = PRINTEMPS, 2 = ETE, 3 = AUTOMNE

        case 0: // HIVER
            hiver(saisonActuel, agriculture, EvnmtExt, phero, colo, elevage);
            GestionEvenementExterneRandom(EvnmtExt, phero, colo, saisonActuel);
            PonteEtMortalite(phero, colo);
            NiveauPropreteEtMaladie(hyg, colo);
            NiveauSecuritéEtProtection(secu, colo);
            // printf("\n****************************** Récapitulatif de l'HIVER ****************************\n");
            affichageCycleSaisonRandom(colo, agriculture, elevage, phero);
            break;

        case 1: // PRINTEMPS
            printf("\n****************************** Récapitulatif du PRINTEMPS **************************\n");
            printemps(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
            GestionEvenementExterneRandom(EvnmtExt, phero, colo, saisonActuel);
            PonteEtMortalite(phero, colo);
            NiveauPropreteEtMaladie(hyg, colo);
            NiveauSecuritéEtProtection(secu, colo);
            affichageCycleSaisonRandom(colo, agriculture, elevage, phero);

            break;

        case 2: // ETE
            printf("\n****************************** Récapitulatif de l'ÉTÉ ******************************\n");
            ete(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
            GestionEvenementExterneRandom(EvnmtExt, phero, colo, saisonActuel);
            PonteEtMortalite(phero, colo);
            NiveauPropreteEtMaladie(hyg, colo);
            NiveauSecuritéEtProtection(secu, colo);
            affichageCycleSaisonRandom(colo, agriculture, elevage, phero);
            break;

        case 3: // AUTOMNE
            printf("\n****************************** Récapitulatif de l'AUTOMNE ******************************\n");
            automne(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
            GestionEvenementExterneRandom(EvnmtExt, phero, colo, saisonActuel);
            PonteEtMortalite(phero, colo);
            NiveauPropreteEtMaladie(hyg, colo);
            NiveauSecuritéEtProtection(secu, colo);
            affichageCycleSaisonRandom(colo, agriculture, elevage, phero);
            break;

        default:
            break;
        }
        (*saisonActuel)++; // Incrémenter la valeur pointée par saisonActuel

        // Simuler le vieillissement des fourmis
        Fourmi *current = colo->ouvrieres;
        while (current != NULL)
        {
            evoluerAge(current);
            current = current->suivante;
        }
        current = colo->soldats;
        while (current != NULL)
        {
            evoluerAge(current);
            current = current->suivante;
        }
        current = (Fourmi *)colo->males;
        while (current != NULL)
        {
            evoluerAge(current);
            current = current->suivante;
        }
    }
}

void GestionEvenementExterneRandom(EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo, int *saisonActuel)
{
    if (*saisonActuel == 0)
    {
        printf("\n****************************** Récapitulatif de l'HIVER ****************************\n");
        EvenementExterieurHiver(EvnmtExt, phero, colo, saisonActuel);
    }
    else if (*saisonActuel == 1)
    {
        EvenementExterieurPrintemps(EvnmtExt, phero, saisonActuel);
    }
    else if (*saisonActuel == 2)
    {
        EvenementExterieurEte(EvnmtExt, phero, saisonActuel);
    }
    else if (*saisonActuel == 3)
    {
        EvenementExterieurAutomne(EvnmtExt, phero,colo, saisonActuel);
    }
}

void affichageCycleSaisonRandom(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Pheromone *phero)
{
    colo->nombreReines = 5;
    int GrainesReste = 0, GrainesReste1 = 0, SoldatsReste = 0, OuvrieresReste = 0, OuvrieresReste1 = 0;

    // limite des stocks de graines
    int tempGraines = agriculture->quantitéGraines;
    if (tempGraines > 10000)
    {
        tempGraines = 1000;
        GrainesReste = 8000;
        GrainesReste1 = 999;
    }
    else if (tempGraines > 9000)
    {
        GrainesReste1 = tempGraines - 9000;
        GrainesReste = 8000;
        tempGraines = 1000;
    }
    else if (tempGraines > 1000)
    {
        GrainesReste = tempGraines - 1000;
        tempGraines = 1000;
        GrainesReste1 = 0;
    }
    agriculture->quantitéGraines = tempGraines;

    // limite des stocks de nourriture
    int tempNourriture = agriculture->quantitéDeNourriture;
    if (tempNourriture > 10000000)
    {
        tempNourriture = 9999999;
    }
    agriculture->quantitéDeNourriture = tempNourriture;

    // limite des ouvrieres
    int tempOuvrieres = compterFourmis(colo->ouvrieres);
    if (tempOuvrieres > 900)
    {
        tempOuvrieres = 700;
        OuvrieresReste = 100;
        OuvrieresReste1 = 99;
        int nOuvrieres = compterFourmis(colo->ouvrieres);
        int nOuvrièresSupprimes = nOuvrieres * (50 + rand() % 21) / 100; // suppression entre 50% et 70%
        for (int j = 0; j < nOuvrièresSupprimes; ++j)
        {
            supprimerFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
        }
    }
    else if (tempOuvrieres > 800)
    {
        OuvrieresReste1 = tempOuvrieres - 800 + colo->nombreReines; // car les reines sont sur la même liste chainee mais pas dans la même salle
        tempOuvrieres = 700;
        OuvrieresReste = 100;
    }
    else if (tempOuvrieres > 700)
    {
        OuvrieresReste = tempOuvrieres - 700 + colo->nombreReines;
        tempOuvrieres = 700;
        OuvrieresReste1 = 0;
    }

    // comme ce n'est que pour de l'affichage, on affichera pas la valeur réelle mais temporaire qui = valeur réelle décomposée en plusieurs partie pour respecter la limite de taille des cases

    // limite des pucerons
    int tempPucerons = elevage->nombrePucerons;
    if (tempPucerons > 1000)
    {
        tempPucerons = 999;
    }
    elevage->nombrePucerons = tempPucerons;

    int tempMales = compterFourmisMales(colo->males);
    if (tempMales > 60)
    {
        tempMales = 59;
    } // comme ce n'est que pour de l'affichage, on affichera pas la valeur réelle mais temporaire (idem Ouvrieres)

    // limite des soldats
    int tempSoldats = compterFourmis(colo->soldats);
    if (tempSoldats > 300)
    {
        tempSoldats = 200;
        SoldatsReste = 99;
    }
    else if (tempSoldats > 200)
    {
        SoldatsReste = tempSoldats - 200;
        tempSoldats = 200;
    } // comme ce n'est que pour de l'affichage, on affichera pas la valeur réelle mais temporaire (idem Ouvrieres)

    printf(
        "                                       - Fourmilière -\n"
        "                             \x1b[48;2;115;71;60m--------------------------------\n"
        "                    \x1b[48;2;115;71;60m--------\x1b[48;2;139;93;78m                                 \x1b[0m\x1b[48;2;115;71;60m-------\n"
        "                \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m                       Graines                   \x1b[0m\x1b[48;2;115;71;60m----\n"
        "            \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m                   \x1b[48;2;210;160;135m------------------\x1b[48;2;139;93;78m                       \x1b[0m\x1b[48;2;115;71;60m----\n"
        "        \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m-  %d -          -\x1b[48;2;139;93;78m                          \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m       Soldats           \x1b[48;2;210;160;135m-------    %d    -\x1b[48;2;139;93;78m                             \x1b[0m\x1b[48;2;115;71;60m----\n"
        "    \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m                \x1b[0m\x1b[48;2;210;160;135m-          -------\x1b[48;2;139;93;78m                         \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "  \x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m-       -\x1b[48;2;139;93;78m                \x1b[0m\x1b[48;2;210;160;135m------------  %d -\x1b[48;2;139;93;78m         Ouvrières         \x1b\x1b[0m\x1b[48;2;115;71;60m------\n"
        " \x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m         \x1b[48;2;210;160;135m-   %d  -\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m        \x1b\x1b[0m\x1b[48;2;115;71;60m------\n"
        "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m    \x1b[48;2;210;160;135m---------------\x1b[48;2;139;93;78m                                          \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m          \x1b[0m\x1b[48;2;115;71;60m------\n"
        "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m    \x1b[48;2;210;160;135m- %d  -\x1b[48;2;139;93;78m                          Nourriture               \x1b[48;2;210;160;135m-    %d    -\x1b[48;2;139;93;78m          \x1b[0m\x1b[48;2;115;71;60m------\n"
        "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m    \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                      \x1b\x1b[48;2;210;160;135m-----------------\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m          \x1b[0m\x1b[48;2;115;71;60m------\n"
        "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m           Pucerons             \x1b[48;2;210;160;135m-               -\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m-----------------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m------\n"
        " \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m         \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m-      %d      -\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m- %d  -\x1b[48;2;139;93;78m    \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "  \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-               -\x1b[48;2;139;93;78m                  \x1b[48;2;210;160;135m-----------\x1b[48;2;139;93;78m    \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "   \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m-    %d    -\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-----------------\x1b[48;2;139;93;78m                  \x1b[48;2;210;160;135m- %d  -\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "    \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m    Mâles                                     \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "      \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m     \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m\x1b[48;2;139;93;78m   \x1b\x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                    AMBIANCE                     \x1b\x1b[0m\x1b[48;2;115;71;60m----\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                 \x1b[48;2;210;160;135m- %d  -\x1b[48;2;139;93;78m       Reines         %d/10                 \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "            \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m             \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b\x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                           \x1b\x1b[0m\x1b[48;2;115;71;60m-----\n"
        "                \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                      \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m                   \x1b\x1b[0m\x1b[48;2;115;71;60m-----\n"
        "                    \x1b[48;2;115;71;60m--------\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m             \x1b\x1b[0m\x1b[48;2;115;71;60m------\n"
        "                             \x1b[48;2;115;71;60m--------------------------------\n",
        tempGraines, GrainesReste, GrainesReste1, tempSoldats, SoldatsReste, tempOuvrieres - 5, tempNourriture, OuvrieresReste, tempPucerons, OuvrieresReste1, tempMales, phero->ambiance, colo->nombreReines);
    // tempOuvrieres - 5, car on rappelle que les reines sont dans la même liste chainees que les ouvrières mais pas la même salle
    /*
        printf("\n--- DEBUG INFO APRES ---\n");
        printf("Nombre d'ouvrières : %d\n", compterFourmis(colo->ouvrieres));
        printf("Nombre de soldats : %d\n", compterFourmis(colo->soldats));
        printf("Agriculture - Quantité de Graines : %d\n", ((SystemeAgricole *)agriculture)->quantitéGraines);
        printf("Agriculture - Quantité de Nourriture : %d\n", ((SystemeAgricole *)agriculture)->quantitéDeNourriture);
        printf("Élevage - Nombre de Pucerons : %d\n", ((SystemeElevage *)elevage)->nombrePucerons);
        printf("Nombre de reines : %d\n", colo->nombreReines);
        printf("-------------------\n"); */
    printf("\n");
    sleep(2);
}