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
	Plane(Vec3<float> p0, Vec3<float> p1, Material * m) : p0_(p0), p1_(p1) ,material(m) {
	
		Vec3<float> tmp(p1_.x(), p0.y(), p0.z());
		n0_ = Vec3<float>::cross(tmp - p0, tmp - p1); n0_.normalize(); n1_ = -n0_;
	}
	virtual bool hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const;
	Vec3<float> p0_, p1_, n0_, n1_; // p0 = upleft || p1 rightdown
	Material * material;
};


bool Plane::hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const {

	/*float tmp = Vec3<float>::dot(r.direction(), n0_);
	Vec3<float> normal = n0_;
	if (tmp > 0)
		normal = n1_;
	else if (tmp == 0)
		return false;
	*/
	
	Vec3<float> normal(0, 0, 1), origin = r.origin(), direction = r.direction(); origin.normalize(); direction.normalize();

	float t = Vec3<float>::dot(p0_ - origin, normal) / Vec3<float>::dot(direction, normal);

	rec.t = t;
	rec.p = r.point_at_parameter(rec.t);
	rec.normal = normal;
	rec.mat_ptr = material;

	return true;

}

#endif
