#include "fourmi.h"

#include "AnnexeFunctions.c"
#include "RandomSide.c"
#include "ChosenSide.c"

#include <stdio.h>
#include <string.h>
#include <unistd.h> // Pour le "sleep(3)"
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour srand(time(NULL));

void menu(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int *saisonActuel, EvenementExterne *EvnmtExt, Pheromone *phero, Hygiène *hyg, Sécurité *secu, Architecture archi, Environnement enviro)
{
    printf("\n");
    printf("Souhaitez-vous une simulation aléatoire (1) ou choisir les valeurs (2) ?");
    printf("\n");
    int choice = 0;
    printf(
        "\n1. Valeurs aléatoires\n"
        "2. Valeurs à choisir \n"
        "Entrer votre choix : ");
    scanf("%d", &choice);
    printf("\n");
    switch (choice)
    {
    case 1:

        //FourmiliereEnEvolution(colo);

        RandomColonie(colo, hyg, secu, elevage, agriculture);

        cultiverGraines(agriculture);
        elevagePucerons(elevage);
        construireSalle(&archi);
        explorer(&enviro);

        while (colo->nombreReines > 0)
        {
            simuleUneSaisonRandom(colo, agriculture, elevage, nbSaison, saisonActuel, hyg, secu, EvnmtExt, phero, archi);
            //GestionEvenementExterneRandom(EvnmtExt, phero, colo, saisonActuel);
            PonteEtMortalite(phero, colo);
            // NiveauPropreteEtMaladie(hyg, colo);
            // NiveauSecuritéEtProtection(secu, colo);
            //affichageCycleSaisonRandom(colo, agriculture, elevage, phero);
            if (colo->nombreReines <= 0)
            {
                colo->nombreReines = 0;
                affichageCycleSaisonRandom(colo, agriculture, elevage, phero);
                printf("Toutes les reines sont mortes, la colonie s'arrête ici..\n");
            }
        }
        break;

    case 2:
        ChosenColonie(colo, agriculture, elevage, &archi, hyg, secu);
        // afficherEtatColonie(colo,agriculture,elevage, hyg, secu); // pour un affichage plus simple
        affichageCycleSaisonChosen(archi, colo, agriculture, elevage, phero);

        while (colo->nombreReines > 0)
        {
            simuleUneSaisonChosen(colo, agriculture, elevage, nbSaison, saisonActuel, EvnmtExt, phero, archi);
            GestionEvenementExterneChosen(EvnmtExt, phero, colo, saisonActuel);
            PonteEtMortalite(phero, colo);
            NiveauPropreteEtMaladie(hyg, colo);
            NiveauSecuritéEtProtection(secu, colo);
            affichageCycleSaisonChosen(archi, colo, agriculture, elevage, phero);
            if (colo->nombreReines <= 0)
            {
                colo->nombreReines = 0;
                affichageCycleSaisonChosen(archi, colo, agriculture, elevage, phero);
                printf("Toutes les reines sont mortes, la colonie s'arrête ici..\n");
            }
        }
        break;
    }
}

