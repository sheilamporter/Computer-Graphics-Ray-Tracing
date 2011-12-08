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

#define PATH_RENDERS 5

int width = 500;
int height = 500;
Scene* scene = new Scene();
float* pixelData;
int numRenders = 0;

void pathCast(void)
{
	// spawn rays iteratively using camera point and point on camera plane

	numRenders++;
	cout << numRenders << endl;

	Vector3 camera(0.0f, 0.0f, -5.0f);
	Vector3 planeBotLeft(-1.0f, -1.0f, 0.5f);
	Vector3 planeUp(0.0f, 2.0f, 0.0f);
	Vector3 planeRight(2.0f, 0.0f, 0.0f);

	for(int h = 0; h < height; h++)
	{
		for(int w = 0; w < width; w++)
		{
			float widthPercent = (float)w / width;
			float heightPercent = (float)h / height;
			Vector3 heightPoint = planeBotLeft + (planeUp * heightPercent);
			Vector3 widthPoint = planeBotLeft + (planeRight * widthPercent);
			Vector3 planePoint(widthPoint.v[0], heightPoint.v[1], 0.5f);

			//Ray ray(planePoint, Vector3(0.0f, 0.0f, 1.0f));
			Ray ray(camera, planePoint - camera);
			//ray.cast(scene->objects, scene->lights, 3);
			ray.castPath(scene->objects, scene->lights, 1);
			
			int baseIndex = h*width*3 + w*3;
			pixelData[baseIndex] = ((pixelData[baseIndex] * numRenders) + ray.color.v[0]) / (numRenders + 1);
			pixelData[baseIndex+1] = ((pixelData[baseIndex+1] * numRenders) + ray.color.v[1]) / (numRenders + 1);
			pixelData[baseIndex+2] = ((pixelData[baseIndex+2] * numRenders) + ray.color.v[2]) / (numRenders + 1);
		}
	}

}

// Drawing (display) routine.
void drawScene(void)
{
	// Clear screen to background color.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the pixels to the screen, using the color data from the rays
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixelData);

	// Flush created objects to the screen, i.e., force rendering.
	glFlush();

}

void setupRayTraceScene(void)
{
	Material metal;
	metal.ambient.set(0.2f, 0.2f, 0.2f);
	metal.diffuse.set(0.4f, 0.4f, 0.4f);
	metal.specular.set(0.8f, 0.8f, 0.8f);
	metal.shininess = 80;
	metal.reflection = 0.8f;

	Material red;
	red.ambient.set(0.5f, 0.0f, 0.0f);
	red.diffuse.set(0.8f, 0.0f, 0.0f);
	red.specular.set(0.1f, 0.1f, 0.1f);
	red.emittance.set(0.0f, 0.9f, 0.9f);
	red.shininess = 30;
	red.reflection = 0.3f;
	red.transmission = 0.8f;
	red.refractionIndex = 1.5f;

	Material blue;
	blue.ambient.set(0.0f, 0.0f, 0.5f);
	blue.diffuse.set(0.0f, 0.0f, 0.8f);
	blue.specular.set(0.0f, 0.0f, 0.0f);
	blue.emittance.set(0.2f, 0.2f, 0.2f);
	blue.shininess = 5;
	blue.reflection = 0.5f;

	Material glass;
	glass.ambient.set(0.0f, 0.0f, 0.0f);
	glass.diffuse.set(0.0f, 0.0f, 0.0f);
	glass.specular.set(0.9f, 0.9f, 0.9f);
	glass.shininess = 60;
	glass.reflection = 0.9f;
	glass.transmission = 0.9f;
	glass.refractionIndex = 1.0f;

	Sphere* s = new Sphere(Vector3(0.0f, 0.0f, 10.0f), 1.0f);
	s->setMaterial(metal);
	scene->addObject(s);

	Sphere* two = new Sphere(Vector3(0.0f, 1.5f, 10.0f), 0.5f);
	two->setMaterial(red);
	scene->addObject(two);

	Sphere* three = new Sphere(Vector3(1.5f, 0.0f, 9.0f), 0.6f);
	three->setMaterial(blue);
	scene->addObject(three);

	Sphere* four = new Sphere(Vector3(-0.5f, 1.5f, 11.0f), 0.4f);
	four->setMaterial(metal);
	scene->addObject(four);

	Sphere* five = new Sphere(Vector3(-0.3f, 0.0f, 8.0f), 0.5f);
	five->setMaterial(glass);
	scene->addObject(five);

	Plane* plane = new Plane(Vector3(0.0f, 0.0f, 30.0f), Vector3(0.0f, 0.0f, -1.0f), 10.0f, 10.0f);
	Material planeMat;
	planeMat.ambient.set(0.4f, 0.4f, 0.4f);
	planeMat.diffuse.set(0.4f, 0.4f, 0.4f);
	planeMat.specular.set(0.0f, 0.0f, 0.0f);
	planeMat.shininess = 0;
	planeMat.reflection = 0.0f;
	plane->setMaterial(planeMat);
	//scene->addObject(plane);

	Light light;
	light.color.set(1.0f, 1.0f, 1.0f);
	light.position.set(100.0f, 100.0f, 5.0f);
	scene->addLight(light);

	light.position.set(20.0f, 20.0f, 30.0f);
	//scene->addLight(light);
}

