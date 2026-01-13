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

PolygonPointIterationDirection FindIterationDirection(const std::vector<Vec3>&polygon){
    // this function uses the shoelace formula for finding the area
    // https://en.wikipedia.org/wiki/Shoelace_formula
    double area = 0.0;
    int n = polygon.size();
    
    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        area += (polygon[i].x * polygon[j].y - polygon[j].x * polygon[i].y);
    }

    area /= 2.0;

    if(area>0){
        return counterClockWise;
    }
    else if (area < 0)
    {
        return clockWise;
    }
    else
    {
        std::cout << "the polygon is degenerate(collinear), because points are collinear" << std::endl;
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
    Vec3 vectorAB = pointB - pointA;
    Vec3 vectorCB = pointB - pointC;
    Vec3 resultantVector = vectorAB.cross(vectorCB);

    double coefficientOfZcomponentOfCrossProductresultant = resultantVector.z;
    if(Utility::AreEqual(coefficientOfZcomponentOfCrossProductresultant, 0)){
        return false;
    }
        
    switch (iterationDir)
    {
        case clockWise:
            return coefficientOfZcomponentOfCrossProductresultant > 0;
            break;
        case counterClockWise:
            return coefficientOfZcomponentOfCrossProductresultant < 0;
            break;
    }
    return false;
}

std::vector<Vec3> computeKernel(const std::vector<Vec3>& polygon, const PolygonPointIterationDirection &iterationDir) {

    // largest bounding box(kernel), which will be clipped over and over again

    std::vector<Vec3> kernel = {
        *(new Vec3(-1e7, -1e7)),
        *(new Vec3(1e7, -1e7)),
        *(new Vec3(1e7, 1e7)),
        *(new Vec3(-1e7, 1e7))};

    for (int i = 0; i < polygon.size(); i++) {
        Vec3 polygonPointA(polygon[i]);
        int i2 = (i + 1) % polygon.size();
        Vec3 polygonPointB(polygon[i2]);

        std::vector<Vec3> newKernel;

        for (int j = 0; j < kernel.size(); j++) { 
            Vec3 kernelCurrentPoint(kernel[j]);
            int j2 = (j + 1) % kernel.size();
            Vec3 kernalNextPoint(kernel[j2]);

            bool isCurrentKernelPointInside = insideHalfPlane(
                polygonPointA, polygonPointB, kernelCurrentPoint, iterationDir
            );
            bool isNextKernelPointInside = insideHalfPlane(
                polygonPointA, polygonPointB, kernalNextPoint, iterationDir
            );

            if (isCurrentKernelPointInside) newKernel.push_back(*(new Vec3(kernelCurrentPoint)));

            if (isCurrentKernelPointInside ^ isNextKernelPointInside) { // XOR operation

                std::vector<Vec3> polygonEdge = {polygonPointA, polygonPointB};
                std::vector<Vec3> kernalEdge = {kernelCurrentPoint, kernalNextPoint};
                Vec3 intersectionPoint = Utility::LineLineIntersectionPoint2D(polygonEdge, kernalEdge);
                newKernel.push_back(intersectionPoint);
            }
        }
        // for debugging purpose
        // std::string pointStr;
        // for(auto p : newKernel)
        // {
        //     pointStr += "(" + std::to_string(p.x) + "," + std::to_string(p.y) + "),";
        // }
        kernel = newKernel;
        if (kernel.empty()) break;
    }
    return kernel;
}

