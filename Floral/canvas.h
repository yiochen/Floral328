#ifndef CANVAS_H
#define CANVAS_H

#include "common.h"
#include "shape.h"
#include <list>


class Canvas{
public:
    std::list<Shape*> displayList;
    void init();
    void redraw();
    void reshape();
    void add(Shape* shape);
    void remove(Shape* shape);

	
};

#endif