void FourmiliereEnEvolution(Colonie *colo)
{

    srand(time(NULL));

    if (!colo)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la colonie\n");
        printf("-1");
        exit(0);
    }

    colo->ouvrieres = NULL;
    colo->males = NULL;
    colo->soldats = NULL;

    int max = 100; // capacité de stockage max pour une grande salle
    int max2 = 30; // capacité de stockage max pour une petite salle, appeler salle bis

    // ouverture de la salle 1 = debut de saison 1
    // total fourmis : -100
    printf("\n");
    printf("Bienvenue dans les aventures de la fourmilière, nous allons suivre\n"
           "son aventure sur les 3 premières saisons...\n"
           "\n*******************    SAISON 1   *******************\n"
           "C'est le début de la 1ère saison pour la fourmilière...\n");

    for (int i = 0; i < rand() % 11 + 50; ++i) // Ajout d'ouvrières entre 50 et 60
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    for (int i = 0; i < rand() % 11 + 20; ++i) // Ajout de soldats entre 20 et 30
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    int total = compterFourmis(colo->ouvrieres) + compterFourmis(colo->soldats);
    printf(
        "               - Création de la salle 1 -\n"
        "             \x1b[48;2;115;71;60m------------------------------\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m                    \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d   -\x1b[48;2;139;93;78m                      \x1b[0m\x1b[48;2;115;71;60m---\n"
        " \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m                       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                                 \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                                 \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                                 \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                                 \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                              \x1b[0m\x1b[48;2;115;71;60m---\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "        \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "           \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;115;71;60m---\n"
        "             \x1b[48;2;115;71;60m------------------------------\n",
        total);
    printf("1,5 mois plus tard après l'apparution de la fourmilière...");
    printf("\n");
    sleep(2);

    // ouverture de la salle 1 bis = fin de saison 1
    // total fourmis : 100-130
    for (int i = 0; i < rand() % 11; ++i) // Augmente les ouvrières de 0 à 10
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    for (int i = 0; i < rand() % 21; ++i) // Augmente les soldats de 0 à 20
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    colo->nombreReines = 1;
    int totalbis = 100 - total;

    // une sous salle = 30 fourmis
    // sous salle + salle = 130 fourmis => nouvelle reine
    // apparution de la reine + nouvelle sous salle

    printf("C'est la fin de la 1ère saison pour la fourmilière...\n");
    printf(
        "             - Création de la salle 1 bis -\n"
        "             \x1b[48;2;115;71;60m------------------------------\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m      \x1b[0m\x1b[48;2;115;71;60m---\n"
        " \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m-------------\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                    \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                                 \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                                 \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                              \x1b[0m\x1b[48;2;115;71;60m---\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "        \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                  \x1b[0m\x1b[48;2;115;71;60m ---\n"
        "           \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;115;71;60m---\n"
        "             \x1b[48;2;115;71;60m------------------------------\n",
        max, colo->nombreReines, totalbis);
    printf("Une nouvelle reine est apparue !\n");
    printf("3 mois plus tard après l'apparution de la fourmilière...");
    printf("\n");
    sleep(2);
    // ouverture de la salle 2 = debut saison 2
    // total fourmis : 130-230
    for (int i = 0; i < rand() % 51 + 30; ++i) // Augmente les ouvrières de 30 à 80
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    for (int i = 0; i < rand() % 71; ++i) // Augmente les soldats de 0 à 70
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }
    printf("\n*******************    SAISON 2   *********************\n");
    printf("C'est le début de la 2ème saison pour la fourmilière...\n");
    colo->nombreReines = 1;
    totalbis = 130 - total;
    printf(
        "             - Création de la salle 2 -\n"
        "             \x1b[48;2;115;71;60m------------------------------\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m      \x1b[0m\x1b[48;2;115;71;60m---\n"
        " \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m-------------\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m   \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                \x1b[48;2;210;160;135m-  %d   -\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                              \x1b[0m\x1b[48;2;115;71;60m---\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "        \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "           \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;115;71;60m---\n"
        "             \x1b[48;2;115;71;60m------------------------------\n",
        max, colo->nombreReines, max2, totalbis);
    printf("4,5 mois plus tard après l'apparution de la fourmilière...");
    printf("\n");
    sleep(2);

    // ouverture de la salle 2 bis = fin saison 2
    // total fourmis : 230-260
    for (int i = 0; i < rand() % 21; ++i) // Augmente les ouvrières de 0 à 20
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    for (int i = 0; i < rand() % 21 + 10; ++i) // Augmente les soldats de 10 à 30
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    colo->nombreReines = 2;
    totalbis = 90 - total;
    // apparatution d'une nouvelle reine

    printf("C'est la fin de la 2ème saison pour la fourmilière...\n");
    printf(
        "             - Création de la salle 2 bis -\n"
        "             \x1b[48;2;115;71;60m------------------------------\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m      \x1b[0m\x1b[48;2;115;71;60m---\n"
        " \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m-------------\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m   \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                 \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                             \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m    \x1b[0m\x1b[48;2;115;71;60m---\n"
        "        \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "           \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;115;71;60m---\n"
        "             \x1b[48;2;115;71;60m------------------------------\n",
        max, colo->nombreReines, max2, max, totalbis);
    printf("Une nouvelle reine est apparue !\n");
    printf("6 mois plus tard après l'apparution de la fourmilière...");
    printf("\n");
    sleep(2);

    // ouverture de la salle 3 = debut saison 3
    // total fourmis : 260-360
    for (int i = 0; i < rand() % 51 + 30; ++i) // Augmente les ouvrières de 30 à 80
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    for (int i = 0; i < rand() % 71; ++i) // Augmente les soldats de 0 à 70
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    colo->nombreReines = 2;
    totalbis = total;
    printf("\n");
    printf("*******************    SAISON 3   *********************\n");
    printf("C'est le début de la 3ème saison pour la fourmilière...\n");

    printf(
        "               - Création de la salle 3 -\n"
        "             \x1b[48;2;115;71;60m------------------------------\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m      \x1b[0m\x1b[48;2;115;71;60m---\n"
        " \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m-------------\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m   \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d   -\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "        \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "           \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;115;71;60m---\n"
        "             \x1b[48;2;115;71;60m------------------------------\n",
        max, colo->nombreReines, max2, max, totalbis, max2);
    printf("7,5 mois plus tard après l'apparution de la fourmilière...");
    printf("\n");
    sleep(2);

    // ouverture de la salle 3 bis = fin saison 3
    // total fourmis : 360-390
    for (int i = 0; i < rand() % 21 + 10; ++i) // Augmente les ouvrières de 10 à 30
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    for (int i = 0; i < rand() % 11; ++i) // Augmente les soldats de 0 à 10
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    // apparatution d'une nouvelle reine
    colo->nombreReines = 3;
    totalbis = 100 - total;

    printf("C'est la fin de la 3ème saison pour la fourmilière...\n");

    printf(
        "             - Création de la salle 3 bis -\n"
        "             \x1b[48;2;115;71;60m------------------------------\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m      \x1b[0m\x1b[48;2;115;71;60m---\n"
        " \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m-------------\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m   \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-------------\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d   -\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m----------\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                      \x1b[0m\x1b[48;2;115;71;60m---\n"
        "           \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;115;71;60m---\n"
        "             \x1b[48;2;115;71;60m------------------------------\n",
        max, colo->nombreReines, max2, totalbis, max, max, max2);
    printf("Une nouvelle reine est apparue !\n");
    printf("on est 9 mois après l'apparution de la fourmilière\nEt maintenant, après 1 an d'évolution et de travail acharné...");
    printf("\n");
    sleep(3);
}

