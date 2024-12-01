#include "fourmi.h"
#include <stdio.h>
#include <string.h>

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
    printf("La fourmi %d a vieilli. Âge actuel : %d\n", fourmi->id, fourmi->age);
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