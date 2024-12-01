#include "fourmi.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h> //c'est pour le "sleep(3)"

// Fonction pour ajouter une fourmi
void ajouterFourmi(Fourmi **tete, int id, int age, int role) {
    Fourmi *nouvelle = (Fourmi *)malloc(sizeof(Fourmi));
    nouvelle->id = id;
    nouvelle->age = age;
    nouvelle->role = role;
    nouvelle->suivante = *tete;
    *tete = nouvelle;
}

// Fonction pour ajouter une fourmi mâle
void ajouterFourmiMale(FourmiMale **tete, int id, int age, int role) {
    FourmiMale *nouveau = (FourmiMale *)malloc(sizeof(FourmiMale));
    nouveau->id = id;
    nouveau->age = age;
    nouveau->role = role;
    nouveau->suivante = *tete;
    *tete = nouveau;
}

// Créer une colonie
Colonie* creerColonie(int id, int nombreReines) {
    Colonie *colonie = (Colonie *)malloc(sizeof(Colonie));
    colonie->id = id;
    colonie->nombreReines = nombreReines;
    colonie->ouvrieres = NULL;
    colonie->males = NULL;
    colonie->soldats = NULL;
    return colonie;
}

// Cultiver des champignons
void cultiverChampignons(SystemeAgricole *agriculture) {
    agriculture->quantitéChampignons += 10;
    printf("Cultivation de champignons. Quantité actuelle : %d\n", agriculture->quantitéChampignons);
}

// Élever des pucerons
void elevagePucerons(SystemeElevage *elevage) {
    elevage->nombrePucerons += 5;
    printf("Élevage de pucerons. Nombre actuel : %d\n", elevage->nombrePucerons);
}

// Gérer l'hygiène
void gererHygiene(Hygiène *hygiene) {
    hygiene->niveauProprete = 100;
    hygiene->maladies = 0;
    printf("Hygiène gérée. Niveau de propreté : %d, Maladies : %d\n", hygiene->niveauProprete, hygiene->maladies);
}

// Gérer la sécurité
void gererSecurite(Sécurité *securite) {
    securite->niveauProtection = 10;
    securite->attaquesReçues = 0;
    printf("Sécurité gérée. Niveau de protection : %d, Attaques reçues : %d\n", securite->niveauProtection, securite->attaquesReçues);
}

// Ajouter du nectar
void ajouterNectar(Fourmi *fourmi) {
    printf("La fourmi %d a collecté du nectar.\n", fourmi->id);
}

// Construire une salle
void construireSalle(Architecture *architecture) {
    architecture->salles++;
    printf("Construction d'une salle. Nombre de salles : %d\n", architecture->salles);
}

// Explorer l'environnement
void explorer(Environnement *environnement) {
    environnement->exploration++;
    printf("Exploration de l'environnement. Exploration actuelle : %d\n", environnement->exploration);
}

// Gérer les événements externes
void gererEvenement(EvenementExterne *evenement) {
    printf("Gestion de l'événement : type %d, impact %d\n", evenement->type, evenement->impact);
}

// Faire évoluer l'âge d'une fourmi
void evoluerAge(Fourmi *fourmi) {
    fourmi->age++;
    // printf("La fourmi %d a vieilli. Âge actuel : %d\n", fourmi->id, fourmi->age); ça fait une boucle infernal, faut trouver une solution !
}

// Gérer la reproduction de la colonie
void reproduction(Colonie *colonie) {
    printf("Reproduction en cours...\n");
    colonie->nombreReines++;
    ajouterFourmi(&colonie->ouvrieres, 100, 0, ROLE_OUVRIERE);  // Ajouter une ouvrière
    printf("Une nouvelle fourmi ouvrière a été ajoutée.\n");
}

