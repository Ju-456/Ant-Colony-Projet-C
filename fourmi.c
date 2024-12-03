#include "fourmi.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h> //c'est pour le "sleep(3)"
#include <stdlib.h> // Pour rand() et srand()

// Fonction pour ajouter une fourmi
void ajouterFourmi(Fourmi **tete, int id, int age, int role)
{
    Fourmi *nouvelle = (Fourmi *)malloc(sizeof(Fourmi));
    nouvelle->id = id;
    nouvelle->age = age;
    nouvelle->role = role;
    nouvelle->suivante = *tete;
    *tete = nouvelle;
}

// Fonction pour ajouter une fourmi mâle
void ajouterFourmiMale(FourmiMale **tete, int id, int age, int role)
{
    FourmiMale *nouveau = (FourmiMale *)malloc(sizeof(FourmiMale));
    nouveau->id = id;
    nouveau->age = age;
    nouveau->role = role;
    nouveau->suivante = *tete;
    *tete = nouveau;
}

// Créer une colonie
Colonie *creerColonie(int id, int nombreReines)
{
    Colonie *colonie = (Colonie *)malloc(sizeof(Colonie));
    colonie->id = id;
    colonie->nombreReines = nombreReines;
    colonie->ouvrieres = NULL;
    colonie->males = NULL;
    colonie->soldats = NULL;
    return colonie;
}

// Cultiver des champignons
void cultiverChampignons(SystemeAgricole *agriculture)
{
    agriculture->quantitéChampignons += 10;
    printf("Cultivation de champignons. Quantité actuelle : %d\n", agriculture->quantitéChampignons);
}

// Élever des pucerons
void elevagePucerons(SystemeElevage *elevage)
{
    elevage->nombrePucerons += 5;
    printf("Élevage de pucerons. Nombre actuel : %d\n", elevage->nombrePucerons);
}

// Gérer l'hygiène
void gererHygiene(Hygiène *hyg)
{
    hyg->niveauProprete = 100;
    hyg->maladies = 0;
    printf("Hygiène gérée. Niveau de propreté : %d, Maladies : %d\n", hyg->niveauProprete, hyg->maladies);
}

// Gérer la sécurité
void gererSecurite(Sécurité *securite)
{
    securite->niveauProtection = 10;
    securite->attaquesReçues = 0;
    printf("Sécurité gérée. Niveau de protection : %d, Attaques reçues : %d\n", securite->niveauProtection, securite->attaquesReçues);
}

// Ajouter du nectar
void ajouterNectar(Fourmi *fourmi)
{
    printf("La fourmi %d a collecté du nectar.\n", fourmi->id);
}

// Construire une salle
void construireSalle(Architecture *archi)
{
    archi->salles++;
    printf("Construction d'une salle. Nombre de salles : %d\n", archi->salles);
}

// Explorer l'environnement
void explorer(Environnement *enviro)
{
    enviro->exploration++;
    printf("Exploration de l'environnement. Exploration actuelle : %d\n", enviro->exploration);
}

// Faire évoluer l'âge d'une fourmi
void evoluerAge(Fourmi *fourmi)
{
    fourmi->age++;
    // printf("La fourmi %d a vieilli. Âge actuel : %d\n", fourmi->id, fourmi->age); ça fait une boucle infernal, faut trouver une solution !
}

// Gérer la reproduction de la colonie
void reproduction(Colonie *colonie)
{
    printf("Reproduction en cours...\n");
    colonie->nombreReines++;
    ajouterFourmi(&colonie->ouvrieres, 100, 0, ROLE_OUVRIERE); // Ajouter une ouvrière
    printf("Une nouvelle fourmi ouvrière a été ajoutée.\n");
}

// Gérer la saison
void gererSaison(Colonie *colonie, int saison)
{
    switch (saison)
    {
    case 0: // Printemps
        reproduction(colonie);
        break;
    case 1: // Été
        cultiverChampignons(&(SystemeAgricole){0, 0});
        break;
    case 2: // Automne
        elevagePucerons(&(SystemeElevage){0});
        break;
    case 3: // Hiver
        printf("La colonie se prépare pour l'hiver.\n");
        break;
    }
}

// Ajouter une fourmi dans une file
void enfile(Queue *q, Fourmi *fourmi)
{
    if (q->queue == NULL)
    {
        q->tete = fourmi;
        q->queue = fourmi;
    }
    else
    {
        q->queue->suivante = fourmi;
        q->queue = fourmi;
    }
}

// Retirer une fourmi de la file
Fourmi *defile(Queue *q)
{
    if (q->tete == NULL)
    {
        return NULL;
    }
    else
    {
        Fourmi *temp = q->tete;
        q->tete = q->tete->suivante;
        return temp;
    }
}

// Empiler une fourmi dans une pile
void empile(Pile *p, Fourmi *fourmi)
{
    p->elements[p->sommet++] = fourmi;
}

// Dépiler une fourmi de la pile
Fourmi *depile(Pile *p)
{
    if (p->sommet == 0)
        return NULL;
    return p->elements[--p->sommet];
}

