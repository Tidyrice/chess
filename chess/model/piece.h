#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "coordinate.h"

class Board;

class Piece {
public:
    enum class Colour {
        White,
        Black
    };

    enum class PieceType {
        King,
        Queen,
        Bishop,
        Rook,
        Knight,
        Pawn
    };

    Piece() = delete;
    Piece(Coordinate position, Colour colour, PieceType pieceType, Board* board);

    virtual ~Piece() = default;

    virtual Piece& clone() = 0;

    virtual PieceType getPieceType() = 0;
    virtual std::vector<Coordinate> getValidMoves() = 0;
    virtual bool makeMove(Coordinate dest) = 0;
    virtual bool canTargetSquare(Coordinate square) = 0;
private:
    PieceType pieceType;
protected:
    Coordinate position;
    Colour colour;
    Board* board;
};

#endif
