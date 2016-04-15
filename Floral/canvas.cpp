#include "canvas.h"
#include "constants.h"
#include "viewport.h"
#include <stdio.h>
void Canvas::init(){
    glutInitWindowSize(SCR_W,SCR_H);
    glutInitWindowPosition(50,50);
    glutCreateWindow("floral");

}

void Canvas::redraw(){
    glClearColor(0.0f,0.0f, 0.0f, 1.0f);//set the background to balck
    glClear(GL_COLOR_BUFFER_BIT);//clear the color buffer
    std::list<Shape*>::iterator it;
    for (it=displayList.begin();it!=displayList.end();it++){
        printf("drawing shape\n");
        ((Shape*)*it)->draw();
    }
}

void Canvas::reshape(){

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
