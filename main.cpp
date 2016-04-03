#include "opengl_include.h"
#include "viewport.h"
#include "debug.h"
#include "string.h"
#include <math.h>
#include <chrono>
#include <thread>
#include "constants.h"
#include "vector.h"
#include <list>

#define MAX_VERTS 100

using namesapce std;

list<Vec> controlHandles;


void drawCircle(float radius){
    glBegin(GL_LINE_LOOP);
    glColor3f(1,0,0);
    for (int i=0; i<=360;i++){
        float deg=i*DEG2RAD;
        glVertex2f(cos(deg)*radius, sin(deg)*radius);
    }
    glEnd();
}
void display(){
    glClearColor(0.0f,0.0f, 0.0f, 1.0f);//set the background to balck
    glClear(GL_COLOR_BUFFER_BIT);//clear the color buffer
    glLineWidth(2.5);
    glColor3f(1.0,0.0,0.0);

    glBegin(GL_LINES);
    glVertex3f(px2x(50),px2y(0),0);
    glVertex3f(px2x(50),px2y(40),0);
    glEnd();
    drawCircle(l2x(50));
    glFlush();
}


void pause(){
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}
void keyboard(unsigned char key, int x, int y){


}

void mouse(int mousebutton, int mousestate, int x, int y){
    if (controlHandles.size()<3){
        //make a vector and push it
        controlHandles.push(Vec(rawx2px(x),rawy2px(y)));
    }else{
        //the size is 3 draw the circle and clear the list

    }
    glutPostRedisplay();
}



void motion(int x, int y){

    glutPostRedisplay();
    // drawPoint(rawx2px(x),rawy2px(y),NULL);
}
void init(){

}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    init();
    glutInitWindowSize(SCR_W,SCR_H);
    glutInitWindowPosition(50,50);
    glutCreateWindow("floral");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
