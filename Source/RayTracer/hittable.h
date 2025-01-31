#ifndef HITTABLE_H
#define HITTABLE_H

class hit_record {
public:
	point3 p;
	vec3 normal;
	double t;


	bool front_face;




	void set_face_normal(const ray& r, const vec3& outward_normal) {
		//set the hit record normal vector
		//noth the parameter outward normal is assumed to have unit legnth
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	
	}

};


class hittable {

public:
	virtual ~hittable() = default;

	virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;

	//virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;

};



#endif

