#include "fourmi.h"

#include "AnnexeFunctions.c"
#include "RandomSide.c"
#include "ChosenSide.c"

#include <stdio.h>
#include <string.h>
#include <unistd.h> // Pour le "sleep(3)"
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour srand(time(NULL));

void menu(Colonie *colo, int nbSaison, int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, Architecture archi, int saisonChoice)
{
    printf("Souhaitez vous une simulation aléatoire (1) ou choisir les valeurs (2) ?");

    int choice = 0;
    printf(
        "\n1. Valeurs aléatoires\n"
        "2. Valeurs à choisir \n"
        "Entrer votre choix :");
    scanf("%d", &choice);
    
    switch (choice)
    {
    case 1:

        RandomColonie(colo);

        SystemeAgricole agriculture = {100, 50};
        SystemeElevage elevage = {10};
        Hygiène hyg = {100, 0};
        Sécurité secu = {10, 0};
        Architecture archi = {0};
        Environnement enviro = {0, 200};

        cultiverGraines(&agriculture);
        elevagePucerons(&elevage);
        gererHygiene(&hyg);
        gererSecurite(&secu);
        construireSalle(&archi);
        explorer(&enviro);
        
        FourmiliereEnEvolution(colo); // Départ de la colonie
        
        while(colo->nombreReines != 0){
            simuleUneSaisonRandom(colo, &agriculture, &elevage, nbSaison, saisonActuel, EvnmtExt, phero, archi);
        }// simuleUneSaisonRandom (appeler une saison) -> ex : hiver -> GestionEvenementExterneRandom -> ReproductionEtMortalite -> affichageCycleSaison
        break;
    case 2:
        ChosenColonie(saisonChoice, colo, &agriculture, &elevage, &hyg, &secu, &archi);

        while(colo->nombreReines != 0){
            simuleUneSaisonChosen(saisonChoice, colo, &agriculture, &elevage, nbSaison, saisonActuel, EvnmtExt, phero, archi);
        }// idem que simuleUneSaisonRandom
    }
}

int FourmiliereEnEvolution(Colonie *colo)
{

    srand(time(NULL));

    if (!colo)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la colonie\n");
        return -1;
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

void hiver(int saisonActuel, SystemeAgricole *agriculture, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, SystemeElevage *elevage)
{
    saisonActuel = 0;
    agriculture->quantitéDeNourriture += 10; // Simule une faible production alimentaire en hiver
    agriculture->quantitéGraines += 5;
}

void printemps(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo)
{
    saisonActuel = 1;
    agriculture->quantitéDeNourriture += 25; // Production accrue au printemps
    agriculture->quantitéGraines += 15;
    elevage->nombrePucerons += 20;
}

void ete(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo)
{
    saisonActuel = 2;
    agriculture->quantitéDeNourriture += 30; // Production stable en été
    agriculture->quantitéGraines += 20;
    elevage->nombrePucerons += 30;
}

void automne(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo)
{
    saisonActuel = 3;
    agriculture->quantitéDeNourriture += 15; // Production décroissante en automne
    agriculture->quantitéGraines += 10;
    elevage->nombrePucerons += 10;
}
