#ifndef flyingObject_h
#define flyingObject_h

#include "point.h"
#include "velocity.h"


// Put your FlyingObject class here

class FlyingObject
{
protected:
    Point point;
    Velocity velocity;
    float angle;
    bool alive;
    float speed;
    int radius;
    
public:
    //FlyingObject Constructors
    FlyingObject();
    FlyingObject(const Point point, const int speed, const float angle);
    
    //Getters
    Point getPoint() const {return point;}
    Velocity getVelocity() const {return velocity;}
    float getAngle() const {return angle;}
    bool isAlive() const {return alive;}
    float getSpeed() const {return speed;}
    int getRadius() const {return radius;}
    
    //Setters
    void setPoint(const Point point) {this->point = point;}
    void setVelocity(const Velocity velocity) {this->velocity = velocity;}
    void setAngle(const float angle) {this->angle = angle;}
    void setAlive(const bool alive) {this->alive = alive;}
    void setSpeed(const int speed) {this->speed = speed;}
    void setRadius(const int radius) {this->radius = radius;}
    
    //Other functions
    void kill();
    
    //Virtual functions
    virtual void draw() = 0;
    virtual void advance();
};


#endif /* flyingObject_h */
