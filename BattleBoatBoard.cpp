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
    unsigned int error;

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

    //forces rand to be different everytime
    time_t seed; 
    time(&seed);
    srand(static_cast<unsigned int>(seed));

    for (size_t i = 0; i < boatCount; ++i)  //iterates through every boat
    {
        do
        {
            error = 0;

            //randomizes the start (x,y) coordinate and if the ship is vertical
            randomInt = rand() % 10; 
            this->boats[i].setStartX(randomInt);
            randomInt = rand() % 10;
            this->boats[i].setStartY(randomInt);
            randomInt = rand() % 2;
            this->boats[i].setVertical(static_cast<bool>(randomInt));

            for (size_t j = 0; j < i; ++j) //test to make sure none of the boats intersect
            {
                if (this->boats[i].intersects(this->boats[j])) { ++error;}
            }

            //tests to make sure the boats length do not go out of bounds
            if (this->boats[i].isVertical()) //test case if "this" is vertical 
            {
                if (this->boats[i].getStartY() + this->boats[i].getLength() > 9) { ++error; }
            }
            else //test case if "this" is not vertical
            {
                if (this->boats[i].getStartX() + this->boats[i].getLength() > 9) { ++error; }
            }
        } while (error != 0); //redo the boat if there is a possible error
        
    }
}

const BattleBoat* BattleBoatBoard::getBoat(unsigned int x, unsigned int y) const
{
    // TODO: Return a pointer to a boat if one exists at the coordinates (x, y).
    for (size_t i = 0; i < this->boatCount; ++i) 
    {
        if (this->boats[i].isVertical()) //test case if "this" boat is vertical
        {
            if (this->boats[i].getStartX() == x)
            {
                for (size_t j = 0; j < this->boats[i].getLength(); ++j)
                {
                    if ((boats[i].getStartY() + j) == y)
                    {
                        return &boats[i]; //returns the boat pointer if a boat exists at the (x,y) coordinate
                    }
                }
            }
        }

        else //test case if "this" boat is not vertical
        {
            if (this->boats[i].getStartY() == y)
            {
                for (size_t j = 0; j < this->boats[i].getLength(); ++j)
                {
                    if ((boats[i].getStartX() + j) == x)
                    {
                        return &boats[i]; //returns the boat pointer if a boat exists at the (x,y) coordinate
                    }
                }
            }
        }
    }
    return nullptr; //returns null pointer if a boat does not exists at the (x,y) coordinate
}

BattleBoat * BattleBoatBoard::getBoat(unsigned int x, unsigned int y)
{
    // TODO: Return a pointer to a boat if one exists at the coordinates (x, y).
    for (size_t i = 0; i < this->boatCount; ++i) 
    {
        if (this->boats[i].isVertical()) //test case if "this" boat is vertical
        {
            if (this->boats[i].getStartX() == x)
            {
                for (size_t j = 0; j < this->boats[i].getLength(); ++j)
                {
                    if ((boats[i].getStartY() + j) == y)
                    {
                        return &boats[i]; //returns the boat pointer if a boat exists at the (x,y) coordinate
                    }
                }
            }
        }

        else //test case if "this" boat is not vertical
        {
            if (this->boats[i].getStartY() == y)
            {
                for (size_t j = 0; j < this->boats[i].getLength(); ++j)
                {
                    if ((boats[i].getStartX() + j) == x)
                    {
                        return &boats[i]; //returns the boat pointer if a boat exists at the (x,y) coordinate
                    }
                }
            }
        }
    }
    return nullptr; //returns null pointer if a boat does not exists at the (x,y) coordinate
}
