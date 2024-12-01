#ifndef FOURMI_H
#define FOURMI_H

#include <stdlib.h>

// Définition des rôles des fourmis
#define ROLE_OUVRIERE 0
#define ROLE_SOLDAT 1
#define ROLE_REINE 2
#define ROLE_MALE 3
#define ROLE_POT_DE_MIEL 4

typedef struct Fourmi {
    int id;
    int age;
    int role;
    struct Fourmi *suivante;
} Fourmi;

typedef struct FourmiMale {
    int id;
    int age;
    int role;
    struct FourmiMale *suivante;
} FourmiMale;

typedef struct Colonie {
    int id;
    int nombreReines;
    Fourmi *ouvrieres;
    FourmiMale *males;
    Fourmi *soldats;
} Colonie;

typedef struct SystemeAgricole {
    int quantitéDeNourriture;
    int quantitéChampignons;
} SystemeAgricole;

typedef struct SystemeElevage {
    int nombrePucerons;
} SystemeElevage;

typedef struct Hygiène {
    int niveauProprete;
    int maladies;
} Hygiène;

typedef struct Sécurité {
    int niveauProtection;
    int attaquesReçues;
} Sécurité;

typedef struct Architecture {
    int salles;
} Architecture;

typedef struct Environnement {
    int exploration;
    int ressourcesNourriture;
} Environnement;

typedef struct EvenementExterne {
    int type;
    int impact;
} EvenementExterne;

typedef struct Queue {
    Fourmi *tete;
    Fourmi *queue;
} Queue;

typedef struct Pile {
    Fourmi *elements[100];
    int sommet;
} Pile;

typedef struct Noeud {
    char *nom;
    struct Noeud *gauche;
    struct Noeud *droit;
} Noeud;

// --- Gestion des Fourmis ---
void ajouterFourmi(Fourmi **tete, int id, int age, int role);
void ajouterFourmiMale(FourmiMale **tete, int id, int age, int role);
void evoluerAge(Fourmi *fourmi);
void ajouterNectar(Fourmi *fourmi);

// --- Gestion de la Colonie ---
Colonie* creerColonie(int id, int nombreReines);
void reproduction(Colonie *colonie);
// --- Gestion des Saisons ---
//void gererSaison(Colonie *colonie, int saison);
void simulationSaisons(Colonie *colonie, SystemeAgricole *agriculture, SystemeElevage *elevage, int mois);
void hiver(SystemeAgricole *agriculture, Colonie *colonie );
void printemps(SystemeAgricole *agriculture, SystemeElevage *elevage, Colonie *colonie);
void ete (SystemeAgricole *agriculture, SystemeElevage *elevage, Colonie *colonie);
void automne (SystemeAgricole *agriculture, SystemeElevage *elevage, Colonie *colonie);
void afficherStatistiquesSaison(Colonie *colonie, SystemeAgricole *agriculture, SystemeElevage *elevage);

// --- Systèmes Agricoles et d'Élevage ---
void cultiverChampignons(SystemeAgricole *agriculture);
void elevagePucerons(SystemeElevage *elevage);

// --- Infrastructure et Organisation ---
void construireSalle(Architecture *architecture);
void gererHygiene(Hygiène *hygiene);
void gererSecurite(Sécurité *securite);

// --- Exploration et Environnement ---
void explorer(Environnement *environnement);
void gererEvenement(EvenementExterne *evenement);

// --- Gestion des Files ---
void enfile(Queue *q, Fourmi *fourmi);
Fourmi *defile(Queue *q);

// --- Gestion des Piles ---
void empile(Pile *p, Fourmi *fourmi);
Fourmi *depile(Pile *p);

// --- Fonctions pour l'Arbre ---
Noeud *creerNoeud(char *nom);
void insererNoeud(Noeud **racine, char *nom);
void afficherArbre(Noeud *racine);

#endif