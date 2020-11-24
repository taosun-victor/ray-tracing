#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include "hitable.h"

using namespace std;

/*
a. reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution 
b. using glm/glm::vec3 to deal with 3d vectors
c. add bounding box
*/

class triangle: public hitable  {
    public:
	triangle() {}
        triangle(glm::vec3 V0, glm::vec3 V1, glm::vec3 V2, material *m) : 
	       v0(V0), v1(V1), v2(V2), mat_ptr(m) {normal=glm::normalize(glm::cross(v1-v0, v2-v0)); }

	virtual bool hit(const ray & r, float tmin, float tmax, hit_record & rec) const;
        virtual bool bounding_box(float t0, float t1, aabb& box) const;  

    private:
        glm::vec3 v0;
	glm::vec3 v1;
	glm::vec3 v2;
        material *mat_ptr; 
        glm::vec3 normal;   
};

bool triangle::hit(const ray & r, float t_min, float t_max, hit_record & rec) const {

	float thit, t, u, v;

	glm::vec3 v0v1 = v1 - v0;
	glm::vec3 v0v2 = v2 - v0;
	
	glm::vec3 pvec = glm::cross(r.get_direction(), v0v2);
	
	float det = glm::dot(pvec, v0v1);
	float kEpsilon = 0.00001;

	// if the determinant is negative the triangle is backfacing
	// if the determinant is close to 0, the ray misses the triangle
	if (det < kEpsilon) return false;

	float invDet = 1.0 / det;
	
	glm::vec3 tvec = r.get_origin() - v0;
	u = glm::dot(tvec, pvec) * invDet;
	
	if (u < 0 || u > 1) return false;

	glm::vec3 qvec = glm::cross(tvec, v0v1);
	v = glm::dot(r.get_direction(), qvec) * invDet;
	if (v < 0 || u + v > 1) return false;

	t = glm::dot(v0v2, qvec) * invDet;

	
	if (t < 0) return false;// std::cout << t << std::endl;

	rec.p = r.point_at_parameter(t);

	rec.t = t;
	rec.normal = normal;
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

    float eps = 0.0;

    glm::vec3 newmin(x_min, y_min, z_min);
    glm::vec3 newmax(x_max, y_max, z_max);

    box = aabb(newmin-eps, newmax+eps);
    return true;
}	

#endif
