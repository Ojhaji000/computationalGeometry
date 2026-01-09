#include <vector>
#include "../common/Vec3.h"
#include "../common/Utility.h"

enum PolygonPointIterationDirection
{
    clockWise,
    counterClockWise,
    denegerate
};

PolygonPointIterationDirection FindIterationDirection(const std::vector<Vec3>polygon){
    Vec3 pointA = polygon[0], pointB = polygon[1], pointC = polygon[2];
    Vec3 vectorAB = pointB - pointA;
    Vec3 vectorCB = pointB - pointC;
    Vec3 resultantVector = vectorAB.cross(vectorCB);
    if(resultantVector.z>0){
        return counterClockWise;
    }else if(resultantVector.z<0){
        return clockWise;
    }else{
        std::cout << "the polygon is degenerate(collinear)" << std::endl;
        return denegerate;
    }
}

bool insideHalfPlane(const Vec3 pointA, const Vec3 pointB, const Vec3 pointInQuestion, const PolygonPointIterationDirection &iterationDir)
{  
    // usually when we are given the polygon points, either it is in clockwise series
    // or counterclockwise. That's how we tranverse it, going either of the two
    // ways. The below function tells that direction.
// when we are given points, namely A & B, and to form an edge, we do it by
    // forming a vector which B-A, going from A to B. Similarly C-B for the edge
    // between B and C going from B to C.
    //
// and to check the direction of point iteration in for loop is whether
    // clockwise or counter-clockwise on the 2d plane, we could use the cross product
    //
// in polygon all the points are collinear, and they are in 2D plane, so the cross
// product's resulting vector either point to +ve z direction or -ve z direction
    //
    // using the right hand thumb rule the, helps us in the resulting direction orientation
    //
    // so when we go counter-clockwise, the resultant vector's direction is +ve z and
    // vice-versa
    //
    // For the cross product the common origin for the two vecctors is necessary.
// So from any  three consecutive points in the polygon: A, B, C;
    // forming two vectors:
    // (A-B), going from B to A 
    // and 
    // (C-B), going from B to C.
    // and in cross product, we will only focus on the sign of k-cap (or z component)
    // look the image in the current directory for clarity
    Vec3 pointC = pointInQuestion;
    Vec3 vectorAB = pointB - pointA; // point
    Vec3 vectorCB = pointB - pointC;
    Vec3 resultantVector = vectorAB.cross(vectorCB);

    double coefficientOfZcomponentOfCrossProductresultant = resultantVector.z;
    switch (iterationDir)
    {
        case clockWise:
            return coefficientOfZcomponentOfCrossProductresultant <= 0;
            break;
        case counterClockWise:
            return coefficientOfZcomponentOfCrossProductresultant >= 0;
            break;
    }
}

// double polygonArea(const vector<Vec3>& poly) {
//     double area = 0;
//     int n = poly.size();
//     for (int i = 0; i < n; i++) {
//         int j = (i + 1) % n;
//         area += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
//     }
//     return fabs(area) / 2.0;
// }

std::vector<Vec3> computeKernel(const std::vector<Vec3>& poly, const PolygonPointIterationDirection &iterationDir) {
    std::vector<Vec3> kernel = { // largest bounding box(kernel), which will be clipped over and over again
        { -1e9, -1e9 }, { 1e9, -1e9 },
        { 1e9,  1e9 }, { -1e9,  1e9 }
    };

    for (int i = 0; i < poly.size(); i++) {
        Vec3 a = poly[i];
        Vec3 b = poly[(i+1) % poly.size()];
        std::vector<Vec3> newKernel;

        for (int j = 0; j < kernel.size(); j++) { 
            Vec3 curr = kernel[j];
            Vec3 next = kernel[(j+1) % kernel.size()];
            bool currInside = insideHalfPlane(a, b, curr, iterationDir);
            bool nextInside = insideHalfPlane(a, b, next, iterationDir);

            if (currInside) newKernel.push_back(curr);
            if (currInside ^ nextInside) {
                // intersection point
                double A1 = b.y - a.y;
                double B1 = a.x - b.x;
                double C1 = A1*a.x + B1*a.y;

                double A2 = next.y - curr.y;
                double B2 = curr.x - next.x;
                double C2 = A2*curr.x + B2*curr.y;

                double det = A1*B2 - A2*B1;
                if (fabs(det) > 1e-9) {
                    float x = (float)(B2*C1 - B1*C2) / det;
                    float y = (float)(A1*C2 - A2*C1) / det;
                    newKernel.push_back({x,y,0});
                }
            }
        }
        kernel = newKernel;
        if (kernel.empty()) break;
    }
    return kernel;
}

int main() {
    std::vector<Vec3> polygon = {
        {0,0}, {6,0}, {6,2}, {1,2}, {4,5},{3,3},{6,3},{4,6},{0,6}
    };
    if(polygon.size()<3){
        std::cout << "not a polygon" << std::endl;
        return 0;
    }
    PolygonPointIterationDirection iterationDir = FindIterationDirection(polygon);
    if(iterationDir == denegerate)
        return;
    std::vector<Vec3> kernel = computeKernel(polygon, iterationDir);

    if (kernel.empty()) {
        std::cout << "Polygon is NOT star-shaped." << std::endl;
    } else {
        std::cout << "Polygon is star-shaped. Kernel coordinates:" <<std:: endl;
        for (auto &p : kernel) {
            std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
        }
        // cout << "Kernel area = " << polygonArea(kernel) << endl;
    }
    Utility::TextFileGenerator(kernel, polygon)
}