#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <proc_service.h>


#define TOUCHED 'X'
#define WATER 'o'
#define PRISTINE '.'
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

char get_display_value(bool show_already_said, char actual_value) {
    if(actual_value != TOUCHED && actual_value != PRISTINE) {
        if (show_already_said) {
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
            return '=';
        }
        return '|';
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
    for (int i = 0; i < FISHNET_SIZE ; ++i) {
        int current_boat = boats[i];
        int row = 0, col = 0;
        int free = 0;
        //vertical ou horizontal

        while (!free && current_boat != 0) {
            int by_width;
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
                for (int j = 0; j < current_boat; ++j) {
                    fishnet->net[row][col] = get_display_char(current_boat, by_width);
                    if (by_width) {
                        col += 1;
                    } else {
                        row +=1;
                    }
                }
            }

        }


        printf("%d\n", boats[i]);
    }

}




void print_fishnet(struct fishnet_arr fishnet, bool show_already_said) {
    printf("___|  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  | \n");
    for (int i = 0; i < FISHNET_SIZE; ++i) {
        printf("%c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  | \n", ROWS[i],
               get_display_value(show_already_said,fishnet.net[i][0]),
               get_display_value(show_already_said,fishnet.net[i][1]),
               get_display_value(show_already_said,fishnet.net[i][2]),
               get_display_value(show_already_said,fishnet.net[i][3]),
               get_display_value(show_already_said,fishnet.net[i][4]),
               get_display_value(show_already_said,fishnet.net[i][5]),
               get_display_value(show_already_said,fishnet.net[i][6]),
               get_display_value(show_already_said,fishnet.net[i][7]),
               get_display_value(show_already_said,fishnet.net[i][8]),
               get_display_value(show_already_said,fishnet.net[i][9]));
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


int main() {
    // Init the random seed
    srand(time(NULL));
    char letter[2];
    int index_line;
    printf("Entrez une ligne");
    read_reset_stdin(letter, 2);
    index_line = get_line_index(letter[0]);
    if (index_line != -1) {
        printf("l' index de la ligne est : %d\n", index_line);
    } else {
        printf("Mauvaise saisie de lettre, celle ci doit etre comprise entre A et J");
    }

    struct fishnet_arr fishnet = get_new_fishnet();
    feed_fishnet(&fishnet);
    set_case(&fishnet, 9,0, WATER);
    print_fishnet(fishnet, true);

    return 0;
}
