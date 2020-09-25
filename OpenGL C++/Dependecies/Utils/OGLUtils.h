/*
  /------------------------------------------------------------------------\
  | OPENGL UTILITIES FOR VISUAL STUDIO C++ USING GLFW3 OPEN-SOURCE LIBRARY |
  |									   ver. 09.2020 by github.com/Haruno19 |
  \------------------------------------------------------------------------/

********************* D O C U M E N T A T I O N *****************************

	HOW TO USE on VISUAL STUDIO 2019 C++ EMPTY PROJEC

1. Copy Dependencies Folder into Solution Directory
2. Properties > C++ > General > Additional Include Directories		: $(SolutionDir)Dependecies/GLFW/include;$(SolutionDir)Dependecies/Utils
3. Properties > Linker > General > Additional Library Directories	: $(SolutionDir)Dependecies/GLFW/lib-vc2019
4. Properties > Linker > Input > Additional Dependencies		 add: glfw3.lib; opengl32.lib
5. #include "OGLUtils.h"

------------------------------------------------------------------------------------------------

	FUNCTION SHORTCUTS
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

	EXAMPLES

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

*/

/*-----------------NEEDED LIBRARIES-----------------------*/
#include "GLFW/glfw3.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*----------------WINDOW OBJECT DECLARATION--------------*/
GLFWwindow* window;
int MAXX=NULL, MAXY=NULL;

/*---------------FUNCTION LIST BY TYPE-------------------*/
//Core Functions
int InitWindow(int width, int height);
void ClearDevice();
void UpdateWindow();
#define CloseGraph() glfwTerminate()
//Colors
void SetColor(int r, int g, int b) { glColor3f(r,g,b); }
//Shapes
void Circle(float x, float y, float r);
void Line(int x1, int y1, int x2, int y2);
void Rect(int x1, int y1, int width, int height);



/*--------------------IMPLEMENTATION---------------------*/
//CORE
int InitWindow(int width, int height)
{	
	MAXX = width;
	MAXY = height;

	if (!glfwInit())
		return 1;

	window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &width, &height);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

void UpdateWindow()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void ClearDevice()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	UpdateWindow();
}


//SHAPES
void Circle(float x, float y, float r)
{
	glBegin(GL_LINE_LOOP);
		for (int ii = 0; ii < 100; ii++) 
		{
			float theta = 2.0f * 3.1415926f * float(ii) / float(100);//get the current angle 
			float x2 = r * cosf(theta);//calculate the x component 
			float y2 = r * sinf(theta);//calculate the y component 
			glVertex2f(x2 + x, y2 + y);//output vertex 
		}
	glEnd();
}

void Line(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
}

void Rect(int x, int y, int width, int height)
{
	glBegin(GL_LINES);
		glVertex2f(x, y);
		glVertex2f(x, y+height);
		
		glVertex2f(x+width, y+height);
		glVertex2f(x+width, y);

		glVertex2f(x, y);
		glVertex2f(x+width, y);

		glVertex2f(x, y+height);
		glVertex2f(x + width, y + height);
	glEnd();
}