void setupRefractionScene(void)
{
	Material red;
	red.ambient.set(0.5f, 0.0f, 0.0f);
	red.diffuse.set(0.8f, 0.0f, 0.0f);
	red.specular.set(0.1f, 0.1f, 0.1f);
	red.emittance.set(0.0f, 0.9f, 0.9f);
	red.shininess = 30;
	red.reflection = 0.3f;
	red.transmission = 1.0f;
	red.refractionIndex = 2.0f;

	Material blue;
	blue.ambient.set(0.0f, 0.0f, 0.5f);
	blue.diffuse.set(0.0f, 0.0f, 0.8f);
	blue.specular.set(0.0f, 0.0f, 0.0f);
	blue.emittance.set(0.2f, 0.2f, 0.2f);
	blue.shininess = 5;
	blue.reflection = 0.5f;

	Sphere* one = new Sphere(Vector3(-0.5f, 0.0f, 12.0f), 0.5f);
	one->setMaterial(blue);
	scene->addObject(one);

	Sphere* two = new Sphere(Vector3(0.0f, 0.0f, 10.0f), 1.0f);
	two->setMaterial(red);
	scene->addObject(two);

	Light light;
	light.color.set(1.0f, 1.0f, 1.0f);
	light.position.set(100.0f, 100.0f, 5.0f);
	scene->addLight(light);
}

void setupPathTraceScene(void)
{
	Material blue;
	blue.ambient.set(0.0f, 0.0f, 0.5f);
	blue.diffuse.set(0.0f, 0.0f, 0.8f);
	blue.specular.set(0.0f, 0.0f, 0.0f);
	blue.emittance.set(0.2f, 0.2f, 0.8f);
	blue.shininess = 30;
	blue.reflection = 1.0f;
	blue.transmission = 1.0f;
	blue.refractionIndex = 2.0f;

	Material white;
	white.ambient.set(0.5f, 0.5f, 0.5f);
	white.diffuse.set(0.8f, 0.8f, 0.8f);
	white.specular.set(0.0f, 0.0f, 0.0f);
	white.emittance.set(0.8f, 0.8f, 0.8f);
	white.shininess = 5;
	white.reflection = 1.0f;

	Material green;
	green.ambient.set(0.0f, 0.5f, 0.1f);
	green.diffuse.set(0.0f, 0.8f, 0.2f);
	green.specular.set(0.0f, 0.0f, 0.0f);
	green.emittance.set(0.3f, 0.3f, 0.3f);
	green.shininess = 5;
	green.reflection = 1.0f;

	Sphere* one = new Sphere(Vector3(-1.2f, -0.1f, 10.0f), 0.8f);
	one->setMaterial(white);
	scene->addObject(one);

	Sphere* two = new Sphere(Vector3(1.0f, -0.5f, 10.0f), 1.0f);
	two->setMaterial(blue);
	scene->addObject(two);

	Sphere* three = new Sphere(Vector3(0.3f, 1.0f, 13.0f), 1.2f);
	three->setMaterial(green);
	scene->addObject(three);

	Light light;
	light.color.set(1.0f, 1.0f, 1.0f);
	light.position.set(50.0f, 50.0f, 5.0f);
	scene->addLight(light);
}

void setupScene(void)
{
	setupPathTraceScene();
	//setupRayTraceScene();
}

// Initialization routine.
void setup(void) 
{
	// Set background (or clearing) color.
	glClearColor(1.0, 1.0, 1.0, 0.0); 
	for(int h = 0; h < height; h++)
	{
		for(int w = 0; w < width; w++)
		{
			int baseIndex = h*width*3 + w*3;
			pixelData[baseIndex] = 0.0f;
			pixelData[baseIndex+1] = 0.0f;
			pixelData[baseIndex+2] = 0.0f;
		}
	}
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
			delete [] pixelData;
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

	pixelData = new float[3*width*height];

	// Seed the random number generator
	srand(time(NULL));

	// Initialize GLUT.
	glutInit(&argc, argv);
 
	// Set display mode as single-buffered and RGB color.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   
	// Set OpenGL window size.
	glutInitWindowSize(width, height);

	// Set position of OpenGL window upper-left corner.
	glutInitWindowPosition(100, 100); 
   
	// Create OpenGL window with title.
	glutCreateWindow("Path Tracing Demo");
   
	// Initialize.
	setup(); 
   
	glutIdleFunc(pathCast);

	// Register display routine.
	glutDisplayFunc(drawScene); 
   
	// Register reshape routine.
	//glutReshapeFunc(resize);  

	// Register keyboard routine.
	glutKeyboardFunc(keyInput);

	// Begin processing.
	glutMainLoop(); 

	return 0;  
}
