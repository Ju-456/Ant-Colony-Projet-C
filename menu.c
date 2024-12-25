#include "fourmi.h"

#include "AnnexeFunctions.c"
#include "RandomSide.c"
#include "ChosenSide.c"

#include <stdio.h>
#include <string.h>
#include <unistd.h> // Pour le "sleep(3)"
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour srand(time(NULL));

void menu(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int saisonActuel, EvenementExterne EvnmtExt, Pheromone *phero, Hygiène *hyg, Sécurité *secu, Architecture archi, Environnement enviro)
{
    printf("Souhaitez-vous une simulation aléatoire (1) ou choisir les valeurs (2) ?");

    int choice = 0;
    printf(
        "\n1. Valeurs aléatoires\n"
        "2. Valeurs à choisir \n"
        "Entrer votre choix : ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:

        // FourmiliereEnEvolution(colo);

        RandomColonie(colo, elevage, agriculture);

        cultiverGraines(agriculture);
        elevagePucerons(elevage);
        gererHygiene(hyg);
        gererSecurite(secu);
        construireSalle(&archi);
        explorer(&enviro);

        while (colo->nombreReines != 0)
        {
            simuleUneSaisonRandom(colo, agriculture, elevage, nbSaison, saisonActuel, EvnmtExt, phero, archi);
            GestionEvenementExterneRandom(saisonActuel,EvnmtExt,phero,colo);
            PonteEtMortalite(phero,colo);
            affichageCycleSaisonRandom(colo, agriculture, elevage, phero);
        }
        break;

    case 2:
        ChosenColonie(colo, agriculture, elevage, &archi, hyg, secu);
        //afficherEtatColonie(colo,agriculture,elevage, hyg, secu); // pour un affichage plus simple
        affichageCycleSaisonChosen(archi,colo, agriculture, elevage, phero);

        while (colo->nombreReines != 0)
        {
            simuleUneSaisonChosen(colo, agriculture, elevage, nbSaison, saisonActuel, EvnmtExt, phero, archi);
            GestionEvenementExterneChosen(saisonActuel,EvnmtExt,phero,colo);
            PonteEtMortalite(phero,colo);
            affichageCycleSaisonChosen(archi,colo, agriculture, elevage, phero);
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
            supprimerFourmiVieille(&colo->soldats, 5); // reduction des soldats
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
                    ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE); // Augmentation des ouvrières
                    ajouterFourmi(&colo->soldats, ROLE_SOLDAT);     // Augmentation des soldats
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


void hiver(int saisonActuel, SystemeAgricole *agriculture, EvenementExterne EvnmtExt, Pheromone *phero, Colonie *colo, SystemeElevage *elevage)
{
    saisonActuel = 0;

    agriculture->quantitéGraines += agriculture->quantitéGraines * (-40 + rand() % 21) / 100; // Réduction entre -40% et -20%
    agriculture->quantitéDeNourriture += agriculture->quantitéDeNourriture * (-40 + rand() % 21) / 100; // Réduction entre -40% et -20%

    colo->males = NULL;
    
    int hiverVariation = -60 + rand() % 21; // Variation negatives des pucerons (de -40% à -60%)
    elevage->nombrePucerons += elevage->nombrePucerons * hiverVariation / 100;

     
}

void printemps(int *saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone *phero, Colonie *colo) {
    *saisonActuel = 1;

    agriculture->quantitéGraines += agriculture->quantitéGraines * (25 + rand() % 11) / 100; // augmentation entre 25% et 35%
    agriculture->quantitéDeNourriture += agriculture->quantitéDeNourriture * (30 + rand() % 11) / 100;

    int nOuvrieres = compterFourmis(colo->ouvrieres);
    
    int nMalesAjoutes  = nOuvrieres * (20 + rand() % 11) / 100; //augmentation entre 20% et 30%
    for (int j = 0; j < nMalesAjoutes ; ++j) {// Ajout des fourmis mâles
        ajouterFourmiMale(&colo->males);
    }

    int nSoldatsAjoutes = nOuvrieres * (10 + rand() % 6) / 100; //ajout entre 10% et 15%
    for (int j = 0; j < nSoldatsAjoutes ; ++j) {// Ajout des soldats
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    int printempsVariation = 50 + rand() % 51;// Variation des pucerons (augmentation de 50% à 100%)
    elevage->nombrePucerons += elevage->nombrePucerons * printempsVariation / 100;
/*
    printf("Printemps terminé : %d mâles ajoutés,nouveaux soldats : %d, nouvelles graines : %d, nouvelle nourriture : %d\n",
           nMalesAjoutes ,nSoldatsAjoutes, agriculture->quantitéGraines, agriculture->quantitéDeNourriture);
*/}

void ete(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone *phero, Colonie *colo)
{
    saisonActuel = 2;

    agriculture->quantitéGraines += agriculture->quantitéGraines * (60 + rand() % 31) / 100;
    agriculture->quantitéDeNourriture += agriculture->quantitéDeNourriture * (50 + rand() % 11) / 100;

    int eteVariation = 30 + rand() % 41; // Variation entre +30 % et +70 %
    elevage->nombrePucerons += elevage->nombrePucerons * eteVariation / 100;

}

void automne(int *saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone *phero, Colonie *colo) {
    *saisonActuel = 3;

    agriculture->quantitéGraines -= agriculture->quantitéGraines * (30 + rand() % 21) / 100;
    agriculture->quantitéDeNourriture -= agriculture->quantitéDeNourriture * (30 + rand() % 11) / 100;

    int nOuvrieres = compterFourmis(colo->ouvrieres);
    //int nMalesExistants = compterFourmisMales(colo->males);
    int nMalesSupprimer = nOuvrieres * (10 + rand() % 11) / 100;
    
    for (int j = 0; j < nMalesSupprimer; ++j) { // Suppression des fourmis mâles à l'approche de l'hiver
        supprimerFourmiMale(&colo->males);
    }

    int automneVariation = -20 + rand() % 21;// Variation negatives des pucerons (de -20% à -40%)
    elevage->nombrePucerons += elevage->nombrePucerons * automneVariation / 100;

    /*printf("Automne terminé : %d mâles supprimés, nouvelles graines : %d, nouvelle nourriture : %d\n",
           nMalesSupprimer, agriculture->quantitéGraines, agriculture->quantitéDeNourriture);
*/
}

/*
// Fonction pour calculer les pertes en soldats et les appliquer directement
void calculer_pertes_Securite_Protection(Sécurité *securite, Colonie *colo)
{
    float pertes = 0.0;

    // Vérification des niveaux de sécurité et de protection
    if (securite->niveauProtection < 1 || securite->niveauProtection > 3)
    {
        printf("Erreur: niveau de protection invalide.\n");
        return; // Sortir de la fonction pour les cas invalides
    }

    // Calcul des pertes en fonction des niveaux de sécurité et de protection
    if (securite->niveauProtection == 1)
    {
        if (securite->niveauProtection == 1)
        {
            pertes = 15.0; // Sécurité faible, protection faible
        }
        else if (securite->niveauProtection == 2)
        {
            pertes = 8.0; // Sécurité faible, protection moyenne
        }
        else if (securite->niveauProtection == 3)
        {
            pertes = 10.0; // Sécurité faible, protection élevée
        }
    }
    else if (securite->niveauProtection == 2)
    {
        if (securite->niveauProtection == 1)
        {
            pertes = 5.0; // Sécurité moyenne, protection faible
        }
        else if (securite->niveauProtection == 2)
        {
            pertes = 0.0; // Sécurité moyenne, protection moyenne
        }
        else if (securite->niveauProtection == 3)
        {
            pertes = 5.0; // Sécurité moyenne, protection élevée
        }
    }
    else if (securite->niveauProtection == 3)
    {
        if (securite->niveauProtection == 1)
        {
            pertes = 15.0; // Sécurité élevée, protection faible
        }
        else if (securite->niveauProtection == 2)
        {
            pertes = 5.0; // Sécurité élevée, protection moyenne
        }
        else if (securite->niveauProtection == 3)
        {
            pertes = 0.0; // Sécurité élevée, protection élevée
        }
    }

    // Appliquer les pertes aux soldats de la colonie
    int nombreSoldats = compterFourmis(colo->soldats);
    int pertesSoldats = (int)(nombreSoldats * (pertes / 100));

    // Supprimer les soldats en fonction des pertes calculées
    for (int i = 0; i < pertesSoldats; i++)
    {
        supprimerFourmi(&colo->soldats, colo->soldats); // Suppression de la première fourmi soldat
    }

    printf("Pourcentage de pertes en soldats: %.2f%%\n", pertes);
}


// Fonction pour calculer les pertes en ouvrières et les appliquer directement
void calculer_pertes_Hygiene_Maladie(Hygiène *hygiene, Colonie *colo)
{
    float pertes = 0.0;

    // Vérification des niveaux d'hygiène et de maladie
    if (hygiene->niveauHygiene < 1 || hygiene->niveauHygiene > 3 || hygiene->niveauMaladie < 1 || hygiene->niveauMaladie > 3)
    {
        printf("Erreur : niveaux d'hygiène ou de maladie invalides.\n");
        return; // Sortie en cas d'erreur
    }

    // Calcul des pertes en fonction des niveaux d'hygiène et de maladie
    if (hygiene->niveauHygiene == 1)
    {
        if (hygiene->niveauMaladie == 1)
        {
            pertes = 10.0; // Hygiène faible, maladie faible
        }
        else if (hygiene->niveauMaladie == 2)
        {
            pertes = 8.0; // Hygiène faible, maladie moyenne
        }
        else if (hygiene->niveauMaladie == 3)
        {
            pertes = 15.0; // Hygiène faible, maladie élevée
        }
    }
    else if (hygiene->niveauHygiene == 2)
    {
        if (hygiene->niveauMaladie == 1)
        {
            pertes = 5.0; // Hygiène moyenne, maladie faible
        }
        else if (hygiene->niveauMaladie == 2)
        {
            pertes = 0.0; // Hygiène moyenne, maladie moyenne
        }
        else if (hygiene->niveauMaladie == 3)
        {
            pertes = 3.0; // Hygiène moyenne, maladie élevée
        }
    }
    else if (hygiene->niveauHygiene == 3)
    {
        if (hygiene->niveauMaladie == 1)
        {
            pertes = 0.0; // Hygiène élevée, maladie faible
        }
        else if (hygiene->niveauMaladie == 2)
        {
            pertes = 5.0; // Hygiène élevée, maladie moyenne
        }
        else if (hygiene->niveauMaladie == 3)
        {
            pertes = 15.0; // Hygiène élevée, maladie élevée
        }
    }

    // Calculer et appliquer les pertes aux ouvrières de la colonie
    int nombreOuvrieres = compterFourmis(colo->ouvrieres);
    int pertesOuvrieres = (int)(nombreOuvrieres * (pertes / 100));

    // Supprimer les ouvrières en fonction des pertes calculées
    for (int i = 0; i < pertesOuvrieres; i++)
    {
        supprimerFourmi(&colo->ouvrieres, colo->ouvrieres); // Suppression de la première ouvrière
    }

    printf("Pourcentage de pertes en ouvrières : %.2f%%\n", pertes);
}
*/
