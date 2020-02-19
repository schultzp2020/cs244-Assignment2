#pragma once
#include "BattleBoatBoard.h"

// A class for maintaining the state of a game of BattleBoats.
// This includes the board (i.e. the collection of boats and their hit status) but also the number of turns that have been taken.
// This class provides functionality for taking shots at the board (updating the turn counter accordingly), and also for counting the number of boats that have been sunk.
class BattleBoatsGame
{
public:
    // Initialize using a board that has already been set up
    BattleBoatsGame(BattleBoatBoard& board) : board { board }
    {
    }

    // Get the total number of boats
    unsigned int getBoatCount() const
    {
        return board.getBoatCount();
    }

    // Get the number of turns that the player has taken.
    unsigned int getTurnCount() const
    {
        return turnCount;
    }

    const bool isHit(unsigned int x, unsigned int y) const
    {
        const BattleBoat* boat = board.getBoat(x, y);
        return boat && board.getBoat(x, y)->isHit(x, y);
    }

    const bool isRevealed(unsigned int x, unsigned int y) const;

    // Take a shot at an (x,y) coordinate
    // Returns true if it was a hit; false if it was a miss
    bool shot(unsigned int x, unsigned int y);

    // Get the number of boats that have been sunk
    unsigned int getBoatsSunk() const;

private:
    // The board containing the actual positions of all the boats
    BattleBoatBoard& board;

    // Keep track of the number of turns that the player has taken.
    unsigned int turnCount = 0;

    // Add any other private variables you need here.

    // The revealed board
    bool revealedArray[10][10] { false };

};

// Print the board, revealing only hit and miss locations
inline std::ostream& operator << (std::ostream& out, const BattleBoatsGame& game)
{
    out << "  ";
    for (int i = 0; i < BattleBoatBoard::BOARD_SIZE; i++)
    {
        out << " " << i << " ";
    }
    out << std::endl;

    for (int j = 0; j < BattleBoatBoard::BOARD_SIZE; j++)
    {
        out << j << " ";
        for (int i = 0; i < BattleBoatBoard::BOARD_SIZE; i++)
        {
            if (!game.isRevealed(i, j))
            {
                // "Fog of war": unrevealed square
                out << "~~~";
            }
            else
            {
                if (game.isHit(i, j))
                {
                    // Just print a hit marker to avoid revealing what part of the boat was hit.
                    out << " X ";
                }
                else
                {
                    // Previous miss
                    out << "   ";
                }
            }
        }
        out << std::endl;
    }

    return out;
}
