#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_TACHES 100  

typedef struct {
    int id;
    char description[100];
    int est_complete;
} Tache; 

Tache liste_taches[MAX_TACHES];
int nombre_taches = 0;

void ajouter_tache(const char* description)
{
    if (nombre_taches < MAX_TACHES) 
    {
        Tache nouvelle_tache;
        nouvelle_tache.id = nombre_taches + 1; // ID unique
        strncpy(nouvelle_tache.description, description, sizeof(nouvelle_tache.description) - 1);
        nouvelle_tache.est_complete = 0; // Tache nouvellement créée, non encore complete
        // Assurez-vous que la chaîne est terminée
        nouvelle_tache.description[sizeof(nouvelle_tache.description) - 1] = '\0';
        liste_taches[nombre_taches] = nouvelle_tache;
        nombre_taches++;
    }
    else
    {
        printf("Impossible d'ajouter plus de tâches : limite atteinte.\n");
    }

}

void afficher_taches()
{
    if (nombre_taches == 0)
    {
        printf("Aucune tâche à afficher.\n");
        return;
    }
    for (int i = 0; i < nombre_taches; i++)
    {
        printf("Tache %d : %s\n", liste_taches[i].id, liste_taches[i].description);
        printf("Statut   : %s\n", liste_taches[i].est_complete ? "Complete" : "Incomplete");
        printf("-----------------------------\n");
    }
}

void marquer_tache_complete(int id)
{
    for (int i = 0; i < nombre_taches; i++)
    {
        if (liste_taches[i].id == id)
        {
            liste_taches[i].est_complete = 1; // Marquer comme complète
            printf("Tâche %d marquée comme complète.\n", id);
            return;
        }
    }
    printf("Aucune tâche trouvée avec l'ID %d.\n", id);
}

int main()
{
    // Exemple d'utilisation
    ajouter_tache("Apprendre le C");
    ajouter_tache("Apprendre les pointeurs");

    afficher_taches();

    return 0;
}