void EvenementExterieurHiver(EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo, int *saisonActuel)
{
    static int EvnmtChoice = -1;
    if (EvnmtChoice != -1) // si EvnmtChoice = !-1, ça veut dire que l'utilisateur a déjà choisit au départ
    {
        int Hiv[8] = {0, 0, 1, 1, 2, 3, 3, 4}; // 0 = aucun  ; 1 =  tempete ; 2 = inondation ; 3 = invasion ;  4 = hiver glacial
        // le 4 (hiver glacial) ne parait qu'en hiver

        int index = rand() % 8;      // Génère un index aléatoire entre 0 et 7
        EvnmtExt->type = Hiv[index]; // selectionne une valeur du tableau

        EvnmtExt->impact = 1 + (rand() % 3); // Impact entre 1 et 3
    }
    EvnmtChoice++;

    if (EvnmtExt->type == 0) // AUCUN
    {
        EvnmtExt->impact = 0;
        printf("Comme il n'y aucun Evenement exterieur, l'impact = %d !", EvnmtExt->impact);
        phero->alarme = EvnmtExt->impact;
        phero->reine = 2 + (rand() % 2);
        phero->cohesion = 2 + (rand() % 2);
        printf("Tout va bien dans la fourmilière cet hiver,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis\n!");
        printf("\n");
    }
    else if (EvnmtExt->type == 1 || EvnmtExt->type == 2) // TEMPETE OU INONDATION
    {
        if (EvnmtExt->impact == 1)
        {
            phero->reine = 2 + (rand() % 2);
            phero->cohesion = 1 + (rand() % 2);
            phero->alarme = EvnmtExt->impact;
        }
        else if (EvnmtExt->impact == 2)
        {
            phero->reine = 1 + (rand() % 2);
            phero->cohesion = 2 + (rand() % 2);
            phero->alarme = EvnmtExt->impact;
        }
        else if (EvnmtExt->impact == 3)
        {
            phero->reine = 1 + (rand() % 2);
            phero->cohesion = 1 + (rand() % 2);
            phero->alarme = EvnmtExt->impact;
        }
        if (EvnmtExt->type == 1)
        {
            printf("La fourmilière subit une tempête,\n"
                   "c'est un hiver compliqué pour la fourmilière..\n");
            printf("La probabilité que cet événement survienne en hiver est de 25%%\n");
            printf("\n");
        }
        else
        {
            printf("La fourmilière subit une inondation,\n"
                   "c'est un hiver compliqué pour la fourmilière..\n");
            printf("La probabilité que cet événement survienne en hiver est de 12,5%%\n");
            printf("\n");
        }
    }
    else if (EvnmtExt->type == 3) // INVASION
    {
        if (EvnmtExt->impact == 1)
        {
            phero->reine = 1 + (rand() % 3);
            phero->cohesion = 1 + (rand() % 2);
            phero->alarme = EvnmtExt->impact;
        }
        else if (EvnmtExt->impact == 2)
        {
            phero->reine = 1 + (rand() % 2);
            phero->cohesion = 1 + (rand() % 2);
            phero->alarme = EvnmtExt->impact;
        }
        else if (EvnmtExt->impact == 3)
        {
            phero->reine = 1 + (rand() % 2);
            phero->cohesion = 1 + (rand() % 2);
            phero->alarme = EvnmtExt->impact;
        }
        printf("La fourmilière subit une invasion,\n"
               "c'est un hiver TRES compliqué pour la fourmilière..\n");
        printf("La probabilité que cet événement survienne en hiver est de 25%%\n");
        printf("\n");
    }
    if (EvnmtExt->type == 4) // HIVER GLACIAL
    {
        if (EvnmtExt->impact == 1)
        {
            phero->reine = phero->cohesion = 0;
            phero->alarme = EvnmtExt->impact + (rand() % 2);
            printf("La fourmilière subit un hiver glacial,\n"
                   "c'est un hiver est très compliqué pour la fourmilière..\n");
            printf("La probabilité que cet événement survienne en hiver est de 12,5%%\n");
            printf("\n");
        }
        else if (EvnmtExt->impact == 2)
        {
            phero->reine = phero->cohesion = 0;
            phero->alarme = EvnmtExt->impact + (rand() % 2);
            printf("La fourmilière subit un hiver glacial,\n"
                   "c'est un hiver est EXTREMEMENT compliqué pour la fourmilière..\n");
            printf("La probabilité que cet événement survienne en hiver est de 12,5%%\n");
            printf("\n");
        }
        else if (EvnmtExt->impact == 3)
        {
            phero->reine = phero->cohesion = 0;
            phero->alarme = EvnmtExt->impact + (rand() % 2);

            printf("La fourmilière subit un hiver glacial,\n"
                   "c'est un hiver est presque FATAL pour la fourmilière.\nL'aventure aurait pu s'arrête ici...\n");
            printf("La probabilité que cet événement survienne en hiver est de 6,25%%\n");

            int ReductionReines = 2;
            for (int i = 0; i < ReductionReines; ++i) // a chaque hiver glacial, -2 Reines, while(colo->nombreReines == 0) est la condition de sortie de l'algo
            {
                colo->nombreReines--; // les reines sont dans la même liste chainée que les ouvrières mais elles sont en tête de listes
            }
            printf("\n");
        }
    }
}

