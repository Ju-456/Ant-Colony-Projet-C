#include "fourmi.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h> // Pour le "sleep(3)"
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour srand(time(NULL));

void ChosenColonie(Colonie *colo,int nOuvrieres,int nSoldats, SystemeAgricole *agriculture, SystemeElevage *elevage, Architecture *archi, Hygiène *hyg, Sécurité *secu)
{
    if (!colo)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la colonie\n");
        exit(0);
    }

    printf("\n=== Architecture ===\n");
    printf(
        "\n=== Gestion des Salles ===\n"
        ">>> Salles Obligatoires :\n"
        " - Graines, Nourriture, Pucerons, Mâles, Reines, Ouvrières, Soldats\n\n"
        ">>> Salles Complémentaires Disponibles :\n"
        " - +2 Ouvrières, +2 Soldats\n\n"
        "=== Choix des Configurations ===\n"
        " 1. Configuration **Minimale** :\n"
        "    - Salles obligatoires uniquement (7 salles)\n\n"
        " 2. Configuration **Moyenne** :\n"
        "    - Salles obligatoires +1 Ouvrières +1 Soldats (9 salles)\n\n"
        " 3. Configuration **Maximale** :\n"
        "    - Salles obligatoires +2 Ouvrières +2 Soldats (12 salles)\n\n"
        "*****************************************\n"
        ">>> Veuillez entrer 1, 2 ou 3 selon la configuration choisie : ");

    scanf("%d", &archi->salles);
    switch (archi->salles)
    {
    case 1:
        Configuration1(colo, nOuvrieres, nSoldats, agriculture, elevage, hyg, secu);
        archi->salles = 7;
        break;
    case 2:
        Configuration2(colo, nOuvrieres, nSoldats, agriculture, elevage, hyg, secu);
        archi->salles = 9;
        break;
    case 3:
        Configuration3(colo, nOuvrieres, nSoldats, agriculture, elevage, hyg, secu);
        archi->salles = 13;
        break;
    default:
        printf("Invalid choice.\n");
    }
}

void Configuration1(Colonie *colo,int nOuvrieres, int nSoldats, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu)
{
    printf("Voici à quoi ressemblera la configuration minimale (7 salles):\n");
    printf(
        "                                       - Fourmilière -\n"
        "                             --------------------------------\n"
        "                    --------                                  -------\n"
        "                ----                       Graines                    ----\n"
        "            ----                         ------------                       ----\n"
        "        ----                             -          -                          ----\n"
        "      ----       Soldats                 -     ?    -                              ----\n"
        "    -----       ---------                -          -                               -----\n"
        "  ------        -       -                ------------               Ouvrières         ------\n"
        " ------         -   ?   -                                          ------------        ------\n"
        "------          ---------                                          -          -          ------\n"
        "------                                    Nourriture               -     ?    -           ------\n"
        "------                                -----------------            -          -           ------\n"
        "------           Pucerons             -               -            ------------           ------\n"
        " -----         ------------           -       ?       -                                  -----\n"
        "  -----        -          -           -               -                                 -----\n"
        "   -----       -     ?    -           -----------------                                -----\n"
        "    -----      -          -    Mâles                                                  -----\n"
        "      ----     ------------   ------                    AMBIANCE                     ----\n"
        "        -----                 -  ? -       Reines         ?/10                    -----\n"
        "            -----             ------       ------                           -----\n"
        "                -----                      -  ? -                   -----\n"
        "                    --------               ------             ------\n"
        "                             --------------------------------\n");
    printf("\n");
    printf("=== Colonie ===\n");
    printf("Choisissez le nombre de de fourmis ouvrières de départ (100-200):");
    colo->nombreReines = 1; // colonie monogène
    RandomCalculAfterChosen(colo, nOuvrieres, nSoldats, agriculture, elevage, hyg, secu);
}

