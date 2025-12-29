#include <iostream>
#include <vector>
#include <tuple>
#include "Vec3.h"
// struct Vec3{
//     float x, y, z;
//     Vec3():x(0),y(0),z(0){}
//     Vec3(const float& X, const float& Y, const float& Z):x(X),y(Y),z(Z){}
//     Vec3 operator+(const Vec3 &b) { return {x + b.x, y + b.y, z + b.z}; }
//     Vec3 operator-(const Vec3 &b) { return {x - b.x, y - b.y, z - b.z}; }
//     Vec3 operator*(float &scalar) { return {x * scalar, y * scalar, z * scalar}; }

//     float dot(const Vec3& b){
//         // return (a.x * b.x + a.y * b.y, a.z * b.z);
//         return (x * b.x) + (y * b.y) + (z * b.z);
//     }

//     Vec3 cross(Vec3& b){
//         Vec3 c;
//         c.x = (y * b.z) - (z * b.y);
//         c.y = -((x * b.z) - (z * b.x));
//         c.z = (x * b.y) - (y * b.x);
//         return c;
//     }

// };

Vec3 lineIntersectPlane(Vec3 &lineOrigin, Vec3 &lineDirection, Vec3 &pointOnPlane, Vec3 &normalOfPlane)
{
    // below is vector  form of line equation
    // equation of line r = r' + t.dir, where 
    // r is arbitary pint on line
    // r' is origin of line, a.k.a., point on a line
    // t is scalar
    // dir is direction vector
    // 
    // equation plane
    // n.(p-p') = 0
    // n is plane's normal vector
    // p is arbitarty point on plane
    // p' is known point on plane, a.k.a., fixed point
    //
    // after solving the both the equations, for "t"
    // t =  -{n.(r'-p')}  /  {n.dir}
    // float tolerance = 1e-9;
    // float denominator = normalOfPlane.dot(lineDirection);
    Vec3 intersectionPoint;
    intersectionPoint.x = 0, intersectionPoint.y = 0, intersectionPoint.z = 0;
    float t=0;
    float temp = normalOfPlane.dot(lineDirection);
    if (temp > 0.001){
        Vec3 temp1 = pointOnPlane - lineOrigin;
        // t = (normalOfPlane.dot());
        t = normalOfPlane.dot(temp1);
        t = t / temp;
        intersectionPoint = lineOrigin + (lineDirection * t);
    }
    else{
        std::cout << "Either both are parallel or colinear" << std::endl;
    }
    return intersectionPoint;
}

// std::tuple<Vec3, Vec3> Plane3D;

// std::tuple k(std::vector<Vec3*> trainglePoints){
//     Plane3D p;
//     p
//     return p;
// };

int main(int, char **)
{
    // equation of line
    Vec3 pointOnLine{1,2,3};
    Vec3 lineDirection{4,1,2};

    Vec3 pointOnPlane{2,5,8};
    Vec3 normalVector{4,2,8};

    Vec3 intersectionPoint = lineIntersectPlane(pointOnLine, lineDirection, pointOnPlane, normalVector);
    std::cout << "The intersection point is:\n ("
    <<intersectionPoint.x<<","
    <<intersectionPoint.y<<","
    <<intersectionPoint.z<<")" << std::endl;

    std::vector<Vec3*> trianglePoints = {
        new Vec3(1, 2, 3),
        new Vec3(4, 2, 3),
        new Vec3(5, 2, 9)};

    
    

};