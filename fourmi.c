#include "fourmi.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h> // Pour le "sleep(3)"
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour srand(time(NULL));

static int prochainId = 1;// Variable G pour gérer les IDs incrémentaux

void ajouterFourmi(Fourmi **tete, int role)// Fonction générique pour ajouter une fourmi à une liste
{
    Fourmi *nouvelle = malloc(sizeof(Fourmi));
    if (!nouvelle)
    {
        fprintf(stderr, "Erreur d'allocation mémoire pour une nouvelle fourmi\n");
        return;
    }

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

    nouveau->id = prochainIdM++;  // Attribuer un ID unique au mâle
    nouveau->age = 0;
    nouveau->role = ROLE_MALE;
    nouveau->suivante = *tete;  
    *tete = nouveau;  // Mettre à jour la tête de la liste
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

// Suppression d'un mâle (après ReproductionEtMortalite)
void supprimerFourmiMale(FourmiMale **tete)
{
    if (!tete || !*tete)
        return;

    FourmiMale *aSupprimer = *tete;
    *tete = aSupprimer->suivante;
    free(aSupprimer);
}

// Initialisation aléatoire de la colonie
int RandomColonie(Colonie *colo)
{
    if (!colo)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la colonie\n");
        return -1;
    }

    colo->ouvrieres = NULL;
    colo->males = NULL;
    colo->soldats = NULL;

    for (int i = 0; i < (rand() % 61 + 150); ++i)// Ajout d'ouvrières
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }

    for (int i = 0; i < (rand() % 9 + 15); ++i)// Ajout de mâles
    {
        ajouterFourmiMale(&colo->males);
    }

    for (int i = 0; i < (rand() % 41 + 80); ++i) // Ajout de soldats
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    for (int i = 0; i < 3; ++i)// Ajout des reines
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_REINE);
    }

    colo->nombreReines = 3;
    return 0;
}

// Cultiver des champignons
void cultiverChampignons(SystemeAgricole *agriculture)
{
    agriculture->quantitéChampignons += 10;
    //printf("Cultivation de champignons. Quantité actuelle : %d\n", agriculture->quantitéChampignons);
}

// Élever des pucerons
void elevagePucerons(SystemeElevage *elevage)
{
    elevage->nombrePucerons += 5;
    //printf("Élevage de pucerons. Nombre actuel : %d\n", elevage->nombrePucerons);
}

// Gérer l'hygiène
void gererHygiene(Hygiène *hyg)
{
    hyg->niveauProprete = 100;
    hyg->maladies = 0;
    //printf("Hygiène gérée. Niveau de propreté : %d, Maladies : %d\n", hyg->niveauProprete, hyg->maladies);
}

// Gérer la sécurité
void gererSecurite(Sécurité *securite)
{
    securite->niveauProtection = 10;
    securite->attaquesReçues = 0;
    //printf("Sécurité gérée. Niveau de protection : %d, Attaques reçues : %d\n", securite->niveauProtection, securite->attaquesReçues);
}

// Ajouter du nectar
void ajouterNectar(Fourmi *fourmi)
{
    //printf("La fourmi %d a collecté du nectar.\n", fourmi->id);
}

// Construire une salle
void construireSalle(Architecture *archi)
{
    archi->salles++;
    //printf("Construction d'une salle. Nombre de salles : %d\n", archi->salles);
}

