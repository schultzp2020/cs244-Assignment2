#include <iostream>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <string>
#include "BattleBoat.h"
#include "BattleBoatBoard.h"
#include "BattleBoatsGame.h"

using namespace std;

// Brute-force testing of BattleBoat::intersects()
void testIntersects()
{
    for (int boat1Length = 1; boat1Length <= BattleBoat::MAX_LENGTH; boat1Length++)
    {
        for (int boat1StartX = 0; boat1StartX < BattleBoatBoard::BOARD_SIZE; boat1StartX++)
        {
            for (int boat1StartY = 0; boat1StartY < BattleBoatBoard::BOARD_SIZE; boat1StartY++)
            {
                for (int boat2Length = 1; boat2Length <= BattleBoat::MAX_LENGTH; boat2Length++)
                {
                    // boat 1 - vertical; boat 2 - vertical

                    if (boat1StartY + boat1Length <= BattleBoatBoard::BOARD_SIZE)
                    {
                        BattleBoat boat1{ static_cast<unsigned int>(boat1Length) };
                        boat1.setVertical(true);
                        boat1.setStartX(boat1StartX);
                        boat1.setStartY(boat1StartY);

                        for (int boat2StartY = max(0, boat1StartY - boat2Length + 1); boat2StartY + boat2Length <= BattleBoatBoard::BOARD_SIZE && boat2StartY < boat1StartY + boat1Length; boat2StartY++)
                        {
                            BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                            boat2.setVertical(true);
                            boat2.setStartX(boat1StartX);
                            boat2.setStartY(boat2StartY);
                            assert(boat1.intersects(boat2));
                            assert(boat2.intersects(boat1));
                        }

                        for (int boat2StartY = 0; boat2StartY + boat2Length <= BattleBoatBoard::BOARD_SIZE && boat2StartY <= boat1StartY - boat2Length; boat2StartY++)
                        {
                            BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                            boat2.setVertical(true);
                            boat2.setStartX(boat1StartX);
                            boat2.setStartY(boat2StartY);
                            assert(!boat1.intersects(boat2));
                            assert(!boat2.intersects(boat1));
                        }

                        for (int boat2StartY = boat1StartY + boat1Length; boat2StartY + boat2Length <= BattleBoatBoard::BOARD_SIZE; boat2StartY++)
                        {
                            BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                            boat2.setVertical(true);
                            boat2.setStartX(boat1StartX);
                            boat2.setStartY(boat2StartY);
                            assert(!boat1.intersects(boat2));
                            assert(!boat2.intersects(boat1));
                        }

                        for (int boat2StartY = 0; boat2StartY + boat2Length <= BattleBoatBoard::BOARD_SIZE; boat2StartY++)
                        {
                            for (int boat2StartX = 0; boat2StartX < boat1StartX; boat2StartX++)
                            {
                                BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                                boat2.setVertical(true);
                                boat2.setStartX(boat2StartX);
                                boat2.setStartY(boat2StartY);
                                assert(!boat1.intersects(boat2));
                                assert(!boat2.intersects(boat1));
                            }

                            for (int boat2StartX = boat1StartX + 1; boat2StartX < BattleBoatBoard::BOARD_SIZE; boat2StartX++)
                            {
                                BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                                boat2.setVertical(true);
                                boat2.setStartX(boat2StartX);
                                boat2.setStartY(boat2StartY);
                                assert(!boat1.intersects(boat2));
                                assert(!boat2.intersects(boat1));
                            }
                        }
                    }

                    if (boat1Length + boat1StartX <= BattleBoatBoard::BOARD_SIZE)
                    {
                        BattleBoat boat1{ static_cast<unsigned int>(boat1Length) };
                        boat1.setVertical(false);
                        boat1.setStartX(boat1StartX);
                        boat1.setStartY(boat1StartY);

                        // boat 1 - horizontal; boat 2 - horizontal
                        for (int boat2StartX = max(0, boat1StartX - boat2Length + 1); boat2StartX + boat2Length <= BattleBoatBoard::BOARD_SIZE && boat2StartX < boat1StartX + boat1Length; boat2StartX++)
                        {
                            BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                            boat2.setVertical(false);
                            boat2.setStartX(boat2StartX);
                            boat2.setStartY(boat1StartY);
                            assert(boat1.intersects(boat2));
                            assert(boat2.intersects(boat1));
                        }

                        for (int boat2StartX = 0; boat2StartX + boat2Length <= BattleBoatBoard::BOARD_SIZE && boat2StartX <= boat1StartX - boat2Length; boat2StartX++)
                        {
                            BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                            boat2.setVertical(false);
                            boat2.setStartX(boat2StartX);
                            boat2.setStartY(boat1StartY);
                            assert(!boat1.intersects(boat2));
                            assert(!boat2.intersects(boat1));
                        }

                        for (int boat2StartX = boat1StartX + boat1Length; boat2StartX + boat2Length <= BattleBoatBoard::BOARD_SIZE; boat2StartX++)
                        {
                            BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                            boat2.setVertical(false);
                            boat2.setStartX(boat2StartX);
                            boat2.setStartY(boat1StartY);
                            assert(!boat1.intersects(boat2));
                            assert(!boat2.intersects(boat1));
                        }

                        for (int boat2StartX = 0; boat2StartX + boat2Length <= BattleBoatBoard::BOARD_SIZE; boat2StartX++)
                        {
                            for (int boat2StartY = 0; boat2StartY < boat1StartY; boat2StartY++)
                            {
                                BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                                boat2.setVertical(false);
                                boat2.setStartX(boat2StartX);
                                boat2.setStartY(boat2StartY);
                                assert(!boat1.intersects(boat2));
                                assert(!boat2.intersects(boat1));
                            }

                            for (int boat2StartY = boat1StartY + 1; boat2StartY < BattleBoatBoard::BOARD_SIZE; boat2StartY++)
                            {
                                BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                                boat2.setVertical(false);
                                boat2.setStartX(boat2StartX);
                                boat2.setStartY(boat2StartY);
                                assert(!boat1.intersects(boat2));
                                assert(!boat2.intersects(boat1));
                            }
                        }

                        // boat 1 - horizontal; boat 2 - vertical
                        for (int boat2StartX = boat1StartX; boat2StartX < boat1StartX + boat1Length; boat2StartX++)
                        {
                            for (int boat2StartY = max(0, boat1StartY - boat2Length + 1); boat2StartY <= boat1StartY && boat2StartY + boat2Length <= BattleBoatBoard::BOARD_SIZE; boat2StartY++)
                            {
                                BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                                boat2.setVertical(true);
                                boat2.setStartX(boat2StartX);
                                boat2.setStartY(boat2StartY);
                                assert(boat1.intersects(boat2));
                                assert(boat2.intersects(boat1));
                            }
                        }

                        for (int boat2StartX = 0; boat2StartX < boat1StartX; boat2StartX++)
                        {
                            for (int boat2StartY = 0; boat2StartY + boat2Length <= BattleBoatBoard::BOARD_SIZE; boat2StartY++)
                            {
                                BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                                boat2.setVertical(true);
                                boat2.setStartX(boat2StartX);
                                boat2.setStartY(boat2StartY);
                                assert(!boat1.intersects(boat2));
                                assert(!boat2.intersects(boat1));
                            }
                        }

                        for (int boat2StartX = boat1StartX + boat1Length; boat2StartX < BattleBoatBoard::BOARD_SIZE; boat2StartX++)
                        {
                            for (int boat2StartY = 0; boat2StartY + boat2Length <= BattleBoatBoard::BOARD_SIZE; boat2StartY++)
                            {
                                BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                                boat2.setVertical(true);
                                boat2.setStartX(boat2StartX);
                                boat2.setStartY(boat2StartY);
                                assert(!boat1.intersects(boat2));
                                assert(!boat2.intersects(boat1));
                            }
                        }

                        for (int boat2StartX = 0; boat2StartX < BattleBoatBoard::BOARD_SIZE; boat2StartX++)
                        {
                            for (int boat2StartY = 0; boat2StartY <= boat1StartY - boat2Length; boat2StartY++)
                            {
                                BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                                boat2.setVertical(true);
                                boat2.setStartX(boat2StartX);
                                boat2.setStartY(boat2StartY);
                                assert(!boat1.intersects(boat2));
                                assert(!boat2.intersects(boat1));
                            }

                            for (int boat2StartY = boat1StartY + 1; boat2StartY + boat2Length <= BattleBoatBoard::BOARD_SIZE; boat2StartY++)
                            {
                                BattleBoat boat2{ static_cast<unsigned int>(boat2Length) };
                                boat2.setVertical(true);
                                boat2.setStartX(boat2StartX);
                                boat2.setStartY(boat2StartY);
                                assert(!boat1.intersects(boat2));
                                assert(!boat2.intersects(boat1));
                            }
                        }
                    }
                }
            }
        }
    }
}

