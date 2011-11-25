#ifndef _SCENE_H_
#define _SCENE_H_

//#include <cstdlib>
//#include <iostream>
//#include <cmath>
#include <list>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

class Object;
class Camera;
class Vector3;
struct Light;

class Scene
{        
public:
    list<Object*>* objects;
	list<Light*>* lights;
    
    Scene()
	{
		objects = new list<Object*>();
		lights = new list<Light*>();
	}
        
    Scene(list<Object*>* sceneObjects)
    {
        objects = sceneObjects;
		lights = new list<Light*>();
    }
        
    void addObject(Object* newObject)
    {
        objects->push_back(newObject);
    }

	void addLight(Light* newLight)
	{
		lights->push_back(newLight);
	}

    void Sort(/*Vector3 cameraPosition?*/)
    {
        //TODO:
        //use list.sort and write a function that compares objects' depth from the camera
        //http://www.cplusplus.com/reference/stl/list/sort/
    }
};

#endif