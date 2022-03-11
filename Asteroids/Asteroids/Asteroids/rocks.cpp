#include "rocks.h"
#include "flyingObject.h"
#include "velocity.h"
#include "point.h"
#include "uiDraw.h"
#include <vector>

// Put your Rock methods here


/***********************************************************
 * ROCK IMPLEMENTATIONS
 **********************************************************/
Rock::Rock(const Point point, const int speed, const float angle) : FlyingObject(point, speed, angle)
{
    setAlive(true);
    setRotation(0);
    setRotationDelta(0);
    calculateVelocity();
}


void Rock::draw()
{
    //Is not defined in an abstract class
}

void Rock::calculateVelocity()
{
    float dy = 0.5 * (cos(3.14 / 180.0 * angle));
    float dx = 0.5 * (-sin(3.14 / 180.0 * angle));
    
    velocity.setDy(velocity.getDy() + dy);
    velocity.setDx(velocity.getDx() + dx);
}

/***********************************************************
 * BIG ROCKS :: IMPLEMENTATIONS
 **********************************************************/
BigRock::BigRock(const Point point, const int speed, const float angle) : Rock(point, speed, angle)
{
    setRotation(2);
    setRotationDelta(5);
    setRadius(16);
    setSpeed(0.5);
    setAngle(random(-180, 180));
    calculateVelocity();
}


//Drawing the big asteroid
void BigRock::draw()
{
    setRotation(rotation + rotationDelta);
    drawLargeAsteroid(point, rotation);
}


void BigRock::calculateVelocity()
{
    float dy = 0.5 * (cos(3.14 / 180.0 * angle));
    float dx = 0.5 * (-sin(3.14 / 180.0 * angle));
    
    velocity.setDy(velocity.getDy() + dy);
    velocity.setDx(velocity.getDx() + dx);
}

/**********************************************************************
 * BIG ROCKS :: HIT
 * This function will kill the asteroid, and then it will populate a
 * vector with dynamically allocated asteroids, causting it to "break"
 * on the screen.
 **********************************************************************/
std::vector<Rock *> BigRock::hit()
{
    kill();
    std::vector<Rock*> newRocks;
    
    //Populating the vector for when a big asteroid breaks
            newRocks.push_back(new MediumRock(point, speed, 90));
            newRocks.push_back(new MediumRock(point, speed, 270));
            newRocks.push_back(new SmallRock(point, speed, 0));

    return newRocks;
    
}

/***********************************************************
 * MEDIUM ROCKS IMPLEMENTATIONS
 **********************************************************/
MediumRock::MediumRock(const Point point, const int speed, const float angle) : Rock(point, speed, angle)
{
    setRotation(5);
    setRotationDelta(10);
    setSpeed(1);
    setRadius(8);
    setAngle(angle);
    calculateVelocity();
}


//Drawing the medium asteroid
void MediumRock::draw()
{
    setRotation(rotation + rotationDelta);
    drawMediumAsteroid(point, 0);
}


void MediumRock::calculateVelocity()
{
    float dy = 0.75 * (cos(3.14 / 180.0 * angle));
    float dx = 0.75 * (-sin(3.14 / 180.0 * angle));
    
    velocity.setDy(velocity.getDy() + dy);
    velocity.setDx(velocity.getDx() + dx);
}

/**********************************************************************
 * MEDIUM ROCKS :: HIT
 * This function will kill the asteroid, and then it will populate a
 * vector with dynamically allocated asteroids, causting it to "break"
 * on the screen.
 **********************************************************************/
std::vector<Rock *> MediumRock::hit()
{
    kill();
    std::vector<Rock*> newRocks;
    
    //Populating the vector for when a medium asteroid breaks
    newRocks.push_back(new SmallRock(point, speed, 180));
    newRocks.push_back(new SmallRock(point, speed, 0));
    return newRocks;
}



/***********************************************************
 * SMALL ROCK IMPLEMENTATIONS
 **********************************************************/
SmallRock::SmallRock(const Point point, const int speed, const float angle) : Rock(point, speed, angle)
{
    setRotation(10);
    setRotationDelta(15);
    setRadius(4);
    calculateVelocity();
}


//Drawing the small asteroid
void SmallRock::draw()
{
    setRotation(rotation + rotationDelta);
    drawSmallAsteroid(point, 0);
}

void SmallRock::calculateVelocity()
{
    float dy = 1 * (cos(3.14 / 180.0 * angle));
    float dx = 1 * (-sin(3.14 / 180.0 * angle));
    
    velocity.setDy(velocity.getDy() + dy);
    velocity.setDx(velocity.getDx() + dx);
}

/**********************************************************************
 * SMALL ROCKS :: HIT
 * This function will kill the asteroid.
 * Small asteroids do not break apart.  They disappear off of the screen.
 **********************************************************************/
std::vector<Rock *> SmallRock::hit()
{
    kill();
    std::vector<Rock*> newRocks;
    
    //Small asteroids don't return any new asteroids when they break
    
    return newRocks;
}







