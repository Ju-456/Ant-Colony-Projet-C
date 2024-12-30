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
    colo->nombreReines = 3; // colonie polygène
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
    colo->nombreReines = 5; // colonie polygène
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
    agriculture->quantitéGraines = nOuvrieres * (3 + rand() % 3);      // 3 - 5 * proportion d'ouvrières

    printf("\n=== Systeme Agricole ===\n");
    printf("La quantité de nourriture : %d\n", agriculture->quantitéDeNourriture);
    printf("La quantité de graines : %d\n", agriculture->quantitéGraines);

    printf("\n=== Systeme Elevage ===\n");
    printf("Le nombre de pucerons: %d\n", elevage->nombrePucerons);

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

    printf("\n=== Hygiène ===\n");
    printf("Entrez le niveau de propreté (1 - 3): ");
    scanf("%d", &hyg->niveauProprete);

    if (hyg->niveauProprete < 1 || hyg->niveauProprete > 3)
    {
        printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
        scanf("%d", &hyg->niveauProprete);
    }

    printf("Entrez le niveau de maladie (1 - 3): ");
    scanf("%d", &hyg->niveauMaladie);

    if (hyg->niveauMaladie < 1 || hyg->niveauMaladie > 3)
    {
        printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
        scanf("%d", &hyg->niveauMaladie);
    }

    printf("\n=== Sécurité ===\n");
    printf("Entrez le niveau de protection (1 - 3): "); // le niveau de protection allant de 0 à 3
    scanf("%d", &secu->niveauProtection);

    if (secu->niveauProtection < 1 || secu->niveauProtection > 3)
    {
        printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
        scanf("%d", &secu->niveauProtection);
    }

    printf("Entrez le nombre d'attaques reçues (1 - 3): ");
    scanf("%d", &secu->attaquesReçues);

    if (secu->attaquesReçues < 1 || secu->attaquesReçues > 3)
    {
        printf("Veuillez réessayer en respectant l'intervale de valeurs proposé : ");
        scanf("%d", &secu->attaquesReçues);
    }

    printf("\n");

    printf("Voici votre fourmilière de départ avant les changements :\n");
    
    printf("\n");
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

