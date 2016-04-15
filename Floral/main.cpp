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
#include "spiral.h"
#include "branch.h"


#include <list>

#define MAX_VERTS 100

using namespace std;

list<Vec> controlHandles;
Canvas * canvas=NULL;
Branch* branch=NULL;
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
        Vec tp(rawx2px(x), rawy2px(y));

		Circle *lastCircle=NULL;
        Circle * circle;
        Spiral* spiral;
        Vec vl;
		if (branch->parts.begin() != branch->parts.end()) {
			lastCircle= branch->parts.back();
		}
        if (lastCircle!=NULL){
            vl=Vec(lastCircle->x, lastCircle->y);
        }
        switch (controlHandles.size()){
            case 0:
                debug("creating new Circle\n");
                circle=new Circle(tp.x, tp.y, 30.0f);
                circle->startAngle=270.0f;
                circle->clockwise=false;
                branch->add(circle);
                debug("finish creating\n");
                break;
                //creat a stem circle
            case 1:
                debug("creating second Circle\n");
                if (lastCircle->inside(tp)){
                    //get center of lastCircle
                    circle=new Circle(tp.x, tp.y, lastCircle->r-vl.add(tp.neg()).mag());
                    branch->add(circle);
                }else{
                    circle=new Circle(tp.x, tp.y, vl.add(tp.neg()).mag()-lastCircle->r);
                    branch->add(circle);
                    //if outside
                }
                debug("Finish creating\n");
                break;
                //create a stem circle
            case 2:
                debug("creating Spiral\n");
                if (lastCircle->inside(tp)){
                    //get center of lastCircle

                    spiral=new Spiral(tp.x, tp.y, lastCircle->r-vl.add(tp.neg()).mag(),0.0f);
                    branch->add(spiral);
                }else{
                    spiral=new Spiral(tp.x, tp.y, vl.add(tp.neg()).mag()-lastCircle->r,0.0f);
                    branch->add(spiral);
                    //if outside
                }
                debug("finished createing\n");
                break;
                //create a spiral
            case 3:
                //create a new branch
                branch=new Branch(0.0f,0.0f,Vec(0.0f,0.0f));
                canvas->add(branch);
                break;
        }
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
    Vec left=Vec(-1, 0);
    printf("left's angle is suppose to be 180, %f\n", left.angle());
    branch=new Branch(0.0f,0.0f,Vec(0,0));
    // circle=new Circle(50.0f, 0.0f, 50.0f);
    // circle->clockwise=false;
    //
    // Circle* c2=new Circle(110.0f,80.0f,50.0f);
    // printf("the circles are touching %d and at %f,%f\n", circle->touching(c2), circle->touchingAt(c2).x, circle->touchingAt(c2).y);
    // //create a spiral
    // Spiral* s=new Spiral(10.0f,80.0f,50.0f,90.0f);
    //
    // s->gap=5.0f;
    // Branch* branch=new Branch(-40.0f,0.0f,Vec(0,0));
    // branch->add(circle)->add(c2)->add(s);
    canvas->add(branch);


    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
