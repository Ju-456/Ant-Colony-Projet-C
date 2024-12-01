#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

typedef enum {
  reine,
  ouvrieres,
  male,
  butineuses
}
TypeAbeille;

// Déclaration de la structure Abeille
typedef struct Abeille {
  int age;
  TypeAbeille type;
  enum ActiviteAbeille {
    repos,
    butinage,
    accouplement,
    gardien,
    morte
  }
  activite;
  int capaciteTransport;
  struct Abeille * suivante;
}
Abeille;

// Déclaration de la structure Alimentation avant son utilisation
typedef struct {
  int miel;
  int nectar;
}
Alimentation;

// Déclaration de la structure Ruche
typedef struct {
  Abeille * listeAbeilles;
  int totalAbeilles;
  int oeufs;
  Alimentation alimentation;
}
Ruche;

// Déclaration de l'énumération Saison
typedef enum {
  ETE,
  AUTOMNE,
  PRINTEMPS,
  HIVER
}
Saison;

// Déclaration de la structure GestionSaisons
typedef struct {
  int nectarIncrease; // Augmentation du nectar pour chaque saison
  int ouvrieresIncrease; // Augmentation des ouvrieres pour chaque saison
  int butineusesIncrease; // Augmentation des butineuses pour chaque saison
  int malesIncrease; // Augmentation des males pour chaque saison
  Saison saisonActuelle;
}
GestionSaisons;

void genererMonde(Ruche * ruche) {
  // Initialisation de la reine
  ruche -> listeAbeilles = malloc(sizeof(Abeille));
  ruche -> listeAbeilles -> type = reine;
  ruche -> listeAbeilles -> age = 0;
  ruche -> listeAbeilles -> activite = repos;
  ruche -> listeAbeilles -> capaciteTransport = 0;
  ruche -> listeAbeilles -> suivante = NULL;
  ruche -> totalAbeilles = 1; // Une seule reine pour commencer

  // Génération aléatoire du nombre d'ouvrières, de mâles et de butineuses
  int nbOuvrieres = rand() % 101 + 100; // Entre 100 et 200 ouvrières
  int nbMales = rand() % 101 + 100; // Entre 100 et 200 mâles
  int nbButineuses = rand() % 101 + 100; // Entre 100 et 200 butineuses

  // Vérification et ajustement si les nombres deviennent négatifs
  if (nbOuvrieres < 0) {
    nbOuvrieres = 0; // Si négatif, fixer à zéro ou une autre valeur appropriée
  }
  if (nbMales < 0) {
    nbMales = 0; // Si négatif, fixer à zéro ou une autre valeur appropriée
  }
  if (nbButineuses < 0) {
    nbButineuses = 0; // Si négatif, fixer à zéro ou une autre valeur appropriée
  }

  // Ajout des abeilles générées aléatoirement
  for (int i = 0; i < nbOuvrieres; ++i) {
    // Création d'une nouvelle abeille ouvrière
    Abeille * nouvelleAbeille = malloc(sizeof(Abeille));
    nouvelleAbeille -> type = ouvrieres;
    nouvelleAbeille -> age = 0;
    nouvelleAbeille -> activite = repos;
    nouvelleAbeille -> capaciteTransport = 0;
    nouvelleAbeille -> suivante = ruche -> listeAbeilles; // Ajout au début de la liste
    ruche -> listeAbeilles = nouvelleAbeille; // Mise à jour de la liste des abeilles
    ruche -> totalAbeilles++; // Incrémentation du nombre total d'abeilles dans la ruche
  }

  for (int i = 0; i < nbMales; ++i) {
    // Création d'un nouveau mâle
    Abeille * nouvelleAbeille = malloc(sizeof(Abeille));
    nouvelleAbeille -> type = male;
    nouvelleAbeille -> age = 0;
    nouvelleAbeille -> activite = repos;
    nouvelleAbeille -> capaciteTransport = 0;
    nouvelleAbeille -> suivante = ruche -> listeAbeilles; // Ajout au début de la liste
    ruche -> listeAbeilles = nouvelleAbeille; // Mise à jour de la liste des abeilles
    ruche -> totalAbeilles++; // Incrémentation du nombre total d'abeilles dans la ruche
  }

  for (int i = 0; i < nbButineuses; ++i) {
    // Création d'une nouvelle abeille butineuse
    Abeille * nouvelleAbeille = malloc(sizeof(Abeille));
    nouvelleAbeille -> type = butineuses;
    nouvelleAbeille -> age = 0;
    nouvelleAbeille -> activite = repos;
    nouvelleAbeille -> capaciteTransport = 0;
    nouvelleAbeille -> suivante = ruche -> listeAbeilles; // Ajout au début de la liste
    ruche -> listeAbeilles = nouvelleAbeille; // Mise à jour de la liste des abeilles
    ruche -> totalAbeilles++; // Incrémentation du nombre total d'abeilles dans la ruche
  }

  // Génération aléatoire du miel et du nectar
  ruche -> alimentation.nectar = rand() % 401 + 400; // Entre 400 et 800 pour le nectar
  ruche -> alimentation.miel = rand() % 201 + 200; // Entre 200 et 400 pour le miel
}

