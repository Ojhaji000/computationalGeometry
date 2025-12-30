#include <iostream>
#include <vector>
#include "Vec3.h"

struct Line{
    Vec3* origin;
    Vec3* direction;
};

struct Plane{
    Vec3* point;
    Vec3* normal;
};

Vec3 lineIntersectPlane(const Line &line, const Plane &plane) //const Vec3 &lineOrigin, const Vec3 &lineDirection, const Vec3 &pointOnPlane, const Vec3 &normalOfPlane)
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
    Vec3 intersectionPoint(0,0,0);
    // intersectionPoint.x = 0, intersectionPoint.y = 0, intersectionPoint.z = 0;
    float t=0;
    float temp = (plane.normal)->dot(*(line.direction)); // normalOfPlane.dot(lineDirection);
    if (temp > 0.001){
        Vec3 temp1 = *plane.point - *line.origin; // pointOnPlane - lineOrigin;
        // t = (normalOfPlane.dot());
        t = plane.normal->dot(temp1); // normalOfPlane.dot(temp1);
        t = t / temp;
        intersectionPoint = *line.origin +((*line.direction)*t); // lineOrigin + (lineDirection * t);
    }
    else{
        std::cout << "Either both are parallel or colinear" << std::endl;
    }
    return intersectionPoint;
}

Plane triangleToPlane(std::vector<Vec3*> trianglePoints){
    // three pooints:p,q,r
    // vector pq, vector pr;
    Vec3 PQ = *trianglePoints[1] - *trianglePoints[0];
    Vec3 PR = *trianglePoints[2] - *trianglePoints[0];
    
    // cross prduct of above two vectors = normal of the plane;
    Vec3 normal = PQ.cross(PR);

    // return point on plane and normal of plane;
    return {trianglePoints[0], &normal};
}

int main(int, char **)
{
    // equation of line
    // Vec3 pointOnLine{1,2,3};
    // Vec3 lineDirection{4,1,2};

    // Vec3 pointOnPlane{2,5,8};
    // Vec3 normalVector{4,2,8};

    // Vec3 intersectionPoint = lineIntersectPlane(pointOnLine, lineDirection, pointOnPlane, normalVector);
    // std::cout << "The intersection point is:\n ("
    // <<intersectionPoint.x<<","
    // <<intersectionPoint.y<<","
    // <<intersectionPoint.z<<")" << std::endl;

    std::vector<Vec3*> trianglePoints = {
        new Vec3(1, 2, 3),
        new Vec3(4, 2, 3),
        new Vec3(5, 2, 9)};

    
    // std::tuple<Vec3*, Vec3*> planeOfTriangle = triangleToPlane(trianglePoints);

    Plane planeOfTriangle= triangleToPlane(trianglePoints);
    Line line = {new Vec3(1,2,3),new Vec3(4,1,2)};

    // delete &intersectionPoint;
    Vec3 intersectionPoint = lineIntersectPlane(line, planeOfTriangle);
        std::cout << "The intersection point is:\n ("
    <<intersectionPoint.x<<","
    <<intersectionPoint.y<<","
    <<intersectionPoint.z<<")" << std::endl;

};