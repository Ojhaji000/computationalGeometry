#include "Utility.h"

Vec3 Utility::LinePlaneIntersection(const Line &line, const Plane &plane)
// Vec3 lineIntersectPlane(const Line &line, const Plane &plane)
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

Plane Utility::PlaneOfTriangle(const std::vector<Vec3*> &trianglePoints){
    // three pooints:p,q,r
    // vector pq, vector pr;
    Vec3 PQ = *trianglePoints[0] - *trianglePoints[1];
    Vec3 PR = *trianglePoints[0] - *trianglePoints[2];
    
    // cross prduct of above two vectors = normal of the plane;
    Vec3 normal = PQ.cross(PR);

    // return point on plane and normal of plane;
    return {*trianglePoints[0], normal};
}

bool Utility::PointInTriangleOrNot(const std::vector<Vec3*> &trianglePoints, const Vec3 &point){
    float originalArea = CalculateTriangleArea(trianglePoints);
    // area method
    
    for (int i = 0; i < trianglePoints.size();i++){
        int i1 = i, i2 = i + 1;
        i2 = (AreEqual(i2,trianglePoints.size())) ? 0 : i2;
        std::vector <Vec3*> triangleWithAnotherPoint = {
            new Vec3(point),
            new Vec3(*trianglePoints[i1]),
            new Vec3(*trianglePoints[i2])
        };
        float tempArea = CalculateTriangleArea(triangleWithAnotherPoint);
        if ((tempArea-originalArea)>0.001)
        {
            return false;
        }
    }
    return true;
}

float Utility::CalculateTriangleArea(const std::vector<Vec3*> &trianglePoints){
    float semiPerimeter = 0;
    std::vector<float> tempVector;
    for (int i = 0; i < trianglePoints.size(); i++)
    {
        float distanceBetweenConsecutivePoints = 0;
        
        int i1 = i, i2 = i + 1;
        i2 = AreEqual(i2, trianglePoints.size()) ? 0 : i2;
        distanceBetweenConsecutivePoints = DistanceBetweenTwoPoints(*trianglePoints[i1], *trianglePoints[i2]);
        tempVector.push_back(distanceBetweenConsecutivePoints);
        semiPerimeter += distanceBetweenConsecutivePoints;
    }
    semiPerimeter /= 2;
    float area = sqrt(semiPerimeter * (semiPerimeter - tempVector[0]) * (semiPerimeter - tempVector[1]) * (semiPerimeter - tempVector[2]));
    return area;
}

float Utility::DistanceBetweenTwoPoints(const Vec3 &a,const Vec3 &b){
    return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2) + pow((b.z - a.z), 2));
}

bool Utility::AreEqual(float a, float b){
    return std::abs(a - b) < Epsilon;
}

void Utility::TextFileGenerator(const Line &line, const std::vector<Vec3*> &trianglePoints, const Vec3 &intersectionPoint){
    const std::string filePath = "../data/output.txt"; 
    std::ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return; // Return an error code
    }

    // line
    outputFile << "\\ \\left("
    <<line.origin.x<<","<< line.origin.y<<","<<line.origin.z
    <<"\\right)+t\\left("<<
    line.direction.x<<","<<line.direction.y<<","<<line.direction.z
    <<"\\right)"<<std::endl;

    // plane
    // outputFile << "4\\left(x-2\\right)+2\\left(y-5\\right)+8\\left(z-8\\right)=0" << std::endl;

    // triangle
    outputFile << "\\operatorname{triangle}\\left(\\left("
    <<trianglePoints[0]->x<<","<<trianglePoints[0]->y<<","<<trianglePoints[0]->z
    <<"\\right),\\left("
    <<trianglePoints[1]->x<<","<<trianglePoints[1]->y<<","<<trianglePoints[1]->z
    <<"\\right),\\left("
    <<trianglePoints[2]->x<<","<<trianglePoints[2]->y<<","<<trianglePoints[2]->z
    <<"\\right)\\right)" << std::endl;

    // point of intersection
    outputFile << "("
    <<intersectionPoint.x<<","<<intersectionPoint.y<<","<<intersectionPoint.z
    <<")" << std::endl;

    // 4. Close the file
    outputFile.close();
    std::cout << "Data successfully written to output.txt" << std::endl;
}