#include "fourmi.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h> // Pour le "sleep(3)"
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour srand(time(NULL));

void menu(Colonie *colo, int nbSaison, int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero)
{
    printf("Souhaitez vous une simulation aléatoire (1) ou avec des valeurs choisies (2) ?");

    int choice = 0;
    printf(
        "\n1. Random Value\n"
        "2. Chosen Value \n"
        "Entrer votre choix :");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        RandomColonie(colo);

        SystemeAgricole agriculture = {100, 50};
        SystemeElevage elevage = {10};
        Hygiène hyg = {100, 0};
        Sécurité secu = {10, 0};
        Architecture archi = {0};
        Environnement enviro = {0, 200};

        FourmiliereEnEvolution(colo);                                                           // Départ de la colonie
        simuleUneSaison(colo, &agriculture, &elevage, nbSaison, saisonActuel, EvnmtExt, phero); //
        // simuleUneSaison (appeler une saison) -> ex : hiver -> GestionEvenementExterne -> ReproductionEtMortalite -> affichageCycleSaison

        cultiverGraines(&agriculture);
        elevagePucerons(&elevage);
        gererHygiene(&hyg);
        gererSecurite(&secu);
        construireSalle(&archi);
        explorer(&enviro);

        // les nouveautés en commentaire ont besoin d'être faites, notamment implémenter en aléatoire
        break;
    case 2:
        ChosenColonie(colo);

        // SystemeAgricole
        printf("=== Systeme Agricole ===\n");
        printf("Entrez la quantité de nourriture (100 - 400):");
        scanf("%d", &agriculture.quantitéDeNourriture);
        printf("Entrez la quantité de graines (60 - 160): ");
        scanf("%d", &agriculture.quantitéGraines);

        // SystemeElevage
        printf("\n=== Systeme Elevage ===\n");
        printf("Entrez le nombre de pucerons (100 - 300):");
        scanf("%d", &elevage.nombrePucerons);

        // Hygiène
        printf("\n=== Hygiène ===\n");
        printf("Entrez le niveau de propreté (1 à 5): ");
        scanf("%d", &hyg.niveauProprete);
        printf("Entrez le type de maladies (1, 2 ou 3): "); // definir 2/3 maladies possibles
        scanf("%d", &hyg.maladies);

        // Sécurité
        printf("\n=== Sécurité ===\n");
        printf("Entrez le niveau de protection (1 - 5): "); // le niveau de protection allant de 0 à 5
        scanf("%d", &secu.niveauProtection);
        printf("Entrez le nombre d'attaques reçues (1 - 10): "); // une attaque = - 1 à 10 soldats
        scanf("%d", &secu.attaquesReçues);

        // Architecture
        printf("\n=== Architecture ===\n");
        printf("Entrez le type de configuration de la fourmilière : ");
        printf(
            "\n       === Architecture ===\n"
            "Type de configuration de la fourmilière : "
            "*****************************************\n"
            "*          Gestion des Salles           *\n"
            "*****************************************\n\n"
            ">>> Salles Obligatoires :\n"
            " - Graines, Nourriture, Pucerons, Mâles, Reines, Ouvrières, Soldats\n\n"
            ">>> Salles Complémentaires Disponibles :\n"
            " - +2 Ouvrières, +2 Soldats\n\n"
            "=== Choix des Configurations ===\n"
            " 1. Configuration **Minimale** :\n"
            "    - Salles obligatoires uniquement (7 salles)\n\n"
            " 2. Configuration **Moyenne** :\n"
            "    - Salles obligatoires +1 Ouvrières +1 Soldats (9 salles)\n\n"
            " 3. Configuration **Maximale** :\n"
            "    - Salles obligatoires +2 Ouvrières +2 Soldats (12 salles)\n\n"
            "*****************************************\n"
            ">>> Veuillez entrer 1, 2 ou 3 selon la configuration choisie : ");
        int choice = 0;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Voici à quoi ressemblera la configuration minimale (7 salles):\n");
            printf(
                "                                       - Fourmilière -\n"
                "                             --------------------------------\n"
                "                    --------                                  -------\n"
                "                ----                       Graines                    ----\n"
                "            ----                         ------------                       ----\n"
                "        ----                             -          -                          ----\n"
                "      ----       Soldats                 -     ?    -                              ----\n"
                "    -----       ---------                -          -                               -----\n"
                "  ------        -       -                ------------               Ouvrières         ------\n"
                " ------         -   ?   -                                          ------------        ------\n"
                "------          ---------                                          -          -          ------\n"
                "------                                    Nourriture               -     ?    -           ------\n"
                "------                                -----------------            -          -           ------\n"
                "------           Pucerons             -               -            ------------           ------\n"
                " -----         ------------           -       ?       -                                  -----\n"
                "  -----        -          -           -               -                                 -----\n"
                "   -----       -     ?    -           -----------------                                -----\n"
                "    -----      -          -    Mâles                                                  -----\n"
                "      ----     ------------   ------                    AMBIANCE                     ----\n"
                "        -----                 -  ? -       Reines         ?/10                    -----\n"
                "            -----             ------       ------                           -----\n"
                "                -----                      -  ? -                   -----\n"
                "                    --------               ------             ------\n"
                "                             --------------------------------\n");
            break;
        case 2:
            printf("Voici à quoi ressemblera la configuration moyenne (7 + 2 salles):\n");
            printf(
                "                                       - Fourmilière -\n"
                "                             --------------------------------\n"
                "                    --------                                  -------\n"
                "                ----                       Graines                    ----\n"
                "            ----                   ------------------                       ----\n"
                "        ----                       -  +1 -          -                          ----\n"
                "      ----       Soldats           -------     ?    -                              ----\n"
                "    -----       ---------                -          -                               -----\n"
                "  ------        -       -                ------------               Ouvrières         ------\n"
                " ------         -   ?   -                                          ------------        ------\n"
                "------          ---------                                          -          -          ------\n"
                "------                                    Nourriture               -     ?    -           ------\n"
                "------                                -----------------            -          -           ------\n"
                "------           Pucerons             -               -            ------------------     ------\n"
                " -----         ------------           -       ?       -                        - +1 -    -----\n"
                "  -----        -          -           -               -                        ------   -----\n"
                "   -----       -     ?    -           -----------------                                -----\n"
                "    -----      -          -    Mâles                                                  -----\n"
                "      ----     ------------   ------                    AMBIANCE                     ----\n"
                "        -----                 -  ? -       Reines         ?/10                    -----\n"
                "            -----             ------       ------                           -----\n"
                "                -----                      -  ? -                   -----\n"
                "                    --------               ------             ------\n"
                "                             --------------------------------\n");
            break;
        case 3:
            printf("Voici à quoi ressemblera la configuration maximale (7 + 5 salles):\n");
            printf(
                "                                       - Fourmilière -\n"
                "                             --------------------------------\n"
                "                    --------                                  -------\n"
                "                ----                       Graines                    ----\n"
                "            ----                   ------------------                       ----\n"
                "        ----                       - +1  -          -                          ----\n"
                "      ----       Soldats           -------     ?    -                              ----\n"
                "    -----       ---------                -          -------                          -----\n"
                "  ------        -       -                ------------- +1 -         Ouvrières         ------\n"
                " ------         -   ?   -                            ------        ------------        ------\n"
                "------    ---------------                                          -          -          ------\n"
                "------    - +1 -                          Nourriture               -     ?    -           ------\n"
                "------    ------                      -----------------            -          -           ------\n"
                "------           Pucerons             -               -            ------------------     ------\n"
                " -----         ------------           -       ?       -                        - +1 -    -----\n"
                "  -----        -          -           -               -                  ------------   -----\n"
                "   -----       -     ?    -           -----------------                  - +1 -        -----\n"
                "    -----      -          -    Mâles                                     ------       -----\n"
                "      ----     ------------   ------                    AMBIANCE                     ----\n"
                "        -----                 -  ? -       Reines         ?/10                    -----\n"
                "            -----             ------       ------                           -----\n"
                "                -----                      -  ? -                   -----\n"
                "                    --------               ------             ------\n"
                "                             --------------------------------\n");

            printf("\n");
            // saison de début
            // puis simulation aleatoire
            break;
        default:
            printf("Invalid choice.\n");
        }
    }
}

