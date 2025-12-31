#include <iostream>
#include <vector>
#include "Vec3.h"
#include "Line.h"
#include "Plane.h"

Vec3 lineIntersectPlane(const Line &line, const Plane &plane)
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
    float t=0;
    Vec3 planeNormal(plane.normal.x, plane.normal.y, plane.normal.z);
    Vec3 lineDir(line.direction.x, line.direction.y, line.direction.z);
    Vec3 lineOrigin(line.origin.x, line.origin.y, line.origin.z);
    Vec3 planePoint(plane.point.x, plane.point.y, plane.point.z);
    const float temp = planeNormal.dot(lineDir);
    if (temp > 0.001){
        const Vec3 temp1 = planePoint - lineOrigin;
        t = planeNormal.dot(temp1);
        t = t / temp;
        intersectionPoint = lineOrigin +(lineDir*t);
    }
    else{
        std::cout << "Either both are parallel or collinear" << std::endl;
    }
    return intersectionPoint;
}

Plane triangleToPlane(const std::vector<Vec3*> &trianglePoints){
    // three pooints:p,q,r
    // vector pq, vector pr;
    Vec3 PQ = *trianglePoints[0] - *trianglePoints[1];
    Vec3 PR = *trianglePoints[0] - *trianglePoints[2];
    
    // cross prduct of above two vectors = normal of the plane;
    Vec3 normal = PQ.cross(PR);

    // return point on plane and normal of plane;
    return {*trianglePoints[0], normal};
}


int main(int, char **){

    Line line = {*(new Vec3(1,2,3)), *(new Vec3(4,1,2))};
    std::vector<Vec3*> trianglePoints = {
        new Vec3(1, 1, 3),
        new Vec3(6, 9, 2),
        new Vec3(5, 6, 7)
    };
    Plane planeOfTriangle= triangleToPlane(trianglePoints);
    Vec3 intersectionPoint = lineIntersectPlane(line, planeOfTriangle);

    // Line l = {*(new Vec3(2,0,0)),*(new Vec3(0,1,0))};
    // Plane p = {*(new Vec3(0, 0, 0)), *(new Vec3(1, 1, 1))};
    // Vec3 intersectionPoint = lineIntersectPlane(l, p);

    std::cout << "The intersection point is:\n ("
        <<intersectionPoint.x<<","
        <<intersectionPoint.y<<","
        <<intersectionPoint.z<<")" << 
    std::endl;

};