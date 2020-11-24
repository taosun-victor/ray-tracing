#ifndef RAY_H
#define RAY_H
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/vec3.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/ext.hpp>
#include <iostream>

using namespace std;

/*
a. modified from https://github.com/petershirley/raytracinginoneweekend/blob/master/ray.h
b. using glm/vec3 to deal with 3d vectors
*/

class ray
{
    public:
        ray(){} 
        ray(const glm::vec3 & newOrigin, const glm::vec3 & newDirec) {
	    origin_ = newOrigin; 
	    direction_ = newDirec; 
	}  

	glm::vec3 get_origin() const { return origin_; }
	glm::vec3 get_direction() const { return direction_; }
	glm::vec3 point_at_parameter(float t) const { return origin_ + t*direction_; }

    private:
	glm::vec3 origin_;
	glm::vec3 direction_;
};

#endif 