// A helper function that makes it possible to recursively test different combinations of boat lengths
void testBoardHelper(void (*testFunction) (unsigned int*, unsigned int), unsigned int* lengths, unsigned int lengthCount, unsigned int lengthSum)
{
    testFunction(lengths, lengthCount);

    if (lengthCount < BattleBoatBoard::MAX_BOAT_COUNT)
    {
        // Recursively check cases with the same boats plus one more boat.
        // Consider any legal boat length for the next boat that does not cause the total length sum to exceed 20.
        for (lengths[lengthCount] = 1; lengths[lengthCount] <= BattleBoat::MAX_LENGTH && lengthSum + lengths[lengthCount] < 20; lengths[lengthCount]++)
        {
            testBoardHelper(testFunction, lengths, lengthCount + 1, lengthSum + lengths[lengthCount]);
        }
    }
}

// Uses recursion to exhaustively check all possible combinations of boat lengths.
// The actual test to run for each board is specified as a parameter.
void testBoards(void (*testFunction) (unsigned int*, unsigned int))
{
    // Array to store the boat lengths
    unsigned int lengths[BattleBoatBoard::MAX_BOAT_COUNT];

    // Consider any legal boat length (between 1 and the max length) for the first boat.
    for (lengths[0] = 1; lengths[0] <= BattleBoat::MAX_LENGTH; lengths[0]++)
    {
        // Helper function actually runs the tests (and calls itself recursively).
        testBoardHelper(testFunction, lengths, 1, lengths[0]);
    }
}