void libererAbeilles(Abeille * abeille) {
  if (abeille == NULL) {
    return;
  }
  libererAbeilles(abeille -> suivante);
  free(abeille);
}

void cycleDeVieAbeilles(Ruche * ruche) {
  Abeille * precedente = NULL;
  Abeille * courante = ruche -> listeAbeilles;

  while (courante != NULL) {
    courante -> age++; // Vieillissement de l'abeille

    // Vérification de l'âge et suppression si nécessaire
    if ((courante -> type == butineuses || courante -> type == ouvrieres || courante -> type == male) && courante -> age >= 2) {
      if (precedente == NULL) {
        ruche -> listeAbeilles = courante -> suivante;
      } else {
        precedente -> suivante = courante -> suivante;
      }
      free(courante);
      courante = (precedente == NULL) ? ruche -> listeAbeilles : precedente -> suivante;
      ruche -> totalAbeilles--;
    } else {
      precedente = courante;
      courante = courante -> suivante;
    }
  }
}

/// Evan va mettre ramdom_ruche

void ponte(Ruche * ruche) {
  int consommationMiel = 100 / 3; // 3 miels = 1 œuf

  // Consommation du miel pour la ponte, jusqu'à épuisement du miel disponible
  int oeufsPondus = (ruche -> alimentation.miel >= consommationMiel) ? 100 : (ruche -> alimentation.miel * 3);
  ruche -> alimentation.miel -= oeufsPondus / 3;

  // Pondre les œufs avec la quantité de miel disponible
  ruche -> oeufs += oeufsPondus;

  // Éclosion des œufs le mois suivant
  // Chaque œuf donne naissance aléatoirement à une ouvrière, une butineuse et un mâle
  for (int i = 0; i < ruche -> oeufs; ++i) {
    // Simulation de naissance aléatoire (exemple : 33% chance pour chaque type)
    int naissance = rand() % 3; // Génération aléatoire de 0 à 2

    // Création d'une nouvelle abeille
    Abeille * nouvelleAbeille = malloc(sizeof(Abeille));
    nouvelleAbeille -> age = 0; // Âge initial à la naissance
    nouvelleAbeille -> suivante = ruche -> listeAbeilles; // Ajout au début de la liste

    // Assignation du type en fonction du résultat aléatoire
    switch (naissance) {
    case 0:
      nouvelleAbeille -> type = ouvrieres;
      break;
    case 1:
      nouvelleAbeille -> type = butineuses;
      break;
    case 2:
      nouvelleAbeille -> type = male;
      break;
    default:
      // En cas d'anomalie, attribuer un type par défaut (par exemple, ouvrière)
      nouvelleAbeille -> type = ouvrieres;
      break;
    }

    // Ajout de la nouvelle abeille à la liste des abeilles de la ruche
    ruche -> listeAbeilles = nouvelleAbeille;
    ruche -> totalAbeilles++;
  }

  // Les œufs ont éclos, réinitialisation du compteur d'œufs
  ruche -> oeufs = 0;
}

