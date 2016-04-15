#include "branch.h"
#include <stdio.h>
#include <list>

using namespace std;

Branch* Branch::add(Circle* part){
    //add the circle, calculating the touching point and change the begin angle or range
    //If the part is not the first element in the array
    //Then assume that it is touching the previous element

    if (this->parts.size()>=1){
        //not the first element, change the property
        Circle* lastCircle=this->parts.back();
        Vec touchingPoint=lastCircle->touchingAt(part);
        //find the angle
        Vec o1(lastCircle->x, lastCircle->y);
        Vec o2(part->x, part->y);
        Vec dis1=touchingPoint.add(o1.neg());
        Vec dis2=touchingPoint.add(o2.neg());
        //modify the range of the previous circle and the startAngle of the current circle
        GLfloat ang1=dis1.angle();
        GLfloat ang2=dis2.angle();
        if (lastCircle->clockwise){
            printf("last circle starting angle is %f and ang1 is %f\n", lastCircle->startAngle, ang1);
            lastCircle->range=abs(lastCircle->startAngle-ang1);
        }else{
            lastCircle->range=ang1-lastCircle->startAngle;
            if (lastCircle->range<0) lastCircle->range+=360;
        }
        part->startAngle=ang2;
        if (lastCircle->inside(part)){
            part->clockwise=lastCircle->clockwise;
        }else{
            part->clockwise=!(lastCircle->clockwise);
        }
        
    }
    this->parts.push_back(part);
    return this;
}

void Branch::draw(){
    list<Circle*>::iterator it=parts.begin();
    while (it!=parts.end()){
        //save the original location
        Circle * c=(Circle*)(*it);
        GLfloat cx=c->x;
        GLfloat cy=c->y;
        c->x=this->x+cx;
        c->y=this->y+cy;
        ((Circle*)(*it))->draw();
        //recover the position
        c->x=cx;
        c->y=cy;
        it++;
    }
}
