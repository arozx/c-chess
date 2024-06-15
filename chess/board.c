#include <stdio.h>
#include <string.h>
#include "functions.h"

int main()
{
    __int64_t pawn, rook, knight, bishop, queen, king;
    __int64_t white, black;

    // define starting positions
    // read as top left to bottom right
    pawn = 0x00FF00000000FF00ULL; // 8-15 white, 48-55 black
    rook = 0x8100000000000081ULL;
    knight = 0x4200000000000042ULL;
    bishop = 0x2400000000000024ULL;
    queen = 0x0800000000000008ULL;
    king = 0x1000000000000010ULL;

    // define colors, where 1 is a piece and 0 is empty
    white = 0x000000000000FFFFULL;
    black = 0xFFFF000000000000ULL;

    // player turn
    int isWhiteTurn = 1;

    printBoard(pawn, rook, knight, bishop, queen, king, white, black);

    // print number board
    printf("  a b c d e f g h\n");
    for (int i = 0; i < 64; i++)
    {
        printf("%d ", i);
        if (i % 8 == 7)
        {
            printf("\n");
        }
    }

    // Generate moves for a knight on b1
    __int64_t knightMoves = generateMoves('N', white, black, 1, isWhiteTurn);

    // Print moves
    for (int i = 0; i < 64; i++)
    {
        if (knightMoves & (1ULL << i))
        {
            printf("Knight can move to %d\n", i);
        }
    }

    return 0;
}

// Function to find if check
check(__int64_t white, __int64_t black, int isWhiteTurn)
{
    // Find the king
    int whiteKing = 0;
    int blackKing = 0;
    for (int i = 0; i < 64; i++)
    {
        if (white & (1ULL << i))
        {
            if (white & (1ULL << i))
            {
                whiteKing = i;
            }
            else if (black & (1ULL << i))
            {
                blackKing = i;
            }
        }
    }

    // Check if the king is in check
    __int64_t allPieces = white | black;
    __int64_t whiteAttacks = 0;
    __int64_t blackAttacks = 0;
    for (int i = 0; i < 64; i++)
    {
        if (black & (1ULL << i))
        {
            whiteAttacks |= generateMoves('P', white, black, i, isWhiteTurn);
            whiteAttacks |= generateMoves('R', white, black, i, isWhiteTurn);
            whiteAttacks |= generateMoves('N', white, black, i, isWhiteTurn);
            whiteAttacks |= generateMoves('B', white, black, i, isWhiteTurn);
            whiteAttacks |= generateMoves('Q', white, black, i, isWhiteTurn);
            whiteAttacks |= generateMoves('K', white, black, i, isWhiteTurn);
        }
        else if (white & (1ULL << i))
        {
            blackAttacks |= generateMoves('p', white, black, i, isWhiteTurn);
            blackAttacks |= generateMoves('r', white, black, i, isWhiteTurn);
            blackAttacks |= generateMoves('n', white, black, i, isWhiteTurn);
            blackAttacks |= generateMoves('b', white, black, i, isWhiteTurn);
            blackAttacks |= generateMoves('q', white, black, i, isWhiteTurn);
            blackAttacks |= generateMoves('k', white, black, i, isWhiteTurn);
        }
    }

    if (whiteAttacks & (1ULL << blackKing))
    {
        printf("Black is in check\n");
    }
    else if (blackAttacks & (1ULL << whiteKing))
    {
        printf("White is in check\n");
    }

    // Check if the king is in checkmate or stalemate
    int whiteMoves = 0;
    int blackMoves = 0;
    for (int i = 0; i < 64; i++)
    {
        if (white & (1ULL << i))
        {
            whiteMoves += generateMoves('P', white, black, i, isWhiteTurn) != 0;
            whiteMoves += generateMoves('R', white, black, i, isWhiteTurn) != 0;
            whiteMoves += generateMoves('N', white, black, i, isWhiteTurn) != 0;
            whiteMoves += generateMoves('B', white, black, i, isWhiteTurn) != 0;
            whiteMoves += generateMoves('Q', white, black, i, isWhiteTurn) != 0;
            whiteMoves += generateMoves('K', white, black, i, isWhiteTurn) != 0;
        }
        else if (black & (1ULL << i))
        {
            blackMoves += generateMoves('p', white, black, i, isWhiteTurn) != 0;
            blackMoves += generateMoves('r', white, black, i, isWhiteTurn) != 0;
            blackMoves += generateMoves('n', white, black, i, isWhiteTurn) != 0;
            blackMoves += generateMoves('b', white, black, i, isWhiteTurn) != 0;
            blackMoves += generateMoves('q', white, black, i, isWhiteTurn) != 0;
            blackMoves += generateMoves('k', white, black, i, isWhiteTurn) != 0;
        }
    }

    if (whiteAttacks & (1ULL << blackKing))
    {
        printf("Black is in check\n");
        if (blackMoves == 0)
        {
            printf("Black is in checkmate\n");
        }
    }
    else if (blackAttacks & (1ULL << whiteKing))
    {
        printf("White is in check\n");
        if (whiteMoves == 0)
        {
            printf("White is in checkmate\n");
        }
    }
    else if (whiteMoves == 0 || blackMoves == 0)
    {
        printf("Stalemate\n");
    }
    return 0;
}
