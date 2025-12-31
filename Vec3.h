#pragma once
class Vec3{
    public:
        float x, y, z;
        Vec3();
        Vec3(const float &X, const float &Y, const float &Z);
        Vec3 operator+(const Vec3 &b)const;
        Vec3 operator-(const Vec3 &b)const;
        Vec3 operator*(float &scalar)const;
        float dot(const Vec3 &b)const;
        Vec3 cross(Vec3 &b);
};