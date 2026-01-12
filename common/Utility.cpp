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
    Vec3 planeNormal(plane.normal.x, plane.normal.y, plane.normal.z);
    Vec3 lineDir(line.direction.x, line.direction.y, line.direction.z);
    Vec3 lineOrigin(line.origin.x, line.origin.y, line.origin.z);
    Vec3 planePoint(plane.point.x, plane.point.y, plane.point.z);
    const float temp = planeNormal.dot(lineDir);
    if (temp > 0.001){
        const Vec3 temp1 = planePoint - lineOrigin;
        float t = planeNormal.dot(temp1);
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

// void Utility::TextFileGenerator(const Line &line, const std::vector<Vec3*> &trianglePoints, const Vec3 &intersectionPoint){
//     const std::string filePath = "../output.txt"; 
//     std::ofstream outputFile(filePath);
//     if (!outputFile.is_open()) {
//         std::cerr << "Error opening the file!" << std::endl;
//         return; // Return an error code
//     }
//     // line
//     outputFile << "\\ \\left("
//     <<line.origin.x<<","<< line.origin.y<<","<<line.origin.z
//     <<"\\right)+t\\left("<<
//     line.direction.x<<","<<line.direction.y<<","<<line.direction.z
//     <<"\\right)"<<std::endl;
//     // plane
//     // outputFile << "4\\left(x-2\\right)+2\\left(y-5\\right)+8\\left(z-8\\right)=0" << std::endl;
//     // triangle
//     outputFile << "\\operatorname{triangle}\\left(\\left("
//     <<trianglePoints[0]->x<<","<<trianglePoints[0]->y<<","<<trianglePoints[0]->z
//     <<"\\right),\\left("
//     <<trianglePoints[1]->x<<","<<trianglePoints[1]->y<<","<<trianglePoints[1]->z
//     <<"\\right),\\left("
//     <<trianglePoints[2]->x<<","<<trianglePoints[2]->y<<","<<trianglePoints[2]->z
//     <<"\\right)\\right)" << std::endl;
//     // point of intersection
//     outputFile << "("
//     <<intersectionPoint.x<<","<<intersectionPoint.y<<","<<intersectionPoint.z
//     <<")";
//     // 4. Close the file
//     outputFile.close();
//     std::cout << "Data successfully written to output.txt" << std::endl;
// }
// void Utility::TextFileGenerator(const std::vector<Vec3*> polygonPoints, std::string fileName){
//     const std::string filePath = "../"+fileName+".txt"; 
//     std::ofstream outputFile(filePath);
//     if (!outputFile.is_open()) {
//         std::cerr << "Error opening the file!" << std::endl;
//         return; // Return an error code
//     }
//     // \operatorname{polygon}((0,0),(3,0),(3,4),(0,4))
//     // line
//     outputFile << "\\operatorname{polygon}\\left(";
//     for (size_t i = 0; i < polygonPoints.size();i++)
//     {
//         outputFile << "\\left(" << (*polygonPoints[i]).x << "," << (*polygonPoints[i]).y << "\\right)";
//         if(AreEqual(i+1,polygonPoints.size())){break;}
//         outputFile << ",";
//     }
//     outputFile << "\\right)";
// // \operatorname{polygon}\left(\left(1,2\right),\left(5,7\right),\left(4,9\right)\right)
//     // 4. Close the file
//     outputFile.close();
//     std::cout << "Data successfully written to "<<fileName<<".txt" << std::endl;
// }

Vec3 Utility::LineLineIntersectionPoint2D(const std::vector<Vec3> line2DFirst, const std::vector<Vec3> line2DSecond){
    // intersection point
    // forming two lines, each from polygon and kernel points respectively
    // for representation, using standard form for line eqaution: Ax + By + C = 0
    // and using two point form for finding the value of A,B,C
    // (y - y1) / (y2 - y1) = (x - x1) / (x2 - x1)
    // so A = (y2 - y1);
    // B = -(x2 - x1) = (x1 - x2);
    // C = (y2 - y1) * x1 - (x2 - x1) * y1 
    //   = (y2 - y1) * x1 + (x1 - x2) * y1
    //   = A * x1 + B * y1;
    double A1 = ((double)line2DFirst[1].y ) -((double) line2DFirst[0].y );
    double B1 = ((double)line2DFirst[0].x ) -((double) line2DFirst[1].x );
    double A2 = ((double)line2DSecond[1].y) -((double) line2DSecond[0].y);
    double B2 = ((double)line2DSecond[0].x) -((double) line2DSecond[1].x);
    double C1 = A1 * ((double)line2DFirst[0].x) + B1 * ((double)line2DFirst[0].y);
    double C2 = A2 * ((double)line2DSecond[0].x);
    double temp = B2 *((double)line2DSecond[0].y);
    C2 += temp;

    // cramer rule
    // https://en.wikipedia.org/wiki/Cramer%27s_rule#Applications

    float x, y;
    double determinant = (A1 * B2) - (A2 * B1);
    if (fabs(determinant) > 1e-7) {
        x = ((B2 * C1 - B1 * C2) / determinant);
        x = AreEqual(0, x) ? 0 : x;
        y = ((A1 * C2 - A2 * C1) / determinant);
        y = AreEqual(0, y) ? 0 : y;
    }
    Vec3 resultant((float)x, (float)y);
    return resultant;
}