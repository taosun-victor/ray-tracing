#ifndef CAMERA_PROJ_H 
#define CAMERA_PROJ_H

#include <iostream>
#include "ray.h"

using namespace std;

/*
a. modified from https://github.com/petershirley/raytracinginoneweekend/blob/master/camera.h
b. using glm/vec3 to deal with 3d vectors
c. removing some complicated functionality
*/

class camera_proj  {  
    public:  

	//camera_proj(){}
         
	camera_proj() {  
            lower_left_corner = glm::vec3(-1.5, -1.5, -1.0);  
            horizontal = glm::vec3(3.0, 0.0, 0.0);  
            vertical = glm::vec3(0.0, 3.0, 0.0);  
            origin = glm::vec3(0.0, 0.0, 0.5);  
        }

	camera_proj(glm::vec3 newLLC, glm::vec3 newH, glm::vec3 newV, glm::vec3 newOrigin) {  
            lower_left_corner = newLLC;  
            horizontal = newH;  
            vertical = newV;  
            origin = newOrigin;  
        } 

        ray get_ray(float u, float v) {
	    return ray(origin, lower_left_corner + u*horizontal + v*vertical);
	}  


    private:	
	glm::vec3 lower_left_corner;  
	glm::vec3 horizontal;  
	glm::vec3 vertical;  
	glm::vec3 origin;  
}; 

#endif
