#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include "hitable.h"

using namespace std;

/*
a. very similar to the triangle class. 
b. using glm/glm::vec3 to deal with 3d vectors
*/

class plane: public hitable  {
    public:
	plane() {}
        plane(glm::vec3 V0, glm::vec3 V1, glm::vec3 V2, material *m) : 
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

bool plane::hit(const ray & r, float t_min, float t_max, hit_record & rec) const {

    glm::vec3 N = get_N();	

    float NdotRayDirection = glm::dot(N, r.get_direction());
    if (fabs(NdotRayDirection) < 0.0000001)
        return false;

    float D = glm::dot(N, v0);
    float t = (glm::dot(N, r.get_origin()) + D) / NdotRayDirection;
    glm::vec3 P = r.point_at_parameter(t);

    if (t < t_min || t > t_max){ 
        return false;
    }
    else{
        rec.t = t;
        rec.p = P;
        rec.normal = N;
        rec.mat_ptr = mat_ptr;
        return true;
    }
}

bool plane::bounding_box(float t0, float t1, aabb& box) const{
    return false;
}	

#endif
