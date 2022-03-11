#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#include "point.h"
#include "velocity.h"
#include "flyingObject.h"


// Put your Ship class here

class Ship : public FlyingObject
{
private:
    bool isThrust;
public:
    Ship(const Point &point);
    Point getPoint() const {return point;}
    Velocity getVelocity() const {return velocity;}
    bool getIsThrust() const {return isThrust;}
    
    void setPoint(const Point point) {this->point = point;}
    void setVelocity(const Velocity velocity) {this->velocity = velocity;}
    void setIsThrust(const bool isThrust) {this->isThrust = isThrust;}
    
    void applyThrust();
    void moveRight();
    void moveLeft();
    void draw();
};

#endif /* ship_h */