void Configuration2(Colonie *colo,int nOuvrieres, int nSoldats, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu)
{
    printf("Voici à quoi ressemblera la configuration moyenne (7 + 2 salles):\n");
    printf(
        "                                       - Fourmilière -\n"
        "                             --------------------------------\n"
        "                    --------                                  -------\n"
        "                ----                       Graines                    ----\n"
        "            ----                   ------------------                       ----\n"
        "        ----                       -  +1 -          -                          ----\n"
        "      ----       Soldats           -------     ?    -                              ----\n"
        "    -----       ---------                -          -                               -----\n"
        "  ------        -       -                ------------               Ouvrières         ------\n"
        " ------         -   ?   -                                          ------------        ------\n"
        "------          ---------                                          -          -          ------\n"
        "------                                    Nourriture               -     ?    -           ------\n"
        "------                                -----------------            -          -           ------\n"
        "------           Pucerons             -               -            ------------------     ------\n"
        " -----         ------------           -       ?       -                        - +1 -    -----\n"
        "  -----        -          -           -               -                        ------   -----\n"
        "   -----       -     ?    -           -----------------                                -----\n"
        "    -----      -          -    Mâles                                                  -----\n"
        "      ----     ------------   ------                    AMBIANCE                     ----\n"
        "        -----                 -  ? -       Reines         ?/10                    -----\n"
        "            -----             ------       ------                           -----\n"
        "                -----                      -  ? -                   -----\n"
        "                    --------               ------             ------\n"
        "                             --------------------------------\n");
    printf("\n");

    printf("=== Colonie ===\n");
    printf("Choisissez le nombre de de fourmis ouvrières de départ (300-400):");
    colo->nombreReines = 2; // colonie polygène
    RandomCalculAfterChosen(colo, nOuvrieres, nSoldats, agriculture, elevage, hyg, secu);

}

void Configuration3(Colonie *colo,int nOuvrieres, int nSoldats, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu)
{

    printf("Voici à quoi ressemblera la configuration maximale (7 + 5 salles):\n");
    printf(
        "                                       - Fourmilière -\n"
        "                             --------------------------------\n"
        "                    --------                                  -------\n"
        "                ----                       Graines                    ----\n"
        "            ----                   ------------------                       ----\n"
        "        ----                       - +1  -          -                          ----\n"
        "      ----       Soldats           -------     ?    -                              ----\n"
        "    -----       ---------                -          -------                          -----\n"
        "  ------        -       -                ------------- +1 -         Ouvrières         ------\n"
        " ------         -   ?   -                            ------        ------------        ------\n"
        "------    ---------------                                          -          -          ------\n"
        "------    - +1 -                          Nourriture               -     ?    -           ------\n"
        "------    ------                      -----------------            -          -           ------\n"
        "------           Pucerons             -               -            ------------------     ------\n"
        " -----         ------------           -       ?       -                        - +1 -    -----\n"
        "  -----        -          -           -               -                  ------------   -----\n"
        "   -----       -     ?    -           -----------------                  - +1 -        -----\n"
        "    -----      -          -    Mâles                                     ------       -----\n"
        "      ----     ------------   ------                    AMBIANCE                     ----\n"
        "        -----                 -  ? -       Reines         ?/10                    -----\n"
        "            -----             ------       ------                           -----\n"
        "                -----                      -  ? -                   -----\n"
        "                    --------               ------             ------\n"
        "                             --------------------------------\n");
    printf("\n");

    printf("=== Colonie ===\n");
    printf("Choisissez le nombre de de fourmis ouvrières de départ (300-400):");
    colo->nombreReines = 4; // colonie polygène
    RandomCalculAfterChosen(colo, nOuvrieres, nSoldats, agriculture, elevage, hyg, secu);
}

