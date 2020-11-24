#ifndef AABBH
#define AABBH

#include <cmath>
#include "ray.h"
#include "hitable.h"

/*
1. modified from https://github.com/petershirley/raytracingthenextweek/blob/master/aabb.h
2. using glm/glm::vec3 to deal with 3-d vectors
*/

class aabb {
    public:
        aabb() {}
        aabb(const glm::vec3 & newmin, const glm::vec3 & newmax) { 
	    _min = newmin; 
	    _max = newmax;
	}  

	glm::vec3 min() const {return _min; }
	glm::vec3 max() const {return _max; }

        bool hit(const ray& r, float tmin, float tmax) const {
            for (int a = 0; a < 3; a++) {
                float t0 = fmin((_min[a] - r.get_origin()[a]) / r.get_direction()[a],  
                                (_max[a] - r.get_origin()[a]) / r.get_direction()[a]);

		float t1 = fmax((_min[a] - r.get_origin()[a]) / r.get_direction()[a],  
                                (_max[a] - r.get_origin()[a]) / r.get_direction()[a]);

		tmin = fmax(t0, tmin);
                tmax = fmin(t1, tmax);

		if (tmax <= tmin)
                    return false;
            }
            return true;
        }

    private:	
	glm::vec3 _min;
	glm::vec3 _max;
};

aabb surrounding_box(aabb box0, aabb box1) {

    glm::vec3 small(fmin(box0.min().x, box1.min().x),
                    fmin(box0.min().y, box1.min().y),
                    fmin(box0.min().z, box1.min().z));

    glm::vec3 big(fmax(box0.max().x, box1.max().x),
                  fmax(box0.max().y, box1.max().y),
                  fmax(box0.max().z, box1.max().z));

    return aabb(small,big);
}


#endif
