# PROGRAMME Exercice2;
# VARIABLE
#     A : ENTIER;
#     B : ENTIER;
#     C : ENTIER;
#     MAX : ENTIER;
#
# ECRIRE ('Entrez la valeur de A : ');
a = int( input('Entrez la valeur de A : '))
# LIRE(A);
# ECRIRE ('Entrez la valeur de B : ');
b = int(input('Entrez la valeur de B : '))
# LIRE(B);
# ECRIRE ('Entrez la valeur de C : ');
# LIRE(C);
c = int(input('Entrez la valeur de C : '))


#
# TANT QUE( (A == B) ET (B == C) ) FAIRE
#     ECRIRE ('Erreur de saisie : les nombres en entrée doivent être differents !')
#     ECRIRE ('Entrez la valeur de A : ');
#     LIRE(A);
#     ECRIRE ('Entrez la valeur de B : ');
#     LIRE(B);
#     ECRIRE ('Entrez la valeur de C : ');
#     LIRE(C);
# FAIT;
#
# MAX <- A;
max = a
# SI B > MAX
if b > max :
    max = b 
if c > max :
    max = c 
print("la plus grande valeur est {}".format(max))
# ALORS
#     MAX <- B;
# FIN SI;
# SI C > MAX
# ALORS
#     MAX <- C;
# FIN SI;
# ECRIRE ('La plus grande valeur est : ' & CHAINE_DE_CARACTERE(MAX));
# FIN PROGRAMME;

