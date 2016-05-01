#pragma once
#include "opengl_include.h"
bool initGL();
/*
Pre Condition:
-A valid OpenGL context
Post Condition:
-Initializes viewport, matrices, and clear color
-Reports to console if there was an OpenGL error
-Returns false if there was an error in initialization
Side Effects:
-Sets viewport to the fill rendering area
-Projection matrix is set to an orthographic matrix
-Modelview matrix is set to identity matrix
-Matrix mode is set to modelview
-Clear color is set to black
-Texturing is enabled
*/

//bool lLoadMedia();
/*
Pre Condition:
-A valid OpenGL context
Post Condition:
-Loads media to use in the program
-Reports to console if there was an error in loading the media
-Returns true if the media loaded successfully
Side Effects:
-None
*/

void update();
/*
Pre Condition:
-None
Post Condition:
-Does per frame logic
Side Effects:
-None
*/

void lRender();
/*
Pre Condition:
-A valid OpenGL context
-Active modelview matrix
Post Condition:
-Renders the scene
Side Effects:
-Clears the color buffer
-Swaps the front/back buffer
*/
void runMainLoop(int val);