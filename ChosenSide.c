#include "fourmi.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h> // Pour le "sleep(3)"
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour srand(time(NULL));

void ChosenColonie(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Architecture *archi, Hygiène *hyg, Sécurité *secu)
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
        Configuration1(colo, agriculture, elevage, hyg, secu);
        archi->salles = 7;
        break;
    case 2:
        Configuration2(colo, agriculture, elevage, hyg, secu);
        archi->salles = 9;
        break;
    case 3:
        Configuration3(colo, agriculture, elevage, hyg, secu);
        archi->salles = 13;
        break;
    default:
        printf("Invalid choice.\n");
    }
}

void Configuration1(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu)
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
    RandomCalculAfterChosen(colo, agriculture, elevage, hyg, secu);
}

void Configuration2(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu)
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
    RandomCalculAfterChosen(colo, agriculture, elevage, hyg, secu);
}

void Configuration3(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu)
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
    printf("Choisissez le nombre de de fourmis ouvrières de départ (500-600):");
    colo->nombreReines = 4; // colonie polygène
    RandomCalculAfterChosen(colo, agriculture, elevage, hyg, secu);
}

void RandomCalculAfterChosen(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu)
{
    int nOuvrieres = 0;
    scanf("%d", &nOuvrieres);

    if (nOuvrieres < 100 || nOuvrieres > 600)
    {
        printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
        scanf("%d", &nOuvrieres);
    }

    int nReines = colo->nombreReines;
    int nSoldats = nOuvrieres * (5 + rand() % 6) / 100;
    printf("Le nombre de soldats: %d\n", nSoldats);
    printf("Le nombre de reines: %d\n", nReines);
    printf("(Le nombre de mâles dépendra de la saison)\n");

    colo->ouvrieres = NULL;
    colo->males = NULL;
    colo->soldats = NULL;

    elevage->nombrePucerons = nOuvrieres * (20 + rand() % 6) / 100;    // 20 - 25% de la proportion d'ouvrières
    agriculture->quantitéDeNourriture = nOuvrieres * (2 + rand() % 2); // 2 - 3 * proportion d'ouvrières
    agriculture->quantitéGraines = nOuvrieres * (2 + rand() % 3);      // 2 - 4 * proportion d'ouvrières

    printf("=== Systeme Agricole ===\n");
    printf("La quantité de nourriture : %d\n", agriculture->quantitéDeNourriture);
    printf("La quantité de graines : %d\n", agriculture->quantitéGraines);

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

    if (hyg->niveauProprete < 1 || hyg->niveauProprete > 3)
    {
        printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
        scanf("%d", &hyg->niveauProprete);
    }

    printf("Entrez le niveau de maladie (1 - 3): ");
    scanf("%d", &hyg->maladies);

    if (hyg->maladies < 1 || hyg->maladies > 3)
    {
        printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
        scanf("%d", &hyg->maladies);
    }

    printf("\n");

    // faire sys tableau doubles entrer
    printf("\n=== Sécurité ===\n");
    printf("Entrez le niveau de protection (1 - 3): "); // le niveau de protection allant de 0 à 3
    scanf("%d", &secu->niveauProtection);

    if (secu->niveauProtection < 1 || secu->niveauProtection > 3)
    {
        printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
        scanf("%d", &secu->niveauProtection);
    }

    printf("Entrez le nombre d'attaques reçues (1 - 3): "); // une attaque = - 1 à 10 soldats
    scanf("%d", &secu->attaquesReçues);

    if (secu->attaquesReçues < 1 || secu->attaquesReçues > 3)
    {
        printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
        scanf("%d", &secu->attaquesReçues);
    }

    printf("\n");

    printf("Voici votre fourmilière de départ avant les changements :\n");
}