// Créer un arbre pour l'architecture
Noeud *creerNoeud(char *nom)
{
    Noeud *nouveau = (Noeud *)malloc(sizeof(Noeud));
    nouveau->nom = strdup(nom);
    nouveau->gauche = NULL;
    nouveau->droit = NULL;
    return nouveau;
}

// Insérer un nœud dans l'arbre
void insererNoeud(Noeud **racine, char *nom)
{
    if (*racine == NULL)
    {
        *racine = creerNoeud(nom);
    }
    else
    {
        if (strcmp(nom, (*racine)->nom) < 0)
        {
            insererNoeud(&((*racine)->gauche), nom);
        }
        else
        {
            insererNoeud(&((*racine)->droit), nom);
        }
    }
}

// Afficher l'arbre
void afficherArbre(Noeud *racine)
{
    if (racine != NULL)
    {
        afficherArbre(racine->gauche);
        printf("%s\n", racine->nom);
        afficherArbre(racine->droit);
    }
}

void hiver(SystemeAgricole *agriculture, Colonie *colonie)
{
    agriculture->quantitéDeNourriture += 10; // Simule une faible production alimentaire en hiver
    agriculture->quantitéChampignons += 5;

    // Ajout de nouveaux ouvriers et soldats pour l'hiver
    for (int j = 0; j < rand() % 21 + 40; ++j)
    {
        ajouterFourmi(&colonie->ouvrieres, rand(), 0, ROLE_OUVRIERE);
    }
}

void printemps(SystemeAgricole *agriculture, SystemeElevage *elevage, Colonie *colonie)
{
    agriculture->quantitéDeNourriture += 25; // Production accrue au printemps
    agriculture->quantitéChampignons += 15;
    elevage->nombrePucerons += 20;

    // Ajout de nouveaux ouvriers et soldats pour le printemps
    for (int j = 0; j < rand() % 101 + 150; ++j)
    {
        ajouterFourmi(&colonie->ouvrieres, rand(), 0, ROLE_OUVRIERE);
    }
}

void ete(SystemeAgricole *agriculture, SystemeElevage *elevage, Colonie *colonie)
{
    agriculture->quantitéDeNourriture += 30; // Production stable en été
    agriculture->quantitéChampignons += 20;
    elevage->nombrePucerons += 30;

    // Ajout de nouveaux ouvriers et soldats pour l'été
    for (int j = 0; j < rand() % 201 + 250; ++j)
    {
        ajouterFourmi(&colonie->ouvrieres, rand(), 0, ROLE_OUVRIERE);
    }
}

void automne(SystemeAgricole *agriculture, SystemeElevage *elevage, Colonie *colonie)
{
    agriculture->quantitéDeNourriture += 15; // Production décroissante en automne
    agriculture->quantitéChampignons += 10;
    elevage->nombrePucerons += 10;

    // Ajout de nouveaux ouvriers et soldats pour l'automne
    for (int j = 0; j < rand() % 51 + 71; ++j)
    {
        ajouterFourmi(&colonie->ouvrieres, rand(), 0, ROLE_OUVRIERE);
    }
}

// appeler après GestionEvenementExterne
void affichageCycleSaison(Colonie *colonie, SystemeAgricole *agriculture, SystemeElevage *elevage)
{
    int totalOuvrieres = 0;
    int totalSoldats = 0;
    int totalMales = 0;

    // Compter les ouvrières
    Fourmi *current = colonie->ouvrieres;
    while (current != NULL)
    {
        totalOuvrieres++;
        current = current->suivante;
    }

    // Compter les soldats
    current = colonie->soldats;
    while (current != NULL)
    {
        totalSoldats++;
        current = current->suivante;
    }

    // Compter les mâles
    FourmiMale *currentMale = colonie->males;
    while (currentMale != NULL)
    {
        totalMales++;
        currentMale = currentMale->suivante;
    }

    // Affichage des statistiques
    /*
    printf("=== Statistiques de la Colonie ===\n");
    printf("Nombre d'ouvrières : %d\n", totalOuvrieres);
    printf("Nombre de soldats : %d\n", totalSoldats);
    printf("Nombre de mâles : %d\n", totalMales);
    printf("Nombre de reines : %d\n", colonie->nombreReines);
    printf("\n=== Statistiques des Systèmes ===\n");
    printf("Quantité de nourriture : %d\n", agriculture->quantitéDeNourriture);
    printf("Quantité de champignons : %d\n", agriculture->quantitéChampignons);
    printf("Nombre de pucerons : %d\n", elevage->nombrePucerons);
    printf("=============================\n");
    sleep(3);
    */
    printf(
        "*                                                                     *\n"
        "*                 === Statistiques de la Colonie ===                  *\n"
        "*                                                                     *\n"
        "*       *******************              *****************            *\n"
        "*       * Ouvrière :  %d  *             *  Reine :  %d   *            *\n"
        "*       * Soldats :   %d  ******          *               *            *\n"
        "*       *                      *         *               *            *\n"
        "*       *****           ********         *************************    *\n"
        "*           *            *                          * Mâle : %d   *    *\n"
        "*           **************                          *            *    *\n"
        "*                                                   **************    *\n"
        "*                 === Statistiques des Systèmes ===                   *\n"
        "*                                                                     *\n"
        "*       ********************                                          *\n"
        "*       * Nourriture : %d  *             *****************           *\n"
        "*       *                   *******      * pucerons :  %d *           *\n"
        "*       * Champignons : %d        *      *                *           *\n"
        "*       *****                ******      ********************         *\n"
        "*           *               **                      *       *         *\n"
        "*           *climat :   /10 *                       *********         *\n"
        "*           *****************                                         *\n"
        "*                                                                     *\n"
        "***********************************************************************\n",
        totalOuvrieres, colonie->nombreReines, totalSoldats, totalMales, agriculture->quantitéDeNourriture, elevage->nombrePucerons, agriculture->quantitéChampignons);
    sleep(3);
}