// Gérer la saison
void gererSaison(Colonie *colonie, int saison) {
    switch(saison) {
        case 0: // Printemps
            reproduction(colonie);
            break;
        case 1: // Été
            cultiverChampignons(&(SystemeAgricole){0,0});
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
void enfile(Queue *q, Fourmi *fourmi) {
    if (q->queue == NULL) {
        q->tete = fourmi;
        q->queue = fourmi;
    } else {
        q->queue->suivante = fourmi;
        q->queue = fourmi;
    }
}

// Retirer une fourmi de la file
Fourmi *defile(Queue *q) {
    if (q->tete == NULL) {
        return NULL;
    } else {
        Fourmi *temp = q->tete;
        q->tete = q->tete->suivante;
        return temp;
    }
}

// Empiler une fourmi dans une pile
void empile(Pile *p, Fourmi *fourmi) {
    p->elements[p->sommet++] = fourmi;
}

// Dépiler une fourmi de la pile
Fourmi *depile(Pile *p) {
    if (p->sommet == 0) return NULL;
    return p->elements[--p->sommet];
}

// Créer un arbre pour l'architecture
Noeud *creerNoeud(char *nom) {
    Noeud *nouveau = (Noeud *)malloc(sizeof(Noeud));
    nouveau->nom = strdup(nom);
    nouveau->gauche = NULL;
    nouveau->droit = NULL;
    return nouveau;
}

// Insérer un nœud dans l'arbre
void insererNoeud(Noeud **racine, char *nom) {
    if (*racine == NULL) {
        *racine = creerNoeud(nom);
    } else {
        if (strcmp(nom, (*racine)->nom) < 0) {
            insererNoeud(&((*racine)->gauche), nom);
        } else {
            insererNoeud(&((*racine)->droit), nom);
        }
    }
}

// Afficher l'arbre
void afficherArbre(Noeud *racine) {
    if (racine != NULL) {
        afficherArbre(racine->gauche);
        printf("%s\n", racine->nom);
        afficherArbre(racine->droit);
    }
}

void hiver(SystemeAgricole *agriculture, Colonie *colonie ){
    agriculture->quantitéDeNourriture += 10; // Simule une faible production alimentaire en hiver
    agriculture->quantitéChampignons += 5;

    // Ajout de nouveaux ouvriers et soldats pour l'hiver
    for (int j = 0; j < rand() % 21 + 40; ++j)
    {
        ajouterFourmi(&colonie->ouvrieres, rand(), 0, ROLE_OUVRIERE);
    }
}

void printemps(SystemeAgricole *agriculture, SystemeElevage *elevage, Colonie *colonie){
    agriculture->quantitéDeNourriture += 25; // Production accrue au printemps
    agriculture->quantitéChampignons += 15;
    elevage->nombrePucerons += 20;

    // Ajout de nouveaux ouvriers et soldats pour le printemps
    for (int j = 0; j < rand() % 101 + 150; ++j)
    {
        ajouterFourmi(&colonie->ouvrieres, rand(), 0, ROLE_OUVRIERE);
    }
}

void ete(SystemeAgricole *agriculture, SystemeElevage *elevage, Colonie *colonie){
    agriculture->quantitéDeNourriture += 30; // Production stable en été
    agriculture->quantitéChampignons += 20;
    elevage->nombrePucerons += 30;

    // Ajout de nouveaux ouvriers et soldats pour l'été
    for (int j = 0; j < rand() % 201 + 250; ++j)
    {
        ajouterFourmi(&colonie->ouvrieres, rand(), 0, ROLE_OUVRIERE);
    }
}

void automne(SystemeAgricole *agriculture, SystemeElevage *elevage, Colonie *colonie){
    agriculture->quantitéDeNourriture += 15; // Production décroissante en automne
    agriculture->quantitéChampignons += 10;
    elevage->nombrePucerons += 10;

    // Ajout de nouveaux ouvriers et soldats pour l'automne
    for (int j = 0; j < rand() % 51 + 71; ++j)
    {
        ajouterFourmi(&colonie->ouvrieres, rand(), 0, ROLE_OUVRIERE);
    }
}

void afficherStatistiquesSaison(Colonie *colonie, SystemeAgricole *agriculture, SystemeElevage *elevage) {
    int totalOuvrieres = 0;
    int totalSoldats = 0;
    int totalMales = 0;

    // Compter les ouvrières
    Fourmi *current = colonie->ouvrieres;
    while (current != NULL) {
        totalOuvrieres++;
        current = current->suivante;
    }

    // Compter les soldats
    current = colonie->soldats;
    while (current != NULL) {
        totalSoldats++;
        current = current->suivante;
    }

    // Compter les mâles
    FourmiMale *currentMale = colonie->males;
    while (currentMale != NULL) {
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
        "*       * Ouvrière :  %d  *             *  Reine :  %d   *             *\n"
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
        "*       *****                ******      *******************          *\n"
        "*           *           *****                      *       *          *\n"
        "*           *           *                          *********          *\n"
        "*           *************                                             *\n"
        "*                                                                     *\n"
        "***********************************************************************\n",
    totalOuvrieres, colonie->nombreReines, totalSoldats, totalMales, agriculture->quantitéDeNourriture, elevage->nombrePucerons , agriculture->quantitéChampignons);
    sleep(3);
}

void simulationSaisons(Colonie *colonie, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison) {
    for (int i = 0; i < nbSaison; ++i) {
        switch (i % 4) { // Répartition des saisons : 0 = HIVER, 1 = PRINTEMPS, 2 = ETE, 3 = AUTOMNE
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
        afficherStatistiquesSaison(colonie, agriculture, elevage);

        // Simuler le vieillissement des fourmis
        Fourmi *current = colonie->ouvrieres;
        while (current != NULL) {
            evoluerAge(current);
            current = current->suivante;
        }
        current = colonie->soldats;
        while (current != NULL) {
            evoluerAge(current);
            current = current->suivante;
        }
        current = (Fourmi *)colonie->males;
        while (current != NULL) {
            evoluerAge(current);
            current = current->suivante;
        }
    }
}