// Tests the constructor for BattleBoatBoard for a specific combination of boat lengths.
// Intended to be used with testBoards().
void testBoardConstructor(unsigned int* lengths, unsigned int lengthCount)
{
    // create the board
    BattleBoatBoard board{ lengths, lengthCount };

    // make sure the boat count is correct
    assert(board.getBoatCount() == lengthCount);

    const BattleBoat* boats = board.getBoats();

    for (unsigned int i = 0; i < board.getBoatCount(); i++)
    {
        // make sure each boat length is correct
        assert(boats[i].getLength() == lengths[i]);

        // make sure getBoat() works.
        for (unsigned int j = 0; j < boats[i].getLength(); j++)
        {
            // non-const version
            if (boats[i].isVertical())
            {
                assert(board.getBoat(boats[i].getStartX(), boats[i].getStartY() + j) == &boats[i]);
            }
            else
            {
                assert(board.getBoat(boats[i].getStartX() + j, boats[i].getStartY()) == &boats[i]);
            }

            // const version
            const BattleBoatBoard& cboard{ board };
            if (boats[i].isVertical())
            {
                assert(cboard.getBoat(boats[i].getStartX(), boats[i].getStartY() + j) == &boats[i]);
            }
            else
            {
                assert(cboard.getBoat(boats[i].getStartX() + j, boats[i].getStartY()) == &boats[i]);
            }

        }

        // make sure none of the boats overlap
        for (unsigned int j = 0; j < board.getBoatCount(); j++)
        {
            if (j != i)
            {
                if (boats[i].intersects(boats[j])) {
                    cout << "(" << boats[i].getStartX() << "," << boats[i].getStartY() << ")" << " " << boats[i].getLength() << " " << boats[i].isVertical() << endl;
                    cout << "(" << boats[j].getStartX() << "," << boats[j].getStartY() << ")" << " " << boats[j].getLength() << " " << boats[j].isVertical() << endl;
                }
                assert(!boats[i].intersects(boats[j]));
            }
        }
    }
}

// Brute-force testing of BattleBoat::hit() and BattleBoat::isHit()
void testHit()
{
    // test every possible boat size and location
    for (unsigned int length = 1; length <= BattleBoat::MAX_LENGTH; length++)
    {
        for (unsigned int startX = 0; startX < BattleBoatBoard::BOARD_SIZE; startX++)
        {
            for (unsigned int startY = 0; startY < BattleBoatBoard::BOARD_SIZE; startY++)
            {
                if (startX + length <= BattleBoatBoard::BOARD_SIZE)
                {
                    // horizontal boat
                    for (unsigned int i = 0; i < length; i++)
                    {
                        BattleBoat boat{ length };
                        boat.setVertical(false);
                        boat.setStartX(startX);
                        boat.setStartY(startY);

                        // make sure the boat is initially not hit, then hit it and check that it's hit
                        assert(!boat.isHit(startX + i, startY));
                        boat.hit(startX + i, startY);
                        assert(boat.isHit(startX + i, startY));

                        // make sure the boat was only hit in the correct location
                        for (unsigned int j = 0; j < length; j++)
                        {
                            if (i != j)
                            {
                                assert(!boat.isHit(startX + j, startY));
                            }
                        }
                    }
                }

                if (startY + length <= BattleBoatBoard::BOARD_SIZE)
                {
                    // vertical boat
                    for (unsigned int i = 0; i < length; i++)
                    {
                        BattleBoat boat{ length };
                        boat.setVertical(true);
                        boat.setStartX(startX);
                        boat.setStartY(startY);

                        assert(!boat.isHit(startX, startY + i));
                        boat.hit(startX, startY + i);
                        assert(boat.isHit(startX, startY + i));

                        // make sure the boat was only hit in the correct location
                        for (unsigned int j = 0; j < length; j++)
                        {
                            if (i != j)
                            {
                                assert(!boat.isHit(startX, startY + j));
                            }
                        }
                    }
                }
            }
        }
    }
}

// Tests the BattleBoatsGame::shot() on a board with a specific combination of boat lengths.
// Intended to be used with testBoards().
void testShot(unsigned int* lengths, unsigned int lengthCount)
{
    // create the board
    BattleBoatBoard board{ lengths, lengthCount };
    BattleBoatsGame game{ board };

    unsigned int shotCount = 0;

    for (unsigned int x = 0; x < BattleBoatBoard::BOARD_SIZE; x++)
    {
        for (unsigned int y = 0; y < BattleBoatBoard::BOARD_SIZE; y++)
        {
            BattleBoat* boat = board.getBoat(x, y);
            if (!boat)
            {
                assert(!game.isRevealed(x, y));
                assert(!game.isHit(x, y));
                assert(!game.shot(x, y));
                assert(game.isRevealed(x, y));
                assert(!game.isHit(x, y));
                shotCount++;
                assert(shotCount == game.getTurnCount());
            }
        }
    }

    for (unsigned int x = 0; x < BattleBoatBoard::BOARD_SIZE; x++)
    {
        for (unsigned int y = 0; y < BattleBoatBoard::BOARD_SIZE; y++)
        {
            BattleBoat* boat = board.getBoat(x, y);
            if (boat)
            {
                assert(!game.isRevealed(x, y));
                assert(!game.isHit(x, y));
                assert(game.shot(x, y));
                assert(game.isRevealed(x, y));
                assert(game.isHit(x, y));
                shotCount++;
                assert(shotCount == game.getTurnCount());
            }
        }
    }
}

