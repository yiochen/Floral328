#include "common.h"
#include "viewport.h"
#include "debug.h"
#include "string.h"
#include <math.h>

#include "main_include.h"
#define MAX_VERTS 100

using namespace std;
using namespace sel;
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
	lDisplay();
	if (canvas!=NULL){
        canvas->redraw();
    }
    renderUI();
    glFlush();
}
void reshape(int width, int height) {
	lReshape(width, height);
	canvas->reshape();
	display();
}


void keyboard(unsigned char key, int x, int y){


}

void mouse(int mousebutton, int mousestate, int x, int y){
    if (mousestate==GLUT_DOWN){
        Vec tp(rawx2px(x), rawy2px(y));
		canvas->addNewHandles(tp);
        if (controlHandles.size()<2){
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
	//screenshot();
}




int main(int argc, char** argv){
	sel::State state{ true };
	state.Load("hello.lua");
	
    glutInit(&argc, argv);
	
    canvas=Canvas::instance();
    canvas->init();
	initGL();
	angleTest();
	branch = canvas->getCurrentBranch();
    glutDisplayFunc(display);

	glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
