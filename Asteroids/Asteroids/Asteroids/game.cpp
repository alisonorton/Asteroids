/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"
#include "ship.h"
#include "bullet.h"
#include "point.h"
#include "flyingObject.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;



/**********************************************************
 * GAME CONSTRUCTOR
 *********************************************************/
Game::Game(Point tl, Point br) : topLeft(tl), bottomRight(br), ship(0)
{
    Point point;
    createInitialAsteroids();
}

/**********************************************************
 * GAME DESTRUCTOR
 *********************************************************/
Game::~Game()
{
    std::vector<Rock *>::iterator it = rocks.begin();
    
    while (it != rocks.end())
    {
        if ((*it) != NULL)
        {
            delete (*it);
        }
        it++;
    }
    
    delete ship;
}


/**********************************************************
 * GAME :: CREATE INITIAL ASTEROIDS
 *********************************************************/
void Game::createInitialAsteroids()
{
    for (int i = 0; i < 5; i++)
    {
        Point point;
        
        int x = random(-200, 200);
        int y = random(-200, 200);
        
        point.setX(x);
        point.setY(y);
        
        int speed = 8;
        float angle = (random(-180, 180));
        
        rocks.push_back(new BigRock(point, speed, angle));
    }
}


/**********************************************************
 * GAME :: CREATE SHIP
 *********************************************************/
Ship* Game::createShip()
{
    Ship *newShip = NULL;
    Point point;
    
    point.setX(random(-200, 200));
    point.setY(random(-200, 200));
    
    newShip = new Ship(point);
    
    return newShip;
}


/**********************************************************
 * GAME :: ADVANCE
 *********************************************************/
void Game::advance()
{
    //Advancing all flying objects
    
    advanceShip();
    advanceRock();
    advanceBullets();
    handleCollisions();
}


/**********************************************************
 * GAME :: ADVANCE BULLETS
 *********************************************************/
void Game :: advanceBullets()
{
    // Move each of the bullets forward if it is alive
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].isAlive())
        {
            // this bullet is alive, so tell it to move forward
            bullets[i].advance();
            bullets[i].kill();
        }
    }
}

/**********************************************************
 * GAME :: ADVANCE SHIP
 *********************************************************/
void Game::advanceShip()
{
    if (ship == NULL)
    {
        // there is no ship right now, possibly create one
        ship = createShip();
        // "resurrect" it will some random chance
        if (random(0, 30) == 0)
        {
            // create a new ship
            ship = createShip();
        }
    }
    else
    {
        //If there is a ship, move it
        if (ship->isAlive())
        ship->advance();
    }
}
/**********************************************************
 * GAME :: ADVANCE ASTEROID
 *********************************************************/
void Game::advanceRock()
{
    std::vector<Rock *>::iterator it = rocks.begin();
    
    while (it != rocks.end())
    {
        //If the rock is alive...
        if ((*it)->isAlive())
        {
            //move it
            (*it)->advance();
        }
        it++;   //Incrementing through the loop
    }
}

/**********************************************************
 * GAME :: DRAW
 *********************************************************/
void Game::draw(const Interface & ui)
{
    //Drawing the ship
    if(ship->isAlive())
    {
        ship->draw();
    }
    
    //Going through the vecotr of pointers and drawing each
    //rock.
    for (int i =0; i < rocks.size(); i++)
    {
        if(rocks[i]->isAlive())
        {
            rocks[i]->draw();
        }
    }
    
    //Going through the vector of bullets and drawing them
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].isAlive())
        {
            bullets[i].draw();
        }
    }
    
}

/**********************************************************
 * GAME :: HANDLE INPUT
 *********************************************************/
void Game::handleInput(const Interface &ui)
{
    if(ui.isLeft())
    {
        ship->moveLeft();
    }
    
    if(ui.isRight())
    {
        ship->moveRight();
    }
    
    if(ui.isUp())
    {
        ship->applyThrust();
    }
    else if (!ui.isUp())
    {
        ship->setIsThrust(false);
    }
    
    //Check spacebar to fire bullets
    if(ui.isSpace())
    {
        Bullet newBullet;
        newBullet.fire(ship->getPoint(), ship->getAngle());
        
        bullets.push_back(newBullet);
    }
}


/**********************************************************
 * GAME :: HANDLE COLLISION
 *********************************************************/
void Game::cleanUpZombies()
{
    std::vector<Rock *>::iterator it = rocks.begin();
    
    while (it != rocks.end())
    {
        if ( ! ((*it)->isAlive()) )
        {
            delete (*it);
            it = rocks.erase(it);
        }
        else
        {
        it++;
        }
    }
}

/**********************************************************
 * GAME :: HANDLE COLLISION
 *********************************************************/
void Game::handleCollisions()
{
    std::vector<Rock *>::iterator it = rocks.begin();
    std::vector<Rock *> newRocks;
    
    while (it != rocks.end())
    {
        // now check for a hit (if it is close enough to any live bullets)
        for (int i = 0; i < bullets.size(); i++)
        {
            if (bullets[i].isAlive())
            {
                // this bullet is alive, see if its too close
                
                // check if the bird is at this point (in case it was hit)
                if ((*it) != NULL && (*it)->isAlive())
                {
                    
                    //getClosestDistance((*it), bullets[i]);
                    if (fabs(bullets[i].getPoint().getX() - (*it)->getPoint().getX()) < (*it)->getRadius()
                        && fabs(bullets[i].getPoint().getY() - (*it)->getPoint().getY()) < (*it)->getRadius())
                    {
                        //we have a hit!
                        newRocks = (*it)->hit();
                        // the bullet is dead as well
                        bullets[i].setAlive(false);
                        cout << bullets[i].isAlive();
                    }
                }
            } // if bullet is alive
            
        } // for bullets
        it++;
    }
    
    
    //Checking for collisions between rocks and the ship
    //I have not added a check for if the asteroid and the ship start at the same point
    for (int i = 0; i < rocks.size(); i++)
    {
        if(rocks[i]->isAlive() && ship->isAlive())
        {
            if (fabs(rocks[i]->getPoint().getX() - ship->getPoint().getX()) < ( ship->getRadius() + rocks[i]->getRadius() )
                && fabs(rocks[i]->getPoint().getY() - ship->getPoint().getY()) < ( ship->getRadius() + rocks[i]->getRadius()) )
            {
                ship->setAlive(false);
            }
        }
    }
    
    //Removing any dead objects from the vector
    cleanUpZombies();
    //Adding the returned vecotors to the main rock vector
    rocks.insert(rocks.end(), newRocks.begin(), newRocks.end());
}

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

