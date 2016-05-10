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
sel::State state{ true };
LTexture* texture = NULL;
bool useTexture = true;
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
	//texture->render(100, 0);
    glFlush();
}
void reshape(int width, int height) {
	lReshape(width, height);
	state["config"]["win_width"] = width;
	state["config"]["win_height"] = height;
	canvas->reshape();
	display();
}
void constructScene() {
	canvas->clear();
	if (useTexture) printf("using texture");
	int totalBanch = state["getTotalBranch"]();
	for (int i = 0; i < totalBanch; i++) {
		int branchSize = state["getBranchSize"](i);
		canvas->addNewBranch(Vec(0, 0), true);
		for (int j = 0; j < branchSize; j++) {
			int x, y;
			sel::tie(x, y) = state["getVec"](i, j);
			canvas->addNewHandles(Vec(x, y));
		}
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 's':screenshot(); break;
	case 'c':state["construct"](); constructScene(); break;
	}

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
	
	state.Load("main.lua");
	if ((bool)(state["config"]["use_texture"]) == true) {
		useTexture = true;
	}
    glutInit(&argc, argv);
    canvas=Canvas::instance();
    canvas->init((int)state["config"]["win_width"],(int)state["config"]["win_height"]);
	initGL();
	if (useTexture) {
		texture = new LTexture();
		texture->init();
		texture->loadTextureFromFile("colorstrip.jpg");
	}
	
	//angleTest();
	constructScene();
    glutDisplayFunc(display);

	glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
