# README

Computer-generated spiral ornaments  

name: Yiou Chen  

Requirement: Visual Studio 2015  

## Overview
The code is comprised of two parts. C++ engine and the lua files. C++ engine handles the rendering, while lua specifies the rules and configuration. This project is based on the paper *Computer-Generated Floral Ornament*

## How to run it  
Before running the program, you can modify the setting in the configuration file ($solutionDir/Floral/lua/config.lua). You can set the width and the height of the window, the numbers of branches to generate, whether you want to use texture.  
After you save the lua file, you can fire up Visual Studio 2015, open the solution and run the program.

## Control
- Press **s** to save the image. Image will be saved as bmp format under ($SolutionDir/Floral/Floral/), by default, it's called **new_screenshot.bmp**)  
- Press **c** to reconstruct the scene. A new pattern will be generated based on the lua files. (Note that there is a bug that the new pattern will not be rendered immediately. You need to move the window to let it refresh in order to render)  
- You can resize the window, and when you press **c** again, the newly generated pattern will be adapt to the new window size.   

## Credit
This project uses the following libraries.  
- [SOIL][SOIL]: Simple Opengl Image Library. It's a library used for leading texture.
- [Selene][Selene]: A library for reading lua files.


[SOIL]:http://www.lonesock.net/soil.html
[Selene]:https://github.com/jeremyong/Selene
