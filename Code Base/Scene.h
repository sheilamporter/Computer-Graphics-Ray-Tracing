#ifndef _SCENE_H_
#define _SCENE_H_

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <list>

#include "Object.h"
#include "Camera.h"
#include "Vector3.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

class Scene
{        
    public:
        list<Object> objects;
    
        Scene() { }
        
        Scene(list<Object> sceneObjects)
        {
            objects = sceneObjects;
        }
        
        void AddObject(Object newObject)
        {
            objects.push_back(newObject);
        }

        void Sort(/*Vector3 cameraPosition?*/)
        {
            //TODO:
            //use list.sort and write a function that compares objects' depth from the camera
            //http://www.cplusplus.com/reference/stl/list/sort/
        }
}

#endif