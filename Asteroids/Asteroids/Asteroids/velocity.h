#ifndef VELOCITY_H
#define VELOCITY_H


// Put your velocity class here, or overwrite this file with your own
// velocity class from the previous project

#include <stdio.h>

class Velocity
{
private:
    float Dx;
    float Dy;
    
public:
    Velocity();
    Velocity(const float Dx, const float Dy);
    
    void calcVelocity(const int angle, const float speed);
    
    float getDx() const {return Dx;}
    float getDy() const {return Dy;}
    
    void setDx(const float Dx) {this->Dx = Dx;}
    void setDy(const float Dy) {this->Dy = Dy;}
};

#endif /* velocity_h */
