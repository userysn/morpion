#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PLAYER 'X'
#define COMPUTER 'O'

// Fonction pour initialiser le plateau de jeu
void initialise_plateau(char plateau[9])
{
    for (int i = 0; i < 9; i++)
    {
        plateau[i] = '1' + i;
    }
}

// Fonction pour afficher le plateau de jeu
void affiche_plateau(char plateau[9])
{
    printf("\n");
    for (int i = 0; i < 9; i++)
    {
        if (i > 0 && i % 3 == 0)
        {
            printf("\n-----\n");
        }
        printf("%c ", plateau[i]);
        if (i % 3 < 2)
        {
            printf("| ");
        }
    }
    printf("\n\n");
}

// Fonction pour vérifier si quelqu'un a gagné et retourne le caractère du gagnant
char a_un_gagnant(char plateau[9])
{
    int conditions_de_victoire[8][3] = 
    {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // lignes
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8}, // colonnes
        {0, 4, 8},
        {2, 4, 6} // diagonales
    };

    for (int i = 0; i < 8; i++)
    {
        if (plateau[conditions_de_victoire[i][0]] == plateau[conditions_de_victoire[i][1]] &&
            plateau[conditions_de_victoire[i][1]] == plateau[conditions_de_victoire[i][2]])
        {
            return plateau[conditions_de_victoire[i][0]];
        }
    }

    return 0; // Retourne 0 si personne n'a gagné
}

// Fonction pour vérifier s'il y a match nul
bool est_match_nul(char plateau[9])
{
    for (int i = 0; i < 9; i++)
    {
        if (plateau[i] != PLAYER && plateau[i] != COMPUTER)
        {
            return false; // S'il reste des cases non occupées, ce n'est pas un match nul
        }
    }
    return true; // Si toutes les cases sont occupées et qu'il n'y a pas de gagnant, c'est un match nul
}

// Fonction pour effectuer le mouvement du joueur
void mouvement_joueur(char plateau[9])
{
    int choix;
    do
    {
        printf("Choisissez une case (1-9) : ");
        scanf("%d", &choix);
        choix--; // Ajuster pour l'index du tableau
    } while (choix < 0 || choix >= 9 || plateau[choix] == PLAYER || plateau[choix] == COMPUTER);

    plateau[choix] = PLAYER;
}

// Fonction pour effectuer le mouvement de l'ordinateur (très basique)
void mouvement_ordinateur(char plateau[9])
{
    int choix;
    do
    {
        choix = rand() % 9; // Choix aléatoire
    } while (plateau[choix] == PLAYER || plateau[choix] == COMPUTER);

    plateau[choix] = COMPUTER;
}

int main()
{
    char plateau[9];
    char gagnant = 0;
    bool match_nul = false;

    initialise_plateau(plateau);
    affiche_plateau(plateau);

    while (true)
    {
        mouvement_joueur(plateau);
        affiche_plateau(plateau);
        gagnant = a_un_gagnant(plateau);
        if (gagnant || (match_nul = est_match_nul(plateau)))
        {
            break;
        }

        mouvement_ordinateur(plateau);
        affiche_plateau(plateau);
        gagnant = a_un_gagnant(plateau);
        if (gagnant || (match_nul = est_match_nul(plateau)))
        {
            break;
        }
    }

    if (gagnant)
    {
        printf("Le gagnant est %c!\n", gagnant);
    }
    else if (match_nul)
    {
        printf("Match nul!\n");
    }

    return 0;
}