void simulationSaisons(Colonie *colonie, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison)
{
    for (int i = 0; i < nbSaison; ++i)
    {
        switch (i % 4)
        { // Répartition des saisons : 0 = HIVER, 1 = PRINTEMPS, 2 = ETE, 3 = AUTOMNE

        case 0: // HIVER
            hiver(agriculture, colonie);
            printf(
                "***********************************************************************\n"
                "*                      --- Fin de l'HIVERS ---                        *\n");
            break;

        case 1: // PRINTEMPS
            printemps(agriculture, elevage, colonie);
            printf(
                "***********************************************************************\n"
                "*                      --- Fin de PRINTEMPS ---                       *\n");
            break;

        case 2: // ETE
            ete(agriculture, elevage, colonie);
            printf(
                "***********************************************************************\n"
                "*                         --- Fin de l'ÉTÉ ---                        *\n");
            break;

        case 3: // AUTOMNE
            automne(agriculture, elevage, colonie);
            printf(
                "***********************************************************************\n"
                "*                      --- Fin de l'AUTOMNE ---                       *\n");
            break;

        default:
            break;
        }

        // Afficher les statistiques après chaque saison
        affichageCycleSaison(colonie, agriculture, elevage);

        // Simuler le vieillissement des fourmis
        Fourmi *current = colonie->ouvrieres;
        while (current != NULL)
        {
            evoluerAge(current);
            current = current->suivante;
        }
        current = colonie->soldats;
        while (current != NULL)
        {
            evoluerAge(current);
            current = current->suivante;
        }
        current = (Fourmi *)colonie->males;
        while (current != NULL)
        {
            evoluerAge(current);
            current = current->suivante;
        }
    }
}

// impact le taux de pheromones des fourmis qui impact la reproduction
void GestionEvenementExterne(int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero)
{
    // récuperer la saison actuel !!!
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
        }
        if (EvnmtExt.type == 4) // HIVER GLACIAL
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
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3) // regrouper car pas bcp de reproduction de tte façon => even ext rend encore + bas
            {
                phero.reine = 2 + (rand() % 3);
                phero.male = 1 + (rand() % 3);
                phero.alarme = EvnmtExt.impact;
            }
        }
        else if (EvnmtExt.type == 3 ) // INVASION
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
        }
        else if (EvnmtExt.type == 1) // Tempête
        {
            EvnmtExt.impact = 1 + (rand() % 3); // Impact entre 1 et 3
            if (EvnmtExt.impact == 1 || EvnmtExt.impact == 2) // reste une période de forte reproduction malgré even ext d'ou regrouper
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
        } 
        else if (EvnmtExt.type == 3) // Invasion
        {
            EvnmtExt.impact = 1 + (rand() % 3); // Impact entre 1 et 3
            if (EvnmtExt.impact == 1 || EvnmtExt.impact == 2) // reste une période de forte reproduction malgré even ext d'ou regrouper
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
        }
    }
    else if (saisonActuel == 3)
    {  // AUTOMNE
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
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3) // regrouper car pas bcp de reproduction de tte façon => even ext rend encore + bas
            {
                phero.alarme = EvnmtExt.impact;
                phero.reine = 1 + (rand() % 2);
                phero.male = 1 + (rand() % 2);
            }
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
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3) // regrouper car pas bcp de reproduction de tte façon => even ext rend encore + bas
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
        }
    }
    
}

// utiliser les pheromones changés dans GestionEvenementExterne pour la reproduction
void reproduction(Pheromone phero)
{
    int climat;            // le climat qui regne dans la fourmilliere
    if (phero.alarme >= 3) // le danger est trop grand, pas de reproduction
    {
        climat = 1 + (rand() % 3); // le climat est de 1-3/10
    }
    else
    {
        int pheroGlobal = phero.reine + phero.male ;
        if (pheroGlobal >= 4)
        {
            climat = 4 + (rand() % 8);
            if (climat = 4 || climat = 5 || climat = 6){
                // augmentation de la population des femelles de 20% et baisse de celle des males de 10%
            } else if (climat = 7 || climat = 8){
                // augmentation de la population des femelles 30% et baisse de celle des males de 15%
            }
            
        }
    }
}

// à faire : augmentation de la population en fct des pheromones et faire en sorte que saisonActuel soit prit en entree 