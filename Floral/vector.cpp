
#include "vector.h"
#include <stdio.h>
#include "constants.h"

float Vec::PI = 3.1415926f;

Vec::Vec(){
    this->x=1.0f;
    this->y=0.0f;
}
Vec::Vec(GLfloat x, GLfloat y){
    this->x=x;
    this->y=y;
}
Vec Vec::add(Vec v2){
    Vec v(this->x+v2.x, this->y+v2.y);
    return v;
}
Vec Vec::sub(Vec v2) {
	Vec v(this->x - v2.x, this->y - v2.y);
	return v;
}
Vec Vec::neg(){
    Vec v(-(this->x), -(this->y));
    return v;
}
Vec Vec::norm(){
    Vec v;
    GLfloat m=this->mag();
    if (m==0){
        fprintf(stderr, "cal norm for zero length vector");
        exit(1);
    }
    return this->mul(1/m);
}
Vec Vec::mul(GLfloat s){
    Vec v(this->x*s,this->y*s);
    return v;
}

GLfloat Vec::mag(){
    return sqrt(this->x*this->x+this->y*this->y);
}

GLfloat Vec::angle(){
    if (x==0 && y>=0) return 90.0f;
    if (x==0 && y<0) return 270.0f;
    if (x>0 && y==0) return 0.0f;
    if (x<0 && y==0) return 180.0f;
    if (y>0 && x>0){//0-90 deg
		//printf("y=%f, x=%f, y>0,x>0 y/x is %f, atan(y/x) is %f, rad2deg(atan) is %f\n", y, x, y / x, atan(y / x), rad2deg(y / x));
        return Vec::rad2deg(atan(y/x));
    }
    if (y>0 && x<0){//90-180 deg y/x<0 atan<0
        return Vec::regulizeDeg(rad2deg(atan(y/x))+180.0f);
    }
    if (y<0 && x<0){//180-270 deg y/x>0 atan>0
        return Vec::regulizeDeg(rad2deg(atan(y/x))+180.0f);
    }
    if (y<0 && x>0){//270-360 deg y/x<0 atan<0
        return Vec::regulizeDeg(rad2deg(atan(y/x))+360.0f);
    }
    return rad2deg(atan(y/x));
}
