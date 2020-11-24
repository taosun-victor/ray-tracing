#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
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
d. test only involves spheres, do scaling tests. See report.
*/

hitable *read_obj(const string &filename) {

    std::vector<glm::vec3> vertices;
    std::vector<triangle *> faces;

    std::ifstream in_file(filename);
    std::string line, op;
    std::stringstream linestream;
    float x, y, z;

    //material *mat = new metal(glm::vec3(drand48(), drand48(), drand48() ) ); 
    material *mat = new metal(glm::vec3(0.2, 0.7, 0.6)); 

    while (std::getline(in_file, line)){
        linestream << line;
        linestream >> op;

	if (op == "v") {
	    linestream >> x >> y >> z;
	    glm::vec3 tmp_vert(x, y, z);
	    vertices.push_back(tmp_vert);
        }
        else if (op == "f") {
	    int v0, v1, v2;
	    linestream >> v0 >> v1 >> v2;
	    faces.push_back(new triangle(vertices[v0-1], vertices[v1-1], vertices[v2-1], mat));
        }

	linestream.clear();
    }

	
    hitable **list = new hitable*[faces.size()];
    std::copy(faces.begin(), faces.end(), list);

    //return new hitable_list(list, faces.size());
    return new bvh_node(list, faces.size(), 0.0, 1.0);
}


int main(int argc, char **argv){

    int nx = 600;
    int ny = 400;
    int ns = 6;

    ofstream myfile;
    myfile.open("cow.ppm");
    myfile << "P3\n" << nx << " " << ny << "\n255\n";

    hitable *list[2];

    list[0] = read_obj("cow.obj");
    list[1] = new sphere(glm::vec3(0,-1003,0), 1000,
			  new metal(glm::vec3(0.9,0.4,0.3))  );

    hitable *world = new hitable_list(list, 2);

    glm::vec3 lookfrom(1.5, 0.2, 0.4); //->for 1000
    glm::vec3 lookat(0.0, 0.0, -0.0);
    float dist_to_focus = glm::length(lookfrom - lookat);
    float aperture = 0.0;

    camera cam(lookfrom, lookat, glm::vec3(0,1,0), 60, float(nx)/float(ny), aperture, dist_to_focus);
    

    glm::vec3 light(-0.0, -1.0, -0.0);

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
