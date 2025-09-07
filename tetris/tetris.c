/* tetris.c
 * Tetris console en C avec ncurses
 *
 * Compile:
 *   gcc -O2 -o tetris tetris.c -lncurses
 *
 * Usage:
 *   ./tetris
 *
 * Contrôles:
 *   ← / →    : gauche / droite
 *   ↓       : soft drop
 *   SPACE   : hard drop
 *   z / x   : rotate CCW / CW
 *   c       : hold
 *   p       : pause
 *   t       : toggle thème (clair/sombre)
 *   q       : quitter
 *
 * Notes:
 *   - Best score sauvegardé dans ~/.tetris_best
 *   - Animation : lignes complètes clignotent avant suppression
 */

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#define COLS_PLAY 10
#define ROWS_PLAY 20
#define BLOCK_CHAR "  "  /* two spaces to look square */
#define NEXT_COUNT 3
#define BAG_SIZE 7

/* Timing (ms) */
#define BASE_DROP_MS 800
#define MIN_DROP_MS 80
#define LEVEL_DROP_DECREASE 60

/* Clear animation */
#define CLEAR_BLINK_MS 75
#define CLEAR_BLINKS 6

/* Color pairs */
enum {
    CP_DEFAULT = 1,
    CP_I, CP_J, CP_L, CP_O, CP_S, CP_T, CP_Z,
    CP_BORDER, CP_TEXT, CP_GHOST, CP_CLEAR
};

typedef enum {I, J, L, O, S, T, Z_TYPE} TetType;

