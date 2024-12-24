#ifndef ANNEXE_FUNCTIONS_H
#define ANNEXE_FUNCTIONS_H
#endif // ANNEXE_FUNCTIONS_H

#include "fourmi.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h> // Pour le "sleep(3)"
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour srand(time(NULL));

void ajouterFourmi(Fourmi **tete, int role) // Fonction générique pour ajouter une fourmi à une liste
{
    Fourmi *nouvelle = malloc(sizeof(Fourmi));
    if (!nouvelle)
    {
        fprintf(stderr, "Erreur d'allocation mémoire pour une nouvelle fourmi\n");
        return;
    }

    static int prochainId = 1;
    
    nouvelle->id = prochainId++; // Une fourmi = un ID unique
    nouvelle->age = 0;
    nouvelle->role = role;
    nouvelle->suivante = *tete;
    *tete = nouvelle;
}

void ajouterFourmiMale(FourmiMale **tete)
{
    static int prochainIdM = 1;
    FourmiMale *nouveau = malloc(sizeof(FourmiMale));
    if (!nouveau)
    {
        fprintf(stderr, "Erreur d'allocation mémoire pour un mâle\n");
        return;
    }

    nouveau->id = prochainIdM++; // Attribuer un ID unique au mâle
    nouveau->age = 0;
    nouveau->role = ROLE_MALE;
    nouveau->suivante = *tete;
    *tete = nouveau; // Mettre à jour la tête de la liste
}

// Suppression d'une fourmi, a utiliser peut etre plus tard
void supprimerFourmi(Fourmi **tete, Fourmi *cible)
{
    if (!tete || !*tete || !cible)
        return;

    Fourmi *courant = *tete;
    Fourmi *precedent = NULL;

    while (courant)
    {
        if (courant->id == cible->id)
        {
            if (precedent == NULL)
                *tete = courant->suivante; // Suppression en tête
            else
                precedent->suivante = courant->suivante;

            free(courant);
            return;
        }
        precedent = courant;
        courant = courant->suivante;
    }
}

// Suppression des fourmis les plus âgées (hors reines)
void supprimerFourmiVieille(Fourmi **tete, int ignorerReines)
{
    if (!tete || !*tete)
        return;

    Fourmi *courant = *tete;
    Fourmi *Vieille = NULL;
    Fourmi *precedent = NULL;
    Fourmi *precedentVieille = NULL;

    int index = 0;

    while (courant)
    {
        if (index >= ignorerReines && (!Vieille || courant->age > Vieille->age))
        {
            Vieille = courant;
            precedentVieille = precedent;
        }
        precedent = courant;
        courant = courant->suivante;
        index++;
    }

    // Suppression de la plus vieille fourmi
    if (Vieille)
    {
        if (precedentVieille)
            precedentVieille->suivante = Vieille->suivante;
        else
            *tete = Vieille->suivante;

        free(Vieille);
    }
}

// Suppression d'un mâle (après PonteEtMortalite)
void supprimerFourmiMale(FourmiMale **tete)
{
    if (!tete || !*tete)
    return;

    FourmiMale *aSupprimer = *tete;
    *tete = aSupprimer->suivante;
    free(aSupprimer);
}

// Cultiver des Graines
void cultiverGraines(SystemeAgricole *agriculture)
{
    agriculture->quantitéGraines += 10;
    // printf("Cultivation de Graines. Quantité actuelle : %d\n", agriculture->quantitéGraines);
}

// Élever des pucerons
void elevagePucerons(SystemeElevage *elevage)
{
    elevage->nombrePucerons += 5;
    // printf("Élevage de pucerons. Nombre actuel : %d\n", elevage->nombrePucerons);
}

// Gérer l'hygiène
void gererHygiene(Hygiène *hyg)
{
    hyg->niveauProprete = 100;
    hyg->maladies = 0;
    // printf("Hygiène gérée. Niveau de propreté : %d, Maladies : %d\n", hyg->niveauProprete, hyg->maladies);
}

// Gérer la sécurité
void gererSecurite(Sécurité *securite)
{
    securite->niveauProtection = 10;
    securite->attaquesReçues = 0;
    // printf("Sécurité gérée. Niveau de protection : %d, Attaques reçues : %d\n", securite->niveauProtection, securite->attaquesReçues);
}

// Ajouter du nectar
void ajouterNectar(Fourmi *fourmi)
{
    // printf("La fourmi %d a collecté du nectar.\n", fourmi->id);
}

// Construire une salle
void construireSalle(Architecture *archi)
{
    archi->salles++;
    // printf("Construction d'une salle. Nombre de salles : %d\n", archi->salles);
}

// Explorer l'environnement
void explorer(Environnement *enviro)
{
    enviro->exploration++;
    // printf("Exploration de l'environnement. Exploration actuelle : %d\n", enviro->exploration);
}

// Faire évoluer l'âge d'une fourmi
void evoluerAge(Fourmi *fourmi)
{
    fourmi->age++;
    // printf("La fourmi %d a vieilli. Âge actuel : %d\n", fourmi->id, fourmi->age); ça fait une boucle infernal, faut trouver une solution !
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

// Fonction pour compter les fourmis dans une liste
int compterFourmis(Fourmi *tete)
{
    int count = 0;
    while (tete)
    {
        count++;
        tete = tete->suivante;
    }
    return count;
}

int compterFourmisMales(FourmiMale *tete) {
    int count = 0;
    while (tete) {
        count++;
        tete = tete->suivante;
    }
    return count;
}


// Fonction pour libérer la mémoire de la colonie
void libererColonie(Colonie *colo) {
    // Implémentez la libération de chaque liste de fourmis
    // Exemple :
    while (colo->ouvrieres) {
        supprimerFourmi(&colo->ouvrieres, colo->ouvrieres);
    }
    while (colo->soldats) {
        supprimerFourmi(&colo->soldats, colo->soldats);
    }
    while (colo->males) {
        supprimerFourmiMale(&colo->males);
    }
}