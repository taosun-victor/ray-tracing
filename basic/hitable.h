#ifndef HITABLE_H
#define HITABLE_H 

#include <iostream>
#include "ray.h"

using namespace std;

/*
a. modified from https://github.com/petershirley/raytracinginoneweekend/blob/master/hitable.h
b. using glm/vec3 to deal with 3d vectors
*/

class material;

struct hit_record
{
    float t;  
    glm::vec3 p;
    glm::vec3 normal; 
    material *mat_ptr;
};


class hitable  {
    public:
        virtual bool hit(const ray & r, float t_min, float t_max, hit_record & rec) const = 0;
};

#endif

