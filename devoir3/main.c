#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#define TOUCHED 'X'
#define WATER 'o'
#define PRISTINE '.'
#define GRID_PREFIX "|  "
#define GRID_ANGLE "   "
#define GRID_SUFIX "  "
#define FISHNET_SIZE 10
#define ROWS ((char[]){'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'})
#define BOAT_NUMBER 9
#define BOATS ((int[]){5, 4, 3, 3, 3, 2, 2, 2, 2})

#define DEBUG_MODE 0

struct boat {
    int size;
    int coord[5][2];
    int status;
};

int read_reset_stdin(char s[], int maxlen) {
    // init empty character, counter and remains character indicator
    char ch;
    int i;
    int chars_remain;

    // assign 0 to the counter
    i = 0;

    // assign 1 to character remains indicator (otherwise it wont enter the loop)
    chars_remain = 1;
    while (chars_remain) {
        // get the first character from stdin
        ch = getchar();
        // if the character is EOF or new line
        if((ch == '\n') || (ch == EOF)) {
            // then exit the loop by setting the char_remain to 0
            chars_remain = 0;
        } else if (i < maxlen -1) {
            // otherwise set the current character to the index of i
            s[i] = ch;
            i++;
        }
    }
    // set the last character to NULL
    s[i] = '\0';
    // return the actual size of the string
    return i -1;

}



struct fishnet_arr {
    char net[FISHNET_SIZE][FISHNET_SIZE];
};

struct fishnet_arr get_new_fishnet() {
    struct fishnet_arr fishnet ={{}};
    for (int i = 0; i < FISHNET_SIZE; ++i) {
        for (int j = 0; j < FISHNET_SIZE; ++j) {
            fishnet.net[i][j] = PRISTINE;
        }
    }
    return fishnet;
}



char get_display_value(char actual_value, int display_boats) {
    if(actual_value != PRISTINE) {

        if (DEBUG_MODE || display_boats) {
            return actual_value;
        }
        if (actual_value == TOUCHED || actual_value == WATER) {
            return actual_value;
        }
        return PRISTINE;
    }
    return actual_value;
}


int *get_shuffled_boats() {
    size_t number_of_boats = sizeof(BOATS)/sizeof(BOATS[0]);
    int* copy = malloc(sizeof(int) * number_of_boats);
    for (int i = 0; i < BOAT_NUMBER; i++) {
        copy[i] = BOATS[i];
    }
    for (int i = 0; i < BOAT_NUMBER; ++i) {
        size_t j = rand() % (number_of_boats);
        int t = copy[j];
        copy[j] = copy[i];
        copy[i] = t;
    }
    return copy;
}
int get_start_index(int original_index, int boat_length) {
    return original_index - boat_length < 0 ? 0 : original_index - boat_length;
}

int check_free_row(const char row[], int start_index, int boat_length) {
    start_index =  get_start_index(start_index, boat_length);
    for (int i = start_index; i < boat_length; ++i) {
        if (row[i] != PRISTINE) {
            return 0;
        }
    }
    return 1;
}
char int_to_char(int num) {
    char str[10];
    sprintf(str, "%d", num);
    return str[0];
}


int set_boat_status(struct boat targeted_boat) {
    //check targeted boat status
    int boat_status = 0;
    for (int i = 0; i < targeted_boat.size; ++i) {
        if (targeted_boat.coord[i][0] != -1 && targeted_boat.coord[i][1] != -1) {
            boat_status = 1;
            break;
        }
    }
    targeted_boat.status = boat_status;
    return boat_status;
}

int set_coord_touched(struct boat *boat_list, int row_index, int col_index, int target_boat_size) {
    struct boat targeted_boat;
    for (int i = 0; i < BOAT_NUMBER; ++i) {
        if (boat_list[i].size == target_boat_size) {
            for (int j = 0; j < target_boat_size; ++j) {
                if(boat_list[i].coord[j][0] == row_index && boat_list[i].coord[j][1] == col_index) {
                    boat_list[i].coord[j][0] = -1;
                    boat_list[i].coord[j][1] = -1;
                    targeted_boat = boat_list[i];
                }
            }
        }
    }
    return !set_boat_status(targeted_boat);
}
int check_free_col(struct fishnet_arr *fishnet,int start_line_index, int start_col_index, int boat_length) {
    start_line_index = get_start_index(start_line_index,boat_length);
    for (int i = start_line_index; i < boat_length + start_line_index; ++i) {
        if (fishnet->net[i][start_col_index] != PRISTINE) {
            return 0;
        }
    }
    return 1;
}

