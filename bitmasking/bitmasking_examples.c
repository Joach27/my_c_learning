
#include <stdio.h>

// ---------- Fonctions Utilitaires ----------
void print_binary(unsigned char x) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
    }
    printf("\n");
}

// ---------- Exemple 1 : Manipulation simple ----------
void exemple1() {
    printf("\n--- Exemple 1 : Manipulation simple ---\n");
    unsigned char x = 0b00101010;  // 42 en décimal

    // Tester si le bit 5 est à 1.
    if (x & (1 << 5)){
        printf("Le bit 5 est à 1\n");
    }

    // Activer le bit 5.
    x |= (1 << 5);
    printf("Après activation bit 5 : %u\n", x);

    // Désactiver le bit 3.
    x &= ~(1 << 3);
    printf("Après désactivation bit 3 : %u\n", x);

    // Inverser le bit 1
    x ^= (1 << 1);
    printf("Après inversion bit 1 : %u\n", x);

    // Afficher binaire
    printf("Valeur binaire finale : ");
    print_binary(x);
}

// ---------- Exemple 2 : Droits d'accès ----------
void exemple2() {
    printf("\n--- Exemple 2 : Droits d'accès ---\n");
    #define READ    (1 << 0)
    #define WRITE   (1 << 1)
    #define EXECUTE (1 << 2)
    #define DELETE  (1 << 3)
    #define ADMIN   (1 << 4)

    unsigned char permissions = 0;

    // Donner les droits READ, WRITE et EXECUTE
    permissions |= READ | WRITE | EXECUTE;
    print_binary(permissions);

    // Vérifier si le droit delete est activé
    if (permissions & DELETE){
        printf("Le droit Delete est activé.\n");
    } else {
        printf("Le droit Delete n'est pas activé.\n");
    }

    // Suppression du droit write
    permissions &= ~WRITE;
    print_binary(permissions);

    // Inversion du droit admin
    permissions ^= ADMIN;
    print_binary(permissions);
}

// ---------- Exemple 3 : Capteurs ----------
void exemple3() {
    printf("\n--- Exemple 3 : Capteurs ---\n");
    #define CAPTEUR_IR           (1 << 0)
    #define CAPTEUR_ULTRASON     (1 << 1)
    #define CAPTEUR_LUMIERE      (1 << 2)
    #define CAPTEUR_TEMPERATURE  (1 << 3)
    #define CAPTEUR_HUMIDITE     (1 << 4)
    #define CAPTEUR_GAZ          (1 << 5)

    unsigned char capteurs = 0;

    // Activer les capteurs IR, Ultrason et Température
    capteurs |= CAPTEUR_IR | CAPTEUR_ULTRASON | CAPTEUR_TEMPERATURE;
    print_binary(capteurs);

    // Vérifier gaz
    if (capteurs & CAPTEUR_GAZ){
        printf("Capteur gaz activé\n");
    } else {
        printf("Capteur gaz NON activé\n");
    }

    // Désactiver Ultrason
    capteurs &= ~CAPTEUR_ULTRASON;
    print_binary(capteurs);

    // Inverser lumière
    capteurs ^= CAPTEUR_LUMIERE;
    print_binary(capteurs);
}

// ---------- Exemple 4 : Rôles utilisateurs ----------
#define ROLE_VISITEUR    (1 << 0)
#define ROLE_USER        (1 << 1)
#define ROLE_MODERATEUR  (1 << 2)
#define ROLE_ADMIN       (1 << 3)
#define ROLE_SUPERADMIN  (1 << 4)

void afficher_roles(unsigned char profil) {
    printf("Rôles actifs : ");
    int has_role = 0;

    if (profil & ROLE_VISITEUR)    { printf("VISITEUR "); has_role = 1; }
    if (profil & ROLE_USER)        { printf("USER "); has_role = 1; }
    if (profil & ROLE_MODERATEUR)  { printf("MODERATEUR "); has_role = 1; }
    if (profil & ROLE_ADMIN)       { printf("ADMIN "); has_role = 1; }
    if (profil & ROLE_SUPERADMIN)  { printf("SUPERADMIN "); has_role = 1; }

    if (!has_role) {
        printf("Aucun");
    }
    printf("\n");
}

void exemple4() {
    printf("\n--- Exemple 4 : Rôles utilisateurs ---\n");
    unsigned char profil = 0;

    profil |= ROLE_VISITEUR | ROLE_USER | ROLE_MODERATEUR;
    printf("Permissions initiales : ");
    print_binary(profil);

    if (profil & ROLE_ADMIN) {
        printf("L'utilisateur est ADMIN.\n");
    } else {
        printf("L'utilisateur n'est PAS ADMIN.\n");
    }

    // Retirer USER
    profil &= ~ROLE_USER;

    // Inverser SUPERADMIN
    profil ^= ROLE_SUPERADMIN;

    printf("Permissions après modifications : ");
    print_binary(profil);

    afficher_roles(profil);
}

// ---------- main ----------
int main() {
    exemple1();
    exemple2();
    exemple3();
    exemple4();
    return 0;
}
