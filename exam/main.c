
/*****************************************************************************/
/*  Licence informatique EXAMEN Module ABP PARTIE II
 *  Etudiant : Regis Azoulay
 *  Ce qui fonctionne :
 *     1 - Propose a l'utilisateur les possibilités
 *     2 - Fait un choix qleqtoire pour l'ordinqteur
 *     3 - Verifie qui a gagné
 *  Ce qui ne fonctionne toujours pas :
 *     - Probleme de sasie de chiffre pour le nombre de manche : jùobtiens une erreur de segmentqtion
 *     Du coup j'ai commenté ce code et mis une valeur de manche par defaut dans les macros. En debuggant je pense que
 *     je serais parvenu a bien initialiser le pointeur et le buffer mais j ai été pris a court
 *
 *
 *  */
/*****************************************************************************/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define POSS_NUMBER 5
#define POSSIBILITIES ((char *[]){ "scissors", "paper", "rock", "lizard", "spock" })
#define PAPER "paper"
#define ROCK "rock"
#define SCISSOR "scissors"
#define LIZARD "lizard"
#define SPOCK "spock"
#define NOMBREMANCHE 2


int is_input_valid(char user_input[]) {
    int possibilities_size = sizeof(POSSIBILITIES)/sizeof(POSSIBILITIES[0]);
    int i;
    for(i = 0; i < possibilities_size; ++i)
    {
        if(!strcmp(POSSIBILITIES[i], user_input))
        {
            return 1;
        }
    }
    return 0;
}

int get_computer_choice() {
    return rand() % (POSS_NUMBER + 1);
}

int read_reset_stdin(char s[], int maxlen) {
    int len_s;
    fgets(s, maxlen, stdin);
    len_s = strlen(s);
    if(s[len_s - 1] == '\n') {
        s[len_s - 1] = '\0';
        len_s -= 1;
    }
    rewind(stdin);
    return len_s;
}

int is_digit(char str[]) {
    size_t length_of_input = strlen(str);
    int is_digit=0;
    if (length_of_input > 0)
    {
        is_digit=1;
        for (int i = 0; i < length_of_input; ++i)
        {
            if (!isdigit(str[i]))
            {
                is_digit=0;
                break;
            }
        }
    }
    return is_digit;
}

void display_possibilities() {
    printf("Vous pouvez choisir entre toutes ces possibilite");
    for (int i = 0; i < POSS_NUMBER; ++i) {
        printf("- %s \n", POSSIBILITIES[i] );
    }
}



int str_to_int(char str[]) {
    return (int)strtol(str, (char **)NULL, 10);
}

int user_won(char* computer_choice, char* should_be) {
    if(!strcmp(computer_choice, should_be)) {
        return 1;
    }
    return 0;
}

int user_is_winner(char* computer_choice, char* user_choice) {
    if (!strcmp(user_choice, computer_choice)) {
        return 2;
    }
    if (!strcmp(user_choice, SCISSOR))
    {
        return user_won(computer_choice, PAPER);
    }
    else if (!strcmp(user_choice, PAPER))
    {
        return user_won(computer_choice, ROCK);
    }
    else if (!strcmp(user_choice, ROCK))
    {
        return user_won(computer_choice, LIZARD);
    }
    else if (!strcmp(user_choice, LIZARD))
    {
        return user_won(computer_choice, SPOCK);
    }
    else if (!strcmp(user_choice, SPOCK))
    {
        return user_won(computer_choice, SCISSOR);
    }

}


int main() {
    // On instancie un flux permettant de randomiser
    srand(time(NULL));
//    char * try_number_char = "";
    int user_win = 0;
    int computer_win = 0;

//    do {
//        printf("Entrez le nombre de manche souhaite entre 2 et 5\n ");
//        read_reset_stdin(try_number_char, 2);
//    } while (!is_digit(try_number_char) && (str_to_int(try_number_char) >= 2 && str_to_int(try_number_char) <= 5));

   // ICi j ai eu un souci pour fqir choisir le no;bre de manche a l utilisateur
   // Du coup j ai initialise une macro definition a la place du code precedent que j ai neutralise du coup
   // Il me semble que je serqis parvenu a trouver mon erreur en debuggant un peu mais j ai ete pris par le temps
    int try_number = NOMBREMANCHE;

    for (int i = 0; i < try_number; ++i) {
        char* computer_choice = POSSIBILITIES[get_computer_choice()];
        char user_choice[8];
        do {
            printf("Entrez une des possibilites\n ");
            display_possibilities();
            read_reset_stdin(user_choice, 8);
        } while (!is_input_valid(user_choice));
        if(user_is_winner(computer_choice,user_choice) == 2) {
            user_win+=1;
            printf("L'ordinateur a choisi %s : C'est un ex-aquo\n", computer_choice);
        } else if (user_is_winner(computer_choice,user_choice)) {
            user_win+=1;
            printf("L'ordinateur a choisi %s : Vous avez gagne la manche\n", computer_choice);
        } else {
            computer_win+=1;
            printf("L'ordinateur a choisi %s : L'ordinateur a gagné cette manche\n", computer_choice);
        }
    }

    if (user_win > computer_win) {
        printf("Vous avez gagné la partie !!");
    } else {
        printf("L'ordinateur a gagné la partie !!");
    }

    return 0;
}