static int prochainId = 1; // Variable G pour gérer les IDs incrémentaux

void ajouterFourmi(Fourmi **tete, int role) // Fonction générique pour ajouter une fourmi à une liste
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

    for (int i = 0; i < (rand() % 61 + 150); ++i) // Ajout d'ouvrières
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }

    for (int i = 0; i < (rand() % 9 + 15); ++i) // Ajout de mâles
    {
        ajouterFourmiMale(&colo->males);
    }

    for (int i = 0; i < (rand() % 41 + 80); ++i) // Ajout de soldats
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    for (int i = 0; i < 5; ++i) // Ajout des reines
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_REINE);
    }

    colo->nombreReines = 5;
    return 0;
}

int ChosenColonie(Colonie *colo)
{

    if (!colo)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la colonie\n");
        return -1;
    }

    int nOuvrieres, nSoldats, nMales;

    printf("Choisissez le nombre de de fourmis ouvrières de départ (0-200):");
    scanf("%d", &nOuvrieres);

    printf("Choisissez le nombre de de fourmis soldats de départ (0-150):");
    scanf("%d", &nSoldats);

    printf("Choisissez le nombre de de fourmis mâles de départ (0-130):");
    scanf("%d", &nMales);

    colo->ouvrieres = NULL;
    colo->males = NULL;
    colo->soldats = NULL;

    for (int i = 0; i < nOuvrieres; ++i) // Ajout d'ouvrières
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE);
    }

    for (int i = 0; i < nSoldats; ++i) // Ajout de mâles
    {
        ajouterFourmiMale(&colo->males);
    }

    for (int i = 0; i < nMales; ++i) // Ajout de soldats
    {
        ajouterFourmi(&colo->soldats, ROLE_SOLDAT);
    }

    for (int i = 0; i < 5; ++i) // Ajout des reines
    {
        ajouterFourmi(&colo->ouvrieres, ROLE_REINE);
    }

    return 0;
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
        "             \x1b[48;2;115;71;60m------------------------------\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m                    \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d   -\x1b[48;2;139;93;78m                      \x1b[0m\x1b[48;2;115;71;60m---\n"
        " \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m                       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                                 \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                                 \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                                 \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                                 \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                              \x1b[0m\x1b[48;2;115;71;60m---\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "        \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "           \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;115;71;60m---\n"
        "             \x1b[48;2;115;71;60m------------------------------\n",
        total);
    printf("1,5 mois plus tard après l'apparution de la fourmilière...");
    printf("\n");
    sleep(2);

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
        "             \x1b[48;2;115;71;60m------------------------------\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m      \x1b[0m\x1b[48;2;115;71;60m---\n"
        " \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m-------------\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                    \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                                 \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                                 \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                              \x1b[0m\x1b[48;2;115;71;60m---\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "        \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                  \x1b[0m\x1b[48;2;115;71;60m ---\n"
        "           \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;115;71;60m---\n"
        "             \x1b[48;2;115;71;60m------------------------------\n",
        max, colo->nombreReines, totalbis);
    printf("Une nouvelle reine est apparue !\n");
    printf("3 mois plus tard après l'apparution de la fourmilière...");
    printf("\n");
    sleep(2);
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
        "             - Création de la salle 2 -\n"
        "             \x1b[48;2;115;71;60m------------------------------\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m      \x1b[0m\x1b[48;2;115;71;60m---\n"
        " \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m-------------\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m   \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                \x1b[48;2;210;160;135m-  %d   -\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                              \x1b[0m\x1b[48;2;115;71;60m---\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "        \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "           \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;115;71;60m---\n"
        "             \x1b[48;2;115;71;60m------------------------------\n",
        max, colo->nombreReines, max2, totalbis);
    printf("4,5 mois plus tard après l'apparution de la fourmilière...");
    printf("\n");
    sleep(2);

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
        "             \x1b[48;2;115;71;60m------------------------------\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m      \x1b[0m\x1b[48;2;115;71;60m---\n"
        " \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m-------------\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m   \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                 \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                             \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m    \x1b[0m\x1b[48;2;115;71;60m---\n"
        "        \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "           \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;115;71;60m---\n"
        "             \x1b[48;2;115;71;60m------------------------------\n",
        max, colo->nombreReines, max2, max, totalbis);
    printf("Une nouvelle reine est apparue !\n");
    printf("6 mois plus tard après l'apparution de la fourmilière...");
    printf("\n");
    sleep(2);

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
        "             \x1b[48;2;115;71;60m------------------------------\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m      \x1b[0m\x1b[48;2;115;71;60m---\n"
        " \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m-------------\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m   \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d   -\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "        \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "           \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;115;71;60m---\n"
        "             \x1b[48;2;115;71;60m------------------------------\n",
        max, colo->nombreReines, max2, max, totalbis, max2);
    printf("7,5 mois plus tard après l'apparution de la fourmilière...");
    printf("\n");
    sleep(2);

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
        "             \x1b[48;2;115;71;60m------------------------------\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                               \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m          \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m      \x1b[0m\x1b[48;2;115;71;60m---\n"
        " \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m-------------\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m                   \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m   \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m-  %d  -\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-------------\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m---\n"
        "\x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m              \x1b[48;2;210;160;135m-  %d   -\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m- %d -\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m---\n"
        "  \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m----------\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m---\n"
        "    \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                                      \x1b[0m\x1b[48;2;115;71;60m---\n"
        "           \x1b[48;2;115;71;60m---\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;115;71;60m---\n"
        "             \x1b[48;2;115;71;60m------------------------------\n",
        max, colo->nombreReines, max2, totalbis, max, max, max2);
    printf("Une nouvelle reine est apparue !\n");
    printf("on est 9 mois après l'apparution de la fourmilière\nEt maintenant, après 1 an d'évolution et de travail acharné...");
    printf("\n");
    sleep(3);
}