/* affichage simple pour test
void afficherEtatColonie(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu) {
    printf("=== État de la Colonie ===\n");
    printf("Nombre de reines: %d\n", colo->nombreReines);
    printf("Nombre de soldats: %d\n", compterFourmis(colo->soldats));
    printf("Nombre d'ouvrières: %d\n", compterFourmis(colo->ouvrieres));
    printf("\n");

    printf("=== Système Agricole ===\n");
    printf("Quantité de nourriture: %d\n", agriculture->quantitéDeNourriture);
    printf("Quantité de graines: %d\n", agriculture->quantitéGraines);
    printf("\n");

    printf("=== Système Élevage ===\n");
    printf("Nombre de pucerons: %d\n", elevage->nombrePucerons);
    printf("\n");

    printf("=== Hygiène ===\n");
    printf("Niveau de propreté: %d\n", hyg->niveauProprete);
    printf("Niveau de maladies: %d\n", hyg->maladies);
    printf("\n");

    printf("=== Sécurité ===\n");
    printf("Niveau de protection: %d\n", secu->niveauProtection);
    printf("Nombre d'attaques reçues: %d\n", secu->attaquesReçues);
    printf("\n");
}
*/
void simuleUneSaisonChosen(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, Architecture archi)
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
    }

    // Simulation d'une saison
    switch (saisonChoice)
    { // Répartition des saisons : 0 = HIVER, 1 = PRINTEMPS, 2 = ETE, 3 = AUTOMNE

    case 0: // HIVER
        hiver(saisonActuel, agriculture, EvnmtExt, phero, colo, elevage);
        GestionEvenementExterneChosen(saisonActuel, EvnmtExt, phero, colo);
        printf("************************************** Fin de l'HIVER ****************************\n");
        break;

    case 1:
        /*
        int nMales;
        printf("Nous sommes au printemps, saison des fleurs et de la reproduction ! Il y a donc des mâles dans la colonie.\nIndications : mâles = 15% de la pop des ouvrières.\nChoississez un nombre de mâles :")
        scanf("%d", &nMales);
        compterFourmis(colo->males)
        */
        printemps(&saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
        GestionEvenementExterneChosen(saisonActuel, EvnmtExt, phero, colo);
        printf("************************************** Fin du PRINTEMPS **************************\n");
        break;

    case 2: // ETE
        ete(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
        GestionEvenementExterneChosen(saisonActuel, EvnmtExt, phero, colo);
        printf("************************************** Fin de l'ÉTÉ ******************************\n");
        break;

    case 3: // AUTOMNE
        automne(&saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
        GestionEvenementExterneChosen(saisonActuel, EvnmtExt, phero, colo);
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

void GestionEvenementExterneChosen(int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo)
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
                       "c'est un hiver est presque FATAL pour la fourmilière.\nL'aventure aurait pu s'arrête ici...\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 6,25%%\n");
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
}

void affichageCycleSaisonChosen(Architecture archi, Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Pheromone phero)
{
    if (archi.salles == 7)
    {   
        colo->nombreReines = 1;
        // limite des stocks de graines
        int tempGraines = agriculture->quantitéGraines;
        if (tempGraines > 12000)
        {
            tempGraines = 11999;
        }
        agriculture->quantitéGraines = tempGraines;

        // limite des stocks de nourriture
        int tempNourriture = agriculture->quantitéDeNourriture;
        if (tempNourriture > 300000)
        {
            tempNourriture = 299999;
        }
        agriculture->quantitéDeNourriture = tempNourriture;

        // limite des ouvrieres
        int tempOuvrieres = compterFourmis(colo->ouvrieres);
        if (tempOuvrieres > 150)
        {
            tempOuvrieres = 149;
        }

        // limite des pucerons
        int tempPucerons = elevage->nombrePucerons;
        if (tempPucerons > 600)
        {
            tempPucerons = 599;
        }
        elevage->nombrePucerons = tempPucerons;

        int tempMales = compterFourmisMales(colo->males);
        if (tempMales > 50)
        {
            tempMales = 49;
        } // comme ce n'est que pour de l'affichage, on affichera pas la valeur réelle mais temporaire (idem Ouvrieres)

        // limite des soldats
        int tempSoldats = compterFourmis(colo->soldats);
        if (tempSoldats > 200)
        {
            tempSoldats = 199;
        } // comme ce n'est que pour de l'affichage, on affichera pas la valeur réelle mais temporaire (idem Ouvrieres)

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
            "                \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                      \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "                    \x1b[48;2;115;71;60m--------\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m             \x1b[0m\x1b[48;2;115;71;60m------\n"
            "                             \x1b[48;2;115;71;60m--------------------------------\n",
            tempGraines, tempSoldats, tempOuvrieres - 2, tempNourriture, tempPucerons, tempMales, phero.ambiance, colo->nombreReines);
        printf("\n");
        printf("\n--- DEBUG INFO ---\n");
        printf("Nombre d'ouvrières : %d\n", compterFourmis(colo->ouvrieres));
        printf("Nombre de soldats : %d\n", compterFourmis(colo->soldats));
        printf("Agriculture - Quantité de Graines : %d\n", ((SystemeAgricole *)agriculture)->quantitéGraines);
        printf("Agriculture - Quantité de Nourriture : %d\n", ((SystemeAgricole *)agriculture)->quantitéDeNourriture);
        printf("Élevage - Nombre de Pucerons : %d\n", ((SystemeElevage *)elevage)->nombrePucerons);
        printf("-------------------\n");
        sleep(2);
    }

    else if (archi.salles == 9)
    {
        colo->nombreReines = 2;

        int GrainesReste = 0, OuvrieresReste = 0;

        // limite des stocks de graines
        int tempGraines = agriculture->quantitéGraines;
        if (tempGraines > 15000)
        {
            tempGraines = 2000;
            GrainesReste = 12999;
        }
        else if (tempGraines > 2000)
        {
            GrainesReste = tempGraines - 2000;
            tempGraines = 2000;
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
        if (tempOuvrieres > 200)
        {
            tempOuvrieres = 199;
        }
        else if (tempOuvrieres > 150)
        {
            OuvrieresReste = tempOuvrieres - 150;
            tempOuvrieres = 100;
        } // comme ce n'est que pour de l'affichage, on affichera pas la valeur réelle mais temporaire qui = valeur réelle décomposée en plusieurs partie pour respecter la limite de taille des cases

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
        if (tempSoldats > 200)
        {
            tempSoldats = 199;
        } // comme ce n'est que pour de l'affichage, on affichera pas la valeur réelle mais temporaire (idem Ouvrieres)

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
            "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m                                \x1b[48;2;210;160;135m-----------------\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m           \x1b[0m\x1b[48;2;115;71;60m------\n"
            "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m           Pucerons             \x1b[48;2;210;160;135m-               -\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m------------------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m------\n"
            " \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m         \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-      %d       -\x1b[48;2;139;93;78m                        \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m    \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "  \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-               -\x1b[48;2;139;93;78m                        \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m   \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "   \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m-    %d    -\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-----------------\x1b[48;2;139;93;78m                                \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "    \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m    Mâles                                                  \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "      \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m     \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m   \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                    AMBIANCE                     \x1b[0m\x1b[48;2;115;71;60m----\n"
            "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                 \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m       Reines        %d/10                    \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "            \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m             \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                           \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "                \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                      \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m-----\n"
            "                    \x1b[48;2;115;71;60m--------\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m             \x1b[0m\x1b[48;2;115;71;60m------\n"
            "                             \x1b[48;2;115;71;60m--------------------------------\n",
            tempGraines, GrainesReste, tempSoldats, tempOuvrieres - 2, tempNourriture, OuvrieresReste, tempPucerons, tempMales, phero.ambiance, colo->nombreReines);
        printf("\n"); // tempOuvrieres - 2, car on rappelle que les reines sont dans la même liste chainees que les ouvrières
        sleep(2);
    }

    else if (archi.salles == 13)
    {

        colo->nombreReines = 4;

        int GrainesReste = 0, GrainesReste1 = 0, SoldatsReste = 0, OuvrieresReste = 0, OuvrieresReste1 = 0;

        // limite des stocks de graines
        int tempGraines = agriculture->quantitéGraines;
        if (tempGraines > 500000)
        {
            tempGraines = 2000;
            GrainesReste = 46000;
            GrainesReste1 = 1999;
        }
        else if (tempGraines > 48000)
        {
            GrainesReste1 = tempGraines - 48000;
            GrainesReste = 46000;
            tempGraines = 2000;
        }
        else if (tempGraines > 2000)
        {
            GrainesReste = tempGraines - 2000;
            tempGraines = 2000;
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
        if (tempOuvrieres > 300)
        {
            tempOuvrieres = 299;
        }
        else if (tempOuvrieres > 200)
        {
            OuvrieresReste = tempOuvrieres - 200;
            tempOuvrieres = 200;
        } // comme ce n'est que pour de l'affichage, on affichera pas la valeur réelle mais temporaire qui = valeur réelle décomposée en plusieurs partie pour respecter la limite de taille des cases

        // limite des pucerons
        int tempPucerons = elevage->nombrePucerons;
        if (tempPucerons > 1000)
        {
            tempPucerons = 999;
        }
        elevage->nombrePucerons = tempPucerons;

        int tempMales = compterFourmisMales(colo->males);
        if (tempMales > 70)
        {
            tempMales = 69;
        } // comme ce n'est que pour de l'affichage, on affichera pas la valeur réelle mais temporaire (idem Ouvrieres)

        // limite des soldats
        int tempSoldats = compterFourmis(colo->soldats);
        if (tempSoldats > 300)
        {
            tempSoldats = 299;
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
            tempGraines, GrainesReste, GrainesReste1, tempSoldats, SoldatsReste, tempOuvrieres - 4, tempNourriture, OuvrieresReste, tempPucerons, OuvrieresReste1, tempMales, phero.ambiance, colo->nombreReines);
        printf("\n"); // tempOuvrieres - 4, car on rappelle que les reines sont dans la même liste chainees que les ouvrières
        sleep(2);
    }
}
