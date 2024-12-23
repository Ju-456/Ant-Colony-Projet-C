// Fonction pour calculer les pertes en soldats et les appliquer directement
void calculer_pertes_Securite_Protection(Sécurité *securite, Colonie *colo)
{
    float pertes = 0.0;

    // Vérification des niveaux de sécurité et de protection
    if (securite->niveauProtection < 1 || securite->niveauProtection > 3)
    {
        printf("Erreur: niveau de protection invalide.\n");
        return; // Sortir de la fonction pour les cas invalides
    }

    // Calcul des pertes en fonction des niveaux de sécurité et de protection
    if (securite->niveauProtection == 1)
    {
        if (securite->niveauProtection == 1)
        {
            pertes = 15.0; // Sécurité faible, protection faible
        }
        else if (securite->niveauProtection == 2)
        {
            pertes = 8.0; // Sécurité faible, protection moyenne
        }
        else if (securite->niveauProtection == 3)
        {
            pertes = 10.0; // Sécurité faible, protection élevée
        }
    }
    else if (securite->niveauProtection == 2)
    {
        if (securite->niveauProtection == 1)
        {
            pertes = 5.0; // Sécurité moyenne, protection faible
        }
        else if (securite->niveauProtection == 2)
        {
            pertes = 0.0; // Sécurité moyenne, protection moyenne
        }
        else if (securite->niveauProtection == 3)
        {
            pertes = 5.0; // Sécurité moyenne, protection élevée
        }
    }
    else if (securite->niveauProtection == 3)
    {
        if (securite->niveauProtection == 1)
        {
            pertes = 15.0; // Sécurité élevée, protection faible
        }
        else if (securite->niveauProtection == 2)
        {
            pertes = 5.0; // Sécurité élevée, protection moyenne
        }
        else if (securite->niveauProtection == 3)
        {
            pertes = 0.0; // Sécurité élevée, protection élevée
        }
    }

    // Appliquer les pertes aux soldats de la colonie
    int nombreSoldats = compterFourmis(colo->soldats);
    int pertesSoldats = (int)(nombreSoldats * (pertes / 100));

    // Supprimer les soldats en fonction des pertes calculées
    for (int i = 0; i < pertesSoldats; i++)
    {
        supprimerFourmi(&colo->soldats, colo->soldats); // Suppression de la première fourmi soldat
    }

    printf("Pourcentage de pertes en soldats: %.2f%%\n", pertes);
}


// Fonction pour calculer les pertes en ouvrières et les appliquer directement
void calculer_pertes_Hygiene_Maladie(Hygiène *hygiene, Colonie *colo)
{
    float pertes = 0.0;

    // Vérification des niveaux d'hygiène et de maladie
    if (hygiene->niveauHygiene < 1 || hygiene->niveauHygiene > 3 || hygiene->niveauMaladie < 1 || hygiene->niveauMaladie > 3)
    {
        printf("Erreur : niveaux d'hygiène ou de maladie invalides.\n");
        return; // Sortie en cas d'erreur
    }

    // Calcul des pertes en fonction des niveaux d'hygiène et de maladie
    if (hygiene->niveauHygiene == 1)
    {
        if (hygiene->niveauMaladie == 1)
        {
            pertes = 10.0; // Hygiène faible, maladie faible
        }
        else if (hygiene->niveauMaladie == 2)
        {
            pertes = 8.0; // Hygiène faible, maladie moyenne
        }
        else if (hygiene->niveauMaladie == 3)
        {
            pertes = 15.0; // Hygiène faible, maladie élevée
        }
    }
    else if (hygiene->niveauHygiene == 2)
    {
        if (hygiene->niveauMaladie == 1)
        {
            pertes = 5.0; // Hygiène moyenne, maladie faible
        }
        else if (hygiene->niveauMaladie == 2)
        {
            pertes = 0.0; // Hygiène moyenne, maladie moyenne
        }
        else if (hygiene->niveauMaladie == 3)
        {
            pertes = 3.0; // Hygiène moyenne, maladie élevée
        }
    }
    else if (hygiene->niveauHygiene == 3)
    {
        if (hygiene->niveauMaladie == 1)
        {
            pertes = 0.0; // Hygiène élevée, maladie faible
        }
        else if (hygiene->niveauMaladie == 2)
        {
            pertes = 5.0; // Hygiène élevée, maladie moyenne
        }
        else if (hygiene->niveauMaladie == 3)
        {
            pertes = 15.0; // Hygiène élevée, maladie élevée
        }
    }

    // Calculer et appliquer les pertes aux ouvrières de la colonie
    int nombreOuvrieres = compterFourmis(colo->ouvrieres);
    int pertesOuvrieres = (int)(nombreOuvrieres * (pertes / 100));

    // Supprimer les ouvrières en fonction des pertes calculées
    for (int i = 0; i < pertesOuvrieres; i++)
    {
        supprimerFourmi(&colo->ouvrieres, colo->ouvrieres); // Suppression de la première ouvrière
    }

    printf("Pourcentage de pertes en ouvrières : %.2f%%\n", pertes);
}
