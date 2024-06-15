#include <stdio.h>
#include "functions.h"

void printBoard(unsigned long long pawn, unsigned long long rook, unsigned long long knight, unsigned long long bishop, unsigned long long queen, unsigned long long king, unsigned long long white, unsigned long long black)
{
    // print the board with the pieces white is capital, black is lowercase
    printf("  a b c d e f g h\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", 8 - i);
        for (int j = 0; j < 8; j++)
        {
            int square = (7 - i) * 8 + j;
            if (pawn & (1ULL << square))
            {
                if (white & (1ULL << square))
                {
                    printf("P ");
                }
                else
                {
                    printf("p ");
                }
            }
            else if (rook & (1ULL << square))
            {
                if (white & (1ULL << square))
                {
                    printf("R ");
                }
                else
                {
                    printf("r ");
                }
            }
            else if (knight & (1ULL << square))
            {
                if (white & (1ULL << square))
                {
                    printf("N ");
                }
                else
                {
                    printf("n ");
                }
            }
            else if (bishop & (1ULL << square))
            {
                if (white & (1ULL << square))
                {
                    printf("B ");
                }
                else
                {
                    printf("b ");
                }
            }
            else if (queen & (1ULL << square))
            {
                if (white & (1ULL << square))
                {
                    printf("Q ");
                }
                else
                {
                    printf("q ");
                }
            }
            else if (king & (1ULL << square))
            {
                if (white & (1ULL << square))
                {
                    printf("K ");
                }
                else
                {
                    printf("k ");
                }
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");
    }
}
