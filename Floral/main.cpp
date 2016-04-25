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

#include "IL/il.h"
#include "IL/ilu.h"
#include "LTexture.h"

#define MAX_VERTS 100

using namespace std;

list<Vec> controlHandles;
Canvas * canvas=NULL;
Branch* branch=NULL;


LTexture gLoadedTexture;


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
    if (canvas!=NULL){
        canvas->redraw();
    }
    renderUI();
	//gLoadedTexture.render(0, 0);
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
		printf("click at %f,%f\n", tp.x, tp.y);
		Circle *lastCircle=NULL;
        Circle * circle;
        Spiral* spiral;
        Vec vl;
		Vec dis;
		if (branch->parts.begin() != branch->parts.end()) {
			lastCircle= branch->parts.back();
		}
        if (lastCircle!=NULL){
            vl=Vec(lastCircle->x, lastCircle->y);
        }
        switch (controlHandles.size()){
            case 0:
                debug("creating new Circle\n");
				dis=Vec(branch->root.x, branch->root.y);
				dis = dis.add(tp.neg());
				printf("root at %f, %f\n", branch->root.x, branch->root.y);
                circle=new Circle(tp.x, tp.y, dis.mag());
				circle->range = 180.0f;
                circle->startAngle=dis.angle();
				printf("start angle is %f\n", circle->startAngle);
                circle->clockwise=true;
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
                branch=new Branch(0.0f,0.0f,Vec(50.0f,0.0f));
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
bool loadMedia() {
	
	//Load texture
	if (!gLoadedTexture.loadTextureFromFile("texture.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	}

	return true;
	
}
void angleTest() {
	Vec a(0, 1);
	printf("the angle of 0,1 is %f", a.angle());
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
	
	/*glutInitDisplayMode(GLUT_DOUBLE);
	glEnable(GL_TEXTURE_2D);*/
    canvas=new Canvas();
    canvas->init();
	angleTest();
	/*ilInit();
	loadMedia();*/
    
    branch=new Branch(0.0f,0.0f,Vec(50,0));
   
    canvas->add(branch);


    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
