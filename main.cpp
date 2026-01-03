#include <iostream>
#include <vector>
#include "Vec3.h"
#include "Line.h"
#include "Plane.h"
#include "Utility.h"

int main(int, char **){

    Line line = {*(new Vec3(1,2,3)), *(new Vec3(4,1,2))};
    std::vector<Vec3*> trianglePoints = {
        new Vec3(1, 1, 3),
        new Vec3(6, 9, 2),
        new Vec3(5, 6, 7)
    };
    Plane planeOfTriangle = Utility::PlaneOfTriangle(trianglePoints);
    Vec3 intersectionPoint = Utility::LinePlaneIntersection(line, planeOfTriangle);

    std::cout << "The intersection point is:\n ("
        <<intersectionPoint.x<<","
        <<intersectionPoint.y<<","
        <<intersectionPoint.z<<")" << 
    std::endl;

    bool result = Utility::PointInTriangleOrNot(trianglePoints, intersectionPoint);
    std::cout << "and the line crosses the triangle or not:" << result << std::endl;

    Utility::TextFileGenerator(line, trianglePoints, intersectionPoint);
};