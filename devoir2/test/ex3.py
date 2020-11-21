####### Question 1 #######

# FONCTION CalculDizaine (NB:ENTIER) : ENTIER;
# VARIABLE
#     RESTE : ENTIER;
# DEBUT {CalculDizaine}
#     RESTE <- NB MOD 10;
#     RENVOYER (NB - RESTE) / 10;
# FIN; {CalculDizaine}

def CalculDizaine(nb):
    reste = nb % 10
    return (nb - reste) / 10

####### Question 2 #######


def Transformation(tableau, len_tableau, matrice):
    nbcol = 0
    ligne_dizaine = 0
    temp_sup = 0
    temp_inf = 0

    nbcol = int(len_tableau / 5)

    for i in range(0, len_tableau):

        ligne_dizaine = int(CalculDizaine(tableau[i]))
        temp_sup = tableau[i]
        affeted = False
        for j in range(0, nbcol):
            if matrice[ligne_dizaine][j] != 50 and affeted == False:
                if temp_sup < matrice[ligne_dizaine][j]:
                    temp_inf = temp_sup
                    temp_sup = matrice[ligne_dizaine][j]
                    matrice[ligne_dizaine][j] = temp_inf
            else:
                if affeted == False:
                    matrice[ligne_dizaine][j] = temp_sup
                    affeted = True

        pass
    print(mat)


mat = [
    [50, 50, 50],
    [50, 50, 50],
    [50, 50, 50],
    [50, 50, 50],
    [50, 50, 50]
]

tab = [43, 19, 10, 5, 8, 41, 31, 15, 21, 48, 24, 36, 37, 9, 22]

Transformation(tab, len(tab), mat)

# PROCEDURE Transformation (TAB:TYPTAB, DIM:ENTIER, VARIABLE MAT:TYPEMAT);
# VARIABLE
#     NBCOL : ENTIER;
#     LIGNE_DIZAINE : ENTIER;
#     TEMP_SUP : ENTIER;
#     TEMP_INF : ENTIER;
#     I,J,K : ENTIER;
# DEBUT {Transformation}
#     NBCOL <- DIM / 5;
#     POUR I VARIANT DE 1 A DIM FAIRE
#         LIGNE_DIZAINE <- CalculDizaine(TAB [I]);
#         TEMP_SUP <- TAB[I];
#         POUR J VARIANT DE 0 A NBCOL FAIRE
#             SI (MAT[LIGNE_DIZAINE, J] != 50)
#             ALORS
#                 SI (TEMP_SUP < MAT[LIGNE_DIZAINE, J])
#                 ALORS
#                     TEMP_INF <- TEMP_SUP;
#                     TEMP_SUP <- MAT[LIGNE_DIZAINE, J];
#                     MAT[LIGNE_DIZAINE, J] <- TEMP_INF;
#                 FIN SI;
#                 TEMP <- MAT[LIGNE_DIZAINE, J];
#             SINON
#                 MAT[LIGNE_DIZAINE, J] <- TEMP_SUP;
#             FIN SI;
#         FAIT;
#     FAIT;
# FIN; {Transformation}
