#include <iostream>
#include <fstream>
#include <ctime>
#include "sphere.h"
#include "triangle.h"
#include "plane.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"
#include "aabb.h"
#include "bvh.h"

using namespace std;

/*
a. modified from https://github.com/petershirley/raytracinginoneweekend/blob/master/main.cc
b. using glm/vec3 to deal with 3d vectors
c. self implemented plane.h and triangle.h
*/

hitable *random_scene() {
    //int n = 108;
    //int m = 3;

    int n = 1000;
    int m = 5;

    //int n = 10648;
    //int m = 11;
    hitable **list = new hitable*[n];

    int i = 0;
    for (int a=-m; a<m; a++) {
        for (int b=-m; b<m; b++) {
            for (int c=-m; c<m; c++) {
    		float choose_mat = drand48();
	        glm::vec3 center(a+0.9*drand48(), b+0.9*drand48(), c+0.9*drand48()); 
                if (choose_mat < 0.8) { 
                    list[i++] = new sphere(center, 0.2, 
	    	                new lambertian(glm::vec3(drand48()*drand48(), 
	    		        drand48()*drand48(), drand48()*drand48())));
                }
                else { 
                    list[i++] = new sphere(center, 0.2,
                                new metal(glm::vec3(0.5*(1 + drand48()))));
                }
            }
    	}
    }	


    return new hitable_list(list,i);
    //return new bvh_node(list, i, 0.0, 1.0);
}


int main(int argc, char **argv){

    int nx = 1200;
    int ny = 800;
    int ns = 10;

    ofstream myfile;
    myfile.open("output.txt");
    myfile << "P3\n" << nx << " " << ny << "\n255\n";

    //unsigned char pix[nx*ny*3];

    hitable * world = random_scene();

    //glm::vec3 lookfrom(2,2,20); //->for 108
    glm::vec3 lookfrom(20,20,40.0); //->for 1000
    //glm::vec3 lookfrom(50,50,100.0); //->for 10648
    glm::vec3 lookat(0,0,-2.0);
    float dist_to_focus = glm::length(lookfrom - lookat);
    float aperture = 0.0;

    camera cam(lookfrom, lookat, glm::vec3(0,1,0), 40, float(nx)/float(ny), aperture, dist_to_focus);

    glm::vec3 light(0.0, -1.0, 0.0);

    clock_t begin = clock();

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

	    myfile << ir << " " << ig << " " << ib << "\n";

	}
    }

    myfile.close();

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "elapsed seconds: " << elapsed_secs << endl;

    return 0;


}