void EvenementExterieurPrintemps(EvenementExterne *EvnmtExt, Pheromone *phero, int *saisonActuel)
{
    static int EvnmtChoice = -1;
    if (EvnmtChoice != -1) // si EvnmtChoice = !-1, ça veut dire que l'utilisateur a déjà choisit au départ
    {
        int Print[8] = {0, 1, 2, 2, 3, 3, 3, 3}; // 0 = aucun  ; 1 =  tempete ; 2 = inondation ; 3 = invasion ;
        // les risques de 3 (invasion) sont plus eleves pdt le printemps

        int index = rand() % 8;       // Génère un index aléatoire entre 0 et 7
        EvnmtExt->type = Print[index]; // selectionne une valeur du tableau

        EvnmtExt->impact = 1 + (rand() % 3); // Impact entre 1 et 3
    }
    EvnmtChoice++;

    if (EvnmtExt->type == 0) // aucun
    {
        EvnmtExt->impact = 0;
        printf("Comme il n'y aucun Evenement exterieur, l'impact = %d !", EvnmtExt->impact);
        phero->alarme = EvnmtExt->impact;
        phero->reine = 4 + (rand() % 5);
        phero->cohesion = 3 + (rand() % 3);
        printf("Tout va bien dans la fourmilière ce printemps,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis !\n");
        printf("\n");
    }
    else if (EvnmtExt->type == 1 || EvnmtExt->type == 2) // TEMPETE OU INONDATION
    {
        if (EvnmtChoice != -1)
        {
            EvnmtExt->impact = 1 + (rand() % 3); // Impact entre 1 et 3
            printf("Impact de l'evenement exterieur : %d\n", EvnmtExt->impact);
        }

        if (EvnmtExt->impact == 1)
        {
            phero->reine = 3 + (rand() % 5);
            phero->cohesion = 2 + (rand() % 3);
            phero->alarme = EvnmtExt->impact;
        }
        else if (EvnmtExt->impact == 2 || EvnmtExt->impact == 3) // regrouper car pas bcp de PonteEtMortalite de tte façon => even ext rend encore + bas
        {
            phero->reine = 2 + (rand() % 3);
            phero->cohesion = 2 + (rand() % 3);
            phero->alarme = EvnmtExt->impact;
        }
        if (EvnmtExt->impact == 1)
        {
            printf("La fourmilière subit une tempête,\n"
                   "nous pensons qu'elle s'en sortira, on est au printemps quand même !\n");
            printf("La probabilité que cet événement survienne en printemps est de 12,5%%\n");
            printf("\n");
        }
        else // ( EvnmtExt->type == 2)
        {
            printf("La fourmilière subit une inondation,\n"
                   "nous pensons qu'elle s'en sortira, on est au printemps quand même !\n");
            printf("La probabilité que cet événement survienne en printemps est de 25%%\n");
            printf("\n");
        }
    }
    else if (EvnmtExt->type == 3) // INVASION
    {
        if (EvnmtChoice != -1)
        {
            EvnmtExt->impact = 1 + (rand() % 3); // Impact entre 1 et 3
            printf("Impact de l'evenement exterieur : %d\n", EvnmtExt->impact);
        }

        if (EvnmtExt->impact == 1)
        {
            phero->reine = 1 + (rand() % 2);
            phero->cohesion = 1 + (rand() % 2);
            phero->alarme = EvnmtExt->impact;
        }
        else if (EvnmtExt->impact == 2)
        {
            phero->reine = 1 + (rand() % 2);
            phero->cohesion = 1 + (rand() % 2);
            phero->alarme = EvnmtExt->impact;
        }
        else if (EvnmtExt->impact == 3)
        {
            phero->reine = 1 + (rand() % 2);
            phero->cohesion = 1 + (rand() % 2);
            phero->alarme = EvnmtExt->impact;
        }
        printf("La fourmilière subit une invasion,\n"
               "c'est un printemps compliqué !\n");
        printf("La probabilité que cet événement survienne en printemps est de 50%%\n");
        printf("\n");
    }
}

