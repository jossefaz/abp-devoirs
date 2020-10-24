# PROGRAMME Exercice1;
# VARIABLE 
#     A : ENTIER;
#     B : ENTIER;
#     C : ENTIER;
# DEBUT
#     ECRIRE ('Entrez la valeur de A : ');
#     LIRE(A);
#     ECRIRE ('Entrez la valeur de B : ');
#     LIRE(B);
#     ECRIRE ('Entrez la valeur de C : ');
#     LIRE(C);

a = input("enter a")
b = input("enter b")
c = input("enter c")

#     TANT QUE( (A == B) ET (B == C) ) FAIRE
#         ECRIRE ('Erreur de saisie : les nombres en entrée doivent être differents !')
#         ECRIRE ('Entrez la valeur de A : ');
#         LIRE(A);
#         ECRIRE ('Entrez la valeur de B : ');
#         LIRE(B);
#         ECRIRE ('Entrez la valeur de C : ');
#         LIRE(C);
#     FAIT;


#     SI ((A < B) ET (A < C)) 
if a<b:
    if a<c :
        print("la plus petite valeur est a")
    else :
        print("la plus petite valeur est c")
elif b<c:
    print("la plus petite valeur est b")
else :
    print("la plus petite valeur est c")
    
    
#     ALORS
#         ECRIRE ('La plus petite valeur est A');
#     SINON
#         SI ((B < A) ET (B < C))
#         ALORS
#             ECRIRE ('La plus petite valeur est B');
#         SINON
#             ECRIRE ('La plus petite valeur est C');
#         FIN SI;
#     FIN SI;
# FIN;
