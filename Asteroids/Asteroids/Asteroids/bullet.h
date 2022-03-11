#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "flyingObject.h"


// Put your Bullet class here
/*****************************************************************
 * I don't know why it's complaining about the bullet class when I
 * make it in LINUX, but the code works just fine in xcode.
 ****************************************************************/

class Bullet : public FlyingObject
{
private:
    int life;
public:
    Bullet();
    int getLife() const {return life;}
    void setLife(const int life) {this->life = life;}
    void draw();
    void kill();
    void fire(const Point point, const float angle);
};



#endif /* bullet_h */