void EvenementExterieurEte(EvenementExterne *EvnmtExt, Pheromone *phero, int *saisonActuel)
{   
    static int EvnmtChoice = -1;
    if (EvnmtChoice != -1) // si EvnmtChoice = !-1, ça veut dire que l'utilisateur a déjà choisit au départ
    {
        int Ete[8] = {0, 1, 1, 1, 3, 3, 3, 3}; // 0 = aucun  ; 1 = tempete ; 2 = inondation ; 3 = invasion
        // Les inondations (2) sont inexistantes en été, et les invasions (3) sont fréquentes.

        int index = rand() % 8;     // Génère un index aléatoire entre 0 et 7
        EvnmtExt->type = Ete[index]; // Sélectionne une valeur du tableau

        EvnmtExt->impact = 1 + (rand() % 3); // Impact entre 1 et 3
    }
    EvnmtChoice++;

    if (EvnmtExt->type == 0) // aucun
    {
        EvnmtExt->impact = 0;
        phero->alarme = EvnmtExt->impact;
        phero->cohesion = 5;
        phero->reine = 4 + (rand() % 5);
        printf("Tout va bien dans la fourmilière cet été,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis !\n");
        printf("\n");
    }
    else if (EvnmtExt->type == 1) // Tempête
    {
        EvnmtExt->impact = 1 + (rand() % 3);               // Impact entre 1 et 3
        if (EvnmtExt->impact == 1 || EvnmtExt->impact == 2) // reste une période de forte PonteEtMortalite malgré even ext d'ou regrouper
        {
            phero->reine = 3 + (rand() % 5);
            phero->cohesion = 2 + (rand() % 3);
            phero->alarme = EvnmtExt->impact;
        }
        else if (EvnmtExt->impact == 3)
        {
            phero->reine = 2 + (rand() % 2);
            phero->cohesion = 3 + (rand() % 2);
            phero->alarme = EvnmtExt->impact;
        }
        printf("La fourmilière subit une tempête d'impact %d,\n"
               "elle s'en sortira !\n",
               EvnmtExt->impact);
        printf("La probabilité que cet événement survienne en été est de 37,5%%\n");
        printf("\n");
    }
    else if (EvnmtExt->type == 3) // Invasion
    {
        EvnmtExt->impact = 1 + (rand() % 3);               // Impact entre 1 et 3
        if (EvnmtExt->impact == 1 || EvnmtExt->impact == 2) // reste une période de forte PonteEtMortalite malgré even ext d'ou regrouper
        {
            phero->reine = 3 + (rand() % 5);
            phero->cohesion = 2 + (rand() % 2);
            phero->alarme = EvnmtExt->impact;
        }
        else if (EvnmtExt->impact == 3)
        {
            phero->reine = 1 + (rand() % 2);
            phero->cohesion = 2 + (rand() % 2);
            phero->alarme = EvnmtExt->impact;
        }
        printf("La fourmilière subit une invasion d'impact %d.\n", EvnmtExt->impact);
        printf("La probabilité que cet événement survienne en été est de 50%%\n");
        printf("\n");
    }
}

