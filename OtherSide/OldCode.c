//V1
// utiliser les pheromones changés dans GestionEvenementExterne pour la reproduction
void reproduction(Pheromone phero, Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage)
{
    if (phero.alarme <= 2) // le danger est trop grand, pas de reproduction, baisse de la pop
    {
        phero.climat = 1 + (rand() % 4);                 // le phero.climat est de 1-4/10, generalement l'hiver
        for (int j = 0; j < rand() % 16 + 25; ++j) // baisse de la population des femelles 15 - 25%
        {
            // *depile(Pile *p); faut qu'on puisse supprimer des fourmis !!!
        }

        for (int j = 0; j < rand() % 11 + 15; ++j) // baisse de celle des males de 10 - 15%
        {
            // *depile(Pile *p); faut qu'on puisse supprimer des fourmis !!!
        }
    }
    else
    {
        int pheroGlobal = phero.reine + phero.male;
        if (pheroGlobal >= 3)
        {
            phero.climat = (5 + (rand() % 4));

            if (phero.climat == 5 || phero.climat == 6) // concerne generalement l'automne
            {                       // recuperer la valeur du rand pour creer ensuite
                for (int j = 0; j < rand() % 6 + 15; ++j) // augmentation de la population des femelles 15 - 20%
                {
                    ajouterFourmi(&colo->ouvrieres, rand() % 6 + 15, 0, ROLE_OUVRIERE);
                }

                for (int j = 0; j < rand() % 6 + 10; ++j) // baisse de celle des males de 5 - 10%
                {
                    supprimerFourmiMale(**tete, id, age, role);
                }
            }
            else if (phero.climat == 7 || phero.climat == 8) // concerne generalement l'ete et le printemps
            {
                for (int j = 0; j < rand() % 11 + 30; ++j) // augmentation de la population des femelles 30 - 40%
                {
                    ajouterFourmi(&colo->ouvrieres, rand(), 0, ROLE_OUVRIERE);
                }

                for (int j = 0; j < rand() % 16 + 20; ++j) // baisse de celle des males de 15 - 20%
                {
                    // *depile(Pile *p); faut qu'on puisse supprimer des fourmis !!!
                }
            }
        }
    }
    affichageCycleSaison(colo, agriculture, elevage, phero);
}*/

supprimerFourmiVieille(&colo->soldats, 5);
supprimerFourmiVieille(&colo->ouvrieres, 5);

supprimerFourmiMale(&colo->males);

ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
ajouterFourmi(&colo->soldats, ROLE_SOLDAT);

// V2
void reproduction(Pheromone phero, Colonie *colo, void *agriculture, void *elevage)
{
    srand(time(NULL)); // générateur de nombres aléatoires

    if (phero.alarme <= 2)
    {
        phero.climat = 1 + (rand() % 4); // Climat hivernal (1 à 4)

        for (int j = 0; j < rand() % 16 + 25; ++j)
        {
            supprimerFourmiMale(&colo->males, NULL);// Réduire les mâles
        }
        for (int j = 0; j < rand() % 11 + 15; ++j)
        {
            supprimerFourmiMale(&colo->males, NULL); // Réduit les mâles
        }
    }
    else
    {
        int pheroGlobal = phero.reine + phero.male;
        if (pheroGlobal >= 3)
        {
            phero.climat = 5 + (rand() % 4); // Climat automne ou printemps (5 à 8)

            if (phero.climat == 5 || phero.climat == 6)
            {
                for (int j = 0; j < rand() % 6 + 15; ++j) // Ajouter de nouvelles ouvrières si le climat est favorable (printemps/automne)
                {
                    ajouterFourmi(&colo->ouvrieres, NULL); // Augmente les ouvrières
                }
                
                for (int j = 0; j < rand() % 6 + 10; ++j)
                {
                    supprimerFourmiMale(&colo->males, NULL); // Réduit les mâles
                }
            }
            else if (phero.climat == 7 || phero.climat == 8)
            {
                for (int j = 0; j < rand() % 11 + 30; ++j)// Ajouter encore plus d'ouvrières si le climat est plus favorable (printemps/automne)
                {
                    ajouterFourmi(&colo->ouvrieres, NULL); // Augmente les ouvrières
                }
                for (int j = 0; j < rand() % 16 + 20; ++j)
                {
                    supprimerFourmiMale(&colo->males, NULL); // Réduit les mâles
                }
            }
        }
    }

    affichageCycleSaison(colo, agriculture, elevage, phero); // Affiche l'état du cycle saisonnier
}

// Affichage des statistiques, interface plus epuré 
    
    printf("=== Statistiques de la Colonie ===\n");
    printf("Nombre d'ouvrières : %d\n", totalOuvrieres);
    printf("Nombre de soldats : %d\n", totalSoldats);
    printf("Nombre de mâles : %d\n", totalMales);
    printf("Nombre de reines : %d\n", colo->nombreReines);
    printf("\n=== Statistiques des Systèmes ===\n");
    printf("Quantité de nourriture : %d\n", agriculture->quantitéDeNourriture);
    printf("Quantité de champignons : %d\n", agriculture->quantitéChampignons);
    printf("Nombre de pucerons : %d\n", elevage->nombrePucerons);
    printf("=============================\n");
    sleep(3);
    
// Créer une colonie
Colonie *creerColonie(int id, int nombreReines)
{
    Colonie *colo = (Colonie *)malloc(sizeof(Colonie));
    colo->id = id;
    colo->nombreReines = nombreReines;
    colo->ouvrieres = NULL;
    colo->males = NULL;
    colo->soldats = NULL;
    return colo;
}

//ancienne fonction ajout

void ajouterFourmi(Fourmi **tete, Fourmi *nouvelle)
{
    if (!nouvelle)
    {
        fprintf(stderr, "Erreur creation de la fourmi\n");
        return;
    }
    nouvelle->suivante = *tete;
    *tete = nouvelle;
}

void ajouterFourmiMale(FourmiMale **tete, FourmiMale *nouveau)
{
    if (!nouveau)
    {
        fprintf(stderr, "Erreur creation de la fourmi male\n");
        return;
    }
    nouveau->suivante = *tete;
    *tete = nouveau;
}

int totalOuvrieres = 0;
    int totalSoldats = 0;
  /*  int totalMales = 0;

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