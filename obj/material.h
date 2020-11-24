#ifndef MATERIALH
#define MATERIALH 
#include "ray.h"
#include "hitable.h"

/*
a. modified from https://github.com/petershirley/raytracinginoneweekend/blob/master/ray.h
b. using glm/vec3 to deal with 3d vectors
c. removed dielectric class
d. self implemented the color_shadow function, for shading
*/

using namespace std;

glm::vec3 reflect(const glm::vec3 & v, const glm::vec3 & n) {
     return v - 2*glm::dot(v,n)*n;
}


glm::vec3 random_in_unit_sphere() {
    glm::vec3 p(1.0, 1.0, 1.0);

    while (glm::length2(p) >= 1.0){
        p = float(2.0)*glm::vec3(drand48(),drand48(),drand48()) - glm::vec3(1,1,1);
    }

    return p;
}


class material  {
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec, 
			     glm::vec3& attenuation, ray& scattered) const = 0;
	virtual glm::vec3 get_albedo() const = 0;
};

class lambertian : public material {
    public:
        lambertian(const glm::vec3& a) : albedo(a) {}

        virtual bool scatter(const ray& r_in, const hit_record& rec, 
			     glm::vec3& attenuation, ray& scattered) const  {

   	     glm::vec3 target = rec.p + rec.normal + random_in_unit_sphere();
             scattered = ray(rec.p, target-rec.p);
             attenuation = albedo;
             return true;
        }
        virtual glm::vec3 get_albedo() const {return albedo; }

    private:	
        glm::vec3 albedo;
};

class metal : public material {
    public:
        metal(const glm::vec3& a) : albedo(a) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, 
			     glm::vec3& attenuation, ray& scattered) const  {

    	    glm::vec3 reflected = reflect(glm::normalize(r_in.get_direction()), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (glm::dot(scattered.get_direction(), rec.normal) > 0);
        }

        virtual glm::vec3 get_albedo() const {return albedo; }

    private:	
        glm::vec3 albedo;
};


glm::vec3 color_shadow(const ray & r, glm::vec3 light_dir, hitable * world){
    hit_record rec;
    if (world->hit(r, 0.0001, FLT_MAX, rec)){
        ray to_light(rec.p, -light_dir);
        glm::vec3 attenuation = rec.mat_ptr->get_albedo();
	glm::vec3 normal = rec.normal;
        if (world->hit(to_light, 0.0001, FLT_MAX, rec)){
            return glm::vec3(0.0, 0.0, 0.0);
	}	
        else{
    	    float NdotLight = glm::dot(normal, to_light.get_direction());
            if (fabs(NdotLight) < 0.05 || NdotLight < 0)
	        return glm::vec3(0.0, 0.0, 0.0);
            else
		//cout << "HaHaHa" << endl;
	        //cout << NdotLight << endl;    
	        return attenuation * NdotLight;	    
	}
    }	    
    else {
        glm::vec3 unit_direction = glm::normalize(r.get_direction());
        float t = 0.5*(unit_direction.x + 1.0);
        return (float(1.0)-t)*glm::vec3(1.0, 1.0, 1.0) + t*glm::vec3(0.5, 0.7, 1.0);
    }	    
}


glm::vec3 color_scatter(const ray & r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.0001, FLT_MAX, rec)) { 
        ray scattered;
	glm::vec3 attenuation;

	if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
             return attenuation*color_scatter(scattered, world, depth+1);
        }
        else {
            return glm::vec3(0,0,0);
        }
    }
    else {
        glm::vec3 unit_direction = glm::normalize(r.get_direction());
        float t = 0.5*(unit_direction.x + 1.0);
        return (float(1.0)-t)*glm::vec3(1.0, 1.0, 1.0) + t*glm::vec3(0.5, 0.7, 1.0);
    }
}


#endif

