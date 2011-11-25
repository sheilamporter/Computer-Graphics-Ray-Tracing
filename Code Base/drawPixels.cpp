#include <iostream>
#include <stdlib.h>
#include <time.h>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

int width = 0;
int height = 0;

// Drawing (display) routine.
void drawScene(void)
{
	// Clear screen to background color.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Fill an array of floats (3 for each pixel) with random color data
	float *pixelData = new float[3*width*height];
	for(int h = 0; h < height; h++)
	{
		for(int w = 0; w < width; w++)
		{
			float heightPercent = (float)h / height;
			float widthPercent = (float)w / width;
			int baseIndex = h*width*3 + w*3;
			pixelData[baseIndex] = widthPercent;
			pixelData[baseIndex+1] = heightPercent;
			pixelData[baseIndex+2] = 0.0f;
		}
	}

	// Draw the pixels to the screen, using the random color data
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixelData);

	// Flush created objects to the screen, i.e., force rendering.
	glFlush(); 
}

// Initialization routine.
void setup(void) 
{
	// Set background (or clearing) color.
	glClearColor(1.0, 1.0, 1.0, 0.0); 
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	// store the width and height as globals
	width = w;
	height = h;

	// Set viewport size to be entire OpenGL window.
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  
	// Set matrix mode to projection.
	glMatrixMode(GL_PROJECTION);

	// Clear current projection matrix to identity.
	glLoadIdentity();

	// Specify the orthographic (or perpendicular) projection, 
	// i.e., define the viewing box.
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);

	// Set matrix mode to modelview.
	glMatrixMode(GL_MODELVIEW);

	// Clear current modelview matrix to identity.
	glLoadIdentity();
	glutPostRedisplay();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch(key) 
	{
		// Press escape to exit.
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

void callback(int cdecl)
{
	glutPostRedisplay();
}

// Main routine: defines window properties, creates window,
// registers callback routines and begins processing.
int main(int argc, char **argv) 
{
	// Seed the random number generator
	srand(time(NULL));

	// Initialize GLUT.
	glutInit(&argc, argv);
 
	// Set display mode as single-buffered and RGB color.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   
	// Set OpenGL window size.
	glutInitWindowSize(500, 500);

	// Set position of OpenGL window upper-left corner.
	glutInitWindowPosition(100, 100); 
   
	// Create OpenGL window with title.
	glutCreateWindow("Draw Pixels");
   
	// Initialize.
	setup(); 
   
	// Register display routine.
	glutDisplayFunc(drawScene); 
   
	// Register reshape routine.
	glutReshapeFunc(resize);  

	// Register keyboard routine.
	glutKeyboardFunc(keyInput);

	// Register a timer callback for redisplay
	glutTimerFunc(5, callback, 1);
   
	// Begin processing.
	glutMainLoop(); 

	return 0;  
}