void EvenementExterieurAutomne(EvenementExterne *EvnmtExt, Pheromone *phero, int *saisonActuel)
{   
    static int EvnmtChoice = -1;
    if (EvnmtChoice != -1) // si EvnmtChoice = !-1, ça veut dire que l'utilisateur a déjà choisit au départ
    {
        int Aut[8] = {0, 0, 1, 1, 2, 3, 3, 3}; // 0 = aucun  ; 1 = tempête ; 2 = inondation ; 3 = invasion
        // Les invasions (3) et inondations (2) sont plus probables en automne.

        int index = rand() % 8;     // Génère un index aléatoire entre 0 et 7
        EvnmtExt->type = Aut[index]; // Sélectionne une valeur du tableau

        EvnmtExt->impact = 1 + (rand() % 3); // Impact entre 1 et 3
    }
    EvnmtChoice++;

    if (EvnmtExt->type == 0) // aucun
    {
        EvnmtExt->impact = 0;
        phero->alarme = EvnmtExt->impact;
        phero->reine = 4;
        phero->cohesion = 4;
        printf("Tout va bien dans la fourmilière cet automne,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis !\n");
        printf("\n");
    }
    else if (EvnmtExt->type == 1) // Tempête
    {
        EvnmtExt->impact = 1 + (rand() % 3); // Impact entre 1 et 3
        if (EvnmtExt->impact == 1)
        {
            phero->alarme = EvnmtExt->impact;
            phero->reine = 2 + (rand() % 2);
            phero->cohesion = 1 + (rand() % 2);
        }
        else if (EvnmtExt->impact == 2 || EvnmtExt->impact == 3) // regrouper car pas bcp de PonteEtMortalite de tte façon => even ext rend encore + bas
        {
            phero->alarme = EvnmtExt->impact;
            phero->reine = 2 + (rand() % 2);
            phero->cohesion = 1 + (rand() % 2);
        }
        printf("La fourmilière subit une tempête d'impact %d,\n"
               "un peu cocasse mais habituel, ça devrait aller pour un automne !\n",
               EvnmtExt->impact);
        printf("La probabilité que cet événement survienne en automne est de 50%%\n");
        printf("\n");
    }
    else if (EvnmtExt->type == 2) // Inondation
    {
        EvnmtExt->impact = 1 + (rand() % 3); // Impact entre 1 et 3
        if (EvnmtExt->impact == 1)
        {
            phero->alarme = EvnmtExt->impact;
            phero->reine = 2 + (rand() % 2);
            phero->cohesion = 1 + (rand() % 2);
        }
        else if (EvnmtExt->impact == 2 || EvnmtExt->impact == 3) // regrouper car pas bcp de PonteEtMortalite de tte façon => even ext rend encore + bas
        {
            phero->alarme = EvnmtExt->impact;
            phero->reine = 2 + (rand() % 2);
            phero->cohesion = 1 + (rand() % 2);
        }
        else if (EvnmtExt->impact == 3)
        {
            phero->alarme = EvnmtExt->impact;
            phero->reine = 1 + (rand() % 2);
            phero->cohesion = 1 + (rand() % 3);
        }
        printf("La fourmilière subit une inondation d'impact %d\n", EvnmtExt->impact);
        printf("La probabilité que cet événement survienne en automne est de 12,5%%\n");
        printf("\n");
    }
    else if (EvnmtExt->type == 3) // Invasion
    {
        EvnmtExt->impact = 1 + (rand() % 3); // Impact entre 1 et 3
        if (EvnmtExt->impact == 1)
        {
            phero->alarme = EvnmtExt->impact;
            phero->reine = 1;
            phero->cohesion = (EvnmtExt->impact == 3) ? 0 : 1; // Impact fort peut affecter les mâles
        }
        else if (EvnmtExt->impact == 2 || EvnmtExt->impact == 3)
        {
            phero->alarme = EvnmtExt->impact;
            phero->reine = 0;
            phero->cohesion = 0;
        }
        printf("La fourmilière subit une invasion d'impact %d,\n"
               "un peu cocasse mais gérable!",
               EvnmtExt->impact);
        printf("La probabilité que cet événement survienne en automne est de 37,5%%\n");
        printf("\n");
    }

}

