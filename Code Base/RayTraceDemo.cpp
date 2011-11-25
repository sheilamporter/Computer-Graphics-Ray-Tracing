#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Scene.h"
#include "Objects.h"
#include "Rays.h"
#include "Camera.h"
#include "Vector3.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

int width = 0;
int height = 0;
Scene* scene = new Scene();

// Drawing (display) routine.
void drawScene(void)
{
	// Clear screen to background color.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// spawn rays iteratively using camera point and point on camera plane
	float* pixelData = new float[3*width*height];

	Vector3* camera = new Vector3(0.0f, 0.0f, 0.0f);
	Vector3* planeBotLeft = new Vector3(-1.0f, -1.0f, 0.5f);
	Vector3* planeUp = new Vector3(0.0f, 2.0f, 0.0f);
	Vector3* planeRight = new Vector3(2.0f, 0.0f, 0.0f);

	for(int h = 0; h < height; h++)
	{
		for(int w = 0; w < width; w++)
		{
			float widthPercent = (float)w / width;
			float heightPercent = (float)h / height;
			Vector3* heightPoint = (*planeBotLeft) + ((*planeUp) * heightPercent);
			Vector3* widthPoint = (*planeBotLeft) + ((*planeRight) * widthPercent);
			Vector3* planePoint = new Vector3(widthPoint->v[0], heightPoint->v[1], 0.5f);

			Ray* ray = new Ray(camera, (*planePoint) - camera);
			ray->cast(scene->objects, scene->lights);
			
			int baseIndex = h*width*3 + w*3;
			pixelData[baseIndex] = ray->color->v[0];
			pixelData[baseIndex+1] = ray->color->v[1];
			pixelData[baseIndex+2] = ray->color->v[2];

			//delete ray;
			delete heightPoint;
			delete widthPoint;
			delete planePoint;
		}
	}

	// Draw the pixels to the screen, using the color data from the rays
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixelData);

	// Flush created objects to the screen, i.e., force rendering.
	glFlush();

	delete camera;
	delete planeBotLeft;
	delete planeUp;
	delete planeRight;
	delete [] pixelData;
}

void setupScene(void)
{
	scene->addObject(new Sphere(new Vector3(0.0f, 0.0f, 2.0f), 1.0f));
}

// Initialization routine.
void setup(void) 
{
	// Set background (or clearing) color.
	glClearColor(1.0, 1.0, 1.0, 0.0); 
	setupScene();
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
	glutCreateWindow("Ray Tracing Demo");
   
	// Initialize.
	setup(); 
   
	// Register display routine.
	glutDisplayFunc(drawScene); 
   
	// Register reshape routine.
	glutReshapeFunc(resize);  

	// Register keyboard routine.
	glutKeyboardFunc(keyInput);

	// Begin processing.
	glutMainLoop(); 

	return 0;  
}
