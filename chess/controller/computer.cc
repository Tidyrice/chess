#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <random>
#include "computer.h"
#include "../model/board.h"
#include "../shared/colour.h"
#include "../shared/coordinate.h"

std::mt19937 ComputerPlayer::rng{std::random_device{}()};

ComputerPlayer::ComputerPlayer(Board* board, Colour colour, int level)
    : Player{board, colour}, level(level) {}

ComputerPlayer::ComputerPlayer(Board* board, Colour colour)
    : Player{board, colour}, level(0) {
        std::cout << "Choose level for " << (colour == Colour::Black ? "black" : "white") << " AI opponent: ";
        while (level < 1 || level > 4)
        {
            std::cin >> level;
        }
    }

bool ComputerPlayer::takeTurn() {
    if (colour == Colour::White) {
        std::cout << "White's turn: ";
    }
    else {
        std::cout << "Black's turn: ";
    }

    bool turnTaken;

    switch (level)
    {
    case 4:
        turnTaken = levelFour();
        break;
    case 3:
        turnTaken = levelThree();
        break;
    case 2:
        turnTaken = levelTwo();
        break;
    default:
        turnTaken = levelOne();
        break;
    }

    return turnTaken;
}

bool ComputerPlayer::levelOne() {
    std::unique_ptr<Piece> **pieces = board->cloneBoard();
    std::vector<std::unique_ptr<Piece>> myPieces {};

    for (int i = 0; i < board->getBoardDimension(); ++i) {
        for (int j = 0; j < board->getBoardDimension(); ++j) {
            if (pieces[i][j] != nullptr && pieces[i][j]->getColour() == colour) {
                myPieces.push_back(std::move(pieces[i][j]));
            }
        }
    }

    while (myPieces.size() > 0)
    {
        int randPiece = std::uniform_int_distribution<int>(0, myPieces.size() - 1)(rng);

        std::vector<Coordinate::Coordinate> validMoves = myPieces[randPiece]->getValidLegalMoves();

        if (validMoves.size() == 0) {
            myPieces.erase(myPieces.begin() + randPiece);
            continue;
        }

        int randMove = std::uniform_int_distribution<int>(0, validMoves.size() - 1)(rng);

        bool turnTaken = board->takeTurn(myPieces[randPiece]->getPosition(), validMoves[randMove], colour);

        std::cout << "move " << Coordinate::cartesianToChess(myPieces[randPiece]->getPosition()) << " "
            << Coordinate::cartesianToChess(validMoves[randMove]) << std::endl;

        if (turnTaken)
            return true;
    }

    return false;
}

bool ComputerPlayer::levelTwo() {
    std::unique_ptr<Piece> **pieces = board->cloneBoard();
    std::vector<std::unique_ptr<Piece>> myPieces {};

    for (int i = 0; i < board->getBoardDimension(); ++i) {
        for (int j = 0; j < board->getBoardDimension(); ++j) {
            if (pieces[i][j] != nullptr && pieces[i][j]->getColour() == colour) {
                myPieces.push_back(std::move(pieces[i][j]));
            }
        }
    }

    std::vector<ChessMove> moves = {};

    for (auto& piece : myPieces) {
        std::vector<Coordinate::Coordinate> validMoves = piece->getValidLegalMoves();

        for (auto& coord : validMoves) {
            std::unique_ptr<Piece> enemy = board->getPiece(coord);
            moves.push_back(ChessMove{piece->getPosition(), coord, (enemy == nullptr ? 0 : enemy->toValue())});
        }
    }

    std::shuffle(moves.begin(), moves.end(), rng);

    std::sort(moves.begin(), moves.end(), [](const ChessMove& a, const ChessMove& b) {
        return a.point < b.point;
    });

    while (moves.size() > 0) {
        bool turnTaken = board->takeTurn(moves.back().from, moves.back().to, colour);

        std::cout << "move " << Coordinate::cartesianToChess(moves.back().from) << " "
            << Coordinate::cartesianToChess(moves.back().to) << std::endl;

        if (turnTaken)
            return true;

        moves.pop_back();
    }

    return false;
}

bool ComputerPlayer::levelThree() {
    return false;
}

bool ComputerPlayer::levelFour() {
    return false;
}