// Brute-force testing of BattleBoat::isSunk()
void testIsSunk()
{
    // test every possible boat size and location
    for (unsigned int length = 1; length <= BattleBoat::MAX_LENGTH; length++)
    {
        for (unsigned int startX = 0; startX < BattleBoatBoard::BOARD_SIZE; startX++)
        {
            for (unsigned int startY = 0; startY < BattleBoatBoard::BOARD_SIZE; startY++)
            {
                if (startX + length <= BattleBoatBoard::BOARD_SIZE)
                {
                    // horizontal boat
                    BattleBoat boat{ length };
                    boat.setVertical(false);
                    boat.setStartX(startX);
                    boat.setStartY(startY);

                    for (unsigned int i = 0; i < length; i++)
                    {
                        // make sure the boat is not sunk before each hit
                        assert(!boat.isSunk());
                        boat.hit(startX + i, startY);
                    }

                    // make sure the boat is sunk
                    assert(boat.isSunk());
                }

                if (startY + length <= BattleBoatBoard::BOARD_SIZE)
                {
                    // vertical boat
                    BattleBoat boat{ length };
                    boat.setVertical(true);
                    boat.setStartX(startX);
                    boat.setStartY(startY);

                    for (unsigned int i = 0; i < length; i++)
                    {
                        // make sure the boat is not sunk before each hit
                        assert(!boat.isSunk());
                        boat.hit(startX, startY + i);
                    }

                    // make sure the boat is sunk
                    assert(boat.isSunk());
                }
            }
        }
    }
}

// Tests BattleBoatsGame::getBoatsSunk() on a board with a specific combination of boat lengths.
// Intended to be used with testBoards().
void testSunkCount(unsigned int* lengths, unsigned int lengthCount)
{
    // create the board
    BattleBoatBoard board{ lengths, lengthCount };
    BattleBoatsGame game{ board };

    unsigned int sunkCount = 0;

    for (unsigned int x = 0; x < BattleBoatBoard::BOARD_SIZE; x++)
    {
        for (unsigned int y = 0; y < BattleBoatBoard::BOARD_SIZE; y++)
        {
            BattleBoat* boat = board.getBoat(x, y);
            if (boat)
            {
                game.shot(x, y);

                if (boat->isSunk())
                {
                    sunkCount++;
                    assert(sunkCount == game.getBoatsSunk());
                }
            }
        }
    }

    assert(game.getBoatsSunk() == game.getBoatCount());
}

// Test BattleBoat::hit() and BattleBoat::isHit() for cases where the coordinates aren't occupied by the boat
// (including coordinates that are out-of-bounds for the board in general).
void testHitEdgeCases()
{
    // test every possible boat size and location
    for (unsigned int length = 1; length <= BattleBoat::MAX_LENGTH; length++)
    {
        for (unsigned int startX = 0; startX < BattleBoatBoard::BOARD_SIZE; startX++)
        {
            for (unsigned int startY = 0; startY < BattleBoatBoard::BOARD_SIZE; startY++)
            {
                // test every board location and every space just beyond the edge of the board
                for (unsigned int x = 0; x <= BattleBoatBoard::BOARD_SIZE; x++)
                {
                    for (unsigned int y = 0; y <= BattleBoatBoard::BOARD_SIZE; y++)
                    {
                        if (startX + length <= BattleBoatBoard::BOARD_SIZE)
                        {
                            // horizontal boat
                            BattleBoat boat{ length };
                            boat.setVertical(false);
                            boat.setStartX(startX);
                            boat.setStartY(startY);

                            if (y != startY || x < startX || startX + length <= x)
                            {
                                // The boat does not occupy space (x, y).
                                // Make sure the space is initially not hit, then try to hit (x, y).
                                assert(!boat.isHit(x, y));
                                boat.hit(x, y);

                                // Check that the boat still isn't hit.
                                for (unsigned int i = 0; i < boat.getLength(); i++)
                                {
                                    assert(!boat.isHit(startX + i, startY));
                                }
                            }
                        }

                        if (startY + length <= BattleBoatBoard::BOARD_SIZE)
                        {
                            // vertical boat
                            BattleBoat boat{ length };
                            boat.setVertical(true);
                            boat.setStartX(startX);
                            boat.setStartY(startY);

                            if (x != startX || y < startY || startY + length <= y)
                            {
                                // The boat does not occupy space (x, y).
                                // Make sure the space is initially not hit, then try to hit (x, y).
                                assert(!boat.isHit(x, y));
                                boat.hit(x, y);

                                // Check that the boat still isn't hit.
                                for (unsigned int i = 0; i < boat.getLength(); i++)
                                {
                                    assert(!boat.isHit(startX, startY + i));
                                }
                            }
                        }
                    }
                }

                // test some random large out of bounds cases
                for (unsigned int i = 0; i < 1000; i++)
                {
                    unsigned int x = max(BattleBoatBoard::BOARD_SIZE, static_cast<unsigned int>(rand()));
                    unsigned int y = max(BattleBoatBoard::BOARD_SIZE, static_cast<unsigned int>(rand()));

                    if (startX + length <= BattleBoatBoard::BOARD_SIZE)
                    {
                        // horizontal boat
                        BattleBoat boat{ length };
                        boat.setVertical(false);
                        boat.setStartX(startX);
                        boat.setStartY(startY);

                        if (y != startY || x < startX || startX + length <= x)
                        {
                            // The boat does not occupy space (x, y).
                            // Make sure the space is initially not hit, then try to hit (x, y).
                            assert(!boat.isHit(x, y));
                            boat.hit(x, y);

                            // Check that the boat still isn't hit.
                            for (unsigned int i = 0; i < boat.getLength(); i++)
                            {
                                assert(!boat.isHit(startX + i, startY));
                            }
                        }
                    }

                    if (startY + length <= BattleBoatBoard::BOARD_SIZE)
                    {
                        // vertical boat
                        BattleBoat boat{ length };
                        boat.setVertical(true);
                        boat.setStartX(startX);
                        boat.setStartY(startY);

                        if (x != startX || y < startY || startY + length <= y)
                        {
                            // The boat does not occupy space (x, y).
                            // Make sure the space is initially not hit, then try to hit (x, y).
                            assert(!boat.isHit(x, y));
                            boat.hit(x, y);

                            // Check that the boat still isn't hit.
                            for (unsigned int i = 0; i < boat.getLength(); i++)
                            {
                                assert(!boat.isHit(startX, startY + i));
                            }
                        }
                    }
                }
            }
        }
    }
}