void productionNectar(Ruche * ruche) {
  // Production de nectar par chaque ouvrière
  Abeille * courante = ruche -> listeAbeilles;

  while (courante != NULL) {
    if (courante -> type == ouvrieres) {
      // Chaque ouvrière produit / 2 nectar
      ruche -> alimentation.nectar += 2;
    }
    courante = courante -> suivante;
  }

  // Transformation du nectar en miel par les butineuses
  while (ruche -> alimentation.nectar >= 4) {
    ruche -> alimentation.nectar -= 4; // Consommation de 4 nectar
    ruche -> alimentation.miel++; // Production de 1 miel
  }
}

void simulationSaisons(GestionSaisons * saison, Alimentation * alimentation, int mois, Ruche * ruche) {
  for (int i = 0; i < mois; ++i) {
    switch (saison -> saisonActuelle) {
    case HIVER:
      alimentation -> nectar += saison -> nectarIncrease * 1.25;

      // Nombre d'ouvrieres ou butineuses a générer pendant l'HIVER
      int nbOuvrieresButineusesHiver = rand() % 21 + 40; // environ 20-40% de la population maximale annuelle
      for (int i = 0; i < nbOuvrieresButineusesHiver; ++i) { // Création d'une nouvelle abeille ouvriere
        Abeille * nouvelleAbeille = malloc(sizeof(Abeille));
        nouvelleAbeille -> age = 0;
        nouvelleAbeille -> capaciteTransport = 0;
        nouvelleAbeille -> suivante = ruche -> listeAbeilles; // Ajout au début de la liste

        // Utilisation de srand pour déterminer aléatoirement le type d'abeille
        int typeAleatoire = rand() % 2; // Génere 0 ou 1
        if (typeAleatoire == 0) {
          nouvelleAbeille -> type = ouvrieres;
        } else {
          nouvelleAbeille -> type = butineuses;
        }

        // Utilisation de srand pour déterminer aléatoirement l'activité de l'abeille
        int activiteAleatoire = rand() % 5; // Génere un nombre entre 0 et 4
        nouvelleAbeille -> activite = activiteAleatoire;

        // Ajout de la nouvelle abeille a la liste des abeilles de la ruche
        ruche -> listeAbeilles = nouvelleAbeille;
        ruche -> totalAbeilles++;
      }
      break;

    case PRINTEMPS:
      alimentation -> nectar += saison -> nectarIncrease * 2.5; // Augmentation plus élevée en début de printemps

      // Nombre d'ouvrieres ou butineuses a générer pendant PRINTEMPS
      int nbOuvrieresButineusesPrint = rand() % 101 + 150; // environ 40-60% de la population maximale annuelle.
      for (int i = 0; i < nbOuvrieresButineusesPrint; ++i) { // Création d'une nouvelle abeille ouvriere
        Abeille * nouvelleAbeille = malloc(sizeof(Abeille));
        nouvelleAbeille -> age = 0;
        nouvelleAbeille -> capaciteTransport = 0;
        nouvelleAbeille -> suivante = ruche -> listeAbeilles; // Ajout au début de la liste

        // Utilisation de srand pour déterminer aléatoirement le type d'abeille
        int typeAleatoire = rand() % 2; // Génere 0 ou 1
        if (typeAleatoire == 0) {
          nouvelleAbeille -> type = ouvrieres;
        } else {
          nouvelleAbeille -> type = butineuses;
        }

        // Utilisation de srand pour déterminer aléatoirement l'activité de l'abeille
        int activiteAleatoire = rand() % 5; // Génere un nombre entre 0 et 4
        nouvelleAbeille -> activite = activiteAleatoire;

        // Ajout de la nouvelle abeille a la liste des abeilles de la ruche
        ruche -> listeAbeilles = nouvelleAbeille;
        ruche -> totalAbeilles++;
      }
      break;

    case ETE:
      alimentation -> nectar += saison -> nectarIncrease * 2; // Augmentation plus élevée en été
      // Nombre d'ouvrieres ou butineuses a générer pendant ETE

      int nbOuvrieresButineusesEte = rand() % 201 + 250; //environ 60-80% de la population maximale annuelle.
      for (int i = 0; i < nbOuvrieresButineusesEte; ++i) { // Création d'une nouvelle abeille ouvriere
        Abeille * nouvelleAbeille = malloc(sizeof(Abeille));
        nouvelleAbeille -> age = 0;
        nouvelleAbeille -> capaciteTransport = 0;
        nouvelleAbeille -> suivante = ruche -> listeAbeilles; // Ajout au début de la liste

        // Utilisation de srand pour déterminer aléatoirement le type d'abeille
        int typeAleatoire = rand() % 2; // Génere 0 ou 1
        if (typeAleatoire == 0) {
          nouvelleAbeille -> type = ouvrieres;
        } else {
          nouvelleAbeille -> type = butineuses;
        }

        // Utilisation de srand pour déterminer aléatoirement l'activité de l'abeille
        int activiteAleatoire = rand() % 5; // Génere un nombre entre 0 et 4
        nouvelleAbeille -> activite = activiteAleatoire;

        // Ajout de la nouvelle abeille a la liste des abeilles de la ruche
        ruche -> listeAbeilles = nouvelleAbeille;
        ruche -> totalAbeilles++;
      }
      break;

    case AUTOMNE:
      alimentation -> nectar += saison -> nectarIncrease * 1.5; // Augmentation plus élevée en automne

      // Nombre d'ouvrieres ou butineuses a générer pendant AUTOMNE

      int nbOuvrieresButineusesAut = rand() % 51 + 71; //environ 30-50% de la population maximale annuelle.
      for (int i = 0; i < nbOuvrieresButineusesAut; ++i) { // Création d'une nouvelle abeille ouvriere
        Abeille * nouvelleAbeille = malloc(sizeof(Abeille));
        nouvelleAbeille -> age = 0;
        nouvelleAbeille -> capaciteTransport = 0;
        nouvelleAbeille -> suivante = ruche -> listeAbeilles; // Ajout au début de la liste

        // Utilisation de srand pour déterminer aléatoirement le type d'abeille
        int typeAleatoire = rand() % 2; // Génere 0 ou 1
        if (typeAleatoire == 0) {
          nouvelleAbeille -> type = ouvrieres;
        } else {
          nouvelleAbeille -> type = butineuses;
        }

        // Utilisation de srand pour déterminer aléatoirement l'activité de l'abeille
        int activiteAleatoire = rand() % 5; // Génere un nombre entre 0 et 4
        nouvelleAbeille -> activite = activiteAleatoire;

        // Ajout de la nouvelle abeille a la liste des abeilles de la ruche
        ruche -> listeAbeilles = nouvelleAbeille;
        ruche -> totalAbeilles++;
      }
      break;
      break;
      default:
      break;
    }
  }
}

