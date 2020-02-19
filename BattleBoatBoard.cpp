#include "BattleBoatBoard.h"
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

BattleBoatBoard::BattleBoatBoard(unsigned int* boatLengths, unsigned int boatCount)
{
    // TODO: Write the constructor here.
    unsigned int randomInt;
    unsigned int intersects;

    if (boatCount > 10) { boatCount = 10; } //verify boat count isn't over 10, and if it is set boat count to 10

    for (size_t i = 0; i < boatCount; ++i) //forces boat lengths at 0 or over 6 to be 1
    {
        if (boatLengths[i] == 0 && boatLengths[i] >= 6)
        {
            boatLengths[i] = 1;
        }
    }

    this->boatCount = boatCount; //set the object boat count to the correct length

    for (size_t i = 0; i < boatCount; ++i) //create the battle boats in the object boats array
    {
        this->boats[i] = BattleBoat(boatLengths[i]);
    }

    time_t seed; //forces rand to be different everytime
    time(&seed);
    srand(static_cast<unsigned int>(seed));

    for (size_t i = 0; i < boatCount; ++i)
    {
        do
        {
            intersects = 0;

            randomInt = rand() % 10;
            this->boats[i].setStartX(randomInt);
            randomInt = rand() % 10;
            this->boats[i].setStartY(randomInt);
            randomInt = rand() % 2;
            this->boats[i].setVertical(static_cast<bool>(randomInt));

            for (size_t j = 0; j < i; ++j)
            {
                if (this->boats[i].intersects(this->boats[j])) { ++intersects;}
            }

            if (this->boats[i].isVertical())
            {
                if (this->boats[i].getStartY() + this->boats[i].getLength() > 9) { ++intersects; }
            }
            else
            {
                if (this->boats[i].getStartX() + this->boats[i].getLength() > 9) { ++intersects; }
            }
        } while (intersects != 0);
        
    }
}

const BattleBoat* BattleBoatBoard::getBoat(unsigned int x, unsigned int y) const
{
    // TODO: Return a pointer to a boat if one exists at the coordinates (x, y).
    for (size_t i = 0; i < this->boatCount; ++i) 
    {
        if (this->boats[i].isVertical()) 
        {
            if (this->boats[i].getStartX() == x)
            {
                for (size_t j = 0; j < this->boats[i].getLength(); ++j)
                {
                    if ((boats[i].getStartY() + j) == y)
                    {
                        return &boats[i];
                    }
                }
            }
        }

        else
        {
            if (this->boats[i].getStartY() == y)
            {
                for (size_t j = 0; j < this->boats[i].getLength(); ++j)
                {
                    if ((boats[i].getStartX() + j) == x)
                    {
                        return &boats[i];
                    }
                }
            }
        }
    }
    return nullptr;
}

BattleBoat * BattleBoatBoard::getBoat(unsigned int x, unsigned int y)
{
    // TODO: Return a pointer to a boat if one exists at the coordinates (x, y).
    for (size_t i = 0; i < this->boatCount; ++i) 
    {
        if (this->boats[i].isVertical()) 
        {
            if (this->boats[i].getStartX() == x)
            {
                for (size_t j = 0; j < this->boats[i].getLength(); ++j)
                {
                    if ((boats[i].getStartY() + j) == y)
                    {
                        return &boats[i];
                    }
                }
            }
        }

        else
        {
            if (this->boats[i].getStartY() == y)
            {
                for (size_t j = 0; j < this->boats[i].getLength(); ++j)
                {
                    if ((boats[i].getStartX() + j) == x)
                    {
                        return &boats[i];
                    }
                }
            }
        }
    }
    return nullptr;
}
