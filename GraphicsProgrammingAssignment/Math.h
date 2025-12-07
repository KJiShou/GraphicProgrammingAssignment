#pragma once
class Math {
public:
    struct Vec3 {
        float x, y, z;
    };

    static Vec3 Normalize(const Vec3& v);
    static Vec3 Cross(const Vec3& a, const Vec3& b);
    static Vec3 CalcNormal(const Vec3& p1, const Vec3& p2, const Vec3& p3);
};