int main() {
    std::vector<Vec3> polygon = {
        // polygon 1 for testing
        // *(new Vec3(0,0)),
        // *(new Vec3(6,0)),
        // *(new Vec3(6,2)),
        // *(new Vec3(1,2)),
        // *(new Vec3(4,5)),
        // *(new Vec3(3,3)),
        // *(new Vec3(6,3)),
        // *(new Vec3(4,6)),
        // *(new Vec3(0,6))

        // polygon 2 for testing
        *(new Vec3(0, 3)),     // top point
        *(new Vec3(1, 1)),     // right upper
        *(new Vec3(3, 1)),     // right lower
        *(new Vec3(1.5, -1)),  // bottom right
        *(new Vec3(2.5, -3)),  // bottom tip
        *(new Vec3(0, -2)),    // bottom center
        *(new Vec3(-2.5, -3)), // bottom left tip
        *(new Vec3(-1.5, -1)), // bottom left
        *(new Vec3(-3, 1)),    // left lower
        *(new Vec3(-1, 1))     // left upper

        // polygon 3 for testing
        // *(new Vec3(0, 3)),
        // *(new Vec3(2, 3)),
        // *(new Vec3(3, 0)),
        // *(new Vec3(4, 3)),
        // *(new Vec3(3, 6)),
        // *(new Vec3(1.5, 5))

        // polygon 4 for testing
        // *(new Vec3(0, 0)),
        // *(new Vec3(4, 0)),
        // *(new Vec3(4, 4)),
        // *(new Vec3(2, 2)), // inward dent → makes it concave
        // *(new Vec3(0, 4))

        // polygon 5 for testing
        // *(new Vec3(0, 0)),
        // *(new Vec3(2.828, 2.828)),
        // *(new Vec3(0, 5.657)),
        // *(new Vec3(0, 2.828)), // inward dent → concave
        // *(new Vec3(-2.828, 2.828))

        // polygon 6 for testing
        // *(new Vec3(0, 0)),
        // *(new Vec3(2.828, 2.828)),
        // *(new Vec3(0, 5.657)),
        // *(new Vec3(-1.414, 4.242)), // new inward dent
        // *(new Vec3(0, 2.828)),      // original inward dent
        // *(new Vec3(-2.828, 2.828))

        // polygon 7 for testing
        // *(new Vec3(0, 0)),
        // *(new Vec3(2.828, 2.828)),
        // *(new Vec3(0, 5.657)),
        // *(new Vec3(0, 2.828)),    // dent #1
        // *(new Vec3(-2.828, 5.657)), // dent #2
        // *(new Vec3(-2.828, 2.828))

        // polygon 8 for testing
        // *(new Vec3(0, 0)),
        // *(new Vec3(2.828, 2.828)),
        // *(new Vec3(0, 5.657)),
        // *(new Vec3(0, 2.828)),      // inward dent #1
        // *(new Vec3(-0.707, 7.778)), // outward bump
        // *(new Vec3(-2.828, 5.657)), // inward dent #2
        // *(new Vec3(-2.828, 2.828))

        // polygon 9 for testing
        // *(new Vec3(0, 3)),
        // *(new Vec3(2, 3)),
        // *(new Vec3(3, 0)),
        // *(new Vec3(4, 3)),
        // *(new Vec3(6, 3)),
        // *(new Vec3(4.5, 5)),
        // *(new Vec3(5.5, 8)),
        // *(new Vec3(3, 6)),
        // *(new Vec3(0.5, 8)),
        // *(new Vec3(1.5, 5))

        // polygon 10 for testing
        // *(new Vec3(0, 0)),      // bottom-left
        // *(new Vec3(2, 1)),      // bottom dent inward
        // *(new Vec3(4, 0)),      // bottom-right
        // *(new Vec3(4, 4)),      // top-right
        // *(new Vec3(2, 3)),      // top dent inward
        // *(new Vec3(0, 4))       // top-left

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

    std::vector<Vec3> kernel = computeKernel(polygon, iterationDir);

    if (kernel.empty()) {
        std::cout << "Polygon is NOT star-shaped." << std::endl;
    }
    else
    {
        std::cout << "Polygon is star-shaped. Kernel coordinates:" <<std:: endl;
        for (auto p : kernel) {
            std::cout << "(" << (p).x << ", " << (p).y << ")" << std::endl;
        }
    }

    TextFile outputFile;
    outputFile.Add2DPolygon(polygon);
    outputFile.Add2DPolygon(kernel);
    outputFile.GeneratorFile("starShapedPloygon");
}