void simuleUneSaisonChosen(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int *saisonActuel, Hygiène *hyg, Sécurité *secu, EvenementExterne *EvnmtExt, Pheromone *phero, Architecture archi)
{
    static int EvnmtChoice = -1;
    int saisonChoice;
    if (EvnmtChoice == -1)
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
        *saisonActuel = saisonChoice;

        if (saisonChoice == 0)
        {
            printf("\n");
            printf("\n******************************** Récapitulatif de l'HIVER ****************************\n");
        }
    }
    // Simulation d'une saison
    if (*saisonActuel == 0)
    {
        // printf("\n******************************** Récapitulatif de l'HIVER ****************************\n");
        hiver(saisonActuel, agriculture, EvnmtExt, phero, colo, elevage);
        if (EvnmtChoice == -1)
        {
            GestionEvenementExterneChosen(EvnmtExt, phero, colo, saisonActuel);
        }
        else
        {
            GestionEvenementExterneRandom(EvnmtExt, phero, colo, saisonActuel);
        }
        PonteEtMortalite(phero, colo);
        NiveauPropreteEtMaladie(hyg, colo);
        NiveauSecuritéEtProtection(secu, colo);
        affichageCycleSaisonChosen(archi, colo, agriculture, elevage, phero);
    }
    else if (*saisonActuel == 1)
    {
        printf("\n********************************** Récapitulatif du PRINTEMPS **************************\n");
        printemps(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
        if (EvnmtChoice == -1)
        {
            GestionEvenementExterneChosen(EvnmtExt, phero, colo, saisonActuel);
        }
        else
        {
            GestionEvenementExterneRandom(EvnmtExt, phero, colo, saisonActuel);
        }
        PonteEtMortalite(phero, colo);
        NiveauPropreteEtMaladie(hyg, colo);
        NiveauSecuritéEtProtection(secu, colo);
        affichageCycleSaisonChosen(archi, colo, agriculture, elevage, phero);
    }
    else if (*saisonActuel == 2)
    {
        printf("\n********************************** Récapitulatif de l'ÉTÉ ******************************\n");
        ete(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
        if (EvnmtChoice == -1)
        {
            GestionEvenementExterneChosen(EvnmtExt, phero, colo, saisonActuel);
        }
        else
        {
            GestionEvenementExterneRandom(EvnmtExt, phero, colo, saisonActuel);
        }
        PonteEtMortalite(phero, colo);
        NiveauPropreteEtMaladie(hyg, colo);
        NiveauSecuritéEtProtection(secu, colo);
        affichageCycleSaisonChosen(archi, colo, agriculture, elevage, phero);
    }
    else if (*saisonActuel == 3)
    {
        printf("\n****************************** Récapitulatif de l'AUTOMNE ******************************\n");
        automne(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
        if (EvnmtChoice == -1)
        {
            GestionEvenementExterneChosen(EvnmtExt, phero, colo, saisonActuel);
        }
        else
        {
            GestionEvenementExterneRandom(EvnmtExt, phero, colo, saisonActuel);
        }
        PonteEtMortalite(phero, colo);
        NiveauPropreteEtMaladie(hyg, colo);
        NiveauSecuritéEtProtection(secu, colo);
        affichageCycleSaisonChosen(archi, colo, agriculture, elevage, phero);
    }
    (*saisonActuel)++;

    if (*saisonActuel > 3)
    {
        *saisonActuel = 0;
    } // afin de perpétuer le cycle 3,0,1,2,3 ects...

    EvnmtChoice = 0; // On marque qu'un choix a été effectué

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

void GestionEvenementExterneChosen(EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo, int *saisonActuel)
{

    if (*saisonActuel == 0) // HIVER
    {
        printf("\n");
        printf("Voici le tableau des événement disponible en hiver :\n"
               "Hiv[5] = {0, 1, 2, 3, 4};\nListe des types d'évènements :\n"
               "0 = aucun  ; \n"
               "1 =  tempete ; \n"
               "2 = inondation ; \n"
               "3 = invasion ;  \n"
               "4 = hiver glacial (exclusivité hivernale !)\n"); // le 4 (hiver glacial) ne parait qu'en hiver
        printf("\n");
        printf("Choisissez un type d'évènement parmis les choix proposés :");
        scanf("%d", &EvnmtExt->type);

        if (EvnmtExt->type > 0)
        {
            printf("Choisissez l'impact de l'évènement sur une échelle de 1 à 3 :");
            scanf("%d", &EvnmtExt->impact);
        }
        else
        {
            EvnmtExt->impact = 0;
        }
    }

    else if (*saisonActuel == 1) // PRINTEMPS
    {
        // les risques de 3 (invasion) sont plus eleves pdt le printemps
        printf("\n");
        printf("Voici le tableau des événement disponible pour le printemps :\n"
               "Print[4] = {0, 1, 2, 3};\nListe des types d'évènements :\n"
               "0 = aucun  ; \n"
               "1 =  tempete ; \n"
               "2 = inondation ; \n"
               "3 = invasion ;  \n");
        printf("\n");
        printf("Choisissez un type d'évènement parmis les choix proposés :");
        scanf("%d", &EvnmtExt->type);

        if (EvnmtExt->type > 0)
        {
            printf("Choisissez l'impact de l'évènement sur une échelle de 1 à 3 :");
            scanf("%d", &EvnmtExt->impact);
        }
        else
        {
            EvnmtExt->impact = 0;
        }
    }
    else if (*saisonActuel == 2) // ETE
    {
        // Les inondations (2) sont inexistantes en été, et les invasions (3) sont fréquentes.
        printf("\n");
        printf("Voici le tableau des événement disponible pour l'été :\n"
               "Ete[4] = {0, 1, 3};\nListe des types d'évènements :\n"
               "0 = aucun  ; \n"
               "1 =  tempete ; \n"
               "3 = invasion ;  \n");
        printf("\n");
        printf("Choisissez un type d'évènement parmis les choix proposés :");
        scanf("%d", &EvnmtExt->type);

        if (EvnmtExt->type > 0)
        {
            printf("Choisissez l'impact de l'évènement sur une échelle de 1 à 3 :");
            scanf("%d", &EvnmtExt->impact);
        }
        else
        {
            EvnmtExt->impact = 0;
        }
    }
    else if (*saisonActuel == 3) // AUTOMNE
    {
        /* Les invasions (3) et inondations (2) sont plus probables en automne 
        (5) est un évènement exclusif à l'automne.
        Les parasites sont typiques de l'automne à cause de l'humidité accrue*/
        printf("\n");
        printf("Voici le tableau des événement disponible pour l'automne :\n"
               "Aut[4] = {0, 1, 2, 3, 5};\nListe des types d'évènements :\n"
               "0 = aucun  ; \n"
               "1 =  tempete ; \n"
               "2 = inondation ; \n"
               "3 = invasion ;  \n"
               "5 = parasite ;  \n");
        printf("\n");
        printf("Choisissez un type d'évènement parmis les choix proposés :");
        scanf("%d", &EvnmtExt->type);

        if (EvnmtExt->type > 0)
        {
            printf("Choisissez l'impact de l'évènement sur une échelle de 1 à 3 :");
            scanf("%d", &EvnmtExt->impact);
        }
        else
        {
            EvnmtExt->impact = 0;
        }
    }
}

void affichageCycleSaisonChosen(Architecture archi, Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Pheromone *phero)
{

    if (archi.salles == 7)
    {
        // limite des stocks de graines
        int tempGraines = agriculture->quantitéGraines;
        if (tempGraines > 9000)
        {
            tempGraines = 8999;
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
        if (tempOuvrieres > 200)
        {
            tempOuvrieres = 199;
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
            tempGraines, tempSoldats, tempOuvrieres - 1, tempNourriture, tempPucerons, tempMales, phero->ambiance, colo->nombreReines);
        printf("\n");
        sleep(2);
    }

    else if (archi.salles == 9)
    {
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
            tempOuvrieres = 150;
            OuvrieresReste = 49;
        }
        else if (tempOuvrieres > 150)
        {
            OuvrieresReste = tempOuvrieres - 150;
            tempOuvrieres = 150;
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
            tempGraines, GrainesReste, tempSoldats, tempOuvrieres - 2, tempNourriture, OuvrieresReste, tempPucerons, tempMales, phero->ambiance, colo->nombreReines);
        printf("\n"); // tempOuvrieres - 2, car on rappelle que les reines sont dans la même liste chainees que les ouvrières
        sleep(2);
    }

    else if (archi.salles == 13) // vu la taille de la colonie, elle devrait contenir 6 reines. Mais on a mit 4 pour faciliter la condition de sortie
    {
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
        // limite des ouvrieres
        int tempOuvrieres = compterFourmis(colo->ouvrieres);
        if (tempOuvrieres > 900)
        {
            tempOuvrieres = 700;
            OuvrieresReste = 100;
            OuvrieresReste1 = 99;
            int nOuvrièresSupprimes = tempOuvrieres * (50 + rand() % 21) / 100; // suppression entre 50% et 70%
            for (int j = 0; j < nOuvrièresSupprimes; ++j)
            {
                supprimerFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
            }
        }
        else if (tempOuvrieres > 800)
        {
            OuvrieresReste1 = tempOuvrieres - 804 + colo->nombreReines; // car les reines sont sur la même liste chainee mais pas dans la même salle
            tempOuvrieres = 700;
            OuvrieresReste = 100;
        }
        else
        {
            tempOuvrieres = tempOuvrieres - 4;
        }
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
            tempSoldats = 200;
            SoldatsReste = 99;
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
            tempGraines, GrainesReste, GrainesReste1, tempSoldats, SoldatsReste, tempOuvrieres, tempNourriture, OuvrieresReste, tempPucerons, OuvrieresReste1, tempMales, phero->ambiance, colo->nombreReines);
        printf("\n");
        sleep(2);
    }
}