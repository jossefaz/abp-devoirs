#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define TOUCHED 'X'
#define WATER 'o'
#define PRISTINE '.'
#define FISHNET_SIZE 10
#define LINES ((char const[]){'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'})

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

void print_fishnet(struct fishnet_arr fishnet, bool show_already_said) {
    printf("___|  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  | \n");
    for (int i = 0; i < FISHNET_SIZE; ++i) {
        printf("%c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  | \n", LINES[i],
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



int get_line(char letter) {
    char upper_letter = toupper(letter);
    int lines_length = sizeof(LINES) / sizeof(char);
    for (int i = 0; i < lines_length; ++i) {
        if(LINES[i] == upper_letter )  {
            return i;
        }
    }
    return -1;
}


int main() {
    char letter[2];
    int index_line;
    printf("Entrez une ligne");
    read_reset_stdin(letter, 2);
    index_line = get_line(letter[0]);
    if (index_line != -1) {
        printf("l' index de la ligne est : %d\n", index_line);
    } else {
        printf("Mauvaise saisie de lettre, celle ci doit etre comprise entre A et J");
    }

    struct fishnet_arr fishnet = get_new_fishnet();
    set_case(&fishnet, 9,0, WATER);
    print_fishnet(fishnet, true);

    return 0;
}
