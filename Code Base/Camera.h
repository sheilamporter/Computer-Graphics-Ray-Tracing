#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <cstdlib>
#include <iostream>
#include <cmath>

class Vector3;

class Camera
{
    public:
        Vector3* position;
        Vector3* normal;
        
        Camera();
        Camera(Vector3* pos, Vector3* norm);
        Camera(float posX, float posY, float posZ, float normX, float normY, float normZ);
}

#endif