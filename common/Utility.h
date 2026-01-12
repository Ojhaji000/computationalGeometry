#pragma once
#include "Vec3.h"
#include "Plane.h"  
#include "Line.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
class Utility{
    private:
        static constexpr float Epsilon = std::numeric_limits<float>::epsilon() * 100;

    public:
        static Vec3 LinePlaneIntersection(const Line &line, const Plane &plane);
        static Plane PlaneOfTriangle(const std::vector<Vec3*> &trianglePoints);
        static bool PointInTriangleOrNot(const std::vector<Vec3 *> &trianglePoints, const Vec3 &point);
        static float CalculateTriangleArea(const std::vector<Vec3*> &trianglePoints);
        static float DistanceBetweenTwoPoints(const Vec3 &a, const Vec3 &b);
        static bool AreEqual(float a, float b);
        static Vec3 LineLineIntersectionPoint2D(const std::vector<Vec3> line2DFirst, const std::vector<Vec3> line2DSecond);
};

// Shoelace formula for signed area
// double signedArea(const vector<Point>& poly) {
//     double area = 0;
//     int n = poly.size();
//     for (int i = 0; i < n; i++) {
//         int j = (i+1) % n;
//         area += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
//     }
//     return area / 2.0;
// }