void feed_fishnet(struct fishnet_arr *fishnet, struct boat *boat_list) {

    int *boats=get_shuffled_boats();
    int by_width = 0;
    for (int i = 0; i < FISHNET_SIZE ; ++i) {
        int current_boat = boats[i];
        int row, col,free = 0;
        while (!free && current_boat != 0) {
            by_width = by_width == 1 ? 0 : 1;
            if (by_width) {
                row = rand() % FISHNET_SIZE;
                col = rand() % (FISHNET_SIZE - current_boat);
            } else {
                row = rand() % (FISHNET_SIZE - current_boat);
                col = rand() % FISHNET_SIZE;
            }
            if(fishnet->net[row][col] == PRISTINE) {
                if (by_width) {
                    free = check_free_row(fishnet->net[row], col, current_boat);
                } else {
                    free = check_free_col(fishnet, row, col, current_boat);
                }
            }
            if(free) {
                int start_index;
                if(by_width) {
                    start_index = get_start_index(col, current_boat);
                } else {
                    start_index = get_start_index(row, current_boat);
                }
                int k = 0;
                
                for (int j = start_index; j < current_boat + start_index; ++j) {
                    char boat_char = int_to_char(current_boat);
                    if (by_width) {
                        fishnet->net[row][j] = boat_char;
                        boat_list[i].coord[k][0] = row;
                        boat_list[i].coord[k][1] = j;
                    } else {
                        fishnet->net[j][col] = boat_char;
                        boat_list[i].coord[k][0] = j;
                        boat_list[i].coord[k][1] = col;
                    }
                    k++;
                }
                boat_list[i].size = current_boat;
                boat_list[i].status = 1;
            }

        }
    }

}

void print_headers() {
    printf(GRID_ANGLE);
    for (int i = 0; i < FISHNET_SIZE; ++i) {
        printf(GRID_PREFIX);
        printf("%d", i);
        printf(GRID_SUFIX);
    }
    printf(GRID_PREFIX);
    printf("\n");
}




void print_fishnet(struct fishnet_arr fishnet, int display_boats) {
    print_headers();
    for (int i = 0; i < FISHNET_SIZE; ++i) {
        printf("%c  |", ROWS[i]);
        for (int j = 0; j < FISHNET_SIZE; ++j) {
            printf("  %c  |", get_display_value(fishnet.net[i][j], display_boats));
        }
        printf("\n");
    }
}

int get_line_index(char letter) {
    char upper_letter = toupper(letter);
    int rows_length = sizeof(ROWS) / sizeof(char);
    for (int i = 0; i < rows_length; ++i) {
        if(ROWS[i] == upper_letter )  {
            return i;
        }
    }
    return -1;
}
int validate_col_index(const char col_index[]) {

    if(!isdigit(col_index[1])) {
        return -1;
    }
    int first_val = col_index[1] - '0';
    if (first_val > 9 || first_val <0) {
        return -1;
    }
    if(!isdigit(col_index[2]) && col_index[2] != '\000') {
        return -1;
    }
    int second_val = col_index[2] - '0';
    if (second_val > 0 || (first_val !=1 && second_val == 0 )) {
        return -1;
    }
    char num_filter[] = "0123456789";
    return atoi(strpbrk(col_index, num_filter));

}

int check_end_game(struct boat *boat_list) {
    // On itere selon le nombre de bqteau sur la liste des structures bateau
    for (int i = 0; i < BOAT_NUMBER; ++i) {
        // des qu un bateau a pour statut non-coulé
        if (boat_list[i].status == 1) {
            // on renvoi 0 indiqant que le jeu n'est pas terminé
            return 0;
        }
    }
    // Sinon tous les bateau on un statut 0 on renvoie que le jeu est terminé
    return 1;
}

int check_case(int row, int col, struct fishnet_arr fishnet) {
    // Si le cqrqctere correspondant à la ligne et la colonne visée n'est ni PRISTINE ni WATER ni TOUCHED
    if (fishnet.net[row][col] != PRISTINE && fishnet.net[row][col] != WATER  && fishnet.net[row][col] != TOUCHED ) {
        // On retourne le chiffre correspondant à la taille du bateau
        return fishnet.net[row][col] - '0';
    }
    // sinon on retourne 0
    return 0;
}

