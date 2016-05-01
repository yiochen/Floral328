#include "branch.h"

#include <list>
#include "common.h"

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
			if (lastCircle->startAngle < ang1) {
				lastCircle->range = lastCircle->startAngle + 360.0 - ang1;
			}
			else {
				lastCircle->range = lastCircle->startAngle - ang1;
			}
            //lastCircle->range=abs(lastCircle->startAngle-ang1);
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
	printf("the radius is %f and the coor is %f, %f\n", part->r, part->x, part->y);
    this->parts.push_back(part);
    return this;
}

void Branch::draw(){
 //   list<Circle*>::iterator it=parts.begin();
 //   while (it!=parts.end()){
 //       //save the original location
 //       Circle * c=(Circle*)(*it);
 //      /* GLfloat cx=c->x;
 //       GLfloat cy=c->y;
 //       c->x=this->x+cx;
 //       c->y=this->y+cy;*/
 //       ((Circle*)(*it))->draw();
 //       //recover the position
 //      /* c->x=cx;
 //       c->y=cy;*/
 //       it++;
 //   }
	//flog("the lenght of the branch is %f", getLength());
	drawSolid(20, 0);
}
void Branch::drawSolid(float initWidth, float endWidth) {
	list<Circle*>::iterator it = parts.begin();
	float total = getLength();
	float current = 0;
	while (it != parts.end()) {
		//save the original location
		Circle * c = (Circle*)(*it);
		/* GLfloat cx=c->x;
		GLfloat cy=c->y;
		c->x=this->x+cx;
		c->y=this->y+cy;*/
		c->drawSolid(Vec::lerp(initWidth,endWidth, current, total),Vec::lerp(initWidth, endWidth, current+c->getLength(), total));
		current += c->getLength();
		//recover the position
		/* c->x=cx;
		c->y=cy;*/
		it++;
	}
}

float Branch::getLength() {
	list<Circle*>::iterator it = parts.begin();
	float length = 0;

	while (it != parts.end()) {
		Circle* c = (Circle*)(*it);
		length += c->getLength();
		it++;
	}
	return length;
}