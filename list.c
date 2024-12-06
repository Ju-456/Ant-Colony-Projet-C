#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Profil
{
    struct Profil *last; 
    char name[20];            
    int age;                  
    struct Profil *next;   
} Profil;

void CreateRandomProfil(Profil *TempProfil) {
    int NbProfil;
    printf("Entrer le nombre de profils à générer : ");
    scanf("%d", &NbProfil);

    Profil *current = TempProfil; 
    Profil *head = current;      
    current->last = NULL;    

    // Générer les profils
    for (int i = 0; i < NbProfil; i++) {
        int NbLettre;
        const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

        // Génération du nom
        NbLettre = 1 + (rand() % 19); 
        for (int j = 0; j < NbLettre; j++) {
            int randomIndex = rand() % (sizeof(alphabet) - 1);
            current->name[j] = alphabet[randomIndex];
        }
        current->name[NbLettre] = '\0'; 

        // Génération de l'âge
        current->age = 17 + (rand() % 4); 

        // Affichage
        printf("Profil n°%d : \nName : %s \nAge : %d\n", i + 1, current->name, current->age);

        // Préparer le prochain profil, sauf pour le dernier
        if (i < NbProfil - 1) {
            Profil *newProfil = malloc(sizeof(Profil));
            if (!newProfil) {
                printf("Erreur d'allocation mémoire.\n");
                break;
            }
            newProfil->last = current; 
            current->next = newProfil;  
            current = newProfil;
        } else {
            current->next = NULL; 
        }
    }
}

void Research(Profil *TempProfil) {
    printf("\nRecherche des profils ayant 18 ans :\n");

    // Parcourir la liste chaînée
    while (TempProfil != NULL) {
        if (TempProfil->age == 18) {
            printf("Nom : %s\n", TempProfil->name);
        }
        TempProfil = TempProfil->next; 
    }
}

int main() {
    
    Profil *head = malloc(sizeof(Profil)); 

    CreateRandomProfil(head);  
    Research(head);            

    // Libération de la mémoire
    Profil *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
