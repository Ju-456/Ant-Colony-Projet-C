#include <stdio.h>
#include <string.h>
#include <unistd.h> // Pour le "sleep(3)"
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour srand(time(NULL));

static int prochainId = 1;// Variable G pour gérer les IDs incrémentaux

// Définition des rôles des fourmis
#define ROLE_OUVRIERE 0
#define ROLE_SOLDAT 1
#define ROLE_REINE 2
#define ROLE_MALE 3
#define ROLE_POT_DE_MIEL 4

// Structure pour une fourmi
typedef struct Fourmi
{
    int id;
    int age;
    int role;
    struct Fourmi *suivante;
} Fourmi;

// Structure pour une fourmi mâle
typedef struct FourmiMale
{
    int id;
    int age;
    int role;
    struct FourmiMale *suivante;
} FourmiMale;

// Structure pour une colonie
typedef struct Colonie
{
    int id;
    int nombreReines;
    Fourmi *ouvrieres;
    FourmiMale *males;
    Fourmi *soldats;
} Colonie;

void ajouterFourmi(Fourmi **tete, int role)// Fonction générique pour ajouter une fourmi à une liste
{
    Fourmi *nouvelle = malloc(sizeof(Fourmi));
    if (!nouvelle)
    {
        fprintf(stderr, "Erreur d'allocation mémoire pour une nouvelle fourmi\n");
        return;
    }

    nouvelle->id = prochainId++; // Une fourmi = un ID unique
    nouvelle->age = 0;
    nouvelle->role = role;
    nouvelle->suivante = *tete;
    *tete = nouvelle;
}

// Fonction pour compter les fourmis dans une liste
int compterFourmis(Fourmi *tete) {
    int count = 0;
    while (tete) {
        count++;
        tete = tete->suivante;
    }
    return count;
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
        "             ------------------------------\n"
        "        -----                               ----\n"
        "      ---                                     ---\n"
        "    ---            ---------                    ---\n"
        "  ---              -  %d   -                      ---\n"
        " ---               ---------                       ---\n"
        "---                                                 ---\n"
        "---                                                 ---\n"
        "---                                                 ---\n"
        "---                                                 ---\n"
        "  ---                                              ---\n"
        "      ---                                        ---\n"
        "        ---                                   ---\n"
        "           ---                            ---\n"
        "             ------------------------------\n",
        total);
        printf("1,5 mois plus tard...");
        printf("\n");
    sleep(3);

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
    printf(
        "             - Création de la salle 1 bis -\n"
        "             ------------------------------\n"
        "        -----                               ----\n"
        "      ---                                     ---\n"
        "    ---            ---------          ------     ---\n"
        "  ---              -  %d  -          - %d -      ---\n"
        " ---               -------------      ------       ---\n"
        "---                       - %d -                   ---\n"
        "---                       ------                    ---\n"
        "---                                                 ---\n"
        "---                                                 ---\n"
        "  ---                                              ---\n"
        "      ---                                        ---\n"
        "        ---                                   ---\n"
        "           ---                            ---\n"
        "             ------------------------------\n",
        max, colo->nombreReines, totalbis);
        printf("C'est la fin de la 1ère saison pour la fourmilière...\n");
        printf("1,5 mois plus tard...");
        printf("\n");
    sleep(3);

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
        "               - Création de la salle 2 -\n"
        "             ------------------------------\n"
        "        -----                               ----\n"
        "      ---                                     ---\n"
        "    ---            ---------          ------     ---\n"
        "  ---              -  %d  -           - %d -      ---\n"
        " ---               -------------      ------       ---\n"
        "---                       - %d -                   ---\n"
        "---                       ------   ---------        ---\n"
        "---                                -  %d   -        ---\n"
        "---                                ---------        ---\n"
        "  ---                                              ---\n"
        "      ---                                       ---\n"
        "        ---                                   ---\n"
        "           ---                            ---\n"
        "             ------------------------------\n",
        max, colo->nombreReines, max2, totalbis);
        printf("1,5 mois plus tard...");
        printf("\n");
    sleep(3);

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
        "             ------------------------------\n"
        "        -----                               ----\n"
        "      ---                                     ---\n"
        "    ---            ---------          ------     ---\n"
        "  ---              -  %d  -           - %d -      ---\n"
        " ---               -------------      ------       ---\n"
        "---                       - %d -                   ---\n"
        "---                       ------   ---------        ---\n"
        "---                                -  %d  -        ---\n"
        "---                                ---------        ---\n"
        "  ---                                 - %d -       ---\n"
        "      ---                             ------    ---\n"
        "        ---                                   ---\n"
        "           ---                            ---\n"
        "             ------------------------------\n",
        max, colo->nombreReines, max2, max, totalbis);
         printf("Une nouvelle reine est apparue !\n");
         printf("1,5 mois plus tard...");
        printf("\n");
    sleep(3);

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
        "             ------------------------------\n"
        "        -----                               ----\n"
        "      ---                                     ---\n"
        "    ---            ---------          ------     ---\n"
        "  ---              -  %d  -           - %d -      ---\n"
        " ---               -------------      ------       ---\n"
        "---                       - %d -                   ---\n"
        "---                       ------   ---------        ---\n"
        "---                                -  %d  -        ---\n"
        "---                ---------       ---------        ---\n"
        "  ---              -   %d  -          - %d -       ---\n"
        "      ---          ---------          ------    ---\n"
        "        ---                                   ---\n"
        "           ---                            ---\n"
        "             ------------------------------\n",
        max, colo->nombreReines, max2, max, totalbis, max2);
        printf("1,5 mois plus tard...");
        printf("\n");
    sleep(3);

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
        "             ------------------------------\n"
        "        -----                               ----\n"
        "      ---                                     ---\n"
        "    ---            ---------          ------     ---\n"
        "  ---              -  %d  -           - %d -      ---\n"
        " ---               -------------      ------       ---\n"
        "---                       - %d -                   ---\n"
        "---           ------      ------   ---------        ---\n"
        "---           - %d -               -  %d  -        ---\n"
        "---           --------------       ---------        ---\n"
        "  ---              -  %d  -          - %d -       ---\n"
        "      ---          ---------          ------    ---\n"
        "        ---                                   ---\n"
        "           ---                            ---\n"
        "             ------------------------------\n",
        max, colo->nombreReines, max2, totalbis, max, max, max2);
        printf("Une nouvelle reine est apparue !\n");
        printf("1 an plus tard...");
        printf("\n");
    sleep(3);
}

int main (){
    Colonie *colo = (Colonie *)malloc(sizeof(Colonie)); // = creerColonie(0, 5); creation de colonie aleatoir à la place
    FourmiliereEnEvolution(colo);
}