void affichageInformations(int mois, GestionSaisons * saison, Ruche * ruche, int mielPrecedent, int abeillesPrecedentes) {
  printf("----------------------- État de la ruche ---------------------------\n");

  printf("Mois :                       O %d O\n", mois);
  printf("Saison : ");
  switch (saison -> saisonActuelle) {
  case ETE:
    printf("                 o O Été O o\n");
    break;
  case AUTOMNE:
    printf("                 O Automne O\n");
    break;
  case HIVER:
    printf("                o O Hiver O o\n");
    break;
  case PRINTEMPS:
    printf("                 O Printemps O\n");
    break;
  default:
    printf("                 O Inconnue O\n");
    break;
  }
  printf("Nb d'abeilles total :   O o O %d O o O\n", ruche -> totalAbeilles);
  // Comptage du nombre de chaque type d'abeille
  int nbButineuses = 0, nbOuvrieres = 0, nbMales = 0;
  Abeille * courante = ruche -> listeAbeilles;
  while (courante != NULL) {
    switch (courante -> type) {
    case butineuses:
      nbButineuses++;
      break;
    case ouvrieres:
      nbOuvrieres++;
      break;
    case male:
      nbMales++;
      break;
    default:
      break;
    }
    courante = courante -> suivante;
  }
  printf("Nb de butineuses :    O O o O %d O o O O\n", nbButineuses);
  printf("Nb ouvrières :        O o O O %d O O o O\n", nbOuvrieres);
  printf("Nb de mâles :           O o O %d O o O\n", nbMales);
  printf("Reine :                  o O OuneO O o\n");
  printf("Nb de miels disponibles :   O %d O\n", ruche -> alimentation.miel);
  // Bilan par rapport au mois précédent
  printf("Bilan miel par rapport au mois précédent : %s\n", (ruche -> alimentation.miel > mielPrecedent) ? "Augmentation" : ((ruche -> alimentation.miel < mielPrecedent) ? "Diminution" : "Stable"));
  printf("Bilan nombre d'abeilles par rapport au mois précédent : %s\n", (ruche -> totalAbeilles > abeillesPrecedentes) ? "Augmentation" : ((ruche -> totalAbeilles < abeillesPrecedentes) ? "Diminution" : "Stable"));
  printf("--------------------------------------------------------------------\n");
}

