#include <iostream>
#include "sphere.h"
#include "triangle.h"
#include "plane.h"
#include "hitable_list.h"
#include "float.h"
#include "camera_orth.h"
#include "material.h"

using namespace std;

/*
a. modified from https://github.com/petershirley/raytracinginoneweekend/blob/master/main.cc
b. using glm/vec3 to deal with 3d vectors
c. self implemented plane.h and triangle.h
d. simplified version of projective/orthogonal view cameras.
e. print out the pixel values into a file, and use xnview software to visualize
*/

int main(){

    int nx = 600;
    int ny = 600;
    int ns = 10;

    cout << "P3\n" << nx << " " << ny << "\n255\n";

    hitable *list[4];

    list[0] = new sphere(glm::vec3(-0.3,0.3,-1.2), 0.5, 
		         new lambertian(glm::vec3(0.1, 0.2, 0.5)));

    list[1] = new sphere(glm::vec3(0.8,0.3,-1.5), 0.5, 
		         new metal(glm::vec3(0.7, 0.5, 0.1)));

    list[2] = new triangle(glm::vec3( 0.3, -0.8, -2.0), 
		           glm::vec3(-0.7, -1.4, -1.1),
			   glm::vec3( 0.7, -1.2, -1.1), 
		           new lambertian(glm::vec3(0.9, 0.4, 0.3)));

    list[3] = new triangle(glm::vec3( 1.3, -0.8, -2.0), 
		           glm::vec3( 0.3, -1.4, -1.1),
			   glm::vec3( 1.7, -1.2, -1.1), 
		           new metal(glm::vec3(0.2, 0.6, 0.2)));
    

    /*
    list[3] = new sphere(glm::vec3( 0.0, -1002, -0.0), 1000, 
   		         new lambertian(glm::vec3(0.5, 0.5, 0.5)));
    */
    hitable *world = new hitable_list(list,4);

    camera_orth cam;

    glm::vec3 light(0.0, -1.0, 0.0);

    for (int j = ny-1; j>= 0; j--){
        for (int i = 0; i< nx; i++){
            glm::vec3 col(0,0,0);
            for (int s = 0; s < ns; s++){
                float random = rand()%(100)/(float)(100);
                float u = float(i + random) / float(nx);
                float v = float(j + random) / float(ny);
                ray r = cam.get_ray(u, v);

		col += float(0.6) * color_shadow(r, light, world);
                col += float(0.4) * color_scatter(r, world, 0);
            }

            col /= float(ns);
            col = glm::sqrt(col);

            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

	    ir == -2147483648 ? (ir = 0): (ir = ir);
	    ig == -2147483648 ? (ig = 0): (ig = ig);
	    ib == -2147483648 ? (ib = 0): (ib = ib);

	    std::cout << ir << " " << ig << " " << ib << "\n";
	}
    }


    return 0;
}
