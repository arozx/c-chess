#include <stdio.h>
#include "functions.h"

// Function prototypes
unsigned long long generatePawnMoves(unsigned long long pawn, unsigned long long white, unsigned long long black, int square);
unsigned long long generateRookMoves(unsigned long long rook, unsigned long long allPieces, int square);
unsigned long long generateKnightMoves(unsigned long long knight, int square);
unsigned long long generateBishopMoves(unsigned long long bishop, unsigned long long allPieces, int square);
unsigned long long generateQueenMoves(unsigned long long queen, unsigned long long allPieces, int square);
unsigned long long generateKingMoves(unsigned long long king, int square);

// Function to output moves for a selected piece
unsigned long long generateMoves(char piece, unsigned long long whitePieces, unsigned long long blackPieces, int square, int isWhiteTurn)
{
    unsigned long long allPieces = whitePieces | blackPieces;

    if (isWhiteTurn && piece >= 'a' && piece <= 'z')
    {
        return 0; // It's white's turn, but the piece is black. So, no moves.
    }

    if (!isWhiteTurn && piece >= 'A' && piece <= 'Z')
    {
        return 0; // It's black's turn, but the piece is white. So, no moves.
    }

    switch (piece)
    {
    case 'P':
        return generatePawnMoves(whitePieces, whitePieces, blackPieces, square);
    case 'p':
        return generatePawnMoves(blackPieces, whitePieces, blackPieces, square);
    case 'R':
    case 'r':
        return generateRookMoves(whitePieces | blackPieces, allPieces, square);
    case 'N':
    case 'n':
        return generateKnightMoves(whitePieces | blackPieces, square);
    case 'B':
    case 'b':
        return generateBishopMoves(whitePieces | blackPieces, allPieces, square);
    case 'Q':
    case 'q':
        return generateQueenMoves(whitePieces | blackPieces, allPieces, square);
    case 'K':
    case 'k':
        return generateKingMoves(whitePieces | blackPieces, square);
    default:
        return 0;
    }
}

unsigned long long generatePawnMoves(unsigned long long pawn, unsigned long long white, unsigned long long black, int square)
{
    unsigned long long moves = 0;
    if (white & (1ULL << square))
    {
        // White pawn moves
        if (!(pawn & (1ULL << (square + 8))))
        {
            moves |= (1ULL << (square + 8)); // Move forward
            if (square / 8 == 1 && !(pawn & (1ULL << (square + 16))))
            {
                moves |= (1ULL << (square + 16)); // Double move from initial position
            }
        }
        if (black & (1ULL << (square + 7)))
        {
            moves |= (1ULL << (square + 7)); // Capture left
        }
        if (black & (1ULL << (square + 9)))
        {
            moves |= (1ULL << (square + 9)); // Capture right
        }
    }
    else
    {
        // Black pawn moves
        if (!(pawn & (1ULL << (square - 8))))
        {
            moves |= (1ULL << (square - 8)); // Move forward
            if (square / 8 == 6 && !(pawn & (1ULL << (square - 16))))
            {
                moves |= (1ULL << (square - 16)); // Double move from initial position
            }
        }
        if (white & (1ULL << (square - 7)))
        {
            moves |= (1ULL << (square - 7)); // Capture left
        }
        if (white & (1ULL << (square - 9)))
        {
            moves |= (1ULL << (square - 9)); // Capture right
        }
    }
    return moves;
}

unsigned long long generateRookMoves(unsigned long long rook, unsigned long long allPieces, int square)
{
    unsigned long long moves = 0;
    int directions[4] = {8, -8, 1, -1};

    for (int i = 0; i < 4; i++)
    {
        int dir = directions[i];
        int pos = square + dir;
        while (pos >= 0 && pos < 64 && (pos % 8 != 0 || dir != -1) && (pos % 8 != 7 || dir != 1))
        {
            moves |= (1ULL << pos);
            if (allPieces & (1ULL << pos))
            {
                break;
            }
            pos += dir;
        }
    }

    return moves;
}

unsigned long long generateKnightMoves(unsigned long long knight, int square)
{
    unsigned long long moves = 0;
    int knightMoves[8] = {17, 15, 10, 6, -6, -10, -15, -17};

    for (int i = 0; i < 8; i++)
    {
        int pos = square + knightMoves[i];
        if (pos >= 0 && pos < 64)
        {
            moves |= (1ULL << pos);
        }
    }

    return moves;
}

unsigned long long generateBishopMoves(unsigned long long bishop, unsigned long long allPieces, int square)
{
    unsigned long long moves = 0;
    int directions[4] = {9, 7, -9, -7};

    for (int i = 0; i < 4; i++)
    {
        int dir = directions[i];
        int pos = square + dir;
        while (pos >= 0 && pos < 64 && (pos % 8 != 0 || dir != -7) && (pos % 8 != 7 || dir != 9))
        {
            moves |= (1ULL << pos);
            if (allPieces & (1ULL << pos))
            {
                break;
            }
            pos += dir;
        }
    }

    return moves;
}

unsigned long long generateQueenMoves(unsigned long long queen, unsigned long long allPieces, int square)
{
    return generateRookMoves(queen, allPieces, square) | generateBishopMoves(queen, allPieces, square);
}

unsigned long long generateKingMoves(unsigned long long king, int square)
{
    unsigned long long moves = 0;
    int kingMoves[8] = {8, -8, 1, -1, 9, 7, -9, -7};

    for (int i = 0; i < 8; i++)
    {
        int pos = square + kingMoves[i];
        if (pos >= 0 && pos < 64)
        {
            moves |= (1ULL << pos);
        }
    }

    return moves;
}
