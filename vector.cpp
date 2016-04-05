#include <math.h>
#include "vector.h"
#include <stdio.h>

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
