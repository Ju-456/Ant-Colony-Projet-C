#include <stdio.h>

// Définitions des couleurs
#define BG_DARK_BROWN "\033[48;5;52m"  // Fond marron foncé
#define FG_BEIGE "\033[38;5;230m"     // Texte beige
#define RESET "\033[0m"               // Réinitialisation des couleurs

int main() {
    int max = 5, max2 = 3, totalbis = 2;
    struct {
        int nombreReines;
    } colo = {4};

    printf(
        BG_DARK_BROWN FG_BEIGE  // Appliquer fond marron foncé et texte beige
        "             - Création de la salle 3 bis -             \n"
        "             ------------------------------             \n"
        "        -----                               ----        \n"
        "      ---                                     ---       \n"
        "    ---            ---------          ------     ---   \n"
        "  ---              - " FG_BEIGE "%d" BG_DARK_BROWN " -           - " FG_BEIGE "%d" BG_DARK_BROWN " -      --- \n"
        " ---               -------------      ------       --- \n"
        "---                       - " FG_BEIGE "%d" BG_DARK_BROWN " -                   --- \n"
        "---           ------      ------   ---------        --- \n"
        "---           - " FG_BEIGE "%d" BG_DARK_BROWN " -               -  " FG_BEIGE "%d" BG_DARK_BROWN "  -        --- \n"
        "---           --------------       ---------        --- \n"
        "  ---              -  " FG_BEIGE "%d" BG_DARK_BROWN "  -          -  " FG_BEIGE "%d" BG_DARK_BROWN " -       --- \n"
        "      ---          ---------          ------    ---     \n"
        "        ---                                   ---        \n"
        "           ---                            ---           \n"
        "             ------------------------------             \n"
        RESET,  // Réinitialiser les couleurs
        max, colo.nombreReines, max2, totalbis, max, max, max2);

    return 0;
}
