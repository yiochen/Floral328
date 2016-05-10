#ifndef CANVAS_H
#define CANVAS_H

#include "common.h"
#include "shape.h"
#include <list>
#include "branch.h"

class Canvas{
private:
	static Canvas* s_instance;
	Branch* currentBranch;
	Canvas() {}
public:
	static Canvas* instance() {
		if (s_instance == NULL) {
			s_instance = new Canvas();
		}
		return s_instance;
	}
    std::list<Shape*> displayList;
	Branch* getCurrentBranch();
	
    void init(float width, float height);
    void redraw();
    void reshape();
    void add(Shape* shape);
    void remove(Shape* shape);
	void clear();
	Branch* addNewHandles(Vec handle);
	Branch* addNewBranch(Vec root, bool clockwise);
};

#endif
