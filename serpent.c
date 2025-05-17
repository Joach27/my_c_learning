#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

#define WIDTH 30
#define HEIGHT 20
#define INITIAL_SNAKE_LENGTH 3

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point body[WIDTH * HEIGHT];
    int length;
    int direction; // 0: up, 1: right, 2: down, 3: left
} Snake;

// Fonction pour effacer l'écran selon le système d'exploitation
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Fonction pour lire un caractère sans attendre la touche Entrée sur Unix/Linux
#ifndef _WIN32
int kbhit() {
    struct termios oldt, newt;
    int ch, oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}

int getch() {
    int ch;
    struct termios oldt, newt;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return ch;
}
#endif

// Fonction pour initialiser le serpent
void initSnake(Snake *snake) {
    snake->length = INITIAL_SNAKE_LENGTH;
    snake->direction = 1; // commence vers la droite
    
    // Positionne le serpent au milieu de l'écran
    int startX = WIDTH / 2;
    int startY = HEIGHT / 2;
    
    for (int i = 0; i < snake->length; i++) {
        snake->body[i].x = startX - i;
        snake->body[i].y = startY;
    }
}

// Fonction pour générer de la nourriture à une position aléatoire
void generateFood(Point *food, Snake *snake) {
    bool validPosition;
    
    do {
        validPosition = true;
        food->x = rand() % WIDTH;
        food->y = rand() % HEIGHT;
        
        // Vérifie que la nourriture n'est pas sur le serpent
        for (int i = 0; i < snake->length; i++) {
            if (snake->body[i].x == food->x && snake->body[i].y == food->y) {
                validPosition = false;
                break;
            }
        }
    } while (!validPosition);
}

// Fonction pour dessiner le jeu
void drawGame(Snake *snake, Point *food, int score) {
    clearScreen();
    
    // Dessine le bord supérieur
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");
    
    // Dessine le terrain de jeu
    for (int y = 0; y < HEIGHT; y++) {
        printf("#"); // Bord gauche
        
        for (int x = 0; x < WIDTH; x++) {
            bool isSnakeBody = false;
            
            // Vérifie si cette position est occupée par le serpent
            for (int i = 0; i < snake->length; i++) {
                if (snake->body[i].x == x && snake->body[i].y == y) {
                    if (i == 0) {
                        printf("O"); // Tête du serpent
                    } else {
                        printf("o"); // Corps du serpent
                    }
                    isSnakeBody = true;
                    break;
                }
            }
            
            // Si ce n'est pas le serpent, vérifie si c'est de la nourriture
            if (!isSnakeBody) {
                if (food->x == x && food->y == y) {
                    printf("@"); // Nourriture
                } else {
                    printf(" "); // Espace vide
                }
            }
        }
        
        printf("#\n"); // Bord droit
    }
    
    // Dessine le bord inférieur
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");
    
    // Affiche le score
    printf("Score: %d\n", score);
    printf("Utilisez les touches ZQSD ou les flèches pour vous déplacer. Q pour quitter.\n");
}

// Fonction pour mettre à jour la position du serpent
bool updateSnake(Snake *snake, Point *food, int *score) {
    // Détermine la nouvelle position de la tête
    Point newHead = snake->body[0];
    
    switch (snake->direction) {
        case 0: newHead.y--; break; // haut
        case 1: newHead.x++; break; // droite
        case 2: newHead.y++; break; // bas
        case 3: newHead.x--; break; // gauche
    }
    
    // Vérifie la collision avec les bords
    if (newHead.x < 0 || newHead.x >= WIDTH || newHead.y < 0 || newHead.y >= HEIGHT) {
        return false;
    }
    
    // Vérifie la collision avec le corps du serpent
    for (int i = 0; i < snake->length; i++) {
        if (newHead.x == snake->body[i].x && newHead.y == snake->body[i].y) {
            return false;
        }
    }
    
    // Vérifie si le serpent a mangé la nourriture
    bool hasEaten = (newHead.x == food->x && newHead.y == food->y);
    
    // Déplace le corps du serpent
    for (int i = snake->length; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }
    
    // Met à jour la tête du serpent
    snake->body[0] = newHead;
    
    // Si le serpent a mangé, augmente sa longueur et génère une nouvelle nourriture
    if (hasEaten) {
        snake->length++;
        *score += 10;
        generateFood(food, snake);
    }
    
    return true;
}

// Fonction principale
int main() {
    srand(time(NULL)); // Initialise le générateur de nombres aléatoires
    
    Snake snake;
    Point food;
    int score = 0;
    bool gameOver = false;
    
    // Initialise le serpent et la nourriture
    initSnake(&snake);
    generateFood(&food, &snake);
    
    // Boucle principale du jeu
    while (!gameOver) {
        // Dessine l'état actuel du jeu
        drawGame(&snake, &food, score);
        
        // Gère les entrées utilisateur
        if (kbhit()) {
            char key = getch();
            
            // Change la direction en fonction de la touche pressée
            switch (key) {
                case 'z': case 'Z': case 72: // flèche haut
                    if (snake.direction != 2) snake.direction = 0; 
                    break;
                case 'd': case 'D': case 77: // flèche droite
                    if (snake.direction != 3) snake.direction = 1; 
                    break;
                case 's': case 'S': case 80: // flèche bas
                    if (snake.direction != 0) snake.direction = 2; 
                    break;
                case 'q': case 'Q': case 75: // flèche gauche
                    if (snake.direction != 1) snake.direction = 3; 
                    break;
                case 27: // Échap
                    gameOver = true;
                    break;
            }
        }
        
        // Mise à jour du serpent
        if (!updateSnake(&snake, &food, &score)) {
            gameOver = true;
        }
        
        // Pause pour ralentir le jeu
        #ifdef _WIN32
        Sleep(100);
        #else
        usleep(100000);
        #endif
    }
    
    // Affiche le message de fin
    clearScreen();
    printf("Game Over! Score final: %d\n", score);
    
    return 0;
}