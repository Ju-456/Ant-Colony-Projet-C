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
    int type;   // 0 = rien ; 1 =  tempete ; 2 = inondation ; 3 = invasion ;  4 = hiver glacial
    int impact; // impact allant de 1 à 3, 3 étant la plus grosse échelle de gravité
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
void evoluerAge(Fourmi *fou);
void ajouterNectar(Fourmi *fou);

// --- Gestion de la Colonie ---
Colonie *creerColonie(int id, int nombreReines);
void reproduction(Pheromone phero, Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int climat);

// --- Gestion des Saisons ---
void simuleUneSaison(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, const int climat);

void hiver(int saisonActuel, SystemeAgricole *agriculture, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, SystemeElevage *elevage, const int climat);
void printemps(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, const int climat);
void ete(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, const int climat);
void automne(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, const int climat);

void affichageCycleSaison(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, const int climat);

// --- Systèmes Agricoles et d'Élevage ---
void cultiverChampignons(SystemeAgricole *agriculture);
void elevagePucerons(SystemeElevage *elevage);

// --- Infrastructure et Organisation ---
void construireSalle(Architecture *archi);
void gererHygiene(Hygiène *hyg);
void gererSecurite(Sécurité *secu);

// --- Exploration et Environnement ---
void explorer(Environnement *enviro);
void GestionEvenementExterne(int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, const int climat);

// --- Gestion des Files ---
void enfile(Queue *q, Fourmi *fou);
Fourmi *defile(Queue *q);

// --- Gestion des Piles ---
void empile(Pile *p, Fourmi *fou);
Fourmi *depile(Pile *p);

// --- Fonctions pour l'Arbre ---
Noeud *creerNoeud(char *nom);
void insererNoeud(Noeud **racine, char *nom);
void afficherArbre(Noeud *racine);

#endif