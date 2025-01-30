#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record {
public:
	point3 p;
	vec3 normal;
	double t;


};


class hittable {

public: 
	virtual ~hittable() = default;

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;

}



#endif