int main() {
    // On declare et on instancie une nouvelle grille pour le programme
    struct fishnet_arr fishnet = get_new_fishnet();
    // On declare une nouvelle liste de structures "boats" pour gerer les bateaux; leurs coordonées, et leurs status
    struct boat boat_list[BOAT_NUMBER];
    // On declare un tableau de char pour recevoir l'entrée utilisateur
    char target[3];

    // On declare 4 integers,
    // un pour l'index ligne,
    // l'autre pour l'index colonne,
    // un compteur d'essai et
    // un qui sert de booleen pour determiner si la partie est finie ou non.
    int row_index,
    col_index,
    try_counter = 0,
    end_game = 0;

    // On instancie un flux permettant de randomiser
    srand(time(NULL));

    // On remplie la grille en y passant notre liste de bateau qui se remplira au fil des iteration sur la grille
    feed_fishnet(&fishnet, boat_list);

    // Tqnt que le jeu n'est pas fini
    while (!end_game) {
        do {
            // On demande à l'utilisateur de rentrer une case sous la forme <index ligne><index colonne> et on donne un exemple
            printf("Entrez une case sous la forme <index ligne><index colonne> Par exemple A1\n");
            // On lit l'entrée utlisateur puis on remet l'entrée standard -stdin- à 0
            read_reset_stdin(target, 4);
            // On verifie a quel index de ligne correspond la lettre entrée par l'utilisateur
            row_index = get_line_index(target[0]);
            // Si cette lettre n'est pas valide (voire ce n'est pas du tout une lettre)
            if (row_index == -1) {
                // on indique a l'utilisateur l'erreur de saisie
                printf("Mauvaise saisie de lettre, celle ci doit etre comprise entre A et J\n");
                // puis on reboucle afin de l'inviter à resaisir
                continue;
            }
            // On verifie a quel index de colonne correspond les chiffres entrés par l'utilisateur
            col_index = validate_col_index(target);
            // Si ces chiffres ne sont pas valides (voire ce ne sont pas des chiffres)
            if (col_index == -1) {
                // on indique a l'utilisateur l'erreur de saisie
                printf("Mauvaise saisie de chiffre, celui ci doit etre comprise entre %d et %d\n", 0, FISHNET_SIZE);
                // puis on reboucle afin de l'inviter à resaisir
                continue;
            }
            // On reboucle tant que la saisie utilisateur n'est pas velide
        } while (row_index == -1 || col_index == -1);
        // On verifie si la case entrée par l'utilisateur est une case occupée
        int check_target = check_case(row_index, col_index, fishnet);
        // Si oui
        if (check_target) {
            // On annonce à l'utilisateur qu'il a touché
            puts("Touché\n");
            // On remplace la case de la grille par le caractère correspondant à touché
            fishnet.net[row_index][col_index] = TOUCHED;
            // On remplace les coordonées du bateau touché par des coordonées invalides indiquant la case touchée, cette fonction nous renvoie le statut du bateau
            int flowed = set_coord_touched(boat_list, row_index, col_index, check_target);
            // Si le statut du bateau est 'coulé'
            if (flowed) {
                // On annonce à l'utilisateur qu'il a coulé un bateau
                puts("Coulé !!");
            }
        } else {
            // Si non; on annonce à l'utilisateur qu'il a fait mouche
            puts("A l'eau\n");
            // Si la case était deja touché on ne fait rien - et tant pis pour l'utilisateur qui a perdu un coup
            if (fishnet.net[row_index][col_index] != TOUCHED) {
                // si la case n'était pas touchée jusqu'à maintenant, on inditque par un symbole que cette case est vide
                fishnet.net[row_index][col_index] = WATER;
            }
        }
        // on affiche à l'utilisateur la grille courrante avec tous les symboles correspondant
        print_fishnet(fishnet,0);
        if (DEBUG_MODE) {
            // Si on est en mode debug, on imprime également la grille mais avec la position de chaque bateau indiqué par le nombre de case du bateau
            print_fishnet(fishnet,1);
        }
        // On verifie si le jeu est fini -si il reste des bateaux dont le statut est 1 à savoir non - coulé
        end_game = check_end_game(boat_list);
        // on incrémente le compteur d'essai
        try_counter++;
    }
    // si le jeu est fini on indique à l'utilisateur qu'il a gagné et le nombre de coup pour y parvenir
    printf("Bravo vous avez gangné en : %d coups", try_counter);
    // on retourne le code 0 pour indiquer le de programme s'est executé sans erreur
    return 0;
}
