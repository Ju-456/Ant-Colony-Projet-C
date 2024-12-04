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
    Colonie *colo = (Colonie *)malloc(sizeof(Colonie));
    colo->id = id;
    colo->nombreReines = nombreReines;
    colo->ouvrieres = NULL;
    colo->males = NULL;
    colo->soldats = NULL;
    return colo;
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
/* void reproduction(Colonie *colo)
{
    printf("Reproduction en cours...\n");
    colo->nombreReines++;
    ajouterFourmi(&colo->ouvrieres, 100, 0, ROLE_OUVRIERE); // Ajouter une ouvrière
    printf("Une nouvelle fourmi ouvrière a été ajoutée.\n");
}

// Gérer la saison
void gererSaison(Colonie *colo, int saison)
{
    switch (saison)
    {
    case 0: // Printemps
        reproduction(colo);
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
*/

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

void hiver(int saisonActuel, SystemeAgricole *agriculture, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, SystemeElevage *elevage,int climat)
{
    saisonActuel = 0;
    agriculture->quantitéDeNourriture += 10; // Simule une faible production alimentaire en hiver
    agriculture->quantitéChampignons += 5;

    GestionEvenementExterne(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage, climat);
}

void printemps(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage,EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo,int climat)
{
    saisonActuel = 1;
    agriculture->quantitéDeNourriture += 25; // Production accrue au printemps
    agriculture->quantitéChampignons += 15;
    elevage->nombrePucerons += 20;

    GestionEvenementExterne(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage, climat);
}

void ete(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage,EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, int climat)
{
    saisonActuel = 2;
    agriculture->quantitéDeNourriture += 30; // Production stable en été
    agriculture->quantitéChampignons += 20;
    elevage->nombrePucerons += 30;

    GestionEvenementExterne(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage, climat);
}

void automne(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, int climat)
{
    saisonActuel = 3;
    agriculture->quantitéDeNourriture += 15; // Production décroissante en automne
    agriculture->quantitéChampignons += 10;
    elevage->nombrePucerons += 10;

    GestionEvenementExterne(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage, climat);
}

// appeler après reproduction
void affichageCycleSaison(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int climat)
{
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

    // Affichage des statistiques
    /*
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
        "*           *                **                     *       *         *\n"
        "*           *climat : %d /10 *                      *********         *\n"
        "*           *****************                                         *\n"
        "*                                                                     *\n"
        "***********************************************************************\n",
        totalOuvrieres, colo->nombreReines, totalSoldats, totalMales, agriculture->quantitéDeNourriture, elevage->nombrePucerons, agriculture->quantitéChampignons, climat);
    sleep(3);
}

void simuleUneSaison(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, int climat)
{
    for (int i = 0; i < nbSaison; ++i)
    {
        switch (i % 4)
        { // Répartition des saisons : 0 = HIVER, 1 = PRINTEMPS, 2 = ETE, 3 = AUTOMNE

        case 0: // HIVER
            hiver(saisonActuel, agriculture, EvnmtExt, phero, colo, elevage, climat);
            printf(
                "***********************************************************************\n"
                "*                      --- Fin de l'HIVERS ---                        *\n");
            break;

        case 1: // PRINTEMPS
            printemps(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo, climat);
            printf(
                "***********************************************************************\n"
                "*                      --- Fin de PRINTEMPS ---                       *\n");
            break;

        case 2: // ETE
            ete(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo, climat);
            printf(
                "***********************************************************************\n"
                "*                         --- Fin de l'ÉTÉ ---                        *\n");
            break;

        case 3: // AUTOMNE
            automne(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo, climat);
            printf(
                "***********************************************************************\n"
                "*                      --- Fin de l'AUTOMNE ---                       *\n");
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

// impact le taux de pheromones des fourmis qui impact la reproduction
void GestionEvenementExterne(int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int climat)
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
            EvnmtExt.impact = 1 + (rand() % 3);               // Impact entre 1 et 3
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
            EvnmtExt.impact = 1 + (rand() % 3);               // Impact entre 1 et 3
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
    reproduction(phero, colo, agriculture, elevage, climat);
}

// utiliser les pheromones changés dans GestionEvenementExterne pour la reproduction
void reproduction(Pheromone phero, Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int climat)
{
    if (phero.alarme >= 3) // le danger est trop grand, pas de reproduction, baisse de la pop
    {
        climat = 1 + (rand() % 4); // le climat est de 1-4/10, generalement l'hiver

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
        if (pheroGlobal >= 4)
        {
            climat = 5 + (rand() % 8);

            if (climat == 5 || climat == 6) // concerne generalement l'automne
            {
                for (int j = 0; j < rand() % 6 + 15; ++j) // augmentation de la population des femelles 15 - 20%
                {
                    ajouterFourmi(&colo->ouvrieres, rand(), 0, ROLE_OUVRIERE);
                }

                for (int j = 0; j < rand() % 6 + 10; ++j) // baisse de celle des males de 5 - 10%
                {
                    // *depile(Pile *p); faut qu'on puisse supprimer des fourmis !!!
                }
            }
            else if (climat == 7 || climat == 8) // concerne generalement l'ete et le printemps
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
    affichageCycleSaison(colo, agriculture, elevage, climat);
}

// à faire : baisse de la pop en fonction des pheromones en hiver, voir reproduction
// utiliser les piles à la place de l'ajout ou les 2

/* gerer les appels de fct entre, normalement :
simuleUneSaison (appeler une saison) -> ex : hiver -> GestionEvenementExterne -> reproduction -> affichageCycleSaison
*/