// Explorer l'environnement
void explorer(Environnement *enviro)
{
    enviro->exploration++;
    //printf("Exploration de l'environnement. Exploration actuelle : %d\n", enviro->exploration);
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
int compterFourmis(Fourmi *tete) {
    int count = 0;
    while (tete) {
        count++;
        tete = tete->suivante;
    }
    return count;
}

int FourmiliereEnEvolution(Colonie *colo)
{

    srand(time(NULL));

    if (!colo)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la colonie\n");
        return -1;
    }

    colo->ouvrieres = NULL;
    colo->males = NULL;
    colo->soldats = NULL;

    int max = 100; // capacité de stockage max pour une grande salle
    int max2 = 30; // capacité de stockage max pour une petite salle, appeler salle bis

    // ouverture de la salle 1 = debut de saison 1
    // total fourmis : -100
    printf("\n");
    printf("Bienvenue dans les aventures de la fourmilière, nous allons suivre\n"
           "son aventure sur les 3 premières saisons...\n"
           "\n*******************    SAISON 1   *******************\n"
           "C'est le début de la 1ère saison pour la fourmilière...\n");

    for (int i = 0; i < rand() % 11 + 50; ++i) // Ajout d'ouvrières entre 50 et 60
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    for (int i = 0; i < rand() % 11 + 20; ++i) // Ajout de soldats entre 20 et 30
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    int total = compterFourmis(colo->ouvrieres) + compterFourmis(colo->soldats);

    printf(
        "               - Création de la salle 1 -\n"
        "             ------------------------------\n"
        "        -----                               ----\n"
        "      ---                                     ---\n"
        "    ---            ---------                    ---\n"
        "  ---              -  %d   -                      ---\n"
        " ---               ---------                       ---\n"
        "---                                                 ---\n"
        "---                                                 ---\n"
        "---                                                 ---\n"
        "---                                                 ---\n"
        "  ---                                              ---\n"
        "      ---                                        ---\n"
        "        ---                                   ---\n"
        "           ---                            ---\n"
        "             ------------------------------\n",
        total);
        printf("1,5 mois plus tard...");
        printf("\n");
    sleep(3);

    // ouverture de la salle 1 bis = fin de saison 1
    // total fourmis : 100-130
    for (int i = 0; i < rand() % 11; ++i) // Augmente les ouvrières de 0 à 10
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    for (int i = 0; i < rand() % 21; ++i) // Augmente les soldats de 0 à 20
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    colo->nombreReines = 1;
    int totalbis = 100 - total;

    // une sous salle = 30 fourmis
    // sous salle + salle = 130 fourmis => nouvelle reine
    // apparution de la reine + nouvelle sous salle

    printf("C'est la fin de la 1ère saison pour la fourmilière...\n");
    printf(
        "             - Création de la salle 1 bis -\n"
        "             ------------------------------\n"
        "        -----                               ----\n"
        "      ---                                     ---\n"
        "    ---            ---------          ------     ---\n"
        "  ---              -  %d  -          - %d -      ---\n"
        " ---               -------------      ------       ---\n"
        "---                       - %d -                   ---\n"
        "---                       ------                    ---\n"
        "---                                                 ---\n"
        "---                                                 ---\n"
        "  ---                                              ---\n"
        "      ---                                        ---\n"
        "        ---                                   ---\n"
        "           ---                            ---\n"
        "             ------------------------------\n",
        max, colo->nombreReines, totalbis);
        printf("1,5 mois plus tard...");
        printf("\n");
    sleep(3);

    // ouverture de la salle 2 = debut saison 2
    // total fourmis : 130-230
    for (int i = 0; i < rand() % 51 + 30; ++i) // Augmente les ouvrières de 30 à 80
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    for (int i = 0; i < rand() % 71; ++i) // Augmente les soldats de 0 à 70
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }
    printf("\n*******************    SAISON 2   *********************\n");
    printf("C'est le début de la 2ème saison pour la fourmilière...\n");
    colo->nombreReines = 1;
    totalbis = 130 - total;
    printf(
        "               - Création de la salle 2 -\n"
        "             ------------------------------\n"
        "        -----                               ----\n"
        "      ---                                     ---\n"
        "    ---            ---------          ------     ---\n"
        "  ---              -  %d  -           - %d -      ---\n"
        " ---               -------------      ------       ---\n"
        "---                       - %d -                   ---\n"
        "---                       ------   ---------        ---\n"
        "---                                -  %d   -        ---\n"
        "---                                ---------        ---\n"
        "  ---                                              ---\n"
        "      ---                                       ---\n"
        "        ---                                   ---\n"
        "           ---                            ---\n"
        "             ------------------------------\n",
        max, colo->nombreReines, max2, totalbis);
        printf("1,5 mois plus tard...");
        printf("\n");
    sleep(3);

    // ouverture de la salle 2 bis = fin saison 2
    // total fourmis : 230-260
    for (int i = 0; i < rand() % 21; ++i) // Augmente les ouvrières de 0 à 20
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    for (int i = 0; i < rand() % 21 + 10; ++i) // Augmente les soldats de 10 à 30
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    colo->nombreReines = 2;
    totalbis = 90 - total;
    // apparatution d'une nouvelle reine

      printf("C'est la fin de la 2ème saison pour la fourmilière...\n");
    printf(
        "             - Création de la salle 2 bis -\n"
        "             ------------------------------\n"
        "        -----                               ----\n"
        "      ---                                     ---\n"
        "    ---            ---------          ------     ---\n"
        "  ---              -  %d  -           - %d -      ---\n"
        " ---               -------------      ------       ---\n"
        "---                       - %d -                   ---\n"
        "---                       ------   ---------        ---\n"
        "---                                -  %d  -        ---\n"
        "---                                ---------        ---\n"
        "  ---                                 - %d -       ---\n"
        "      ---                             ------    ---\n"
        "        ---                                   ---\n"
        "           ---                            ---\n"
        "             ------------------------------\n",
        max, colo->nombreReines, max2, max, totalbis);
         printf("Une nouvelle reine est apparue !\n");
         printf("1,5 mois plus tard...");
        printf("\n");
    sleep(3);

    // ouverture de la salle 3 = debut saison 3
    // total fourmis : 260-360
    for (int i = 0; i < rand() % 51 + 30; ++i) // Augmente les ouvrières de 30 à 80
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    for (int i = 0; i < rand() % 71; ++i) // Augmente les soldats de 0 à 70
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    colo->nombreReines = 2;
    totalbis = total;
    printf("\n");
    printf("*******************    SAISON 3   *********************\n");
    printf("C'est le début de la 3ème saison pour la fourmilière...\n");

    printf(
        "               - Création de la salle 3 -\n"
        "             ------------------------------\n"
        "        -----                               ----\n"
        "      ---                                     ---\n"
        "    ---            ---------          ------     ---\n"
        "  ---              -  %d  -           - %d -      ---\n"
        " ---               -------------      ------       ---\n"
        "---                       - %d -                   ---\n"
        "---                       ------   ---------        ---\n"
        "---                                -  %d  -        ---\n"
        "---                ---------       ---------        ---\n"
        "  ---              -   %d  -          - %d -       ---\n"
        "      ---          ---------          ------    ---\n"
        "        ---                                   ---\n"
        "           ---                            ---\n"
        "             ------------------------------\n",
        max, colo->nombreReines, max2, max, totalbis, max2);
        printf("1,5 mois plus tard...");
        printf("\n");
    sleep(3);

    // ouverture de la salle 3 bis = fin saison 3
    // total fourmis : 360-390
    for (int i = 0; i < rand() % 21 + 10; ++i) // Augmente les ouvrières de 10 à 30
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }
    for (int i = 0; i < rand() % 11; ++i) // Augmente les soldats de 0 à 10
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    // apparatution d'une nouvelle reine
    colo->nombreReines = 3;
    totalbis = 100 - total;

    printf("C'est la fin de la 3ème saison pour la fourmilière...\n");

    printf(
        "             - Création de la salle 3 bis -\n"
        "             ------------------------------\n"
        "        -----                               ----\n"
        "      ---                                     ---\n"
        "    ---            ---------          ------     ---\n"
        "  ---              -  %d  -           - %d -      ---\n"
        " ---               -------------      ------       ---\n"
        "---                       - %d -                   ---\n"
        "---           ------      ------   ---------        ---\n"
        "---           - %d -               -  %d  -        ---\n"
        "---           --------------       ---------        ---\n"
        "  ---              -  %d  -          - %d -       ---\n"
        "      ---          ---------          ------    ---\n"
        "        ---                                   ---\n"
        "           ---                            ---\n"
        "             ------------------------------\n",
        max, colo->nombreReines, max2, totalbis, max, max, max2);
        printf("Une nouvelle reine est apparue !\n");
        printf("1 an plus tard...");
        printf("\n");
    sleep(3);
}