// Test a couple of hard-coded cases where the parameters to the BattleBoatBoard constructor are illegal.
void testBoardConstructorOutOfBounds()
{
    unsigned int lengths1[11]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 };
    BattleBoatBoard board1{ lengths1, 11 };
    assert(board1.getBoatCount() == 10);

    const BattleBoat* boats1 = board1.getBoats();
    for (unsigned int i = 0; i < 10; i++)
    {
        assert(boats1[i].getLength() == 1);
    }


    unsigned int lengths2[3]{ 7, 7, 5 };
    BattleBoatBoard board2{ lengths2, 3 };
    assert(board2.getBoatCount() == 3);

    const BattleBoat* boats2 = board2.getBoats();
    assert(boats2[0].getLength() == 6);
    assert(boats2[1].getLength() == 6);
    assert(boats2[2].getLength() == 5);
}

/// Test cases where the parameters to BattleBoatBoard::getBoat() are out-of-bounds.
void testGetBoatOutOfBounds()
{
    unsigned int lengths[5]{ 5, 4, 3, 3, 2 };
    BattleBoatBoard board{ lengths, 5 };

    // test various places that are just out of bounds
    assert(board.getBoat(BattleBoatBoard::BOARD_SIZE, BattleBoatBoard::BOARD_SIZE) == nullptr);

    for (unsigned int i = 0; i < BattleBoatBoard::BOARD_SIZE; i++)
    {
        assert(board.getBoat(i, BattleBoatBoard::BOARD_SIZE) == nullptr);
        assert(board.getBoat(BattleBoatBoard::BOARD_SIZE, i) == nullptr);
    }

    // test some random large out of bounds cases
    for (unsigned int i = 0; i < 1000; i++)
    {
        unsigned int x = max(BattleBoatBoard::BOARD_SIZE, static_cast<unsigned int>(rand()));
        unsigned int y = max(BattleBoatBoard::BOARD_SIZE, static_cast<unsigned int>(rand()));

        assert(board.getBoat(x, y) == nullptr);
        assert(board.getBoat(x, y) == nullptr);
    }
}

/// Test cases where the parameters to BattleBoatsGame::shot() are out-of-bounds.
void testShotOutOfBounds()
{
    unsigned int lengths[5]{ 5, 4, 3, 3, 2 };
    BattleBoatBoard board{ lengths, 5 };
    BattleBoatsGame game{ board };

    // Test isRevealed and isHit first:

    // Test various places that are just out of bounds
    assert(!game.isRevealed(BattleBoatBoard::BOARD_SIZE, BattleBoatBoard::BOARD_SIZE));
    assert(!game.isHit(BattleBoatBoard::BOARD_SIZE, BattleBoatBoard::BOARD_SIZE));

    for (unsigned int i = 0; i < BattleBoatBoard::BOARD_SIZE; i++)
    {
        assert(!game.isRevealed(i, BattleBoatBoard::BOARD_SIZE));
        assert(!game.isRevealed(BattleBoatBoard::BOARD_SIZE, i));
        assert(!game.isHit(i, BattleBoatBoard::BOARD_SIZE));
        assert(!game.isHit(BattleBoatBoard::BOARD_SIZE, i));
    }

    // Test some random large out of bounds cases
    for (unsigned int i = 0; i < 1000; i++)
    {
        unsigned int x = max(BattleBoatBoard::BOARD_SIZE, static_cast<unsigned int>(rand()));
        unsigned int y = max(BattleBoatBoard::BOARD_SIZE, static_cast<unsigned int>(rand()));

        assert(!game.isRevealed(x, y));
        assert(!game.isHit(x, y));
    }

    // Now test shot():

    // Test various places that are just out of bounds
    assert(!game.shot(BattleBoatBoard::BOARD_SIZE, BattleBoatBoard::BOARD_SIZE));

    // Make sure the space is still not revealed or hit
    assert(!game.isRevealed(BattleBoatBoard::BOARD_SIZE, BattleBoatBoard::BOARD_SIZE));
    assert(!game.isHit(BattleBoatBoard::BOARD_SIZE, BattleBoatBoard::BOARD_SIZE));

    for (unsigned int i = 0; i < BattleBoatBoard::BOARD_SIZE; i++)
    {
        assert(!game.shot(i, BattleBoatBoard::BOARD_SIZE));
        assert(!game.shot(BattleBoatBoard::BOARD_SIZE, i));

        // Make sure the spaces are still not revealed or hit
        assert(!game.isRevealed(i, BattleBoatBoard::BOARD_SIZE));
        assert(!game.isRevealed(BattleBoatBoard::BOARD_SIZE, i));
        assert(!game.isHit(i, BattleBoatBoard::BOARD_SIZE));
        assert(!game.isHit(BattleBoatBoard::BOARD_SIZE, i));
    }

    // Test some random large out of bounds cases
    for (unsigned int i = 0; i < 1000; i++)
    {
        unsigned int x = max(BattleBoatBoard::BOARD_SIZE, static_cast<unsigned int>(rand()));
        unsigned int y = max(BattleBoatBoard::BOARD_SIZE, static_cast<unsigned int>(rand()));

        // Shoot twice for good measure
        assert(!game.shot(x, y));
        assert(!game.shot(x, y));

        // Make sure the space is still not revealed or hit
        assert(!game.isRevealed(x, y));
        assert(!game.isHit(x, y));
    }

    BattleBoat* boats = board.getBoats();

    // Make sure that none of the boats are hit
    for (unsigned int i = 0; i < board.getBoatCount(); i++)
    {
        for (unsigned int j = 0; j < boats[i].getLength(); j++)
        {
            if (boats[i].isVertical())
            {
                assert(!boats[i].isHit(boats[i].getStartX(), boats[i].getStartY() + j));
            }
            else
            {
                assert(!boats[i].isHit(boats[i].getStartX() + j, boats[i].getStartY()));
            }
        }
    }
}

