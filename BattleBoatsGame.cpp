#include "BattleBoatsGame.h"
#include "BattleBoat.h"
#include <iostream>
using namespace std;

const bool BattleBoatsGame::isRevealed(unsigned int x, unsigned int y) const
{
    // TODO: implement this function
    if (x > 9 || y > 9) { return false; } //returns false if the (x,y) coordinate is out of bounds

    return this->revealedArray[x][y]; //returns true if the (x,y) coordinate has been shot at or false if the (x,y) coordinate has not been shot at
}

bool BattleBoatsGame::shot(unsigned int x, unsigned int y)
{
    // TODO: implement this function
    this->turnCount++; //increment turn count

    if (x > 9 || y > 9) { return false; } //returns false if the (x,y) coordinate is out of bounds

    this->revealedArray[x][y] = true; //sets the (x,y) coordinate to true

    for (size_t i = 0; i < this->getBoatCount(); ++i) //iterates through every boat
    {
        if(this->board.getBoats()[i].isHitable(x, y)) //checks to see if a boat exists at the (x,y) coordinate
        {
            this->board.getBoats()[i].hit(x, y); //hits a boat if the boat is hitable
            return true; //returns true after a hit on a boat
        }
    }

    return false; //returns false if the shot did not hit a boat
}

unsigned int BattleBoatsGame::getBoatsSunk() const
{
    // TODO: implement this function
    unsigned int count{ 0 };

    for (size_t i = 0; i < this->getBoatCount(); ++i) //iterates through every boat
    {
        if (this->board.getBoats()[i].isSunk()) //counts how many boats have been sunk
        {
            count++; //increments how many boats have been sunk
        }
    }
    return count; //returns how many boats have been sunk
}
