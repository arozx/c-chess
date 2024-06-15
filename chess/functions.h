#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void printBoard(unsigned long long pawn, unsigned long long rook, unsigned long long knight, unsigned long long bishop, unsigned long long queen, unsigned long long king, unsigned long long white, unsigned long long black);

// piece moves
unsigned long long generateMoves(char piece, unsigned long long whitePieces, unsigned long long blackPieces, int square, int isWhiteTurn);

#endif // FUNCTIONS_H
