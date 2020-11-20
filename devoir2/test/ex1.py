# PROCEDURE RechercheIndiceMiniMaxi (VARIABLE TAB:TYPTAB, 
#                                     IND1:ENTIER, 
#                                     IND2:ENTIER, 
#                                     VARIABLE INDMINI:ENTIER, 
#                                     VARIABLE INDMAXI:ENTIER );
def RechercheIndiceMiniMaxi(liste, ind1, ind2, indmini, indmaxi):
    """
    docstring
    """
    indmini = ind1
    indmaxi = ind2

    for i in range(ind1, ind2) :
        if liste[i] > liste[indmaxi]:
            indmaxi = i
        if liste[i] < liste[indmini]:
            indmini = i
    
    return [indmini, indmaxi]



# DEBUT {RechercheIndiceMiniMaxi}
#     INDMINI <- IND1 ;
#     INDMAXI <- IND1 ;
#     POUR I VARIANT DE IND1 A IND2 FAIRE
#         SI (TAB[I] > TAB[INDMAXI])
#         ALORS
#             INDMAXI <- I ;
#         FIN SI;
#         SI (TAB[I] < TAB[INDMINI])
#         ALORS
#             INDMINI <- I;
#         FIN SI ;
#     FAIT ;
#     RENVOYER INDMINI, INDMAXI ;
# FIN; {RechercheIndiceMiniMaxi}

def Tri(liste, taille) :
    indmini = 0
    inmaxi = 0
    ind1 = 0
    ind2 = taille
    temp = 0
    for i in range(0, taille):
        indmini, inmaxi = RechercheIndiceMiniMaxi(liste, ind1, ind2, indmini, inmaxi)
        temp = liste[ind1]
        liste[ind1] = liste[indmini]
        liste[indmini] = temp

        temp = liste[ind2]
        liste[ind2] = liste[inmaxi]
        liste[inmaxi] = temp

        ind1 += 1
        ind2 -= 1
    return liste

print(Tri([55,2,45,9,4,78,5,89], 7))

# PROCEDURE Tri (VARIABLE TAB:TYPTAB, DIM:ENTIER);
# VARIABLE 
#     INDMINI:ENTIER;
#     INDMAXI:ENTIER;
#     IND1:ENTIER;
#     IND2:ENTIER; 
#     TEMP:ENTIER;
# DEBUT {Tri}

#     IND1<-1;
#     IND2<-DIM; 

#     POUR I VARIANT DE 1 A DIM FAIRE

#         INDMINI, INDMAXI <- RechercheIndiceMiniMaxi(TAB, IND1, IND2, INDMINI, INDMAXI);

#         TEMP <- TAB[IND1];
#         TAB[IND1] = TAB[INDMINI];
#         TAB[INDMINI] = TEMP;

#         TEMP <- TAB[IND2];
#         TAB[IND2] = TAB[INDMAXI];
#         TAB[INDMAXI] = TEMP;

#         IND1 <- IND1 + 1;
#         IND2 <- IND2 - 1;
#     FAIT;
# FIN; {Tri}