void PonteEtMortalite(Pheromone *phero, Colonie *colo)
{
    srand(time(NULL)); // générateur de nombres aléatoires

    if (phero->alarme >= 2)
    {
        phero->ambiance = 1 + (rand() % 4); // ambiance hivernal (1 à 4)

        for (int j = 0; j < rand() % 16 + 25; ++j)
        {                                                //  "5" = seuil d'exclusion, ce sont des fourmis protégés
            supprimerFourmiVieille(&colo->ouvrieres, 5); // reduction des ouvrières
        }
        for (int j = 0; j < rand() % 11 + 15; ++j)
        {
            supprimerFourmiVieille(&colo->soldats, 9); // reduction des soldats, min = 9
        }
    }
    else
    {
        int pheroGlobal = phero->reine + phero->cohesion;

        if (pheroGlobal >= 3)
        {
            phero->ambiance = 5 + (rand() % 4); // ambiance automne ou printemps (5 à 8)

            if (phero->ambiance == 5 || phero->ambiance == 6)
            {
                for (int j = 0; j < rand() % 6 + 15; ++j) // Ajouter de nouvelles ouvrières si le ambiance est favorable (printemps/automne)
                {
                    ajouterFourmi(&colo->soldats, ROLE_SOLDAT); // Augmentation des soldats
                }

                for (int j = 0; j < rand() % 6 + 10; ++j)
                {
                    supprimerFourmiMale(&colo->males); // Réduit les mâles
                }
            }
            else if (phero->ambiance == 7 || phero->ambiance == 8)
            {
                for (int j = 0; j < rand() % 11 + 30; ++j) // Ajouter encore plus d'ouvrières si le ambiance est plus favorable (printemps/automne)
                {
                    ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE); // Augmentation des ouvrières
                }
                for (int j = 0; j < rand() % 16 + 20; ++j)
                {
                    supprimerFourmiMale(&colo->males); // Réduit les mâles
                }
            }
        }
    }
}

