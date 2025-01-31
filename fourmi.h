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

// Structure pour gérer les phéromones impactant la fourmilieres
typedef struct
{
    int ambiance;
    char reine;
    char cohesion;
    char alarme;
} Pheromone;

// Structure pour gérer les événements externes
typedef struct EvenementExterne
{
    int type;   // 0 = rien ; 1 =  tempete ; 2 = inondation ; 3 = invasion ;  4 = hiver glacial
    int impact; // impact allant de 1 à 3, 3 étant la plus grosse échelle de gravité
} EvenementExterne;

// Structures pour les systèmes agricoles et d'élevage
typedef struct SystemeAgricole
{
    int quantitéDeNourriture;
    int quantitéGraines;
} SystemeAgricole;

typedef struct SystemeElevage
{
    int nombrePucerons;
} SystemeElevage;

// Structures pour l'hygiène et la sécurité
typedef struct Hygiène
{
    int niveauProprete;
    int niveauMaladie;
} Hygiène;

typedef struct Sécurité
{
    int niveauProtection;
    int attaquesReçues;
} Sécurité;

// Structure pour l'architecture de la fourmilière
typedef struct Architecture
{
    int salles; // 7, 9 ou 13 selon la configuration choisie
} Architecture;

// Structure pour l'environnement extérieur
typedef struct Environnement
{
    int exploration;
    int ressourcesNourriture;
} Environnement;

// Structure pour gérer un arbre (pour l'architecture)
typedef struct Noeud
{
    char *nom;
    struct Noeud *gauche;
    struct Noeud *droit;
} Noeud;

// --- Gestion des Fourmis ---
void ajouterFourmi(Fourmi **tete, int role);
void ajouterFourmiMale(FourmiMale **tete);

int compterFourmis(Fourmi *tete);
int compterFourmisMales(FourmiMale *tete);

void supprimerFourmi(Fourmi **tete, Fourmi *cible);
void supprimerFourmiVieille(Fourmi **tete, int ignorerReines);
void supprimerFourmiMale(FourmiMale **tete);

void evoluerAge(Fourmi *fou);
void ajouterNectar(Fourmi *fou);

// Menu afin de choisir si gestion automatique ou pas
void menu(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int *saisonActuel, EvenementExterne *EvnmtExt, Pheromone *phero, Hygiène *hyg, Sécurité *secu, Architecture archi, Environnement enviro);
// Fonctionnement de la colonie en Random
void FourmiliereEnEvolution(Colonie *colo);
int RandomColonie(Colonie *colo, Hygiène *hyg, Sécurité *secu, SystemeElevage *elevage, SystemeAgricole *agriculture);

// Fonctionnement de la colonie en entrée utilisateur
void ChosenColonie(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Architecture *archi, Hygiène *hyg, Sécurité *secu);

void Configuration1(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu);
void Configuration2(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu);
void Configuration3(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu);

void RandomCalculAfterChosen(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu);
// void afficherEtatColonie(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Hygiène *hyg, Sécurité *secu);

// --- Gestion des Saisons ---
// simuleUneSaison (appeler une saison) -> ex : hiver -> GestionEvenementExterne -> PonteEtMortalite -> affichageCycleSaison
void simuleUneSaisonRandom(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int *saisonActuel, Hygiène *hyg, Sécurité *secu, EvenementExterne *EvnmtExt, Pheromone *phero, Architecture archi);
void simuleUneSaisonChosen(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int *saisonActuel, Hygiène *hyg, Sécurité *secu, EvenementExterne *EvnmtExt, Pheromone *phero, Architecture archi);
void PonteEtMortalite(Pheromone *phero, Colonie *colo);
void NiveauPropreteEtMaladie(Hygiène *hyg, Colonie *colo);
void NiveauSecuritéEtProtection(Sécurité *secu, Colonie *colo);

// --- Exploration et Environnement ---
void explorer(Environnement *enviro);
void GestionEvenementExterneRandom(EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo, int *saisonActuel);
void GestionEvenementExterneChosen(EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo, int *saisonActuel);

void EvenementExterieurHiver(EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo, int *saisonActuel);
void EvenementExterieurPrintemps(EvenementExterne *EvnmtExt, Pheromone *phero, int *saisonActuel);
void EvenementExterieurEte(EvenementExterne *EvnmtExt, Pheromone *phero, int *saisonActuel);
void EvenementExterieurAutomne(EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo, int *saisonActuel);

void hiver(int *saisonActuel, SystemeAgricole *agriculture, EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo, SystemeElevage *elevage);
void printemps(int *saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo);
void ete(int *saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo);
void automne(int *saisonActuel, SystemeAgricole *agricultur, SystemeElevage *elevage, EvenementExterne *EvnmtExt, Pheromone *phero, Colonie *colo);

void affichageCycleSaisonRandom(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Pheromone *phero);
void affichageCycleSaisonChosen(Architecture archi, Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Pheromone *phero);

// --- Systèmes Agricoles et d'Élevage ---
void cultiverGraines(SystemeAgricole *agriculture);
void elevagePucerons(SystemeElevage *elevage);

// --- Infrastructure et Organisation ---
void construireSalle(Architecture *archi);
void gererHygiene(Hygiène *hyg);
void gererSecurite(Sécurité *secu);

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

void libererColonie(Colonie *colo);

#endif