/// Test cases where the same coordinates are targeted by BattleBoatsGame::shot() multiple times.
void testRepeatShots(unsigned int* lengths, unsigned int lengthCount)
{
    // create the board
    BattleBoatBoard board{ lengths, lengthCount };
    BattleBoatsGame game{ board };

    unsigned int shotCount = 0;

    for (unsigned int x = 0; x < BattleBoatBoard::BOARD_SIZE; x++)
    {
        for (unsigned int y = 0; y < BattleBoatBoard::BOARD_SIZE; y++)
        {
            BattleBoat* boat = board.getBoat(x, y);
            if (boat)
            {
                // first shot counts as a hit
                assert(!game.isRevealed(x, y));
                assert(!game.isHit(x, y));
                assert(game.shot(x, y));
                assert(game.isRevealed(x, y));
                assert(game.isHit(x, y));
                shotCount++;
                assert(shotCount == game.getTurnCount());

                // second shot doesn't count
                assert(!game.shot(x, y));
                assert(game.isRevealed(x, y));
                assert(game.isHit(x, y));
                shotCount++;
                assert(shotCount == game.getTurnCount());

                // third shot doesn't count either
                assert(!game.shot(x, y));
                assert(game.isRevealed(x, y));
                assert(game.isHit(x, y));
                shotCount++;
                assert(shotCount == game.getTurnCount());
            }
        }
    }
}

// Plays a game by randomly guessing coordinates (including some out-of-bounds coordinates 
// to make sure that doesn't cause problems in the course of a real game).
void testRandomGame(unsigned int* lengths, unsigned int lengthCount)
{
    // create the board
    BattleBoatBoard board{ lengths, lengthCount };
    BattleBoatsGame game{ board };

    unsigned int sunkCount = 0;
    unsigned int shotCount = 0;

    // Loop until the game is over, or a maximum shot count is exceeded.
    while (sunkCount < lengthCount)
    {
        // Generate a random coordinate to guess -- including some out-of-bounds coordinates
        unsigned int x = rand() % (BattleBoatBoard::BOARD_SIZE + 1);
        unsigned int y = rand() % (BattleBoatBoard::BOARD_SIZE + 1);

        const BattleBoat* boat = board.getBoat(x, y);

        if (boat)
        {
            if (game.isHit(x, y))
            {
                // repeat hit, shot() should return false.
                assert(!game.shot(x, y));
                assert(game.isHit(x, y));
                assert(game.isRevealed(x, y));
            }
            else
            {
                // hit -- shot() should return true and affect the boat
                assert(game.shot(x, y));
                assert(game.isHit(x, y));
                assert(game.isRevealed(x, y));

                if (boat->isSunk())
                {
                    sunkCount++;
                    assert(sunkCount == game.getBoatsSunk());
                }
            }
        }
        else
        {
            // miss -- shot() should return false.
            assert(!game.shot(x, y));
            assert(!game.isHit(x, y));

            // Space should be revealed now if and only if (x, y) are in bounds, 
            assert(game.isRevealed(x, y) == (x < BattleBoatBoard::BOARD_SIZE && y < BattleBoatBoard::BOARD_SIZE));
        }

        shotCount++;
        assert(game.getTurnCount() == shotCount);
    }

    // Make sure that all the boats were sunk.
    assert(game.getBoatsSunk() == game.getBoatCount());
}

