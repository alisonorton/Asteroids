/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include "point.h"
#include "velocity.h"
#include "ship.h"
#include "rocks.h"
#include "bullet.h"
#include "uiInteract.h"
#include "uiDraw.h"

#include <vector>


class Game
{
private:
    Ship *ship;
    std::vector<Rock *> rocks;
    std::vector<Bullet> bullets;
    Point topLeft;
    Point bottomRight;
    Ship * createShip();
    void advanceShip();
    void createInitialAsteroids();
    void advanceRock();
    void advanceBullets();
    
    float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;
    void handleCollisions();
    void cleanUpZombies();
    
public:
    Game(const Point tl, const Point br);
    ~Game();
    void handleInput(const Interface & ui);
    void advance();
    void draw(const Interface & ui);
    
};


#endif /* GAME_H */
