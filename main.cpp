#include "opengl_include.h"
#include "viewport.h"
#include "debug.h"
#include "string.h"
#include <math.h>
#include <chrono>
#include <thread>
#include "constants.h"
#include "vector.h"
#include "canvas.h"
#include "drawingPrem.h"

//shapes
#include "shape.h"
#include "circle.h"


#include <list>

#define MAX_VERTS 100

using namespace std;

list<Vec> controlHandles;
Canvas * canvas=NULL;
Circle* circle=NULL;

void renderUI(){
    //draw the contollHandles
    list<Vec>::iterator list=controlHandles.begin();
    while (list!=controlHandles.end()){
        Vec v=*list;
        drawPoint(v.x, v.y);
        list++;
    }
}
void display(){
    printf("drawing nothin\n");
    if (canvas!=NULL){
        canvas->redraw();
    }
    renderUI();
    glFlush();
}


void pause(){
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}
void keyboard(unsigned char key, int x, int y){


}

void mouse(int mousebutton, int mousestate, int x, int y){
    if (mousestate==GLUT_DOWN){
        if (controlHandles.size()<3){
            //make a vector and push it
            Vec v(rawx2px(x),rawy2px(y));
            controlHandles.push_back(v);
            printf("control added ,there are %d controls",(int)controlHandles.size());
        }else{
            //the size is 3 draw the circle and clear the list
            controlHandles.clear();
        }
        glutPostRedisplay();
    }

}



void motion(int x, int y){

    glutPostRedisplay();
    // drawPoint(rawx2px(x),rawy2px(y),NULL);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    canvas=new Canvas();
    canvas->init();
    circle=new Circle(0.0f, 0.0f, 50.0f);

    printf("point 50,50");
    Vec tv(93.3013f,75.0f);
    printf("the point is at circle, %d\n",circle->pointAt(tv));
    Circle* c2=new Circle(60.0f,80.0f,50.0f);
    printf("the circles are touching %d and at %f,%f\n", circle->touching(c2), circle->touchingAt(c2).x, circle->touchingAt(c2).y);
    canvas->add(circle);
    canvas->add(c2);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