// A function with all of the test functions
void tests()
{
    // Seed the random number generator
    srand(0); // Start with a deterministic seed

    cout << "Running part 1 tests." << endl;

    cout << "Testing intersects()." << endl;
    testIntersects();
    cout << "Passed!" << endl;

    cout << "Testing BattleBoatBoard constructor." << endl;
    testBoards(&testBoardConstructor);
    cout << "Passed!" << endl;

    cout << "All part 1 tests passed!" << endl << endl;

    cout << "Running part 2 tests." << endl;

    cout << "Testing hit() and BattleBoat::isHit()." << endl;
    testHit();
    cout << "Passed!" << endl;

    cout << "Testing shot() and isRevealed()." << endl;
    testBoards(&testShot);
    cout << "Passed!" << endl;

    cout << "Testing isSunk()." << endl;
    testIsSunk();
    cout << "Passed!" << endl;

    cout << "Testing getBoatsSunk()." << endl;
    testBoards(&testSunkCount);
    cout << "Passed!" << endl;

    cout << "All part 2 tests passed!" << endl << endl;

    cout << "Running part 3 tests." << endl;

    cout << "Testing isHit() edge cases." << endl;
    testHitEdgeCases();
    cout << "Passed!" << endl;

    cout << "Testing BattleBoatBoard constructor out-of-bounds cases." << endl;
    testBoardConstructorOutOfBounds();
    cout << "Passed!" << endl;

    cout << "Testing getBoat() out-of-bounds cases." << endl;
    testGetBoatOutOfBounds();
    cout << "Passed!" << endl;

    cout << "Testing shot() and isRevealed() out-of-bounds cases." << endl;
    testShotOutOfBounds();
    cout << "Passed!" << endl;

    cout << "Testing shot() on the same coordinates more than once." << endl;
    testBoards(&testRepeatShots);
    cout << "Passed!" << endl;

    cout << "More random tests (may take a while)." << endl;

    // Time-based random seed
    time_t seed;
    time(&seed);
    srand(static_cast<unsigned int>(seed));

    for (unsigned int i = 0; i < 3; i++)
    {
        testBoards(&testBoardConstructor);
    }

    cout << "Passed!" << endl;

    cout << "Playing some random games (may take a while)." << endl;

    testBoards(&testRandomGame);

    cout << "Passed!" << endl;

    cout << "All part 3 tests passed!" << endl << endl;
}

// A function to create the board
BattleBoatBoard* createBoard()
{
    unsigned int const MAX_BOAT_COUNT{ 10 };
    unsigned int const MAX_TOTAL_LENGTH{ 20 };
    unsigned int boatLengths[MAX_BOAT_COUNT] = { 0 };
    unsigned int boatCount{ 0 };
    unsigned int totalBoatLength{ 0 };
    string failedUserInput;

    cout << "Welcome to Battleboats!" << endl << endl;
    cout << "Keep in mind these constrants..." << endl;
    cout << "The boat count must be between 1 and 10." << endl;
    cout << "The boat length must be between 1 and 6." << endl;
    cout << "The input will be rounded down, i.e. 4.87 = 4." << endl;
    cout << "The total length of all of the boats cannot exceed 20." << endl;
    
    do //loop until the user input is valid
    {
        cout << "How many boats do you want in the game?" << endl; //ask the user for the desired boat count
        cin >> boatCount;
        cin.ignore();
        cout << endl;

        if (cin.fail()) //clear cin if the input was invalid
        {
            cin.clear();
            getline(cin, failedUserInput);
            cout << "Error (Invalid Input): " << failedUserInput << endl << endl;
        }

        if (boatCount == 0 || boatCount > 10) //make sure the user has a boat count between 1 and 10
        {
            cout << "Invalid boat count." << endl << endl;
        }

    } while (boatCount == 0 || boatCount > 10);

    cout << "What are the boat lengths?" << endl;

    for (size_t i = 0; i < boatCount; ++i) //loop for every boat the user desired
    {
        do //loop until the user input is valid
        {
            cout << "Boat #" << i + 1 << " length:" << endl; //ask the user for the desired boat length
            cin >> boatLengths[i];
            cin.ignore();
            cout << endl;

            if (cin.fail()) //clear cin if the input was invalid
            {
                cin.clear();
                getline(cin, failedUserInput);
                cout << "Error (Invalid Input): " << failedUserInput << endl << endl;
            }

            if (boatLengths[i] == 0 || boatLengths[i] > 6) //make sure the user has a boat length between 1 and 6
            {
                cout << "Invalid boat length." << endl << endl;
            }

        } while (boatLengths[i] == 0 || boatLengths[i] > 6);

        totalBoatLength += boatLengths[i]; //count the total boat length

        if (totalBoatLength > MAX_TOTAL_LENGTH) //if the boat length is over 20 reset
        {
            i = -1;
            totalBoatLength = 0;
            cout << "Exceeded total boat length of 20." << endl << endl;
        }


    }

    BattleBoatBoard* board = new BattleBoatBoard(boatLengths, boatCount);
    return board;
}

