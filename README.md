# README

Computer-generated spiral ornaments  

name: Yiou Chen  

Requirement: Visual Studio 2015  

## Overview 
The code is comprised of two parts. C++ engine and the lua files. C++ engine handles the rendering, while lua specifies the rules and configuration.

## How to run it  
Before running the program, you can modify the setting in the configuration file ($solutionDir/Floral/lua/config.lua). You can set the width and the height of the window, the numbers of branches to generate, whether you want to use texture.  
After you save the lua file, you can fire up Visual Studio 2015, open the solution and run the program. 

## Control
When the program runs, it will start out generate the graphics based on the settings in the lua configuration file. You mouse left click in the window to add more control handles to generate new branches. Each control points represent a center for an arc or spiral. A branch can have at most three components. After three clicks, a new branch will be created.   
Press "s" to save the image. Image will be saved as bmp format under ($SolutionDir/Floral/Floral/), by default, it's called "new_screenshot.bmp")  
Press "c" to reconstruct the scene. A new pattern will be generated based on the lua files. (Note that there is a bug that the new pattern will not be rendered immediately. You need to move the window to let it refresh in order to render)  
You can resize the window, and when you press "c" again, the newly generated pattern will be adapt to the new window size.   
