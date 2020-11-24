#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include "hitable.h"

using namespace std;

/*
a. reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution 
b. using glm/glm::vec3 to deal with 3d vectors
*/

class triangle: public hitable  {
    public:
	triangle() {}
        triangle(glm::vec3 V0, glm::vec3 V1, glm::vec3 V2, material *m) : 
	       v0(V0), v1(V1), v2(V2), mat_ptr(m) {};

	glm::vec3 get_N() const {
            return (glm::normalize(glm::cross(v1-v0, v2-v0)));
	}	

	virtual bool hit(const ray & r, float tmin, float tmax, hit_record & rec) const;
        virtual bool bounding_box(float t0, float t1, aabb& box) const;  

    private:
        glm::vec3 v0;
	glm::vec3 v1;
	glm::vec3 v2;
        material *mat_ptr;    
};

bool triangle::hit(const ray & r, float t_min, float t_max, hit_record & rec) const {

    glm::vec3 N = get_N();	

    float NdotRayDirection = glm::dot(N, r.get_direction());
    if (fabs(NdotRayDirection) < 0.0000001)
        return false;

    float D = glm::dot(N, v0);
    float t = (glm::dot(N, r.get_origin()) + D) / NdotRayDirection;
    if (t < t_min || t > t_max) 
        return false;
  
    glm::vec3 P = r.point_at_parameter(t);

    glm::vec3 C; // vector perpendicular to triangle's plane 
 
    // edge 0
    glm::vec3 edge0 = v1 - v0; 
    glm::vec3 vp0 = P - v0;  
    C = glm::cross(edge0, vp0);
    if (glm::dot(N, C) < 0)  return false; 
 
    // edge 1
    glm::vec3 edge1 = v2 - v1; 
    glm::vec3 vp1 = P - v1; 
    C = glm::cross(edge1, vp1); 
    if (glm::dot(N, C) < 0)  return false; 
 
    // edge 2
    glm::vec3 edge2 = v0 - v2; 
    glm::vec3 vp2 = P - v2; 
    C = glm::cross(edge2, vp2); 
    if (glm::dot(N, C) < 0)  return false; 


    rec.t = t;
    rec.p = P;
    rec.normal = N;
    rec.mat_ptr = mat_ptr;
    return true;

}


bool triangle::bounding_box(float t0, float t1, aabb& box) const {  
    float x_min = fmin(fmin(v0.x, v1.x), v2.x); 
    float x_max = fmax(fmax(v0.x, v1.x), v2.x); 

    float y_min = fmin(fmin(v0.y, v1.y), v2.y); 
    float y_max = fmax(fmax(v0.y, v1.y), v2.y); 

    float z_min = fmin(fmin(v0.z, v1.z), v2.z); 
    float z_max = fmax(fmax(v0.z, v1.z), v2.z); 

    glm::vec3 newmin(x_min, y_min, z_min);
    glm::vec3 newmax(x_max, y_max, z_max);

    box = aabb(newmin, newmax);
    return true;
}	

#endif
