#include <math.h>
#include "vector.h"
#include <stdio.h>
#include "constants.h"

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
    if (x==0 && y>=0) return 90;
    if (x==0 && y<0) return 270;
    if (x>0 && y==0) return 0;
    if (x<0 && y==0) return 180;
    if (y>0 && x>0){//0-90 deg
        return atan(y/x)* RAD2DEG;
    }
    if (y>0 && x<0){//90-180 deg y/x<0 atan<0
        return atan(y/x)* RAD2DEG+180.0f;
    }
    if (y<0 && x<0){//180-270 deg y/x>0 atan>0
        return atan(y/x)* RAD2DEG+180.0f;
    }
    if (y<0 && x>0){//270-360 deg y/x<0 atan<0
        return atan(y/x)* RAD2DEG+360.0f;
    }
    return atan(y/x) * RAD2DEG;
}
