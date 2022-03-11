#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flyingObject.h"
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"
#include <vector>

// Define the following classes here:
//   Rock
//   BigRock
//   MediumRock
//   SmallRock

class Rock : public FlyingObject
{
protected:
    int rotation;
    int rotationDelta;
public:
    Rock(const Point point, const int speed, const float angle);
    int getRotation() const {return rotation;}
    int getRotationDelta() const {return rotationDelta;}
    void setRotation(const int rotation) {this->rotation = rotation;}
    void setRotationDelta(const int rotationDelta) {this->rotationDelta = rotationDelta;}
    virtual void calculateVelocity();
    virtual void draw() = 0;
    virtual std::vector<Rock *> hit() = 0;
};



/**************************************************
 * BIG ROCK
 **************************************************/

class BigRock : public Rock
{
public:
    BigRock(const Point point, const int speed, const float angle);
    void calculateVelocity();
    void draw();
    std::vector<Rock *> hit();
};

/**************************************************
 * MEDIUM ROCK
 **************************************************/

class MediumRock : public Rock
{
public:
    MediumRock(const Point point, const int speed, const float angle);
    void calculateVelocity();
    void draw();
    std::vector<Rock *> hit();
};


/**************************************************
 * SMALL ROCK
 **************************************************/

class SmallRock : public Rock
{
public:
    SmallRock(const Point point, const int speed, const float angle);
    void calculateVelocity();
    void draw();
    std::vector<Rock *> hit();
};



#endif /* rocks_h */










