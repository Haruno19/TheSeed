

# **OPENGL UTILITIES FOR VISUAL STUDIO C++ USING GLFW3 OPEN-SOURCE LIBRARY**

GLFW: https://www.glfw.org/

-----------------------------------------------------------------------------------------------

## HOW TO USE on VISUAL STUDIO 2019 C++ EMPTY PROJECT

1. Copy Dependencies Folder into Solution Directory
2. Properties > C++ > General > Additional Include Directories		: $(SolutionDir)Dependecies/GLFW/include;$(SolutionDir)Dependecies/Utils
3. Properties > Linker > General > Additional Library Directories	: $(SolutionDir)Dependecies/GLFW/lib-vc2019
4. Properties > Linker > Input > Additional Dependencies	     add: glfw3.lib; opengl32.lib
5. Include "OGLUtils.h"

------------------------------------------------------------------------------------------------

## FUNCTION SHORTCUTS
Shortcuts name are taken from BGI library.

CORE FUNCTIONS
InitWindow(int width, int height)	 - Initializes the window of the specified size
CloseGraph()						 - Destroys all the windows
ClearDevice()					 	 - Blacks out the whole window
UpdateWindow()						 - Renders all the drawings on the window

COLORS
SetColor(int r, int g, int b)		 - The next drawing and the following ones will be this color RGB

SHAPES (to render all the drawings you need to call UpdateWindow() once you finished drawing)
Circle(int x, int y, int r)			 - Draws a cirlce, x and y are refering to the center
Line(int x1, int y1, int x2, int y2) - Draws a line from (x1;y1) to (x2;y2)

-------------------------------------------------------------------------------------------------

## EXAMPLE
Here's and example code to draw a red line and a blue circle


	#include "OGLUtils.h"

	int main()
	{
		InitWindow(500,500);	//initializes a 500x500 window
	
		SetColor(255,0,0);		//sets color to red
		Line(0,0,500,500);		//draws a line from the top left corner to the bottom right
		SetColor(0,0,255);		//sets color to blue
		Circle(250,250,50);		//draws a circle at (250,250) 
		UpdateWindow();			//renders the drawings

		system("pause");
		CloseGraph();			//destroys the window

		return 0;
	}

