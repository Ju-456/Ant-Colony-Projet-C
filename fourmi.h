#ifndef FOURMI_H
#define FOURMI_H

#include <stdlib.h>

// Définition des rôles des fourmis
#define ROLE_OUVRIERE 0
#define ROLE_SOLDAT 1
#define ROLE_REINE 2
#define ROLE_MALE 3
#define ROLE_POT_DE_MIEL 4

// Structure pour une fourmi
typedef struct Fourmi 
{
    int id;
    int age;
    int role;
    struct Fourmi *suivante;
} Fourmi;

// Structure pour une fourmi mâle
typedef struct FourmiMale 
{
    int id;
    int age;
    int role;
    struct FourmiMale *suivante;
} FourmiMale;

// Structure pour une colonie
typedef struct Colonie 
{
    int id;
    int nombreReines;
    Fourmi *ouvrieres;
    FourmiMale *males;
    Fourmi *soldats;
} Colonie;

// Structures pour les systèmes agricoles et d'élevage
typedef struct SystemeAgricole 
{
    int quantitéDeNourriture;
    int quantitéChampignons;
} SystemeAgricole;

typedef struct SystemeElevage 
{
    int nombrePucerons;
} SystemeElevage;

// Structures pour l'hygiène et la sécurité
typedef struct Hygiène 
{
    int niveauProprete;
    int maladies;
} Hygiène;

typedef struct Sécurité 
{
    int niveauProtection;
    int attaquesReçues;
} Sécurité;

// Structure pour l'architecture de la fourmilière
typedef struct Architecture 
{
    int salles;
} Architecture;

// Structure pour l'environnement extérieur
typedef struct Environnement 
{
    int exploration;
    int ressourcesNourriture;
} Environnement;

// Structure pour gérer les événements externes
typedef struct EvenementExterne 
{
    int type; // 0 pour invasion, 1 pour tempête
    int impact;
} EvenementExterne;

// Structure pour gérer les pheromones des fourmis reines et mâles
typedef struct
{
    char reine;
    char male;
    char alarme;
} Pheromone;

// Structure pour gérer les files de fourmis
typedef struct Queue 
{
    Fourmi *tete;
    Fourmi *queue;
} Queue;

// Structure pour gérer les piles de fourmis
typedef struct Pile 
{
    Fourmi *elements[100];
    int sommet;
} Pile;

// Structure pour gérer un arbre (pour l'architecture)
typedef struct Noeud 
{
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
void simulationSaisons(Colonie *colonie, SystemeAgricole *agriculture, SystemeElevage *elevage, int mois);
void hiver(SystemeAgricole *agriculture, Colonie *colonie );
void printemps(SystemeAgricole *agriculture, SystemeElevage *elevage, Colonie *colonie);
void ete (SystemeAgricole *agriculture, SystemeElevage *elevage, Colonie *colonie);
void automne (SystemeAgricole *agriculture, SystemeElevage *elevage, Colonie *colonie);
void affichageCycleSaison(Colonie *colonie, SystemeAgricole *agriculture, SystemeElevage *elevage);

// --- Systèmes Agricoles et d'Élevage ---
void cultiverChampignons(SystemeAgricole *agriculture);
void elevagePucerons(SystemeElevage *elevage);

// --- Infrastructure et Organisation ---
void construireSalle(Architecture *architecture);
void gererHygiene(Hygiène *hygiene);
void gererSecurite(Sécurité *securite);

// --- Exploration et Environnement ---
void explorer(Environnement *environnement);
// Gestion evenement ext saison

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