void hiver(int saisonActuel, SystemeAgricole *agriculture, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, SystemeElevage *elevage)
{
    saisonActuel = 0;
    agriculture->quantitéDeNourriture += 10; // Simule une faible production alimentaire en hiver
    agriculture->quantitéChampignons += 5;

    GestionEvenementExterne(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage);
}

void printemps(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo)
{
    saisonActuel = 1;
    agriculture->quantitéDeNourriture += 25; // Production accrue au printemps
    agriculture->quantitéChampignons += 15;
    elevage->nombrePucerons += 20;

    GestionEvenementExterne(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage);
}

void ete(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo)
{
    saisonActuel = 2;
    agriculture->quantitéDeNourriture += 30; // Production stable en été
    agriculture->quantitéChampignons += 20;
    elevage->nombrePucerons += 30;

    GestionEvenementExterne(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage);
}

void automne(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo)
{
    saisonActuel = 3;
    agriculture->quantitéDeNourriture += 15; // Production décroissante en automne
    agriculture->quantitéChampignons += 10;
    elevage->nombrePucerons += 10;

    GestionEvenementExterne(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage);
}

void simuleUneSaison(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero)
{
    for (int i = 0; i < nbSaison; ++i)
    {
        switch (i % 4)
        { // Répartition des saisons : 0 = HIVER, 1 = PRINTEMPS, 2 = ETE, 3 = AUTOMNE

        case 0: // HIVER
            hiver(saisonActuel, agriculture, EvnmtExt, phero, colo, elevage);
            printf(
                "***********************************************************************\n"
                "*                       --- Fin de l'HIVER ---                       *\n");
            break;

        case 1: // PRINTEMPS
            printemps(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
            printf(
                "***********************************************************************\n"
                "*                      --- Fin de PRINTEMPS ---                       *\n");
            break;

        case 2: // ETE
            ete(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
            printf(
                "***********************************************************************\n"
                "*                         --- Fin de l'ÉTÉ ---                        *\n");
            break;

        case 3: // AUTOMNE
            automne(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
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

// impact le taux de pheromones des fourmis qui impact la ReproductionEtMortalite
void GestionEvenementExterne(int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage)
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
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3) // regrouper car pas bcp de ReproductionEtMortalite de tte façon => even ext rend encore + bas
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
            if (EvnmtExt.impact == 1 || EvnmtExt.impact == 2) // reste une période de forte ReproductionEtMortalite malgré even ext d'ou regrouper
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
            if (EvnmtExt.impact == 1 || EvnmtExt.impact == 2) // reste une période de forte ReproductionEtMortalite malgré even ext d'ou regrouper
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
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3) // regrouper car pas bcp de ReproductionEtMortalite de tte façon => even ext rend encore + bas
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
            else if (EvnmtExt.impact == 2 || EvnmtExt.impact == 3) // regrouper car pas bcp de ReproductionEtMortalite de tte façon => even ext rend encore + bas
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
    ReproductionEtMortalite(phero, colo, agriculture, elevage);
}

// Gestion de la Reproduction et de la mortalité
void ReproductionEtMortalite(Pheromone phero, Colonie *colo, void *agriculture, void *elevage)
{
    srand(time(NULL)); // générateur de nombres aléatoires

    if (phero.alarme <= 2)
    {
        phero.climat = 1 + (rand() % 4); // Climat hivernal (1 à 4)

        for (int j = 0; j < rand() % 16 + 25; ++j)
        {                                                //  "5" sont les 5 reines, on appelle cela le seuil d'exclusion, ce sont des fourmis protégés
            supprimerFourmiVieille(&colo->ouvrieres, 5); // reduction des ouvrieres
        }
        for (int j = 0; j < rand() % 11 + 15; ++j)
        {
            supprimerFourmiVieille(&colo->soldats, 5); // reduction des soldats
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
                    ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE); // Augmentation des ouvrières
                    ajouterFourmi(&colo->soldats, ROLE_SOLDAT);     // Augmentation des soldats
                }

                for (int j = 0; j < rand() % 6 + 10; ++j)
                {
                    supprimerFourmiMale(&colo->males); // Réduit les mâles
                }
            }
            else if (phero.climat == 7 || phero.climat == 8)
            {
                for (int j = 0; j < rand() % 11 + 30; ++j) // Ajouter encore plus d'ouvrières si le climat est plus favorable (printemps/automne)
                {
                    ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE); // Augmentation des ouvrières
                }
                for (int j = 0; j < rand() % 16 + 20; ++j)
                {
                    supprimerFourmiMale(&colo->males); // Réduit les mâles
                }
            }
        }
    }
    affichageCycleSaison(colo, agriculture, elevage, phero); // Affiche l'état du cycle saisonnier
}

// appeler après ReproductionEtMortalite
void affichageCycleSaison(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, Pheromone phero)
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

    // Affichage
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
        totalOuvrieres, colo->nombreReines, totalSoldats, totalMales, agriculture->quantitéDeNourriture, elevage->nombrePucerons, agriculture->quantitéChampignons, phero.climat);
    sleep(3);
}