void hiver(int saisonActuel, SystemeAgricole *agriculture, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo, SystemeElevage *elevage)
{
    saisonActuel = 0;
    agriculture->quantitéDeNourriture += 10; // Simule une faible production alimentaire en hiver
    agriculture->quantitéGraines += 5;

    GestionEvenementExterne(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage);
}

void printemps(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo)
{
    saisonActuel = 1;
    agriculture->quantitéDeNourriture += 25; // Production accrue au printemps
    agriculture->quantitéGraines += 15;
    elevage->nombrePucerons += 20;

    GestionEvenementExterne(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage);
}

void ete(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo)
{
    saisonActuel = 2;
    agriculture->quantitéDeNourriture += 30; // Production stable en été
    agriculture->quantitéGraines += 20;
    elevage->nombrePucerons += 30;

    GestionEvenementExterne(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage);
}

void automne(int saisonActuel, SystemeAgricole *agriculture, SystemeElevage *elevage, EvenementExterne EvnmtExt, Pheromone phero, Colonie *colo)
{
    saisonActuel = 3;
    agriculture->quantitéDeNourriture += 15; // Production décroissante en automne
    agriculture->quantitéGraines += 10;
    elevage->nombrePucerons += 10;

    GestionEvenementExterne(saisonActuel, EvnmtExt, phero, colo, agriculture, elevage);
}

