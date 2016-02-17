#ifndef BOX_
#define BOX_

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Hitable.hpp"
#include "Material.hpp"

class Box : public Hitable
{
public:
	Box() {}
	Box(Vec3<float> min, Vec3<float> max, Material * m) {
		bounds[0] = min;
		bounds[1] = max;

		material = m;
	}

	virtual bool hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const;
	Vec3<float> bounds[2];
	Material * material;
};


bool Box::hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const {

	
	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	if (r.direction().x() >= 0) {
		tmin = (bounds[0].x() - r.origin().x()) / r.direction().x();
		tmax = (bounds[1].x() - r.origin().x()) / r.direction().x();
	}
	else {
		tmin = (bounds[1].x() - r.origin().x()) / r.direction().x();
		tmax = (bounds[0].x() - r.origin().x()) / r.direction().x();
	}
	if (r.direction().y() >= 0) {
		tymin = (bounds[0].y() - r.origin().y()) / r.direction().y();
		tymax = (bounds[1].y() - r.origin().y()) / r.direction().y();
	}
	else {
		tymin = (bounds[1].y() - r.origin().y()) / r.direction().y();
		tymax = (bounds[0].y() - r.origin().y()) / r.direction().y();
	}
	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
			tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	if (r.direction().z() >= 0) {
		tzmin = (bounds[0].z() - r.origin().z()) / r.direction().z();
		tzmax = (bounds[1].z() - r.origin().z()) / r.direction().z();
	}
	else {
		tzmin = (bounds[1].z() - r.origin().z()) / r.direction().z();
		tzmax = (bounds[0].z() - r.origin().z()) / r.direction().z();
	}
	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;

	Vec3<float> normal;

	rec.t = tmin;
	rec.p = r.point_at_parameter(tmin);

	if (rec.p.z() == bounds[0].z())
		normal = Vec3<float>(0, 1, 0);
	else if (rec.p.z() == bounds[1].z())
		normal = Vec3<float>(0, -1, 0);
	else if (rec.p.x() == bounds[1].x())
		normal = Vec3<float>(1, 0, 0);
	else if (rec.p.x() == bounds[0].x())
		normal = Vec3<float>(-1, 0, 0);
	else if (rec.p.y() == bounds[1].y())
		normal = Vec3<float>(0, 0, 1);
	else if (rec.p.y() == bounds[0].y())
		normal = Vec3<float>(0, 0, -1);

	rec.normal = normal;
	rec.mat_ptr = material;

	return ((tmin < t_max) && (tmax > t_min));}

#endif

