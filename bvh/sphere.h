#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "hitable.h"

using namespace std;

/*
a. modified from https://github.com/petershirley/raytracinginoneweekend/blob/master/sphere.h
b. using glm/glm::vec3 to deal with 3d vectors
*/

class sphere: public hitable  {
    public:
	sphere() {}
        sphere(glm::vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};
        virtual bool hit(const ray & r, float tmin, float tmax, hit_record & rec) const;
        virtual bool bounding_box(float t0, float t1, aabb& box) const;	

    private:
        glm::vec3 center;
        float radius;
        material *mat_ptr;    
};

bool sphere::hit(const ray & r, float t_min, float t_max, hit_record & rec) const {

    glm::vec3 oc = r.get_origin() - center;
    float a = glm::dot(r.get_direction(), r.get_direction());
    float b = glm::dot(oc, r.get_direction());
    float c = glm::dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;

    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

bool sphere::bounding_box(float t0, float t1, aabb & box) const {
    box = aabb(center - glm::vec3(radius, radius, radius), 
	       center + glm::vec3(radius, radius, radius));     
    return true;
}

#endif
