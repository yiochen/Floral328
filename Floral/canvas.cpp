#include "canvas.h"
#include "constants.h"
#include "viewport.h"
#include <stdio.h>
#include "circle.h"
#include "spiral.h"
#include "debug.h"

Canvas* Canvas::s_instance = NULL;

void Canvas::init(){
    glutInitWindowSize(SCR_W,SCR_H);
    glutInitWindowPosition(50,50);
    glutCreateWindow("floral");
	currentBranch = NULL;
}

void Canvas::redraw(){
	printf("canvas redraw");
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);*/
    glClearColor(0.0f,0.0f, 0.0f, 1.0f);//set the background to balck
    glClear(GL_COLOR_BUFFER_BIT);//clear the color buffer
    std::list<Shape*>::iterator it;
    for (it=displayList.begin();it!=displayList.end();it++){
        printf("drawing shape\n");
        ((Shape*)*it)->draw();
    }
}

void Canvas::reshape(){
	printf("canvas reshape\n");
}

void Canvas::add(Shape* shape){
    displayList.push_back(shape);
}

void Canvas::remove(Shape* shape){
    if (shape==NULL){
        fprintf(stderr,"removing NULL shape\n");
    }else{
        displayList.remove(shape);
    }
}

Branch* Canvas::getCurrentBranch() {
	if (currentBranch == NULL) {
		currentBranch = new Branch();
		this->add(currentBranch);
	}
	return currentBranch;
}

Branch* Canvas::addNewHandles(Vec tp) {
	Branch* branch = getCurrentBranch();
	Circle *lastCircle = NULL;
	Circle * circle;
	Spiral* spiral;
	Vec vl;
	Vec dis;
	if (branch->parts.begin() != branch->parts.end()) {
		lastCircle = branch->parts.back();
	}
	if (lastCircle != NULL) {
		vl = Vec(lastCircle->x, lastCircle->y);
	}
	switch (branch->parts.size()) {
	case 0:
		debug("creating new Circle\n");
		dis = Vec(branch->root.x, branch->root.y);
		dis = dis.add(tp.neg());
		printf("root at %f, %f\n", branch->root.x, branch->root.y);
		circle = new Circle(tp.x, tp.y, dis.mag());
		circle->range = 180.0f;
		circle->startAngle = dis.angle();
		printf("start angle is %f\n", circle->startAngle);
		circle->clockwise = true;
		branch->add(circle);
		debug("finish creating\n");
		break;
	case 1:
		debug("creating second Circle\n");
		if (lastCircle->inside(tp)) {
			//get center of lastCircle
			circle = new Circle(tp.x, tp.y, lastCircle->r - vl.add(tp.neg()).mag());
			branch->add(circle);
		}
		else {
			circle = new Circle(tp.x, tp.y, vl.add(tp.neg()).mag() - lastCircle->r);
			branch->add(circle);
			//if outside
		}
		debug("Finish creating\n");
		break;
		//create a stem circle
	case 2:
		debug("creating Spiral\n");
		if (lastCircle->inside(tp)) {
			//get center of lastCircle

			spiral = new Spiral(tp.x, tp.y, lastCircle->r - vl.add(tp.neg()).mag(), 0.0f);
			branch->add(spiral);
		}
		else {
			spiral = new Spiral(tp.x, tp.y, vl.add(tp.neg()).mag() - lastCircle->r, 0.0f);
			branch->add(spiral);
			//if outside
		}
		debug("finished createing\n");
		currentBranch = NULL;
		break;
		//create a spiral
	}
	return branch;
}