void hiver(int *saisonActuel, SystemeAgricole *agriculture, EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo, SystemeElevage *elevage)
{
    *saisonActuel = 0; // déréférencement du pointeur pour pouvoir lui assigné une valeur

    agriculture->quantitéGraines += agriculture->quantitéGraines * (-40 + rand() % 21) / 100;           // Réduction entre -40% et -20%
    agriculture->quantitéDeNourriture += agriculture->quantitéDeNourriture * (-40 + rand() % 21) / 100; // Réduction entre -40% et -20%

    colo->males = NULL;

    int hiverVariation = -60 + rand() % 21; // Variation negatives des pucerons (de -40% à -60%)
    elevage->nombrePucerons += elevage->nombrePucerons * hiverVariation / 100;

    int nOuvrieres = compterFourmis(colo->ouvrieres);
    int nOuvrièresSupprimes = nOuvrieres * (70 + rand() % 21) / 100; // suppression entre 70% et 90%
    for (int j = 0; j < nOuvrièresSupprimes; ++j)
    {
        supprimerFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
}

void printemps(int *saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo)
{
    *saisonActuel = 1; // déréférencement du pointeur pour pouvoir lui assigné une valeur

    agriculture->quantitéGraines += agriculture->quantitéGraines * (25 + rand() % 11) / 100; // augmentation entre 25% et 35%
    agriculture->quantitéDeNourriture += agriculture->quantitéDeNourriture * (30 + rand() % 11) / 100;

    int nOuvrieres = compterFourmis(colo->ouvrieres);

    int nMalesAjoutes = nOuvrieres * (20 + rand() % 11) / 100; // augmentation entre 20% et 30%
    for (int j = 0; j < nMalesAjoutes; ++j)
    { // Ajout des fourmis mâles
        ajouterFourmiMale(&colo->males);
    }

    int nSoldatsAjoutes = nOuvrieres * (10 + rand() % 6) / 100; // ajout entre 10% et 15%
    for (int j = 0; j < nSoldatsAjoutes; ++j)
    { // Ajout des soldats
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    int printempsVariation = 50 + rand() % 51; // Variation des pucerons (augmentation de 50% à 100%)
    elevage->nombrePucerons += elevage->nombrePucerons * printempsVariation / 100;
/*
    printf("Printemps terminé : %d mâles ajoutés,nouveaux soldats : %d, nouvelles graines : %d, nouvelle nourriture : %d\n",
           nMalesAjoutes ,nSoldatsAjoutes, agriculture->quantitéGraines, agriculture->quantitéDeNourriture);
*/}

void ete(int *saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo)
{
    *saisonActuel = 2; // déréférencement du pointeur pour pouvoir lui assigné une valeur

    agriculture->quantitéGraines += agriculture->quantitéGraines * (60 + rand() % 31) / 100;
    agriculture->quantitéDeNourriture += agriculture->quantitéDeNourriture * (50 + rand() % 11) / 100;

    int eteVariation = 30 + rand() % 41; // Variation entre +30 % et +70 %
    elevage->nombrePucerons += elevage->nombrePucerons * eteVariation / 100;
}

void automne(int *saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo)
{
    *saisonActuel = 3; // déréférencement du pointeur pour pouvoir lui assigné une valeur

    agriculture->quantitéGraines -= agriculture->quantitéGraines * (30 + rand() % 21) / 100;
    agriculture->quantitéDeNourriture -= agriculture->quantitéDeNourriture * (30 + rand() % 11) / 100;

    int nOuvrieres = compterFourmis(colo->ouvrieres);
    int nMalesSupprimes = nOuvrieres * (10 + rand() % 11) / 100;

    for (int j = 0; j < nMalesSupprimes; ++j) // Suppression des fourmis mâles à l'approche de l'hiver
    {
        supprimerFourmiMale(&colo->males);
    }

    int nOuvrièresSupprimes = nOuvrieres * (10 + rand() % 11) / 100; // suppression entre 10% et 20%
    for (int j = 0; j < nOuvrièresSupprimes; ++j)
    {
        supprimerFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }

    int automneVariation = -20 + rand() % 21; // Variation negatives des pucerons (de -20% à -40%)
    elevage->nombrePucerons += elevage->nombrePucerons * automneVariation / 100;

    /*printf("Automne terminé : %d mâles supprimés, nouvelles graines : %d, nouvelle nourriture : %d\n",
           nMalesSupprimer, agriculture->quantitéGraines, agriculture->quantitéDeNourriture);
*/
}

void NiveauSecuritéEtProtection(Sécurité *secu, Colonie *colo)
{

    // Genere aleaatoirement des valeurs entre 1 à 3
    secu->niveauProtection = rand() % 3 + 1;
    secu->attaquesReçues = rand() % 3 + 1;
    int pertes = 0;
    int impact = secu->attaquesReçues - secu->niveauProtection;
    if (impact <= 0)
    {
        pertes = 0; // La protection compense les attaques ou les dépasse
    }
    else
    {
        pertes = impact * 3; // Les pertes augmentent avec la différence, mais sont limitées à un maximum de 10
        if (pertes > 10)
        {
            pertes = 10;
        }
    }

    int nombreSoldats = compterFourmis(colo->soldats); // Calculer le nombre actuel de soldats dans la colonie
    if (pertes > nombreSoldats)                        // Vérification des seuils (les pertes ne dépassent pas le nombre total de soldats)
    {
        pertes = nombreSoldats;
    }

    for (int i = 0; i < pertes; i++) // Appliquer les pertes
    {
        supprimerFourmiVieille(&colo->soldats, 9); // Suppression des fourmis soldats les plus anciennes mais un minimum de 9
    }

    printf("Niveau de protection : %d, Attaques reçues : %d\n", secu->niveauProtection, secu->attaquesReçues);
    printf("Nombre de pertes en soldats (causé par protection/attaques): %d\n", pertes);
    printf("\n");
}

void NiveauPropreteEtMaladie(Hygiène *hyg, Colonie *colo)
{
    // Genere aleaatoirement des valeurs entre 1 à 3
    hyg->niveauProprete = rand() % 3 + 1;
    hyg->niveauMaladie = rand() % 3 + 1;

    int pertes = 0;
    int impact = hyg->niveauMaladie - hyg->niveauProprete;
    if (impact <= 0)
    {
        pertes = 0; // L'hygiène compense ou dépasse le niveau de maladie
    }
    else
    {

        pertes = impact * 4; // Les pertes augmentent avec la différence, mais sont limitées à un maximum de 12
        if (pertes > 12)
        {
            pertes = 12;
        }
    }

    int nombreOuvrieres = compterFourmis(colo->ouvrieres);
    if (pertes > nombreOuvrieres)
    {
        pertes = nombreOuvrieres;
    }

    for (int i = 0; i < pertes; i++)
    {
        supprimerFourmiVieille(&colo->ouvrieres, 5); // Suppression des fourmis soldats les plus anciennes mais protection des reines donc 5 est le seuil d'exclusion
    }

    printf("Niveau de propreté : %d, Niveau de maladie : %d\n", hyg->niveauProprete, hyg->niveauMaladie);
    printf("Nombre de pertes en ouvrières (causé par hyg/maladie): %d\n", pertes);
    printf("\n");
}