void RandomCalculAfterChosen(Colonie *colo, int nOuvrieres, int nSoldats, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu)
{

        scanf("%d", &nOuvrieres);

        if (nOuvrieres < 100 || nOuvrieres > 400){
            printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
            scanf("%d", &nOuvrieres);
        }

        int nReines = colo->nombreReines;
        nSoldats = nOuvrieres * (5 + rand() % 6) / 100;
        printf("Le nombre de soldats: %d\n", nSoldats);
        printf("Le nombre de reines: %d\n", nReines);
        printf("(Le nombre de mâles dépendra de la saison)\n");

        colo->ouvrieres = NULL;
        colo->males = NULL;
        colo->soldats = NULL;

        elevage->nombrePucerons = nOuvrieres * (20 + rand() % 6) / 100;    // 20 - 25% de la proportion d'ouvrières
        agriculture->quantitéDeNourriture = nOuvrieres * (2 + rand() % 3); // 2 - 4 * de la proportion d'ouvrières
        agriculture->quantitéGraines = nOuvrieres * (2 + rand() % 6); // 2 - 7 * de la proportion d'ouvrières

        printf("=== Systeme Agricole ===\n");
        printf("La quantité de nourriture (100 - 1000): %d\n", agriculture->quantitéDeNourriture);
        printf("La quantité de graines (100 - 500): %d\n", agriculture->quantitéGraines);

        printf("\n");

        printf("\n=== Systeme Elevage ===\n");
        printf("Le nombre de pucerons: %d\n", elevage->nombrePucerons);
        printf("\n");

        for (int i = 0; i < nReines; ++i) // Ajout des reines à la liste chaînee
        {
            ajouterFourmi(&colo->ouvrieres, ROLE_REINE);
        } // les reines sont des sortes d'ouvrieres speciales, elles sont dans la même liste chainee avec un rôle différent

        for (int i = 0; i < nOuvrieres; ++i) // Ajout d'ouvrières
        {
            ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
        }

        
        for (int i = 0; i < nSoldats; ++i) // Ajout de soldats
        {
            ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
        }
        
        // partie à faire
        // faire sys tableau doubles entrer
        printf("\n=== Hygiène ===\n");
        printf("Entrez le niveau de propreté (1 - 3): ");
        scanf("%d", &hyg->niveauProprete);

        if (hyg->niveauProprete < 1 || hyg->niveauProprete > 3){
            printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
            scanf("%d", &hyg->niveauProprete);
        }

        printf("Entrez le niveau de maladie (1 - 3): "); 
        scanf("%d", &hyg->maladies);

        if (hyg->maladies < 1 || hyg->maladies > 3){
            printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
            scanf("%d", &hyg->maladies);
        }

        printf("\n");

        // faire sys tableau doubles entrer
        printf("\n=== Sécurité ===\n");
        printf("Entrez le niveau de protection (1 - 3): "); // le niveau de protection allant de 0 à 3
        scanf("%d", &secu->niveauProtection);

        if (secu->niveauProtection < 1 || secu->niveauProtection > 3){
            printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
            scanf("%d", &secu->niveauProtection);
        }

        printf("Entrez le nombre d'attaques reçues (1 - 3): "); // une attaque = - 1 à 10 soldats
        scanf("%d", &secu->attaquesReçues);

        if (secu->attaquesReçues < 1 || secu->attaquesReçues > 3){
            printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
            scanf("%d", &secu->attaquesReçues);
        }

        printf("\n");

        printf("Voici votre fourmilière de départ avant les changements");
}

