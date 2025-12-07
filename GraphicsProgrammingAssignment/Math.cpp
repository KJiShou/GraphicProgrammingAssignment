#include "Math.h"
#include <cmath>

Math::Vec3 Math::Normalize(const Vec3& v)
{
	float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0.0f) return { 0.0f, 0.0f, 0.0f };
	return { v.x / len, v.y / len, v.z / len };
}

Math::Vec3 Math::Cross(const Vec3& a, const Vec3& b)
{
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

Math::Vec3 Math::CalcNormal(const Vec3& p1, const Vec3& p2, const Vec3& p3)
{
	Vec3 v1 = { p2.x - p1.x, p2.y - p1.y, p2.z - p1.z };
	Vec3 v2 = { p3.x - p1.x, p3.y - p1.y, p3.z - p1.z };

	Vec3 n = Cross(v1, v2);
	return Normalize(n);
}