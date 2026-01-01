#pragma once
#include "Vec3.h"
#include "Plane.h"  
#include "Line.h"
#include <iostream>
#include <vector>
#include <math.h>
class Utility{
    private:
        static constexpr float Epsilon = std::numeric_limits<float>::epsilon() * 100;

        static float CalculateTriangleArea(const std::vector<Vec3*> &trianglePoints);
        static float DistanceBetweenTwoPoints(const Vec3 &a, const Vec3 &b);
        static bool AreEqual(float a, float b);

    public:
        static Vec3 LinePlaneIntersection(const Line &line, const Plane &plane);
        static Plane PlaneOfTriangle(const std::vector<Vec3*> &trianglePoints);
        static bool PointInTriangleOrNot(const std::vector<Vec3 *> &trianglePoints, const Vec3 &point);

};