#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "Vector3.h"

class Camera
{
    public:
        Vector3 position;
        Vector3 normal;
        
        Camera();
        Camera(const Vector3& pos, const Vector3& norm);
        Camera(float posX, float posY, float posZ, float normX, float normY, float normZ);
};

#endif