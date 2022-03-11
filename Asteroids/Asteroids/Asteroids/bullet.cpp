#include "bullet.h"
#include "uiDraw.h"
#include "point.h"
#include "ship.h"
#include "math.h"
#include <cmath>


// Put your bullet methods here

Bullet::Bullet()
{
    setAlive(true);
    setAngle(0.0);
    setLife(0);
}

void Bullet::draw()
{
    setLife(life + 1);
    if(isAlive())
    {
        drawDot(point);
    }
}

void Bullet::kill()
{
    if (life == 40)
    {
        setAlive(false);
    }
}

void Bullet::fire(const Point point, const float angle)
{
    float dy = 10.0 * (cos(M_PI / 180.0 * angle));
    float dx = 10.0 * (-sin(M_PI / 180.0 * angle));
    
    velocity.setDx(dx);
    velocity.setDy(dy);
    
    this->point.setX(point.getX());
    this->point.setY(point.getY());
}