/* 4x4 matrices for tetrominos (shape in rotation 0) */
static const int TETROMINO[7][4][4] = {
    /* I */
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* J */
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* L */
    {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* O */
    {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* S */
    {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* T */
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* Z */
    {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }
};

/* Game state */
char board[ROWS_PLAY][COLS_PLAY]; /* 0 = empty, otherwise 1..7 for tet types */
int bag[BAG_SIZE];
int bag_pos = 0;

typedef struct {
    int type;   /* 0..6 */
    int rot;    /* 0..3 */
    int x, y;   /* x in [0..COLS_PLAY-1], y may be negative at spawn */
} Piece;

Piece current;
int hold = -1;
int hold_used = 0;
int nextq[NEXT_COUNT];

int score = 0, level = 0, lines = 0, best_score = 0;
int running = 1, paused = 0;
int drop_ms = BASE_DROP_MS;
struct timespec last_drop;

/* Helpers */
static long now_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec*1000 + ts.tv_nsec/1000000;
}

void read_best_from_file() {
    char path[512];
    const char *home = getenv("HOME");
    if(!home) {
        struct passwd *pw = getpwuid(getuid());
        if(pw) home = pw->pw_dir;
    }
    if(!home) return;
    snprintf(path, sizeof(path), "%s/.tetris_best", home);
    FILE *f = fopen(path, "r");
    if(f) {
        int v;
        if(fscanf(f, "%d", &v)==1) best_score = v;
        fclose(f);
    }
}
void write_best_to_file() {
    if(score <= best_score) return;
    char path[512];
    const char *home = getenv("HOME");
    if(!home) {
        struct passwd *pw = getpwuid(getuid());
        if(pw) home = pw->pw_dir;
    }
    if(!home) return;
    snprintf(path, sizeof(path), "%s/.tetris_best", home);
    FILE *f = fopen(path, "w");
    if(f) return;
    fprintf(f, "%d\n", score);
    fclose(f);
}

/* ncurses color init for dark and light theme */
int theme_light = 0;
void init_colors(){
    start_color();
    use_default_colors();
    if(theme_light){
        /* light theme: background light, shapes with darker colors */
        init_pair(CP_DEFAULT, COLOR_BLACK, COLOR_WHITE);
        init_pair(CP_I, COLOR_CYAN, COLOR_WHITE);
        init_pair(CP_J, COLOR_BLUE, COLOR_WHITE);
        init_pair(CP_L, COLOR_YELLOW, COLOR_WHITE);
        init_pair(CP_O, COLOR_MAGENTA, COLOR_WHITE);
        init_pair(CP_S, COLOR_GREEN, COLOR_WHITE);
        init_pair(CP_T, COLOR_RED, COLOR_WHITE);
        init_pair(CP_Z, COLOR_MAGENTA, COLOR_WHITE);
        init_pair(CP_BORDER, COLOR_BLACK, COLOR_WHITE);
        init_pair(CP_TEXT, COLOR_BLACK, COLOR_WHITE);
        init_pair(CP_GHOST, COLOR_BLACK, COLOR_WHITE);
        init_pair(CP_CLEAR, COLOR_RED, COLOR_WHITE);
    } else {
        /* dark theme */
        init_pair(CP_DEFAULT, COLOR_WHITE, COLOR_BLACK);
        init_pair(CP_I, COLOR_CYAN, COLOR_BLACK);
        init_pair(CP_J, COLOR_BLUE, COLOR_BLACK);
        init_pair(CP_L, COLOR_YELLOW, COLOR_BLACK);
        init_pair(CP_O, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(CP_S, COLOR_GREEN, COLOR_BLACK);
        init_pair(CP_T, COLOR_RED, COLOR_BLACK);
        init_pair(CP_Z, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(CP_BORDER, COLOR_WHITE, COLOR_BLACK);
        init_pair(CP_TEXT, COLOR_WHITE, COLOR_BLACK);
        init_pair(CP_GHOST, COLOR_BLUE, COLOR_BLACK);
        init_pair(CP_CLEAR, COLOR_RED, COLOR_BLACK);
    }
}

/* Draw helpers */
void draw_cell(WINDOW *w, int by, int bx, int color_pair) {
    wattron(w, COLOR_PAIR(color_pair));
    mvwprintw(w, by, bx, BLOCK_CHAR);
    wattroff(w, COLOR_PAIR(color_pair));
}

void draw_board(WINDOW *playwin) {
    werase(playwin);
    box(playwin, 0, 0);
    for(int r=0;r<ROWS_PLAY;r++){
        for(int c=0;c<COLS_PLAY;c++){
            int v = board[r][c];
            if(v){
                draw_cell(playwin, 1 + r, 1 + c*2, CP_I + (v-1)); /* map 1..7 to CP_I..CP_Z */
            } else {
                /* empty = default background (print spaces) */
                mvwprintw(playwin, 1 + r, 1 + c*2, "  ");
            }
        }
    }
}

/* rotate 4x4 matrix clockwise */
void rotate_cw(int dst[4][4], const int src[4][4]) {
    for(int y=0;y<4;y++) for(int x=0;x<4;x++)
        dst[x][3-y] = src[y][x];
}

/* get cell of a tetromino with rotation */
int tet_cell(int type, int rot, int x, int y) {
    int mat[4][4];
    int tmp1[4][4], tmp2[4][4], tmp3[4][4];
    /* base */
    for(int r=0;r<4;r++) for(int c=0;c<4;c++) mat[r][c] = TETROMINO[type][r][c];
    if(rot==0) return mat[y][x];
    rotate_cw(tmp1, mat); if(rot==1) return tmp1[y][x];
    rotate_cw(tmp2, tmp1); if(rot==2) return tmp2[y][x];
    rotate_cw(tmp3, tmp2); return tmp3[y][x];
}

/* collision test */
int collide_piece(const Piece *p) {
    for(int py=0; py<4; py++){
        for(int px=0; px<4; px++){
            if(tet_cell(p->type, p->rot, px, py)){
                int bx = p->x + px;
                int by = p->y + py;
                if(bx < 0 || bx >= COLS_PLAY || by >= ROWS_PLAY) return 1;
                if(by >= 0 && board[by][bx]) return 1;
            }
        }
    }
    return 0;
}

/* place piece into board (type number stored as 1..7) */
void place_piece(const Piece *p) {
    for(int py=0; py<4; py++){
        for(int px=0; px<4; px++){
            if(tet_cell(p->type, p->rot, px, py)){
                int bx = p->x + px;
                int by = p->y + py;
                if(by>=0 && by < ROWS_PLAY && bx>=0 && bx<COLS_PLAY)
                    board[by][bx] = p->type + 1;
            }
        }
    }
}

/* spawn next piece */
void refill_bag_if_needed() {
    if(bag_pos >= BAG_SIZE){
        /* shuffle bag */
        for(int i=0;i<BAG_SIZE;i++) bag[i] = i; /* 0..6 */
        for(int i=BAG_SIZE-1;i>0;i--){
            int j = rand() % (i+1);
            int t = bag[i]; bag[i] = bag[j]; bag[j] = t;
        }
        bag_pos = 0;
    }
}

void spawn_new_piece() {
    refill_bag_if_needed();
    int t = bag[bag_pos++];
    current.type = t;
    current.rot = 0;
    current.x = (COLS_PLAY/2) - 2;
    current.y = -1; /* spawn slightly above */
    hold_used = 0;
}

/* init next queue */
void init_next_queue() {
    for(int i=0;i<NEXT_COUNT;i++){
        refill_bag_if_needed();
        nextq[i] = bag[bag_pos++];
    }
}

/* shift next queue and refill */
int pop_next() {
    int t = nextq[0];
    for(int i=0;i<NEXT_COUNT-1;i++) nextq[i] = nextq[i+1];
    refill_bag_if_needed();
    nextq[NEXT_COUNT-1] = bag[bag_pos++];
    return t;
}

/* rotate with simple wall kicks (basic) */
void rotate_current(int dir) {
    Piece trial = current;
    trial.rot = (trial.rot + (dir>0?1:3)) % 4;
    /* try no kick, left, right, up */
    if(!collide_piece(&trial)) { current.rot = trial.rot; return; }
    trial.x = current.x - 1;
    if(!collide_piece(&trial)) { current.rot = trial.rot; current.x = trial.x; return; }
    trial.x = current.x + 1;
    if(!collide_piece(&trial)) { current.rot = trial.rot; current.x = trial.x; return; }
    trial.x = current.x; trial.y = current.y - 1;
    if(!collide_piece(&trial)) { current.rot = trial.rot; current.y = trial.y - 1; return; }
    /* failed rotation */
}

/* attempt move */
void move_current(int dx) {
    Piece trial = current;
    trial.x += dx;
    if(!collide_piece(&trial)) current = trial;
}

/* soft drop */
int soft_drop_one() {
    Piece trial = current;
    trial.y += 1;
    if(!collide_piece(&trial)) { current.y++; return 1; }
    return 0;
}

/* hard drop */
void hard_drop() {
    int d = 0;
    while(1){
        Piece trial = current; trial.y += 1;
        if(!collide_piece(&trial)) { current.y++; d++; }
        else break;
    }
    score += d * 2;
    place_piece(&current);
}

/* detect full rows and animate then remove */
int detect_full_rows(int *rows_out) {
    int found = 0;
    for(int r=0;r<ROWS_PLAY;r++){
        int full = 1;
        for(int c=0;c<COLS_PLAY;c++) if(!board[r][c]) { full = 0; break; }
        if(full) rows_out[found++] = r;
    }
    return found;
}

void animate_and_clear_rows(WINDOW *playwin, int *rows, int count) {
    /* Blink rows several times */
    for(int b=0;b<CLEAR_BLINKS;b++){
        /* drawn inverted / using CP_CLEAR or blank */
        for(int i=0;i<count;i++){
            int rr = rows[i];
            for(int c=0;c<COLS_PLAY;c++){
                if(b % 2 == 0){
                    /* show as clear color */
                    draw_cell(playwin, 1 + rr, 1 + c*2, CP_CLEAR);
                } else {
                    /* blank */
                    mvwprintw(playwin, 1 + rr, 1 + c*2, "  ");
                }
            }
        }
        wrefresh(playwin);
        napms(CLEAR_BLINK_MS);
    }
    /* remove rows bottom-up */
    int removed = 0;
    for(int r=ROWS_PLAY-1;r>=0;r--){
        int full = 1;
        for(int c=0;c<COLS_PLAY;c++) if(!board[r][c]) { full = 0; break; }
        if(full){
            /* shift down */
            for(int rr=r; rr>0; rr--) {
                for(int c=0;c<COLS_PLAY;c++) board[rr][c] = board[rr-1][c];
            }
            for(int c=0;c<COLS_PLAY;c++) board[0][c] = 0;
            removed++;
            r++; /* recheck this row index as rows shifted */
        }
    }
    /* scoring */
    if(removed > 0){
        lines += removed;
        level = lines / 10;
        static const int SCORES[] = {0, 100, 300, 500, 800};
        int s = (removed >=0 && removed <=4) ? SCORES[removed] : (removed*200);
        score += s * (level + 1);
        /* update drop speed */
        int new_drop = BASE_DROP_MS - level * LEVEL_DROP_DECREASE;
        if(new_drop < MIN_DROP_MS) new_drop = MIN_DROP_MS;
        drop_ms = new_drop;
    }
}

/* draw current piece (and ghost) */
void draw_current_and_ghost(WINDOW *playwin) {
    /* ghost: drop until collision */
    Piece ghost = current;
    while(1){
        Piece trial = ghost; trial.y += 1;
        if(!collide_piece(&trial)) ghost.y++;
        else break;
    }
    /* draw ghost in faint color (CP_GHOST) */
    for(int py=0; py<4; py++){
        for(int px=0; px<4; px++){
            if(tet_cell(ghost.type, ghost.rot, px, py)){
                int bx = ghost.x + px;
                int by = ghost.y + py;
                if(by >= 0 && bx >= 0 && bx < COLS_PLAY && by < ROWS_PLAY)
                    draw_cell(playwin, 1 + by, 1 + bx*2, CP_GHOST);
            }
        }
    }
    /* draw current piece */
    for(int py=0; py<4; py++){
        for(int px=0; px<4; px++){
            if(tet_cell(current.type, current.rot, px, py)){
                int bx = current.x + px;
                int by = current.y + py;
                if(by >= 0 && bx >= 0 && bx < COLS_PLAY && by < ROWS_PLAY)
                    draw_cell(playwin, 1 + by, 1 + bx*2, CP_I + current.type);
            }
        }
    }
}

/* draw next and hold panels */
void draw_side_panels(WINDOW *win, WINDOW *playwin) {
    int startx = COLS_PLAY*2 + 3;
    /* Next */
    mvwprintw(win, 1, startx, "Next:");
    for(int i=0;i<NEXT_COUNT;i++){
        int basey = 2 + i*5;
        for(int r=0;r<4;r++){
            for(int c=0;c<4;c++){
                if(tet_cell(nextq[i], 0, c, r)){
                    draw_cell(win, basey + r, startx + 2 + c*2, CP_I + nextq[i]);
                } else {
                    mvwprintw(win, basey + r, startx + 2 + c*2, "  ");
                }
            }
        }
    }
    /* Hold */
    mvwprintw(win, 2 + NEXT_COUNT*5, startx, "Hold:");
    for(int r=0;r<4;r++){
        for(int c=0;c<4;c++){
            if(hold >= 0 && tet_cell(hold, 0, c, r)){
                draw_cell(win, 4 + NEXT_COUNT*5 + r, startx + 2 + c*2, CP_I + hold);
            } else {
                mvwprintw(win, 4 + NEXT_COUNT*5 + r, startx + 2 + c*2, "  ");
            }
        }
    }

    /* Score / Level / Lines / Best */
    mvwprintw(win, 10 + NEXT_COUNT*5, startx, "Score: %d", score);
    mvwprintw(win, 11 + NEXT_COUNT*5, startx, "Level: %d", level);
    mvwprintw(win, 12 + NEXT_COUNT*5, startx, "Lines: %d", lines);
    mvwprintw(win, 13 + NEXT_COUNT*5, startx, "Best: %d", best_score);
}

/* attempt to lock piece and handle clears */
void lock_and_handle(WINDOW *playwin) {
    place_piece(&current);
    int rows[ROWS_PLAY];
    int cnt = detect_full_rows(rows);
    if(cnt>0){
        /* animate and clear */
        animate_and_clear_rows(playwin, rows, cnt);
    }
    /* spawn next from nextq */
    current.type = pop_next();
    current.rot = 0;
    current.x = (COLS_PLAY/2) - 2;
    current.y = -1;
    if(collide_piece(&current)){
        /* game over */
        if(score > best_score) best_score = score, write_best_to_file();
        mvwprintw(playwin, ROWS_PLAY/2, 4, " GAME OVER ");
        wrefresh(playwin);
        paused = 1;
    }
}

/* hold action */
void do_hold() {
    if(hold_used) return;
    if(hold == -1){
        hold = current.type;
        current.type = pop_next();
        current.rot = 0; current.x = (COLS_PLAY/2)-2; current.y = -1;
    } else {
        int tmp = hold;
        hold = current.type;
        current.type = tmp;
        current.rot = 0; current.x = (COLS_PLAY/2)-2; current.y = -1;
    }
    hold_used = 1;
}

/* main loop */
int main() {
    srand(time(NULL));
    read_best_from_file();

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); /* non-blocking input */
    curs_set(0);

    /* init theme dark by default */
    init_colors();
    bkgd(COLOR_PAIR(CP_DEFAULT));

    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    WINDOW *playwin = newwin(ROWS_PLAY + 2, COLS_PLAY*2 + 2, 1, 1);
    WINDOW *sidewin = newwin(ROWS_PLAY + 2, 30, 1, COLS_PLAY*2 + 4);

    /* prepare game */
    memset(board, 0, sizeof(board));
    bag_pos = BAG_SIZE; /* force refill */
    init_next_queue();
    /* initial piece: pop next */
    current.type = pop_next();
    current.rot = 0; current.x = (COLS_PLAY/2)-2; current.y = -1;
    hold = -1; hold_used = 0;

    /* main timing */
    clock_gettime(CLOCK_MONOTONIC, &last_drop);

    /* draw initial UI */
    draw_board(playwin);
    draw_side_panels(sidewin, playwin);
    wrefresh(playwin);
    wrefresh(sidewin);

    int ch;
    long last_ms = now_ms();
    while(running) {
        long cur_ms = now_ms();
        /* input */
        ch = getch();
        if(ch != ERR){
            if(ch == KEY_LEFT){ move_current(-1); }
            else if(ch == KEY_RIGHT){ move_current(1); }
            else if(ch == KEY_DOWN){ if(soft_drop_one()) score += 1; else { /* if can't drop */ lock_and_handle(playwin); } }
            else if(ch == ' '){ hard_drop(); lock_and_handle(playwin); }
            else if(ch == 'z' || ch == 'Z'){ rotate_current(-1); }
            else if(ch == 'x' || ch == 'X'){ rotate_current(1); }
            else if(ch == 'c' || ch == 'C'){ do_hold(); }
            else if(ch == 'p' || ch == 'P'){ paused = !paused; }
            else if(ch == 't' || ch == 'T'){
                theme_light = !theme_light;
                init_colors();
                wbkgd(playwin, COLOR_PAIR(CP_DEFAULT));
                wbkgd(sidewin, COLOR_PAIR(CP_DEFAULT));
            }
            else if(ch == 'q' || ch == 'Q'){ running = 0; break; }
            else if(ch == KEY_RESIZE){
                /* ignore for simplicity */
            }
        }

        if(!paused){
            long elapsed = cur_ms - last_ms;
            if(elapsed >= drop_ms){
                last_ms = cur_ms;
                /* gravity tick */
                if(soft_drop_one()){
                    /* moved down */
                } else {
                    /* lock piece and spawn next */
                    place_piece(&current);
                    int rows[ROWS_PLAY];
                    int cnt = detect_full_rows(rows);
                    if(cnt>0){
                        animate_and_clear_rows(playwin, rows, cnt);
                    }
                    /* spawn next piece */
                    current.type = pop_next();
                    current.rot = 0; current.x = (COLS_PLAY/2)-2; current.y = -1;
                    hold_used = 0;
                    if(collide_piece(&current)){
                        /* game over */
                        if(score > best_score) best_score = score, write_best_to_file();
                        mvwprintw(playwin, ROWS_PLAY/2, 4, " GAME OVER ");
                        wrefresh(playwin);
                        paused = 1;
                    }
                }
            }
        }

        /* rendering */
        draw_board(playwin);
        draw_current_and_ghost(playwin);
        draw_side_panels(sidewin, playwin);
        /* footer text */
        mvwprintw(sidewin, ROWS_PLAY, 1, "Keys: ←→ ↓  Z/X rotate  SPACE hard");
        mvwprintw(sidewin, ROWS_PLAY+1, 1, "C hold  P pause  T theme  Q quit");
        wrefresh(playwin);
        wrefresh(sidewin);

        /* small sleep to reduce CPU */
        napms(10);
    }

    endwin();
    printf("Merci d'avoir joué ! Score: %d Best: %d\n", score, best_score);
    return 0;
}
