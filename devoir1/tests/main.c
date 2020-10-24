#include <stdio.h>


int main() {
    int n;
    char c;
    printf("Entrer la valeur de n\n");
    scanf("%d", &n);
    scanf("%c", &c);
    printf("entrer la valeur de c");
    scanf("%c", &c);
    printf("Apres saisie , n=%d, code ASCII de c : %d", n,c);
    return 0;
}
