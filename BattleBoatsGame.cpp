#include "BattleBoatsGame.h"
#include "BattleBoat.h"
#include <iostream>
using namespace std;

const bool BattleBoatsGame::isRevealed(unsigned int x, unsigned int y) const
{
    // TODO: implement this function
    if (x > 9 || y > 9) { return false; }

    return this->revealedArray[x][y];
}

bool BattleBoatsGame::shot(unsigned int x, unsigned int y)
{
    // TODO: implement this function
    this->turnCount++;

    if (x > 9 || y > 9) { return false; }

    this->revealedArray[x][y] = true;

    for (size_t i = 0; i < this->getBoatCount(); ++i)
    {
        if(this->board.getBoats()[i].isHitable(x, y))
        {
            this->board.getBoats()[i].hit(x, y);
            return true;
        }
    }

    return false;
}

unsigned int BattleBoatsGame::getBoatsSunk() const
{
    // TODO: implement this function
    unsigned int count{ 0 };

    for (size_t i = 0; i < this->getBoatCount(); ++i)
    {
        if (this->board.getBoats()[i].isSunk())
        {
            count++;
        }
    }
    return count;
}
