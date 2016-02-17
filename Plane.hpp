#ifndef PLANE_
#define PLANE_

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Hitable.hpp"
#include "Material.hpp"

class Plane : public Hitable
{
public:
	Plane() {}
	Plane(Vec3<float> p0, Vec3<float> n, Material * m) : p0_(p0), n_(n) ,material(m) {
		n_.normalize();
	}
	virtual bool hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const;
	Vec3<float> p0_, n_;
	Material * material;
};


bool Plane::hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const {

	
	Vec3<float> origin = r.origin(), direction = r.direction(), test; 
	//origin.normalize(); 
	direction.normalize();

	Vec3<float> normal = n_;
	float tmp = Vec3<float>::dot(direction, normal);
	
	if (tmp > 0)
		normal = -n_;
	else if (tmp == 0)
		return false;

	float t = (Vec3<float>::dot(p0_ - origin, normal)) / Vec3<float>::dot(direction, normal);
	
	if (t < 0) return false;

	test = r.point_at_parameter(rec.t);

	rec.t = t;
	rec.p = r.point_at_parameter(rec.t);
	rec.normal = normal;
	rec.mat_ptr = material;

	return true;

}

#endif
