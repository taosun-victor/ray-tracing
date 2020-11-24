#ifndef CAMERA_ORTH_H 
#define CAMERA_ORTH_H

#include <iostream>
#include "ray.h"

using namespace std;

/*
a. modified from https://github.com/petershirley/raytracinginoneweekend/blob/master/camera.h
b. using glm/vec3 to deal with 3d vectors
c. removing some complicated functionality
*/

class camera_orth  {  
    public:  

	//camera_proj(){}
         
	camera_orth() {  
            lower_left_corner = glm::vec3(-2.0, -2.0, -1.0);  
            horizontal = glm::vec3(4.0, 0.0, 0.0);
            vertical = glm::vec3(0.0, 4.0, 0.0);
        }

	camera_orth(glm::vec3 newLLC, glm::vec3 newH, glm::vec3 newV) {  
            lower_left_corner = newLLC;  
            horizontal = newH;  
            vertical = newV;  
        } 

        ray get_ray(float u, float v) {
	    float x0 = (lower_left_corner + u*horizontal + v*vertical).x;
	    float y0 = (lower_left_corner + u*horizontal + v*vertical).y;
	    return ray(glm::vec3(x0,y0,2.2),
		       glm::vec3(0,0,-1));
	}  


    private:	
	glm::vec3 lower_left_corner;  
	glm::vec3 horizontal;  
	glm::vec3 vertical;  
}; 

#endif
