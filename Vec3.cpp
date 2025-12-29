#include "Vec3.h"

Vec3::Vec3():x(0),y(0),z(0){}

Vec3::Vec3(const float& X, const float& Y, const float& Z):x(X),y(Y),z(Z){}
Vec3 Vec3::operator+(const Vec3 &b) { return {x + b.x, y + b.y, z + b.z}; }
Vec3 Vec3::operator-(const Vec3 &b) { return {x - b.x, y - b.y, z - b.z}; }
Vec3 Vec3::operator*(float &scalar) { return {x * scalar, y * scalar, z * scalar}; }
float Vec3::dot(const Vec3& b){
    // return (a.x * b.x + a.y * b.y, a.z * b.z);
    return (x * b.x) + (y * b.y) + (z * b.z);
}

Vec3 Vec3::cross(Vec3& b){
    Vec3 c;
    c.x = (y * b.z) - (z * b.y);
    c.y = -((x * b.z) - (z * b.x));
    c.z = (x * b.y) - (y * b.x);
    return c;
}
