#include <math.h>
#include <stdio.h>

#define PI 3.141592653

int main(){
    float DEG2RAD=PI/180.0f;
    float RAD2DEG=180.f/PI;
    printf("atan(-1) is 135, %f\n",atan(-1)*RAD2DEG);
}
