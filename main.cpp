#include <iostream>
#include <vector>
#include "Vec3.h"
#include "Line.h"
#include "Plane.h"
#include "Utility.h"
#include <fstream>

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



    const std::string filePath = "../data/output.txt"; 
    std::ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1; // Return an error code
    }




    // line
    // outputFile << "\\ \\left(1,2,3\\right)+t\\left(4,1,2\\right)"<<std::endl;
    outputFile << "\\ \\left("
    <<line.origin.x<<","<< line.origin.y<<","<<line.origin.z
    <<"\\right)+t\\left("<<
    line.direction.x<<","<<line.direction.y<<","<<line.direction.z
    <<"\\right)"<<std::endl;

    // plane
    // outputFile << "4\\left(x-2\\right)+2\\left(y-5\\right)+8\\left(z-8\\right)=0" << std::endl;

    // triangle
    // outputFile << "\\operatorname{triangle}\\left(\\left(2,-1,0\\right),\\left(2,2,0\\right),\\left(0,0,2\\right)\\right)" << std::endl;
    outputFile << "\\operatorname{triangle}\\left(\\left("
    <<trianglePoints[0]->x<<","<<trianglePoints[0]->y<<","<<trianglePoints[0]->z
    <<"\\right),\\left("
    <<trianglePoints[1]->x<<","<<trianglePoints[1]->y<<","<<trianglePoints[1]->z
    <<"\\right),\\left("
    <<trianglePoints[2]->x<<","<<trianglePoints[2]->y<<","<<trianglePoints[2]->z
    <<"\\right)\\right)" << std::endl;

    // point of intersection
    // outputFile << "(6.88235,3.47059,5.94118)" << std::endl;
    outputFile << "("
    <<intersectionPoint.x<<","<<intersectionPoint.y<<","<<intersectionPoint.z
    <<")" << std::endl;
    // outputFile << "This is some text output in C++." << std::endl;
    // outputFile << "You can write numbers too: " << 12345 << std::endl;

    // 4. Close the file
    outputFile.close();

    std::cout << "Data successfully written to output.txt" << std::endl;

};