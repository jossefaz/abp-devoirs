#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#define TOUCHED 'X'
#define WATER 'o'
#define PRISTINE '.'
#define H_BOAT '='
#define V_BOAT 'U'
#define GRID_PREFIX "|  "
#define GRID_ANGLE "   "
#define GRID_SUFIX "  "
#define FISHNET_SIZE 10
#define ROWS ((char[]){'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'})
#define BOATS ((int[]){5, 4, 3, 3, 3, 2, 2, 2, 2})
#define DEBUG_MODE 1

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

void set_case(struct fishnet_arr *fishnet, int line, int column, char value) {
    if (line < FISHNET_SIZE && column < FISHNET_SIZE) {
        fishnet -> net[line][column] = value;
    } else {
        printf("Un numero de colonne ou de ligne eronne fut passe en argument de la fonction 'set_touched'\n");
    }
}

char get_display_value(char actual_value) {
    if(actual_value != TOUCHED && actual_value != PRISTINE) {
        if (DEBUG_MODE) {
            return actual_value;
        }
        return PRISTINE;
    }
    return actual_value;
}


int *get_shuffled_boats() {
    size_t number_of_boats = sizeof(BOATS)/sizeof(BOATS[0]);
    int* copy = malloc(sizeof(int) * number_of_boats);
    for (int i = 0; i < number_of_boats; i++) {
        copy[i] = BOATS[i];
    }
    for (int i = 0; i < number_of_boats; ++i) {
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

char get_display_char(int boat_num, int by_width) {
    if (!DEBUG_MODE) {
        if (by_width) {
            return H_BOAT;
        }
        return V_BOAT;
    }
    char str[10];
    sprintf(str, "%d", boat_num);
    return str[0];

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

void feed_fishnet(struct fishnet_arr *fishnet) {
    int *boats=get_shuffled_boats();
    int by_width = 0;
    for (int i = 0; i < FISHNET_SIZE ; ++i) {
        int current_boat = boats[i];
        int row, col,free = 0;
        while (!free && current_boat != 0) {
            by_width = by_width == 1 ? 0 : 1;
            if (by_width) {
                row = rand() % FISHNET_SIZE;
                col = rand() & FISHNET_SIZE - current_boat;
            } else {
                row = rand() % FISHNET_SIZE - current_boat;
                col = rand() & FISHNET_SIZE;
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
                for (int j = start_index; j < current_boat + start_index; ++j) {
                    if (by_width) {
                        fishnet->net[row][j] = get_display_char(current_boat, by_width);
                    } else {
                        fishnet->net[j][col] = get_display_char(current_boat, by_width);
                    }
                }
            }

        }
    }

}

char * build_headers() {
    char header_index[10];
    char *header;
    header = malloc(100);
    header[0] = 0;
    strcat(header, GRID_ANGLE);
    for (int i = 0; i < FISHNET_SIZE; ++i) {
        sprintf(header_index, "%d", i);
        strcat(header, GRID_PREFIX);
        strcat(header, header_index);
        strcat(header, GRID_SUFIX);
    }
    strcat(header, GRID_PREFIX);
    return header;
}




void print_fishnet(struct fishnet_arr fishnet) {
    printf("%s\n", build_headers());
    for (int i = 0; i < FISHNET_SIZE; ++i) {
        printf("%c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  | \n", ROWS[i],
               get_display_value(fishnet.net[i][0]),
               get_display_value(fishnet.net[i][1]),
               get_display_value(fishnet.net[i][2]),
               get_display_value(fishnet.net[i][3]),
               get_display_value(fishnet.net[i][4]),
               get_display_value(fishnet.net[i][5]),
               get_display_value(fishnet.net[i][6]),
               get_display_value(fishnet.net[i][7]),
               get_display_value(fishnet.net[i][8]),
               get_display_value(fishnet.net[i][9]));
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
    if (first_val > 9 || first_val <1) {
        return -1;
    }
    if(!isdigit(col_index[2])) {
        return -1;
    }
    int second_val = col_index[2] - '0';
    if (second_val > 0 || (first_val !=1 && second_val == 0 )) {
        return -1;
    }
    return atoi(col_index);

}


int main() {
    // Init the random seed
    srand(time(NULL));

    char letter[3];
    int index_line, col_index;
    do {
        printf("Entrez une case sous la forme <index ligne><index colonne> Par exemple A1\n");
        read_reset_stdin(letter, 4);
        index_line = get_line_index(letter[0]);
        if (index_line == -1) {
            printf("Mauvaise saisie de lettre, celle ci doit etre comprise entre A et J\n");
            continue;
        }
        col_index = validate_col_index(letter);
        if (col_index == -1) {
            printf("Mauvaise saisie de chiffre, celui ci doit etre comprise entre 0 et 10\n");
            continue;
        }
    } while (index_line == -1 || col_index == -1);


    struct fishnet_arr fishnet = get_new_fishnet();
    feed_fishnet(&fishnet);
//    set_case(&fishnet, 9,0, WATER);
    print_fishnet(fishnet);

    return 0;
}
