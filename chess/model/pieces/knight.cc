#include "knight.h"
#include "../board.h"
#include <utility>

Knight::Knight(Coordinate::Coordinate position, Colour colour, Board* board):
    PieceClonable{position, colour, Piece::PieceType::Knight, board} {}

std::vector<Coordinate::Coordinate> Knight::getValidMoves() const {
    std::vector<Coordinate::Coordinate> validMoves;

    std::vector<std::pair<int, int>> directions = {{
        {1, 2},
        {1, -2},
        {-1, 2},
        {-1, -2},
        {2, 1},
        {2, -1},
        {-2, 1},
        {-2, -1},
    }};

    for (const auto& dir : directions) {
        int dRow = dir.first;
        int dCol = dir.second;
        Coordinate::Coordinate nextPos{position.row + dRow, position.col + dCol};

        if (!Coordinate::checkBounds(nextPos, board->getBoardDimension())) {
            continue; //unable to move in this direction (edge of board)
        }

        std::unique_ptr<Piece> targetPiece = board->getPiece(nextPos);
        bool canCapture = targetPiece && targetPiece->getColour() != this->getColour();
        bool canMove = !targetPiece || canCapture;

        if (canMove) {
            validMoves.push_back(nextPos);
        }
    }

    return validMoves;
}
