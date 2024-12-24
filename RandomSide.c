#include "fourmi.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h> // Pour le "sleep(3)"
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour srand(time(NULL));

// Initialisation aléatoire de la colonie
int RandomColonie(Colonie *colo, SystemeElevage *elevage, SystemeAgricole *agriculture)
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
    
    // Ajout fixe de reines
    int nReines = 5; // Nombre de reines
    for (int i = 0; i < nReines; ++i)
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_REINE); // les reines sont dans la même liste chainée que les ouvrières mais elles sont en tête de listes
    }

    // Ajout aléatoire d'ouvrières
    int nOuvrieres = rand() % 301 + 150; // Nombre entre 150 et 210
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
    agriculture->quantitéDeNourriture = nOuvrieres * (2 + rand() % 3); // 2 - 4 * de la proportion d'ouvrières
    agriculture->quantitéGraines = nOuvrieres * (2 + rand() % 6);      // 2 - 7 * de la proportion d'ouvrières

    return 0; // Succès
}

void simuleUneSaisonRandom(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, Architecture archi)
{
    for (int i = 0; i < nbSaison; ++i)
    {
        switch (i % 4)
        { // Répartition des saisons : 0 = HIVER, 1 = PRINTEMPS, 2 = ETE, 3 = AUTOMNE

        case 0: // HIVER
            hiver(saisonActuel, agriculture, EvnmtExt, phero, colo, elevage);
            GestionEvenementExterneRandom(saisonActuel, EvnmtExt, phero, colo);
            printf("************************************** Fin de l'HIVER ****************************\n\n");
            break;

        case 1: // PRINTEMPS
            printemps(&saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
            GestionEvenementExterneRandom(saisonActuel, EvnmtExt, phero, colo);
            printf("************************************** Fin du PRINTEMPS **************************\n\n");
            break;

        case 2: // ETE
            ete(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
            GestionEvenementExterneRandom(saisonActuel, EvnmtExt, phero, colo);
            printf("************************************** Fin de l'ÉTÉ ******************************\n\n");
            break;

        case 3: // AUTOMNE
            automne(&saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
            GestionEvenementExterneRandom(saisonActuel, EvnmtExt, phero, colo);
            printf("************************************** Fin de l'AUTOMNE ******************************\n\n");
            break;

        default:
            break;
        }

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

// impact le taux de pheromones des fourmis qui impact la PonteEtMortalite
void GestionEvenementExterneRandom(int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo)
{
    if (saisonActuel == 0) // HIVER
    {
        int Hiv[8] = {0, 0, 1, 1, 2, 3, 3, 4}; // 0 = aucun  ; 1 =  tempete ; 2 = inondation ; 3 = invasion ;  4 = hiver glacial
        // le 4 (hiver glacial) ne parait qu'en hiver

        int index = rand() % 8;     // Génère un index aléatoire entre 0 et 7
        EvnmtExt.type = Hiv[index]; // selectionne une valeur du tableau

        if (EvnmtExt.type == 0) // AUCUN
        {
            EvnmtExt.impact = 0;
            phero.alarme = EvnmtExt.impact;
            phero.reine = 1 + (rand() % 2);
            phero.cohesion = 1 + (rand() % 2);
            printf("Tout va bien dans la fourmilière cet hiver,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis\n!");
        }
        else if (EvnmtExt.type == 1 || EvnmtExt.type == 2) // TEMPETE OU INONDATION
        {
            EvnmtExt.impact = 1 + (rand() % 3); // valeur aleatoire entre 1,2 et 3 pour determiner l'impact de l'even ext
            if (EvnmtExt.impact == 1)
            {
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 2)
            {
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            if (EvnmtExt.type == 1)
            {
                printf("La fourmilière subit une tempête d'impact %d,\n"
                       "c'est un hiver compliqué pour la fourmilière..\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 25%%\n");
            }
            else
            {
                printf("La fourmilière subit une inondation d'impact %d,\n"
                       "c'est un hiver compliqué pour la fourmilière..\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 12,5%%\n");
            }
        }
        else if (EvnmtExt.type == 3) // INVASION
        {
            EvnmtExt.impact = 1 + (rand() % 3); // valeur aleatoire entre 1,2 et 3 pour determiner l'impact de l'even ext
            if (EvnmtExt.impact == 1)
            {
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 2)
            {
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            printf("La fourmilière subit une invasion d'impact %d,\n"
                   "c'est un hiver TRES compliqué pour la fourmilière..\n",
                   EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en hiver est de 25%%\n");
        }
        if (EvnmtExt.type == 4) // HIVER GLACIAL
        {
            EvnmtExt.impact = 1 + (rand() % 3); // valeur aleatoire entre 1,2 et 3 pour determiner l'impact de l'even ext
            if (EvnmtExt.impact == 1)
            {
                phero.reine = phero.cohesion = 0;
                phero.alarme = EvnmtExt.impact + (rand() % 2);
            }
            else if (EvnmtExt.impact == 2)
            {
                phero.reine = phero.cohesion = 0;
                phero.alarme = EvnmtExt.impact + (rand() % 2);
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.reine = phero.cohesion = 0;
                phero.alarme = EvnmtExt.impact + (rand() % 2);
            }
            if (EvnmtExt.impact == 1 || EvnmtExt.impact == 2)
            {
                printf("La fourmilière subit un hiver glacial d'impact %d,\n"
                       "c'est un hiver est EXTREMEMENT compliqué pour la fourmilière..\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 6,25%%\n");
            }
            else // cad si EvnmtExt.impact == 3
            {
                printf("La fourmilière subit un hiver glacial d'impact %d,\n"
                       "c'est un hiver est FATAL pour la fourmilière.\nL'aventure s'arrête ici...\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 12,5%%\n");
                colo->nombreReines = colo->nombreReines - 2; // a chaque hiver glacial, -2 Reines, while(colo->nombreReines == 0) est la condition de sortie de l'algo
            }
        }
    }
    else if (saisonActuel == 1) // PRINTEMPS
    {
        int Print[8] = {0, 1, 2, 2, 3, 3, 3, 3}; // 0 = aucun  ; 1 =  tempete ; 2 = inondation ; 3 = invasion ;
        // les risques de 3 (invasion) sont plus eleves pdt le printemps

        int index = rand() % 8;       // Génère un index aléatoire entre 0 et 7
        EvnmtExt.type = Print[index]; // selectionne une valeur du tableau

        if (EvnmtExt.type == 0) // aucun
        {
            EvnmtExt.impact = 0;
            phero.alarme = EvnmtExt.impact;
            phero.reine = 3 + (rand() % 5);
            phero.cohesion = 2 + (rand() % 3);
            printf("Tout va bien dans la fourmilière ce printemps,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis !\n");
        }
        else if (EvnmtExt.type == 1 || EvnmtExt.type == 2) // TEMPETE OU INONDATION
        {
            EvnmtExt.impact = 1 + (rand() % 3); // valeur aleatoire entre 1,2 et 3 pour determiner l'impact de l'even ext
            if (EvnmtExt.impact == 1)
            {
                phero.reine = 3 + (rand() % 5);
                phero.cohesion = 2 + (rand() % 3);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3) // regrouper car pas bcp de PonteEtMortalite de tte façon => even ext rend encore + bas
            {
                phero.reine = 2 + (rand() % 3);
                phero.cohesion = 1 + (rand() % 3);
                phero.alarme = EvnmtExt.impact;
            }
            if (EvnmtExt.impact == 1)
            {
                printf("La fourmilière subit une tempête d'impact %d,\n"
                       "nous pensons qu'elle s'en sortira, on est au printemps quand même !\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 12,5%%\n");
            }
            else // ( EvnmtExt.type == 2)
            {
                printf("La fourmilière subit une inondation d'impact %d,\n"
                       "nous pensons qu'elle s'en sortira, on est au printemps quand même !\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 25%%\n");
            }
        }
        else if (EvnmtExt.type == 3) // INVASION
        {
            EvnmtExt.impact = 1 + (rand() % 3); // valeur aleatoire entre 1,2 et 3 pour determiner l'impact de l'even ext
            if (EvnmtExt.impact == 1)
            {
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 2)
            {
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            printf("La fourmilière subit une invasion d'impact %d,\n"
                   "c'est un printemps compliqué !\n",
                   EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en hiver est de 50%%\n");
        }
    }
    else if (saisonActuel == 2) // ETE
    {
        int Ete[8] = {0, 1, 1, 1, 3, 3, 3, 3}; // 0 = aucun  ; 1 = tempete ; 2 = inondation ; 3 = invasion
        // Les inondations (2) sont inexistantes en été, et les invasions (3) sont fréquentes.

        int index = rand() % 8;     // Génère un index aléatoire entre 0 et 7
        EvnmtExt.type = Ete[index]; // Sélectionne une valeur du tableau

        if (EvnmtExt.type == 0) // aucun
        {
            EvnmtExt.impact = 0;
            phero.alarme = EvnmtExt.impact;
            phero.reine = 5;
            phero.reine = 3 + (rand() % 5);
            printf("Tout va bien dans la fourmilière cet été,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis !\n");
        }
        else if (EvnmtExt.type == 1) // Tempête
        {
            EvnmtExt.impact = 1 + (rand() % 3);               // Impact entre 1 et 3
            if (EvnmtExt.impact == 1 || EvnmtExt.impact == 2) // reste une période de forte PonteEtMortalite malgré even ext d'ou regrouper
            {
                phero.reine = 3 + (rand() % 5);
                phero.cohesion = 2 + (rand() % 3);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            printf("La fourmilière subit une tempête d'impact %d,\n"
                   "elle s'en sortira !\n",
                   EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en été est de 37,5%%\n");
        }
        else if (EvnmtExt.type == 3) // Invasion
        {
            EvnmtExt.impact = 1 + (rand() % 3);               // Impact entre 1 et 3
            if (EvnmtExt.impact == 1 || EvnmtExt.impact == 2) // reste une période de forte PonteEtMortalite malgré even ext d'ou regrouper
            {
                phero.reine = 3 + (rand() % 5);
                phero.cohesion = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            printf("La fourmilière subit une invasion d'impact %d.\n", EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en été est de 50%%\n");
        }
    }
    else if (saisonActuel == 3) // AUTOMNE
    {
        int Aut[8] = {0, 0, 1, 1, 2, 3, 3, 3}; // 0 = aucun  ; 1 = tempête ; 2 = inondation ; 3 = invasion
        // Les invasions (3) et inondations (2) sont plus probables en automne.

        int index = rand() % 8;     // Génère un index aléatoire entre 0 et 7
        EvnmtExt.type = Aut[index]; // Sélectionne une valeur du tableau

        if (EvnmtExt.type == 0) // aucun
        {
            EvnmtExt.impact = 0;
            phero.alarme = EvnmtExt.impact;
            phero.reine = 4;
            phero.cohesion = 4;
            printf("Tout va bien dans la fourmilière cet automne,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis !\n");
        }
        else if (EvnmtExt.type == 1) // Tempête
        {
            EvnmtExt.impact = 1 + (rand() % 3); // Impact entre 1 et 3
            if (EvnmtExt.impact == 1)
            {
                phero.alarme = EvnmtExt.impact;
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
            }
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3) // regrouper car pas bcp de PonteEtMortalite de tte façon => even ext rend encore + bas
            {
                phero.alarme = EvnmtExt.impact;
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
            }
            printf("La fourmilière subit une tempête d'impact %d,\n"
                   "un peu cocasse mais habituel, ça devrait aller pour un automne !\n",
                   EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en hiver est de 50%%\n");
        }
        else if (EvnmtExt.type == 2) // Inondation
        {
            EvnmtExt.impact = 1 + (rand() % 3); // Impact entre 1 et 3
            if (EvnmtExt.impact == 1)
            {
                phero.alarme = EvnmtExt.impact;
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
            }
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3) // regrouper car pas bcp de PonteEtMortalite de tte façon => even ext rend encore + bas
            {
                phero.alarme = EvnmtExt.impact;
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.alarme = EvnmtExt.impact;
                phero.reine = 1 + (rand() % 2);
                phero.cohesion = 1 + (rand() % 2);
            }
            printf("La fourmilière subit une inondation d'impact %d\n", EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en hiver est de 12,5%%\n");
        }
        else if (EvnmtExt.type == 3) // Invasion
        {
            EvnmtExt.impact = 1 + (rand() % 3); // Impact entre 1 et 3
            if (EvnmtExt.impact == 1)
            {
                phero.alarme = EvnmtExt.impact;
                phero.reine = 1;
                phero.cohesion = (EvnmtExt.impact == 3) ? 0 : 1; // Impact fort peut affecter les mâles
            }
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3)
            {
                phero.alarme = EvnmtExt.impact;
                phero.reine = 0;
                phero.cohesion = 0;
            }
            printf("La fourmilière subit une invasion d'impact %d,\n"
                   "un peu cocasse mais gérable!",
                   EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en hiver est de 37,5%%\n");
        }
    }
}

void affichageCycleSaisonRandom(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Pheromone phero)
{
    colo->nombreReines = 5;
/*
    int GrainesReste = 0, GrainesReste1, GrainesReste2 = 0, SoldatsReste = 0, OuvrieresReste = 0, OuvrieresReste2 = 0;

    int tempGraines = agriculture->quantitéGraines;
    if (tempGraines > 4000)
    {
        tempGraines = 3999;
    }
    else if (tempGraines > 3000)
    {
        GrainesReste2 = 3000 - tempGraines;
        tempGraines = 1000;
        GrainesReste1 = 2000;
        
    }
    else if (tempGraines > 2000)
    {   
        GrainesReste1 = 1000 - tempGraines;
        tempGraines = 1000;
        GrainesReste2 = 0;
    }
    agriculture->quantitéGraines = tempGraines;

    int tempNourriture = agriculture->quantitéDeNourriture;
    if (tempNourriture > 400000)
    {
        tempNourriture = 399999;
    }
    agriculture->quantitéDeNourriture = tempNourriture;

    int tempOuvrieres = colo->ouvrieres;
    if (tempOuvrieres > 200)
    {
        tempOuvrieres = 199;
    }
    else if (tempOuvrieres > 150)
    {
        OuvrieresReste2 = 150 - tempOuvrieres;
        tempOuvrieres = 100;
        OuvrieresReste = 50;
    } 

    int tempPucerons = elevage->nombrePucerons;
    int tempMales = colo->males;

    int tempSoldats = compterFourmis(colo->soldats);
    if (tempSoldats > 150) // le max que la reserve peut supporter
    {
        SoldatsReste = 100;
        tempSoldats = 49;
    }
    else if (tempSoldats > 100) // le max que la reserve peut supporter
    {
        SoldatsReste = 100 - tempSoldats;
    }
    tempSoldats = compterFourmis(colo->soldats);

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
        " \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m         \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-      %d      -\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m- %d  -\x1b[48;2;139;93;78m    \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "  \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-               -\x1b[48;2;139;93;78m                  \x1b[48;2;210;160;135m-----------\x1b[48;2;139;93;78m    \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "   \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m-    %d    -\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-----------------\x1b[48;2;139;93;78m                  \x1b[48;2;210;160;135m- %d  -\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "    \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m    Mâles                                     \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "      \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m     \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m\x1b[48;2;139;93;78m   \x1b\x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                    AMBIANCE                     \x1b\x1b[0m\x1b[48;2;115;71;60m----\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                 \x1b[48;2;210;160;135m- %d  -\x1b[48;2;139;93;78m       Reines         %d/10                 \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "            \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m             \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b\x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                           \x1b\x1b[0m\x1b[48;2;115;71;60m-----\n"
        "                \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                      \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m                   \x1b\x1b[0m\x1b[48;2;115;71;60m-----\n"
        "                    \x1b[48;2;115;71;60m--------\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m             \x1b\x1b[0m\x1b[48;2;115;71;60m------\n"
        "                             \x1b[48;2;115;71;60m--------------------------------\n",
        agriculture->quantitéGraines, GrainesReste, GrainesReste2, compterFourmis(colo->soldats), SoldatsReste, compterFourmis(colo->ouvrieres) - 5, agriculture->quantitéDeNourriture, OuvrieresReste, elevage->nombrePucerons, OuvrieresReste2, compterFourmisMales(colo->males), phero.ambiance, colo->nombreReines);
  */   
    printf("\n--- DEBUG INFO ---\n");
    printf("Nombre d'ouvrières : %d\n", compterFourmis(colo->ouvrieres));
    printf("Nombre de soldats : %d\n", compterFourmis(colo->soldats));
    printf("Agriculture - Quantité de Graines : %d\n", ((SystemeAgricole *)agriculture)->quantitéGraines);
    printf("Agriculture - Quantité de Nourriture : %d\n", ((SystemeAgricole *)agriculture)->quantitéDeNourriture);
    printf("Élevage - Nombre de Pucerons : %d\n", ((SystemeElevage *)elevage)->nombrePucerons);
    printf("Nombre de reines : %d\n", colo->nombreReines);
    printf("-------------------\n");

    sleep(2);
}