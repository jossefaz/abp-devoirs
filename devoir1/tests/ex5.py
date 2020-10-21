# PROGRAMME Exercice4_POUR;

# VARIABLE
#     N : ENTIER;
#     FACT : ENTIER;
# DEBUT
#     ECRIRE ('Entrez la valeur de N : ');
#     LIRE(N);

#     TANT QUE (NON ENTIER(N) OU N <= 0) FAIRE 
#         ECRIRE ('Erreur de saisie : "N" DOIT etre un entier positif, veuillez ressaisir');
#         LIRE(N);
    
#     SI (N == 1 )
#     ALORS 
#         FACT <- 1;
#     SINON
#         FACT <- 1;
#         POUR I VARIANT DE 1 A N FAIRE
#             FACT <- FACT * I;
#         FAIT;
#     ECRIRE('La factorielle de ' & CHAINE DE CARACTER(N) & ' est de : ' & CHAINE DE CARACTER(FACT));
# FIN;

n = input('valeur de N : ')
fact = 1

while not n.isdigit():
    n = input('Erreur de saisie : "N" DOIT etre un entier positif, veuillez ressaisir : ')
n = int(n)
if n != 1 :
    for i in range(1, n+1) :
        fact = fact * i

print("la factorielle de {} est de : {}".format(n, fact))

n = input('valeur de N : ')
fact = 1

while not n.isdigit():
    n = input('Erreur de saisie : "N" DOIT etre un entier positif, veuillez ressaisir : ')
n = int(n)
if n != 1 :
    i = 1
    while i <= n :
        fact = fact * i
        i += 1


print("la factorielle de {} est de : {}".format(n, fact))