void simuleUneSaison(Colonie *colo, SystemeAgricole *agriculture, SystemeElevage *elevage, int nbSaison, int saisonActuel, EvenementExterne EvnmtExt, Pheromone phero)
{
    // if (simuleUneSaison == 0)
    {
        for (int i = 0; i < nbSaison; ++i)
        {
            switch (i % 4)
            { // Répartition des saisons : 0 = HIVER, 1 = PRINTEMPS, 2 = ETE, 3 = AUTOMNE

            case 0: // HIVER
                hiver(saisonActuel, agriculture, EvnmtExt, phero, colo, elevage);
                printf("                                   --- Fin de l'HIVER ---                       \n");
                break;

            case 1: // PRINTEMPS
                printemps(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
                printf("                                   --- Fin du PRINTEMPS ---                       \n");
                break;

            case 2: // ETE
                ete(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
                printf("                                   --- Fin de l'ÉTÉ ---                        \n");
                break;

            case 3: // AUTOMNE
                automne(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
                printf("                                   --- Fin de l'AUTOMNE ---                       \n");
                break;

            default:
                break;
            }
        }
        // else
        {
            int choice;
            printf("Choisissez une saison de départ :\n0.Hiver\n1.Printemps\n2.Ete\n3.Automne");
            switch (choice)
            { // Répartition des saisons : 0 = HIVER, 1 = PRINTEMPS, 2 = ETE, 3 = AUTOMNE

            case 0: // HIVER
                hiver(saisonActuel, agriculture, EvnmtExt, phero, colo, elevage);
                printf("                                   --- Fin de l'HIVER ---                       \n");
                break;

            case 1: // PRINTEMPS
                printemps(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
                printf("                                   --- Fin du PRINTEMPS ---                       \n");
                break;

            case 2: // ETE
                ete(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
                printf("                                   --- Fin de l'ÉTÉ ---                        \n");
                break;

            case 3: // AUTOMNE
                automne(saisonActuel, agriculture, elevage, EvnmtExt, phero, colo);
                printf("                                   --- Fin de l'AUTOMNE ---                       \n");
                break;

            default:
                break;
            }
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
            printf("Tout va bien dans la fourmilière cet hiver,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis\n!");
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
            if (EvnmtExt.type == 1)
            {
                printf("La fourmilière subit une tempête d'impact %d,\n"
                       "c'est un hiver compliqué pour la fourmilière..\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 25%%\n");
            }
            else
            {
                printf("La fourmilière subit une inondation d'impact %d,\n"
                       "c'est un hiver compliqué pour la fourmilière..\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 12,5%%\n");
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
            printf("La fourmilière subit une invasion d'impact %d,\n"
                   "c'est un hiver TRES compliqué pour la fourmilière..\n",
                   EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en hiver est de 25%%\n");
        }
        if (EvnmtExt.type == 4) // HIVER GLACIAL
        {
            EvnmtExt.impact = 1 + (rand() % 3); // valeur aleatoire entre 1,2 et 3 pour determiner l'impact de l'even ext
            if (EvnmtExt.impact == 1)
            {
                phero.reine = phero.male = 0;
                phero.alarme = EvnmtExt.impact + (rand() % 2);
            }
            else if (EvnmtExt.impact == 2)
            {
                phero.reine = phero.male = 0;
                phero.alarme = EvnmtExt.impact + (rand() % 2);
            }
            else if (EvnmtExt.impact == 3)
            {
                phero.reine = phero.male = 0;
                phero.alarme = EvnmtExt.impact + (rand() % 2);
            }
            if (EvnmtExt.impact == 1 || EvnmtExt.impact == 2)
            {
                printf("La fourmilière subit un hiver glacial d'impact %d,\n"
                       "c'est un hiver est EXTREMEMENT compliqué pour la fourmilière..\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 12,5%%\n");
            }
            else // cad si EvnmtExt.impact == 3
            {
                printf("La fourmilière subit un hiver glacial d'impact %d,\n"
                       "c'est un hiver est FATAL pour la fourmilière.\nL'aventure s'arrête ici...\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 12,5%%\n");
                exit(0);
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
            printf("Tout va bien dans la fourmilière ce printemps,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis !\n");
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
            if (EvnmtExt.impact == 1)
            {
                printf("La fourmilière subit une tempête d'impact %d,\n"
                       "nous pensons qu'elle s'en sortira, on est au printemps quand même !\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 12,5%%\n");
            }
            else // ( EvnmtExt.type == 2)
            {
                printf("La fourmilière subit une inondation d'impact %d,\n"
                       "nous pensons qu'elle s'en sortira, on est au printemps quand même !\n",
                       EvnmtExt.impact);
                printf("La probabilité que cet événement survienne en hiver est de 25%%\n");
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
            printf("La fourmilière subit une invasion d'impact %d,\n"
                   "c'est un printemps compliqué !\n",
                   EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en hiver est de 50%%\n");
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
            printf("Tout va bien dans la fourmilière cet été,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis !\n");
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
            printf("La fourmilière subit une tempête d'impact %d,\n"
                   "elle s'en sortira !\n",
                   EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en été est de 37,5%%\n");
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
            printf("La fourmilière subit une invasion d'impact %d.\n", EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en été est de 50%%\n");
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
            printf("Tout va bien dans la fourmilière cet automne,\naucun evenement exterieur n'a impacté la tranquilité de nos fourmis !\n");
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
            printf("La fourmilière subit une tempête d'impact %d,\n"
                   "un peu cocasse mais habituel, ça devrait aller pour un automne !\n",
                   EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en hiver est de 50%%\n");
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
            printf("La fourmilière subit une inondation d'impact %d\n", EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en hiver est de 12,5%%\n");
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
            printf("La fourmilière subit une invasion d'impact %d,\n"
                   "un peu cocasse mais gérable!",
                   EvnmtExt.impact);
            printf("La probabilité que cet événement survienne en hiver est de 37,5%%\n");
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
        phero.ambiance = 1 + (rand() % 4); // ambiance hivernal (1 à 4)

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
            phero.ambiance = 5 + (rand() % 4); // ambiance automne ou printemps (5 à 8)

            if (phero.ambiance == 5 || phero.ambiance == 6)
            {
                for (int j = 0; j < rand() % 6 + 15; ++j) // Ajouter de nouvelles ouvrières si le ambiance est favorable (printemps/automne)
                {
                    ajouterFourmi(&colo->ouvrieres, ROLE_OUVRIERE); // Augmentation des ouvrières
                    ajouterFourmi(&colo->soldats, ROLE_SOLDAT);     // Augmentation des soldats
                }

                for (int j = 0; j < rand() % 6 + 10; ++j)
                {
                    supprimerFourmiMale(&colo->males); // Réduit les mâles
                }
            }
            else if (phero.ambiance == 7 || phero.ambiance == 8)
            {
                for (int j = 0; j < rand() % 11 + 30; ++j) // Ajouter encore plus d'ouvrières si le ambiance est plus favorable (printemps/automne)
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
    colo->nombreReines = 4;
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

    int GrainesReste = 0;
    int GrainesReste2 = 0;
    agriculture->quantitéGraines = 136;
    if (agriculture->quantitéGraines > 30)
    {
        GrainesReste = abs(30 - agriculture->quantitéGraines);
        agriculture->quantitéGraines = 30;
    }
    if (GrainesReste > 100)
    {
        GrainesReste2 = abs(100 - GrainesReste);
        GrainesReste = 100;
    }

    int SoldatsReste = 0;
    if (totalSoldats > 100)
    {
        SoldatsReste = abs(100 - totalSoldats);
        totalSoldats = 100;
    }
    else
    {
        SoldatsReste = 0;
    }

    int OuvrieresReste = 0;
    if (totalOuvrieres > 200)
    {
        OuvrieresReste = abs(200 - totalOuvrieres);
        totalOuvrieres = 200;
    }
    else
    {
        OuvrieresReste = 0;
    }

    int OuvrieresReste2 = 0;
    if (OuvrieresReste > 30)
    {
        OuvrieresReste2 = abs(30 - OuvrieresReste);
        OuvrieresReste = 30;
    }

    printf(
        "                                       - Fourmilière -\n"
        "                             \x1b[48;2;115;71;60m--------------------------------\n"
        "                    \x1b[48;2;115;71;60m--------\x1b[48;2;139;93;78m                                 \x1b[0m\x1b[48;2;115;71;60m-------\n"
        "                \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m                       Graines                   \x1b[0m\x1b[48;2;115;71;60m----\n"
        "            \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m                   \x1b[48;2;210;160;135m------------------\x1b[48;2;139;93;78m                       \x1b[0m\x1b[48;2;115;71;60m----\n"
        "        \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m-  %d -          -\x1b[48;2;139;93;78m                          \x1b[0m\x1b[48;2;115;71;60m----\n"
        "      \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m       Soldats           \x1b[48;2;210;160;135m-------    %d    -\x1b[48;2;139;93;78m                             \x1b[0m\x1b[48;2;115;71;60m----\n"
        "    \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m---------\x1b[48;2;139;93;78m                \x1b[0m\x1b[48;2;210;160;135m-          -------\x1b[48;2;139;93;78m                         \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "  \x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m-       -\x1b[48;2;139;93;78m                \x1b[0m\x1b[48;2;210;160;135m------------  %d -\x1b[48;2;139;93;78m         Ouvrières         \x1b\x1b[0m\x1b[48;2;115;71;60m------\n"
        " \x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m         \x1b[48;2;210;160;135m-   %d  -\x1b[48;2;139;93;78m                            \x1b[0m\x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m        \x1b\x1b[0m\x1b[48;2;115;71;60m------\n"
        "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m    \x1b[48;2;210;160;135m---------------\x1b[48;2;139;93;78m                                          \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m          \x1b[0m\x1b[48;2;115;71;60m------\n"
        "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m    \x1b[48;2;210;160;135m- %d  -\x1b[48;2;139;93;78m                          Nourriture               \x1b[48;2;210;160;135m-    %d    -\x1b[48;2;139;93;78m          \x1b[0m\x1b[48;2;115;71;60m------\n"
        "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m    \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                      \x1b\x1b[48;2;210;160;135m-----------------\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m          \x1b[0m\x1b[48;2;115;71;60m------\n"
        "\x1b[48;2;115;71;60m------\x1b[48;2;139;93;78m           Pucerons             \x1b[48;2;210;160;135m-               -\x1b[48;2;139;93;78m            \x1b[48;2;210;160;135m-----------------\x1b[48;2;139;93;78m     \x1b[0m\x1b[48;2;115;71;60m------\n"
        " \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m         \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-      %d      -\x1b[48;2;139;93;78m                       \x1b[48;2;210;160;135m- %d  -\x1b[48;2;139;93;78m    \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "  \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m        \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-               -\x1b[48;2;139;93;78m                  \x1b[48;2;210;160;135m-----------\x1b[48;2;139;93;78m    \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "   \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m       \x1b[48;2;210;160;135m-    %d    -\x1b[48;2;139;93;78m           \x1b[48;2;210;160;135m-----------------\x1b[48;2;139;93;78m                  \x1b[48;2;210;160;135m- %d  -\x1b[48;2;139;93;78m        \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "    \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m      \x1b[48;2;210;160;135m-          -\x1b[48;2;139;93;78m    Mâles                                     \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "      \x1b[48;2;115;71;60m----\x1b[48;2;139;93;78m     \x1b[48;2;210;160;135m------------\x1b[48;2;139;93;78m\x1b[48;2;139;93;78m   \x1b\x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                    AMBIANCE                     \x1b\x1b[0m\x1b[48;2;115;71;60m----\n"
        "        \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                 \x1b[48;2;210;160;135m- %d  -\x1b[48;2;139;93;78m       Reines         %d/10                 \x1b[0m\x1b[48;2;115;71;60m-----\n"
        "            \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m             \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m       \x1b\x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m                           \x1b\x1b[0m\x1b[48;2;115;71;60m-----\n"
        "                \x1b[48;2;115;71;60m-----\x1b[48;2;139;93;78m                      \x1b[48;2;210;160;135m-  %d -\x1b[48;2;139;93;78m                   \x1b\x1b[0m\x1b[48;2;115;71;60m-----\n"
        "                    \x1b[48;2;115;71;60m--------\x1b[48;2;139;93;78m               \x1b[48;2;210;160;135m------\x1b[48;2;139;93;78m             \x1b\x1b[0m\x1b[48;2;115;71;60m------\n"
        "                             \x1b[48;2;115;71;60m--------------------------------\n",
        agriculture->quantitéGraines, GrainesReste, GrainesReste2, totalSoldats, SoldatsReste, totalOuvrieres, agriculture->quantitéDeNourriture, OuvrieresReste, elevage->nombrePucerons, OuvrieresReste2, totalMales, phero.ambiance, colo->nombreReines);
    printf("\n");
    sleep(2);
}