int main() {
  srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

  Ruche maRuche;
  maRuche.listeAbeilles = NULL; // Initialisation de la liste d'abeilles à NULL
  maRuche.totalAbeilles = 0;
  maRuche.alimentation.nectar = 0;
  maRuche.alimentation.miel = 0;
  maRuche.oeufs = 0;

  GestionSaisons saison;
  saison.saisonActuelle = ETE; // Commencer en été
  saison.nectarIncrease = 10; // Exemple de valeur d'augmentation de nectar pour chaque saison

  int mielPrecedent = 0, abeillesPrecedentes = 0;

  for (int mois = 1; mois <= 48; ++mois) {
    genererMonde( & maRuche);
    cycleDeVieAbeilles( & maRuche);
    ponte( & maRuche);
    productionNectar( & maRuche);
    simulationSaisons( & saison, & maRuche.alimentation, 1, & maRuche);

    if (mois % 3 == 0) {
      // Changer toutes les 3 unités de temps
      if (saison.saisonActuelle == ETE) {
        saison.saisonActuelle = AUTOMNE;
      } else if (saison.saisonActuelle == AUTOMNE) {
        saison.saisonActuelle = HIVER;
      } else if (saison.saisonActuelle == HIVER) {
        saison.saisonActuelle = PRINTEMPS;
      } else {
        saison.saisonActuelle = ETE;
      }
    }

    if (mois % 1 == 0) {
      // Afficher les informations tous les 4 mois
      affichageInformations(mois, & saison, & maRuche, mielPrecedent, abeillesPrecedentes);
    }

    if (mois % 1 == 0) {
      // Réinitialiser les compteurs à la fin des 4 ans
      mielPrecedent = maRuche.alimentation.miel;
      abeillesPrecedentes = maRuche.totalAbeilles;
    }

    // Attendre 10 secondes avant de passer au mois suivant
    sleep(5);
  }

  // Libérer la mémoire à la fin de la simulation
  libererAbeilles(maRuche.listeAbeilles);

  return 0;
}