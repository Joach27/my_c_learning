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

            if (liste_taches[i].est_complete) {
                printf("La tâche %d est déjà complète.\n", id);
            } else {
                liste_taches[i].est_complete = 1;
                printf("Tâche %d marquée comme complète.\n", id);
            }

        }
    }
    printf("Aucune tâche trouvée avec l'ID %d.\n", id);
}


void supprimer_tache(int id){
    for (int i = 0; i < nombre_taches; i++)
    {
        if (liste_taches[i].id == id)
        {
            // Décaler les tâches suivantes vers le haut
            for (int j = i; j < nombre_taches - 1; j++)
            {
                liste_taches[j] = liste_taches[j + 1];
                liste_taches[j].id = j + 1; // mise à jour des IDs
            }
            nombre_taches--;
            printf("Tâche %d supprimée.\n", id);
            return;
        }
    }
    printf("Aucune tâche trouvée avec l'ID %d.\n", id);
}

void sauver_taches_dans_fichier(const char* nom_fichier)
{
    FILE* fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", nom_fichier);
        return;
    }

    for (int i = 0; i < nombre_taches; i++) {
        fprintf(fichier, "%d;%s;%d\n", liste_taches[i].id, liste_taches[i].description, liste_taches[i].est_complete);
    }

    fclose(fichier);
    printf("Tâches sauvegardées dans le fichier %s.\n", nom_fichier);
}

void charger_taches_depuis_fichier(const char* nom_fichier)
{
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", nom_fichier);
        return;
    }

    while (fscanf(fichier, "%d;%99[^;];%d\n", &liste_taches[nombre_taches].id, liste_taches[nombre_taches].description, &liste_taches[nombre_taches].est_complete) == 3) {
        nombre_taches++; 
        if (nombre_taches >= MAX_TACHES) {
            printf("Limite de tâches atteinte lors du chargement depuis le fichier.\n");
            break;
        }
    }

    fclose(fichier);
    printf("Tâches chargées depuis le fichier %s.\n", nom_fichier);
}



int main()
{
    int choix;

    while (1)
    {
        printf("\n=== Gestionnaire de Tâches ===\n");
        printf("1. Ajouter une tâche\n");
        printf("2. Afficher les tâches\n");
        printf("3. Marquer une tâche comme terminée\n");
        printf("4. Supprimer une tâche\n");
        printf("5. Sauvegarder les tâches dans un fichier\n");
        printf("0. Quitter\n");
        printf("Choisissez une action : ");

        scanf("%d", &choix);
        getchar(); // consomme le '\n' restant après scanf

        switch (choix) {
            case 1: {
                char t[100];
                printf("Description de la tâche : ");
                fgets(t, sizeof(t), stdin);
                // Retirer le \n si présent
                size_t len = strlen(t);
                if (len > 0 && t[len - 1] == '\n') {
                    t[len - 1] = '\0';
                }
                ajouter_tache(t);
                break;
            }
            case 2:
                afficher_taches();
                break;
            case 3: {
                int id;
                printf("Entrez l'ID de la tâche à marquer comme terminée : ");
                scanf("%d", &id);
                marquer_tache_complete(id);
                break;
            }
            case 4: {
                int id_sup;
                printf("Entrez l'ID de la tâche à supprimer : ");
                scanf("%d", &id_sup);
                supprimer_tache(id_sup);
                break;
            }
            case 5: {
                printf("Entrez le nom du fichier pour sauvegarder les tâches : ");
                char nom_fichier[100];
                scanf("%s", nom_fichier);
                sauver_taches_dans_fichier(nom_fichier);
                break;
            }
            case 0:
                printf("Fermeture du gestionnaire de tâches.\n");
                return 0;
            default:
                printf("Entrée invalide ! Veuillez choisir une option valide.\n");
        }
    }

    return 0;
}
