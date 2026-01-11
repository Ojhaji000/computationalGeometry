#include <vector>
#include "Vec3.h"
#include "Utility.h"
#include "TextFile.h"

enum PolygonPointIterationDirection
{
    clockWise,
    counterClockWise,
    denegerate
};

PolygonPointIterationDirection FindIterationDirection(const std::vector<Vec3 *>&polygon){
    Vec3 pointA = *polygon[0], pointB = *polygon[1], pointC = *polygon[2];
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
    return false;
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

std::vector<Vec3 *> computeKernel(const std::vector<Vec3 *>& polygon, const PolygonPointIterationDirection &iterationDir) {
    std::vector<Vec3 *> kernel = {// largest bounding box(kernel), which will be clipped over and over again
                                  new Vec3(-1e9, -1e9), new Vec3(1e9, -1e9),
                                  new Vec3(1e9, 1e9), new Vec3(-1e9, 1e9)};

    for (int i = 0; i < polygon.size(); i++) {
        Vec3 polygonPointA = *polygon[i];
        Vec3 polygonPointB = *polygon[(i+1) % polygon.size()];
        
        std::vector<Vec3 *> newKernel;

        for (int j = 0; j < kernel.size(); j++) { 
            Vec3 kernelCurrentPoint = *kernel[j];
            Vec3 kernalNextPoint = *kernel[(j+1) % kernel.size()];

            bool isCurrentKernelPointInside = insideHalfPlane(
                polygonPointA, polygonPointB, kernelCurrentPoint, iterationDir
            );
            bool isNextKernelPointInside = insideHalfPlane(
                polygonPointA, polygonPointB, kernalNextPoint, iterationDir
            );

            if (isCurrentKernelPointInside) newKernel.push_back(&kernelCurrentPoint);

            if (isCurrentKernelPointInside ^ isNextKernelPointInside) { // XOR operation
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
                float A1 = polygonPointB.y - polygonPointA.y;
                float B1 = polygonPointA.x - polygonPointB.x;
                float C1 = A1*polygonPointA.x + B1*polygonPointA.y;

                float A2 = kernalNextPoint.y - kernelCurrentPoint.y;
                float B2 = kernelCurrentPoint.x - kernalNextPoint.x;
                float C2 = A2*kernelCurrentPoint.x + B2*kernelCurrentPoint.y;

                // cramer rule
                // https://en.wikipedia.org/wiki/Cramer%27s_rule#Applications

                float determinant = A1*B2 - A2*B1;
                if (fabs(determinant) > 1e-9) {
                    float x = (B2*C1 - B1*C2) / determinant;
                    float y = (A1*C2 - A2*C1) / determinant;
                    newKernel.push_back(new Vec3(x,y));
                }
            }
        }
        kernel = newKernel;
        if (kernel.empty()) break;
    }
    return kernel;
}

int main() {
    // std::vector<Vec3 *> polygon = {
    //     new Vec3(0,0),
    //     new Vec3(6,0), 
    //     new Vec3(6,2), 
    //     new Vec3(1,2),
    //     new Vec3(4,5),
    //     new Vec3(3,3),
    //     new Vec3(6,3),
    //     new Vec3(4,6),
    //     new Vec3(0,6)
    // };
    std::vector<Vec3*> polygon = {
    // new Vec3(0, 3),   // top point
    // new Vec3(1, 1),   // right upper
    // new Vec3(3, 1),   // right lower
    // new Vec3(1.5, -1),// bottom right
    // new Vec3(2.5, -3),// bottom tip
    // new Vec3(0, -2),  // bottom center
    // new Vec3(-2.5, -3),// bottom left tip
    // new Vec3(-1.5, -1),// bottom left
    // new Vec3(-3, 1),   // left lower
    // new Vec3(-1, 1)    // left upper
    new Vec3(0,0), new Vec3(4,4), new Vec3(2,4)
};

    if(polygon.size()<3){
        std::cout << "not a polygon" << std::endl;
        return 0;
    }
    PolygonPointIterationDirection iterationDir = FindIterationDirection(polygon);
    if(iterationDir == denegerate){
        std::cout << "points of polygon are collinear" <<std::endl;
        return 1;
    }
    std::vector<Vec3 *> kernel = computeKernel(polygon, iterationDir);

    if (kernel.empty()) {
        std::cout << "Polygon is NOT star-shaped." << std::endl;
    } else {
        std::cout << "Polygon is star-shaped. Kernel coordinates:" <<std:: endl;
        for (auto p : kernel) {
            std::cout << "(" << (*p).x << ", " << (*p).y << ")" << std::endl;
        }
    }
    
    
    TextFile outputFile;
    outputFile.Add2DPolygon(polygon);
    outputFile.Add2DPolygon(kernel);
    outputFile.GeneratorFile("starShapedPloygon");
}