void simuleUneSaisonChosen(int nOuvrieres, Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, Architecture archi, int nMales,int nSoldats)
{   
    static int saisonChoice = -1;

    // Demande initiale de la saison de départ
    if (saisonChoice == -1)
    {
        printf("Choisissez une saison de départ :\n"
               "0. Hiver\n"
               "1. Printemps\n"
               "2. Ete\n"
               "3. Automne\n"
               "Entrez votre choix : ");

        scanf("%d", &saisonChoice);

        while (saisonChoice < 0 || saisonChoice > 3)
        {
            printf("Saisie invalide. Veuillez rechoisir une saison (entier compris entre 0 et 3) : ");
            scanf("%d", &saisonChoice);
        }

        /*if (saisonChoice == 1){
            printf("Nous sommes au printemps, il y a donc des mâles dans la colonie.\n Choississez un nombre de mâles ()")
        }*/
    }

    // Simulation d'une saison
    switch (saisonChoice)
    { // Répartition des saisons : 0 = HIVER, 1 = PRINTEMPS, 2 = ETE, 3 = AUTOMNE

    case 0: // HIVER
        hiver(saisonActuel, agriculture, EvnmtExt, phero, colo, elevage);
        GestionEvenementExterneChosen(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage, archi, nSoldats, nOuvrieres, nMales);
        printf("************************************** Fin de l'HIVER ****************************\n");
        break;

    case 1: // PRINTEMPS
        printemps(nOuvrieres, saisonActuel, agriculture, nMales, elevage, EvnmtExt, phero, colo);
        GestionEvenementExterneChosen(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage, archi, nSoldats, nOuvrieres, nMales);
        printf("************************************** Fin du PRINTEMPS **************************\n");
        break;

    case 2: // ETE
        ete(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
        GestionEvenementExterneChosen(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage, archi, nSoldats, nOuvrieres, nMales);
        printf("************************************** Fin de l'ÉTÉ ******************************\n");
        break;

    case 3: // AUTOMNE
        automne(nOuvrieres, saisonActuel, agriculture, nMales, elevage, EvnmtExt, phero, colo);
        GestionEvenementExterneChosen(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage, archi, nSoldats, nOuvrieres, nMales);
        printf("************************************** Fin de l'AUTOMNE ******************************\n");
        break;

    default:
        break;
    }

    // Passer à la saison suivante
    saisonChoice++;
    if (saisonChoice > 3)
    {
        saisonChoice = 0;
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

void GestionEvenementExterneChosen(int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Architecture archi, int nSoldats, int nOuvrieres, int nMales)
{
    static int EvnmtChoice = -1;

    if (saisonActuel == 0) // HIVER
    {
        // Hiv[5] = {0, 1, 2, 3, 4}; // 0 = aucun  ; 1 =  tempete ; 2 = inondation ; 3 = invasion ;  4 = hiver glacial
        // le 4 (hiver glacial) ne parait qu'en hiver
        if (EvnmtChoice == -1)
        {   
            printf("\n");
            printf("Voici le tableau des événement disponible en hiver :\n"
                   "Hiv[5] = {0, 1, 2, 3, 4};\n Liste des types d'évènements :\n"
                   "0 = aucun  ; \n"
                   "1 =  tempete ; \n"
                   "2 = inondation ; \n"
                   "3 = invasion ;  \n"
                   "4 = hiver glacial\n");
            printf("\n");
            printf("Choisissez un type d'évènement parmis les choix proposés :");
            scanf("%d", &EvnmtExt.type);

            if (EvnmtExt.type > 0)
            {
                printf("Choisissez l'impact de l'évènement sur une échelle de 1 à 3 :");
                scanf("%d", &EvnmtExt.impact);
            }
            else 
            {
                EvnmtExt.impact = 0;
            }
        }

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
        // Print[4] = {0, 1, 2, 3}; // 0 = aucun  ; 1 =  tempete ; 2 = inondation ; 3 = invasion ;
        // les risques de 3 (invasion) sont plus eleves pdt le printemps
        if (EvnmtChoice == -1)
        {
            printf("Voici le tableau des événement disponible pour le printemps :\n"
                   "Print[4] = {0, 1, 2, 3};\n Liste des types d'évènements :\n"
                   "0 = aucun  ; \n"
                   "1 =  tempete ; \n"
                   "2 = inondation ; \n"
                   "3 = invasion ;  \n");
            printf("\n");
            printf("Choisissez un type d'évènement parmis les choix proposés :");
            scanf("%d", &EvnmtExt.type);

            if (EvnmtExt.type > 0)
            {
                printf("Choisissez l'impact de l'évènement sur une échelle de 1 à 3 :");
                scanf("%d", &EvnmtExt.impact);
            }
            else 
            {
                EvnmtExt.impact = 0;
            }
        }

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
        // Ete[3] = {0, 1, 3}; // 0 = aucun  ; 1 = tempete ; 2 = inondation ; 3 = invasion
        // Les inondations (2) sont inexistantes en été, et les invasions (3) sont fréquentes.
        if (EvnmtChoice == -1)
        {
            printf("Voici le tableau des événement disponible pour l'été' :\n"
                   "Print[4] = {0, 1, 2, 3};\n Liste des types d'évènements :\n"
                   "0 = aucun  ; \n"
                   "1 =  tempete ; \n"
                   "3 = invasion ;  \n");
            printf("\n");
            printf("Choisissez un type d'évènement parmis les choix proposés :");
            scanf("%d", &EvnmtExt.type);

            if (EvnmtExt.type > 0)
            {
                printf("Choisissez l'impact de l'évènement sur une échelle de 1 à 3 :");
                scanf("%d", &EvnmtExt.impact);
            }
            else 
            {
                EvnmtExt.impact = 0;
            }
        }

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
        // Aut[4] = {0, 1, 2, 3}; // 0 = aucun  ; 1 = tempête ; 2 = inondation ; 3 = invasion
        // Les invasions (3) et inondations (2) sont plus probables en automne.
        if (EvnmtChoice == -1)
        {
            printf("Voici le tableau des événement disponible pour l'automne' :\n"
                   "Aut[4] = {0, 1, 2, 3};\n Liste des types d'évènements :\n"
                   "0 = aucun  ; \n"
                   "1 =  tempete ; \n"
                   "2 = inondation ; \n"
                   "3 = invasion ;  \n");
            printf("\n");
            printf("Choisissez un type d'évènement parmis les choix proposés :");
            scanf("%d", &EvnmtExt.type);

            if (EvnmtExt.type > 0)
            {
                printf("Choisissez l'impact de l'évènement sur une échelle de 1 à 3 :");
                scanf("%d", &EvnmtExt.impact);
            }
            else 
            {
                EvnmtExt.impact = 0;
            }
        }

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
    EvnmtChoice++;
    PonteEtMortaliteChosen(phero, colo, &agriculture, &elevage, archi, nSoldats, nOuvrieres, nMales);
}

// Gestion de la Ponte et de la mortalité
void PonteEtMortaliteChosen(Pheromone phero, Colonie *colo, void *agriculture, void *elevage, Architecture archi, int nSoldats, int nOuvrieres, int nMales)
{
    srand(time(NULL)); // générateur de nombres aléatoires

    if (phero.alarme <= 2)
    {
        phero.ambiance = 1 + (rand() % 4); // ambiance hivernal (1 à 4)

        for (int j = 0; j < rand() % 16 + 25; ++j)
        {                                                //  "5" = seuil d'exclusion, ce sont des fourmis protégés
            supprimerFourmiVieille(&colo->ouvrieres, 5); // reduction des ouvrieres
        }
        for (int j = 0; j < rand() % 11 + 15; ++j)
        {
            supprimerFourmiVieille(&colo->soldats, 5); // reduction des soldats
        }
    }
    else
    {
        int pheroGlobal = phero.reine + phero.cohesion;

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
    } // test : affichageCycleSaisonChosen(colo, agriculture, elevage, phero, archi);
    affichageCycleSaisonChosen(archi, nSoldats, nOuvrieres, agriculture, elevage, nMales, phero);
}

// a revoir !!!
void affichageCycleSaisonChosen(Architecture archi, int nSoldats, int nOuvrieres, SystemeAgricole *agriculture, SystemeElevage *elevage, int nMales, Pheromone phero)
{
    if (archi.salles == 7)
    {
        // colonie monogène
        printf(
            "                                       - Fourmilière -\n"
            "                             \x1b[48;2;115;71;60m--------------------------------\n"
            "                    \x1b[48;2;115;71;60m--------\x1b[48;2;139;93;78m                                 \x1b[0m\x1b[48;2;115;71;60m-------\n"
            "                \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m                       Graines                   \x1b[0m\x1b[48;2;115;71;60m----\n"
            "            \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m                         \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m                       \x1b[0m\x1b[48;2;115;71;60m----\n"
            "        \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m                             \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m                          \x1b[0m\x1b[48;2;115;71;60m----\n"
            "      \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m       Soldats                 \x1b[48;2;210;160;135m-    %d    -\x1b[48;2;139;93;78m                              \x1b[0m\x1b[48;2;115;71;60m----\n"
            "    \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m                \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "  \x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m-       -\x1b[48;2;139;93;78m                \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m               Ouvrières         \x1b[0m\x1b[48;2;115;71;60m------\n"
            " \x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m         \x1b[48;2;210;160;135m-  %d   -\x1b[48;2;139;93;78m                                          \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m------\n"
            "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m                                          \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m          \x1b[0m\x1b[48;2;115;71;60m------\n"
            "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m                                    Nourriture               \x1b[48;2;210;160;135m-    %d    -\x1b[48;2;139;93;78m           \x1b[0m\x1b[48;2;115;71;60m------\n"
            "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m                                \x1b[48;2;210;160;135m-----------------\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m           \x1b[0m\x1b[48;2;115;71;60m------\n"
            "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m           Pucerons             \x1b[48;2;210;160;135m-               -\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m           \x1b[0m\x1b[48;2;115;71;60m------\n"
            " \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m         \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-      %d       -\x1b[48;2;139;93;78m                                  \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "  \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-               -\x1b[48;2;139;93;78m                                 \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "   \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m-    %d    -\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-----------------\x1b[48;2;139;93;78m                                \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "    \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m    Mâles                                                  \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "      \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m     \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m   \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                    AMBIANCE                     \x1b[0m\x1b[48;2;115;71;60m----\n"
            "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                 \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m       Reines        %d/10                    \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "            \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m             \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                           \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "                \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                      \x1b[48;2;210;160;135m-  1 -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "                    \x1b[48;2;115;71;60m--------\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m             \x1b[0m\x1b[48;2;115;71;60m------\n"
            "                             \x1b[48;2;115;71;60m--------------------------------\n",
            agriculture->quantitéGraines, nSoldats, nOuvrieres, agriculture->quantitéDeNourriture, elevage->nombrePucerons, nMales, phero.ambiance);
        printf("\n");
        sleep(2);
    }
    /*
    else if (archi.salles == 9)
    {
        printf(
            "                                       - Fourmilière -\n"
            "                             \x1b[48;2;115;71;60m--------------------------------\n"
            "                    \x1b[48;2;115;71;60m--------\x1b[48;2;139;93;78m                                 \x1b[0m\x1b[48;2;115;71;60m-------\n"
            "                \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m                       Graines                   \x1b[0m\x1b[48;2;115;71;60m----\n"
            "            \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m                   \x1b[48;2;210;160;135m------------------\x1b[48;2;139;93;78m                       \x1b[0m\x1b[48;2;115;71;60m----\n"
            "        \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m-  %d -          -\x1b[48;2;139;93;78m                          \x1b[0m\x1b[48;2;115;71;60m----\n"
            "      \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m       Soldats           \x1b[48;2;210;160;135m-------    %d    -\x1b[48;2;139;93;78m                              \x1b[0m\x1b[48;2;115;71;60m----\n"
            "    \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m                \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "  \x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m-       -\x1b[48;2;139;93;78m                \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m               Ouvrières         \x1b[0m\x1b[48;2;115;71;60m------\n"
            " \x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m         \x1b[48;2;210;160;135m-   %d  -\x1b[48;2;139;93;78m                                          \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m------\n"
            "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m                                          \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m          \x1b[0m\x1b[48;2;115;71;60m------\n"
            "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m                                    Nourriture               \x1b[48;2;210;160;135m-    %d    -\x1b[48;2;139;93;78m           \x1b[0m\x1b[48;2;115;71;60m------\n"
            "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m                                -----------------\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m           \x1b[0m\x1b[48;2;115;71;60m------\n"
            "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m           Pucerons             -               -\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m------------------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m------\n"
            " \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m         \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m           -      %d       -\x1b[48;2;139;93;78m                        \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m    \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "  \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m           -               -\x1b[48;2;139;93;78m                        \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m   \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "   \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m-    %d    -\x1b[48;2;139;93;78m           -----------------\x1b[48;2;139;93;78m                                \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "    \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m    Mâles                                                  \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "      \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m     \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m   ------\x1b[48;2;139;93;78m                    AMBIANCE                     \x1b[0m\x1b[48;2;115;71;60m----\n"
            "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                 \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m       Reines        %d/10                    \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "            \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m             \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                           \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "                \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                      \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "                    \x1b[48;2;115;71;60m--------\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m             \x1b[0m\x1b[48;2;115;71;60m------\n"
            "                             \x1b[48;2;115;71;60m--------------------------------\n",
            agriculture->quantitéGraines, GrainesReste, totalSoldats, totalOuvrieres, agriculture->quantitéDeNourriture, OuvrieresReste, elevage->nombrePucerons, totalMales, phero.ambiance, colo->nombreReines);
        printf("\n");
        sleep(2);
    }

    else if (archi.salles == 13)
    {
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
    }*/
}
