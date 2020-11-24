#ifndef CAMERAH
#define CAMERAH

#include "ray.h"
#include <iostream>

/*
a. modified from https://github.com/petershirley/raytracinginoneweekend/blob/master/camera.h
b. using glm/vec3 to deal with 3d vectors
c. the originally modified projective view camera in mp1 could not achieve broad view. This time we adapt the complicated designed camera with multiple possibilities.
*/

glm::vec3 random_in_unit_disk() {
    glm::vec3 p(1.0, 1.0, 1.0);

    while (glm::length2(p) >= 1.0){
        p = float(2.0)*glm::vec3(drand48(),drand48(), 0) - glm::vec3(1,1,0);
    }

    return p;
}


class camera {
    public:
        camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, 
	       float vfov, float aspect, float aperture, 
	       float focus_dist)  {

            lens_radius = aperture / 2;
            float theta = vfov*3.141592653/180;
            float half_height = tan(theta/2);
            float half_width = aspect * half_height;
            origin = lookfrom;

            w = glm::normalize(lookfrom - lookat);
            u = glm::normalize(glm::cross(vup, w));
            v = glm::cross(w, u);
            lower_left_corner = origin - half_width*focus_dist*u 
		                       - half_height*focus_dist*v 
				       - focus_dist*w;
            horizontal = 2*half_width*focus_dist*u;
            vertical = 2*half_height*focus_dist*v;
        }

        ray get_ray(float s, float t) {
	    glm::vec3 rd = lens_radius * random_in_unit_disk();
	    glm::vec3 offset = u * rd.x + v * rd.y;
            return ray(origin + offset, lower_left_corner + s*horizontal + 
			                t*vertical - origin - offset); 
        }

    private:	
	glm::vec3 origin;
	glm::vec3 lower_left_corner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
	glm::vec3 u, v, w;
        float lens_radius;
};


#endif
