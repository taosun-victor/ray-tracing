#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include <iostream>
#include <stdlib.h>
#include "hitable.h"

using namespace std;

/*
a. adapted from
   https://github.com/petershirley/raytracinginoneweekend/blob/master/hitable_list.h
b. using glm/glm::vec3 to deal with 3d vectors
*/

class hitable_list: public hitable  {
    public:
        hitable **list;
        int list_size;

	hitable_list() {}
        hitable_list(hitable **l, int n) {
            list = l; 
	    list_size = n; 
	}

        virtual bool hit(const ray & r, float tmin, float tmax, hit_record & rec) const;
        virtual bool bounding_box(float t0, float t1, aabb & box) const;
};



bool hitable_list::hit(const ray & r, float t_min, float t_max, hit_record & rec) const {

    hit_record temp_rec;

    bool hit_anything = false;
    double closest_so_far = t_max;

    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}



bool hitable_list::bounding_box(float t0, float t1, aabb & box) const {

    if (list_size < 1) 
        return false;

    aabb tmp_box;
    bool first_true = list[0]->bounding_box(t0, t1, tmp_box);

    if (!first_true)
        return false;
    else 
        box = tmp_box;

    for (int i = 1; i < list_size; i++) {
        if(list[0]->bounding_box(t0, t1, tmp_box)) {
            box = surrounding_box(box, tmp_box);
        }
        else
            return false;
    }
    return true;
}



#endif