// A function to play a game
void playGame(BattleBoatBoard* board, bool debugMode)
{
    BattleBoatsGame game(*board);
    unsigned int x;
    unsigned int y;
    string failedUserInput;
    string userInput;
    bool validatedUserInput{ false };

    cout << "Keep in mind these constrants..." << endl;
    cout << "The x and y values of the shot must be between 0 and 9." << endl << endl;
    do //loop until the game is complete
    {
        if (debugMode) //print the location of the boats if the game is in debug mode
        {
            cout << "YOU ARE IN DEBUG MODE!!!" << endl << endl;
            cout << *board << endl;
        }

        do //loop until the input is valid
        {
            cout << "What is the x coordinate you want to shoot at?" << endl; //ask the user for the deisred x coordinate
            cin >> x;
            cin.ignore();
            cout << endl;

            if (cin.fail()) //clear cin if the input was invalid
            {
                cin.clear();
                getline(cin, failedUserInput);
                cout << "Error (Invalid Input): " << failedUserInput << endl << endl;
                x = 10;
            }

            if (x > 9) //tells the user the shot was out of bounds
            {
                cout << "Shot was out of bounds." << endl << endl;
            }

        } while (x > 9);

        do //loop until the input is valid
        {
            cout << "What is the y coordinate you want to shoot at?" << endl; //ask the user for the deisred y coordinate
            cin >> y;
            cin.ignore();
            cout << endl;

            if (cin.fail()) //clear cin if the input was invalid
            {
                cin.clear();
                getline(cin, failedUserInput);
                cout << "Error (Invalid Input): " << failedUserInput << endl << endl;
                y = 10;
            }

            if (y > 9) //tells the user the shot was out of bounds
            {
                cout << "Shot was out of bounds." << endl << endl;
            }

        } while (y > 9);

        if (game.isRevealed(x, y)) //tells the user they already shot there
        {
            cout << "You have already shot at (" << x << ", " << y << ")." << endl << endl;
        }
        else //takes a shot at the desired location
        {
            if (game.shot(x, y)) //tells the user the shot was a hit
            {
                cout << "The shot at (" << x << ", " << y << ") was a hit!" << endl;
            }
            else //tells the user the shot was a miss
            {
                cout << "The shot at (" << x << ", " << y << ") was a miss." << endl;
            }
            cout << endl;
        }

        if (game.getBoatsSunk() != game.getBoatCount()) //if the game is not complete tell how many boats are left, the turn count, display the board, and ask if the user wants to quit
        {
            cout << "This is turn #" << game.getTurnCount() << endl;
            cout << "There are " << game.getBoatCount() - game.getBoatsSunk() << " boats left." << endl << endl;
            cout << game << endl;

            do //loop until the input is valid
            {
                cout << "Do you want continue playing the game?" << endl << endl; //ask the user if they want to keep playing
                cout << "Type 'Yes' if you want keep playing." << endl;
                cout << "Type 'No' if you want to quit." << endl << endl;
                getline(cin, userInput);

                for (size_t i = 0; i < userInput.length(); ++i) //makes user input lower case
                {
                    userInput.at(i) = tolower(userInput.at(i));
                }

                cout << endl;

                if (userInput == "no" || userInput == "yes") { validatedUserInput = true; }

            } while(!validatedUserInput);

            if (userInput == "no") //if the user wants to quit... tell how many boats are left, the turn count, and display the board
            {
                cout << "You quit on turn #" << game.getTurnCount() << endl;
                cout << "There are " << game.getBoatCount() - game.getBoatsSunk() << " boats left." << endl << endl;
                for (x = 0; x < 10; ++x)
                {
                    for (y = 0; y < 10; ++y)
                    {
                        game.shot(x, y);
                    }
                }
                cout << game;
            }
        }
        else //tell the user the turn count and display the board
        {
            cout << "You finished the game on turn #" << game.getTurnCount() << endl << endl;
            for (x = 0; x < 10; ++x) //cleans the board up
            {
                for (y = 0; y < 10; ++y)
                {
                    game.shot(x, y);
                }
            }
            cout << game;
        }

    } while (game.getBoatsSunk() != game.getBoatCount());
}

// A function to hold all of the required functions to play the game
void game()
{
    string userInput;
    bool validatedUserInput{ false };
    bool debugMode;
    do
    {
        BattleBoatBoard* board = createBoard();
        debugMode = false;

        do //loop until the input is valid
        {
            cout << "Do you want to enter debug mode?" << endl << endl; //ask the user if they want to enter debug mode
            cout << "Type 'Yes' if you want to enter debug mode." << endl;
            cout << "Type 'No' if you do not want to enter debug mode." << endl << endl;
            getline(cin, userInput);

            for (size_t i = 0; i < userInput.length(); ++i) //makes user input lower case
            {
                userInput.at(i) = tolower(userInput.at(i));
            }

            cout << endl;

            if (userInput == "no" || userInput == "yes") { validatedUserInput = true; }

        } while (!validatedUserInput);

        if (userInput == "yes") //turn debug to true
        {
            debugMode = true;
        }

        playGame(board, debugMode);
        delete board;

        validatedUserInput = false; //reset validUserInput
        userInput = "null"; //reset userInput

        do //loop until the input is valid
        {
            cout << "Do you want to play BattleBoats again?" << endl << endl; //ask the user if they want to play BattleBoats again
            cout << "Type 'Yes' if you want to play BattleBoats again." << endl;
            cout << "Type 'No' if you want to quit." << endl << endl;
            getline(cin, userInput);

            for (size_t i = 0; i < userInput.length(); ++i) //makes user input lower case
            {
                userInput.at(i) = tolower(userInput.at(i));
            }

            cout << endl;

            if (userInput == "no" || userInput == "yes") { validatedUserInput = true; }

        } while (!validatedUserInput);

        if (userInput == "no") //if the user wants to quit, close the program
        {
            cout << "Have a nice day!" << endl;
        }
    } while (userInput == "yes");
}

// The main function that runs all the tests.
// Comment this function out when you test your user interface.
int main()
{
    string userInput;
    bool validatedUserInput{ false };
    do
    {
        cout << "Do you want to test the game or play the game?" << endl << endl;
        cout << "Type 'Test' if you want to run the tests." << endl;
        cout << "Type 'Play' if you want to play the game." << endl << endl;
        getline(cin, userInput);

        for (size_t i = 0; i < userInput.length(); ++i) //makes user input lower case
        {
            userInput.at(i) = tolower(userInput.at(i));
        }

        cout << endl;

        if (userInput == "test" || userInput == "play") { validatedUserInput = true; }

    } while (!validatedUserInput);

    if (userInput == "test") { tests(); }
    else { game(); }

    return 0;
}
