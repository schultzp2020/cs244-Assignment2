#include "BattleBoat.h"
#include <algorithm>
using namespace std;

BattleBoat::BattleBoat(unsigned int length) 
    : length { min(MAX_LENGTH, length) }
{
}

unsigned int BattleBoat::getLength() const
{
    return length;
}

unsigned int BattleBoat::getStartX() const
{
    return startX;
}

unsigned int BattleBoat::getStartY() const
{
    return startY;
}

bool BattleBoat::isVertical() const
{
    return vertical;
}

ostream& BattleBoat::printSegment(ostream& out, unsigned int x, unsigned int y) const
{
    if (length == 1)
    {
        // Single cell boat
        out << "<";
        
        if (hits[0])
        {
            out << "X";
        }
        else
        {
            out << "O";
        }

        out << ">";
    }
    else if (vertical)
    {
        if (y == startY)
        {
            // Top end cap
            out << "/";

            if (hits[0])
            {
                out << "X";
            }
            else
            {
                out << "O";
            }

            out << "\\";
        }
        else if (y == startY + length - 1)
        {
            // Bottom end cap
            out << "\\";

            if (hits[length - 1])
            {
                out << "X";
            }
            else
            {
                out << "O";
            }

            out << "/";
        }
        else
        {
            // Middle vertical segment
            out << "|";

            if (hits[y - startY])
            {
                out << "X";
            }
            else
            {
                out << "O";
            }

            out << "|";
        }
    }
    else
    {
        // Left end cap
        if (x == startX)
        {
            out << "<";

            if (hits[0])
            {
                out << "X";
            }
            else
            {
                out << "O";
            }

            out << "=";
        }
        else if (x == startX + length - 1)
        {
            // Right end cap
            out << "=";

            if (hits[length - 1])
            {
                out << "X";
            }
            else
            {
                out << "O";
            }

            out << ">";
        }
        else
        {
            // Middle horizontal segment
            out << "=";

            if (hits[x - startX])
            {
                out << "X";
            }
            else
            {
                out << "O";
            }

            out << "=";
        }
    }

    return out;
}

void BattleBoat::setStartX(unsigned int startX)
{
    this->startX = startX;
}

void BattleBoat::setStartY(unsigned int startY)
{
    this->startY = startY;
}

void BattleBoat::setVertical(bool vertical)
{
    this->vertical = vertical;
}

bool BattleBoat::intersects(const BattleBoat& other) const
{
    if (this->isVertical())
    {
        if (other.isVertical())
        {
            if (this->getStartX() == other.getStartX())
            {
                for (size_t i = 0; i < this->getLength(); ++i)
                {
                    for (size_t j = 0; j < other.getLength(); ++j)
                    {
                        if ((this->getStartY() + i) == (other.getStartY() + j))
                        {
                            return true;
                        }
                    }
                }
            }
        }
        else
        {
            for (size_t i = 0; i < this->getLength(); ++i)
            {
                for (size_t j = 0; j < other.getLength(); ++j)
                {
                    if (this->getStartX() == (other.getStartX() + j))
                    {
                        if ((this->getStartY() + i) == other.getStartY())
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (other.isVertical())
        {
            for (size_t i = 0; i < this->getLength(); ++i)
            {
                for (size_t j = 0; j < other.getLength(); ++j)
                {
                    if ((this->getStartX() + i) == other.getStartX())
                    {
                        if (this->getStartY() == (other.getStartY() + j))
                        {
                            return true;
                        }
                    }
                }
            }
        }
        else {
            if (this->getStartY() == other.getStartY())
            {
                for (size_t i = 0; i < this->getLength(); ++i)
                {
                    for (size_t j = 0; j < other.getLength(); ++j)
                    {
                        if ((this->getStartX() + i) == (other.getStartX() + j))
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool BattleBoat::isHit(unsigned int x, unsigned int y) const
{
    // TODO: Implement this function
    unsigned int distance;

    if (this->isVertical())
    {
        if (this->getStartX() == x)
        {
            for (size_t i = 0; i < this->getLength(); ++i)
            {
                if ((this->getStartY() + i) == y)
                {
                    distance = y - this->getStartY();
                    return this->hits[distance];
                }
            }
        }
    }

    else
    {
        if (this->getStartY() == y)
        {
            for (size_t i = 0; i < this->getLength(); ++i)
            {
                if ((this->getStartX() + i) == x)
                {
                    distance = x - this->getStartX();
                    return this->hits[distance];
                }
            }
        }
    }
    return false;
}

bool BattleBoat::isHitable(unsigned int x, unsigned int y) const
{
    // TODO: Implement this function
    unsigned int distance;

    if (this->isVertical())
    {
        if (this->getStartX() == x)
        {
            for (size_t i = 0; i < this->getLength(); ++i)
            {
                if ((this->getStartY() + i) == y)
                {
                    distance = y - this->getStartY();
                    return !this->hits[distance];
                }
            }
        }
    }

    else
    {
        if (this->getStartY() == y)
        {
            for (size_t i = 0; i < this->getLength(); ++i)
            {
                if ((this->getStartX() + i) == x)
                {
                    distance = x - this->getStartX();
                    return !this->hits[distance];
                }
            }
        }
    }
    return false;
}

void BattleBoat::hit(unsigned int x, unsigned int y)
{
    // TODO: Implement this function
    unsigned int distance;

    if (this->isHitable(x, y))
    {
        if (this->isVertical())
        {
            distance = y - this->getStartY();
        }
        
        else
        {
            distance = x - this->getStartX();
        }

        this->hits[distance] = true;
    }
}

bool BattleBoat::isSunk() const
{
    // TODO: Implement this function
    unsigned int hitsCounted{ 0 };

    for (size_t i = 0; i < this->getLength() && hits[i]; ++i)
    {
        hitsCounted++;
    }
    if (hitsCounted == this->getLength()) { return true; }

    return false;
}
