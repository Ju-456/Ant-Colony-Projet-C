#include "fourmi.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h> // Pour le "sleep(3)"
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour srand(time(NULL));

// Initialisation aléatoire de la colonie
int RandomColonie(Colonie *colo)
{
    if (!colo)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la colonie\n");
        return -1;
    }

    colo->ouvrieres = NULL;
    colo->males = NULL;
    colo->soldats = NULL;

    for (int i = 0; i < (rand() % 61 + 150); ++i) // Ajout d'ouvrières
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }

    for (int i = 0; i < (rand() % 9 + 15); ++i) // Ajout de mâles
    {
        ajouterFourmiMale(&colo->males);
    }

    for (int i = 0; i < (rand() % 41 + 80); ++i) // Ajout de soldats
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    for (int i = 0; i < 5; ++i) // Ajout des reines
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_REINE);
    } // les reines sont des sortes d'ouvrieres speciales, elles sont dans la même liste chainee avec un rôle différent

    colo->nombreReines = 4;
    
    return 0;
}

void simuleUneSaisonRandom(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, Architecture archi)
{   
    for (int i = 0; i < nbSaison; ++i)
    {
        switch (i % 4)
        { // Répartition des saisons : 0 = HIVER, 1 = PRINTEMPS, 2 = ETE, 3 = AUTOMNE

        case 0: // HIVER
            hiver(saisonActuel, agriculture, EvnmtExt, phero, colo, elevage);
            GestionEvenementExterneRandom(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage, archi);
            printf("                                   --- Fin de l'HIVER ---                       \n");
            break;

        case 1: // PRINTEMPS
            printemps(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
            GestionEvenementExterneRandom(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage, archi);
            printf("                                   --- Fin du PRINTEMPS ---                       \n");
            break;

        case 2: // ETE
            ete(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
            GestionEvenementExterneRandom(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage, archi);
            printf("                                   --- Fin de l'ÉTÉ ---                        \n");
            break;

        case 3: // AUTOMNE
            automne(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
            GestionEvenementExterneRandom(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage, archi);
            printf("                                   --- Fin de l'AUTOMNE ---                       \n");
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

// impact le taux de pheromones des fourmis qui impact la ReproductionEtMortalite
void GestionEvenementExterneRandom(int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Architecture archi)
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
            phero.male = 1 + (rand() % 2);
            printf("Tout va bien dans la fourmilière cet hiver,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis\n!");
        }
        else if (EvnmtExt.type == 1 || EvnmtExt.type == 2) // TEMPETE OU INONDATION
        {
            EvnmtExt.impact = 1 + (rand() % 3); // valeur aleatoire entre 1,2 et 3 pour determiner l'impact de l'even ext
            if (EvnmtExt.impact == 1)
            {
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 2)
            {
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
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
                phero.male = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 2)
            {
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
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
                phero.reine = phero.male = 0;
                phero.alarme = EvnmtExt.impact + (rand() % 2);
            }
            else if (EvnmtExt.impact == 2)
            {
                phero.reine = phero.male = 0;
                phero.alarme = EvnmtExt.impact + (rand() % 2);
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.reine = phero.male = 0;
                phero.alarme = EvnmtExt.impact + (rand() % 2);
            }
            if (EvnmtExt.impact == 1 || EvnmtExt.impact == 2)
            {
                printf("La fourmilière subit un hiver glacial d'impact %d,\n"
                       "c'est un hiver est EXTREMEMENT compliqué pour la fourmilière..\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 12,5%%\n");
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
            phero.male = 2 + (rand() % 3);
            printf("Tout va bien dans la fourmilière ce printemps,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis !\n");
        }
        else if (EvnmtExt.type == 1 || EvnmtExt.type == 2) // TEMPETE OU INONDATION
        {
            EvnmtExt.impact = 1 + (rand() % 3); // valeur aleatoire entre 1,2 et 3 pour determiner l'impact de l'even ext
            if (EvnmtExt.impact == 1)
            {
                phero.reine = 3 + (rand() % 5);
                phero.male = 2 + (rand() % 3);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3) // regrouper car pas bcp de ReproductionEtMortalite de tte façon => even ext rend encore + bas
            {
                phero.reine = 2 + (rand() % 3);
                phero.male = 1 + (rand() % 3);
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
                phero.male = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 2)
            {
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
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
            if (EvnmtExt.impact == 1 || EvnmtExt.impact == 2) // reste une période de forte ReproductionEtMortalite malgré even ext d'ou regrouper
            {
                phero.reine = 3 + (rand() % 5);
                phero.male = 2 + (rand() % 3);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
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
            if (EvnmtExt.impact == 1 || EvnmtExt.impact == 2) // reste une période de forte ReproductionEtMortalite malgré even ext d'ou regrouper
            {
                phero.reine = 3 + (rand() % 5);
                phero.male = 1 + (rand() % 2);
                phero.alarme = EvnmtExt.impact;
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
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
            phero.male = 4;
            printf("Tout va bien dans la fourmilière cet automne,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis !\n");
        }
        else if (EvnmtExt.type == 1) // Tempête
        {
            EvnmtExt.impact = 1 + (rand() % 3); // Impact entre 1 et 3
            if (EvnmtExt.impact == 1)
            {
                phero.alarme = EvnmtExt.impact;
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
            }
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3) // regrouper car pas bcp de ReproductionEtMortalite de tte façon => even ext rend encore + bas
            {
                phero.alarme = EvnmtExt.impact;
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
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
                phero.male = 1 + (rand() % 2);
            }
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3) // regrouper car pas bcp de ReproductionEtMortalite de tte façon => even ext rend encore + bas
            {
                phero.alarme = EvnmtExt.impact;
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.alarme = EvnmtExt.impact;
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
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
                phero.male = (EvnmtExt.impact == 3) ? 0 : 1; // Impact fort peut affecter les mâles
            }
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3)
            {
                phero.alarme = EvnmtExt.impact;
                phero.reine = 0;
                phero.male = 0;
            }
            printf("La fourmilière subit une invasion d'impact %d,\n"
                   "un peu cocasse mais gérable!",
                   EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en hiver est de 37,5%%\n");
        }
    }
    ReproductionEtMortaliteRandom(phero, colo, agriculture, elevage, archi);
}
// Gestion de la Reproduction et de la mortalité
void ReproductionEtMortaliteRandom(Pheromone phero, Colonie *colo, void *agriculture, void *elevage, Architecture archi)
{
    srand(time(NULL)); // générateur de nombres aléatoires

    if (phero.alarme <= 2)
    {
        phero.ambiance = 1 + (rand() % 4); // ambiance hivernal (1 à 4)

        for (int j = 0; j < rand() % 16 + 25; ++j)
        {                                                //  "5" sont les 5 reines, on appelle cela le seuil d'exclusion, ce sont des fourmis protégés
            supprimerFourmiVieille(&colo->ouvrieres, 5); // reduction des ouvrieres
        }
        for (int j = 0; j < rand() % 11 + 15; ++j)
        {
            supprimerFourmiVieille(&colo->soldats, 5); // reduction des soldats
        }
    }
    else
    {
        int pheroGlobal = phero.reine + phero.male;

        if (pheroGlobal >= 3)
        {
            phero.ambiance = 5 + (rand() % 4); // ambiance automne ou printemps (5 à 8)

            if (phero.ambiance == 5 || phero.ambiance == 6)
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
            else if (phero.ambiance == 7 || phero.ambiance == 8)
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
    }affichageCycleSaisonRandom(colo,agriculture,elevage,phero);
}

// appeler après ReproductionEtMortalite
void affichageCycleSaisonRandom(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Pheromone phero)
{
    colo->nombreReines = 4;
    int totalOuvrieres = 0;
    int totalSoldats = 0;
    int totalMales = 0;

    // Compter les ouvrières
    Fourmi *current = colo->ouvrieres;
    while (current != NULL)
    {
        totalOuvrieres++;
        current = current->suivante;
    }

    // Compter les soldats
    current = colo->soldats;
    while (current != NULL)
    {
        totalSoldats++;
        current = current->suivante;
    }

    // Compter les mâles
    FourmiMale *currentMale = colo->males;
    while (currentMale != NULL)
    {
        totalMales++;
        currentMale = currentMale->suivante;
    }

    int GrainesReste = 0;
    int GrainesReste2 = 0;
    agriculture->quantitéGraines = 136;
    if (agriculture->quantitéGraines > 30)
    {
        GrainesReste = abs(30 - agriculture->quantitéGraines);
        agriculture->quantitéGraines = 30;
    }
    if (GrainesReste > 100)
    {
        GrainesReste2 = abs(100 - GrainesReste);
        GrainesReste = 100;
    }

    int SoldatsReste = 0;
    if (totalSoldats > 100)
    {
        SoldatsReste = abs(100 - totalSoldats);
        totalSoldats = 100;
    }
    else
    {
        SoldatsReste = 0;
    }

    int OuvrieresReste = 0;
    if (totalOuvrieres > 200)
    {
        OuvrieresReste = abs(200 - totalOuvrieres);
        totalOuvrieres = 200;
    }
    else
    {
        OuvrieresReste = 0;
    }

    int OuvrieresReste2 = 0;
    if (OuvrieresReste > 30)
    {
        OuvrieresReste2 = abs(30 - OuvrieresReste);
        OuvrieresReste = 30;
    }

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
        agriculture->quantitéGraines, GrainesReste, GrainesReste2, totalSoldats, SoldatsReste, totalOuvrieres, agriculture->quantitéDeNourriture, OuvrieresReste, elevage->nombrePucerons, OuvrieresReste2, totalMales, phero.ambiance, colo->nombreReines);
    printf("\n");
    sleep(2);
}