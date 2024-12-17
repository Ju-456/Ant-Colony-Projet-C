#include <stdio.h>
#include <stdlib.h> 

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char *buffer = (char *)malloc(4096 * sizeof(char));
    int max = 10, nombreReines = 5, totalbis = 7;

    if (buffer == NULL) {
        perror("Erreur d'allocation mémoire");
        return 1;
    }

    // Ouvrir le fichier contenant les séquences ANSI
    file = fopen("deco.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        free(buffer);
        return 1;
    }

    // Lire le contenu du fichier dans buffer
    size_t bytesRead = fread(buffer, sizeof(char), 4095, file);
    if (bytesRead == 0 && ferror(file)) {
        perror("Erreur de lecture dans le fichier");
        fclose(file);
        free(buffer);
        return 1;
    }
    buffer[bytesRead] = '\0'; // Fin de chaîne

    fclose(file);

    // Afficher les séquences de couleurs ANSI avec des variables formatées
    printf("%s\n", buffer); // IMPORTANT : %s pour interpréter le buffer brut
    printf(buffer, max, nombreReines, totalbis); // Paramètres formatés (si %d présent)

    free(buffer);
    return 0;
}
