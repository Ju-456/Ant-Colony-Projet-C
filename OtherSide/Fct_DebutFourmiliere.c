void FourmilierEnEvolution(Colonie *colo)
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

    for (int i = 0; i < rand() % 11 + 50; ++i) // Ajout d'ouvrières entre 50 et 60
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    for (int i = 0; i < rand() % 11 + 20; ++i) // Ajout de soldats entre 20 et 30
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    int total = colo->ouvrieres + colo->soldats;
    int max = 100; // capacité de stockage max pour une grande salle
    int max2 = 30; // capacité de stockage max pour une petite salle, appeler salle bis

    if (total < 100) // salle 1
    {
        printf(
            "               - Création de la salle 1 -\n"
            "             ------------------------------\n"
            "        -----                               ----\n"
            "      ---                                     ---\n"
            "    ---            ---------                    ---\n"
            "  ---              -  %d  -                      ---\n"
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
        sleep(3);
    }
    else if (total > 100 && total < 130) // ouverture de la salle 1 bis
    {
        colo->nombreReines = 1;
        int totalbis = total - 100;

        // une sous salle = 30 fourmis
        // sous salle + salle = 130 fourmis => nouvelle reine
        // apparution de la reine + nouvelle sous salle
        printf(
            "             - Création de la salle 1 bis -\n"
            "             ------------------------------\n"
            "        -----                               ----\n"
            "      ---                                     ---\n"
            "    ---            ---------          ------     ---\n"
            "  ---              -  %d  -          -  %d  -      ---\n"
            " ---               -------------      ------       ---\n"
            "---                       - %d-                   ---\n"
            "---                       ------                    ---\n"
            "---                                                 ---\n"
            "---                                                 ---\n"
            "  ---                                              ---\n"
            "      ---                                        ---\n"
            "        ---                                   ---\n"
            "           ---                            ---\n"
            "             ------------------------------\n",
            max, colo->nombreReines, totalbis);
        sleep(3);
    }
    else if (total > 130 && total < 230) // ouverture de la salle 2
    {
        colo->nombreReines = 1;
        int totalbis = total - 130;
        printf(
            "               - Création de la salle 2 -\n"
            "             ------------------------------\n"
            "        -----                               ----\n"
            "      ---                                     ---\n"
            "    ---            ---------          ------     ---\n"
            "  ---              -  %d  -          - %d -      ---\n"
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
        sleep(3);
    }
    else if (total > 230 && total < 260) // ouverture de la salle 2 bis
    {
        colo->nombreReines = 2;
        int totalbis = total - 230;
        // apparatution d'une nouvelle reine
        printf(
            "             - Création de la salle 2 bis -\n"
            "             ------------------------------\n"
            "        -----                               ----\n"
            "      ---                                     ---\n"
            "    ---            ---------          ------     ---\n"
            "  ---              -  %d  -          -  %d  -      ---\n"
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
            max, colo->nombreReines, max2, totalbis);
        sleep(3);
    }
    else if (total > 260 && total < 360) // ouverture de la salle 3
    {
        colo->nombreReines = 2;
        int totalbis = total - 260;

        printf(
            "             - Création de la salle 2 bis -\n"
            "             ------------------------------\n"
            "        -----                               ----\n"
            "      ---                                     ---\n"
            "    ---            ---------          ------     ---\n"
            "  ---              -  %d  -          -  %d  -      ---\n"
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
        sleep(3);
    }
    else if (total > 360 && total < 390) // ouverture de la salle 3 bis
    {
        // apparatution d'une nouvelle reine
        colo->nombreReines = 3;
        int totalbis = total - 260;

        printf(
            "             - Création de la salle 2 bis -\n"
            "             ------------------------------\n"
            "        -----                               ----\n"
            "      ---                                     ---\n"
            "    ---            ---------          ------     ---\n"
            "  ---              -  %d  -          -  %d  -      ---\n"
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
        sleep(3);
    }
}

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

    for (int i = 0; i < ; ++i) // Ajout d'ouvrières
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

    for (int i = 0; i < 3; ++i) // Ajout des reines
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_REINE);
    }

    colo->nombreReines = 3;
    return 0;
}

// augmentation 1
// simulation avec appelle de la nouvelle fonction


// augmentation 2
// simulation avec appelle de la nouvelle fonction

// 6 fois jusqu'a arriver à salle 3 bis

// reprise de la simulation normale avec aleatoire mais valeur entre 0 - 390 max 