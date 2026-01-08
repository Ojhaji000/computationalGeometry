#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

// its a great way to way to find the how i am going around
// the points od the polygon.
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

// double direction()
double cross(Point a, Point b, Point c) {
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

bool insideHalfPlane(Point a, Point b, Point p) {
    return cross(a, b, p) >= 0; // assuming CCW polygon
}

double polygonArea(const vector<Point>& poly) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return fabs(area) / 2.0;
}

// Return kernel polygon (list of points)
vector<Point> computeKernel(const vector<Point>& poly) {
    vector<Point> kernel = {
        { -1e9, -1e9 }, { 1e9, -1e9 },
        { 1e9,  1e9 }, { -1e9,  1e9 }
    };

    for (int i = 0; i < poly.size(); i++) {
        Point a = poly[i];
        Point b = poly[(i+1) % poly.size()];
        vector<Point> newKernel;

        for (int j = 0; j < kernel.size(); j++) {
            Point curr = kernel[j];
            Point next = kernel[(j+1) % kernel.size()];
            bool currInside = insideHalfPlane(a, b, curr);
            bool nextInside = insideHalfPlane(a, b, next);

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
                    double x = (B2*C1 - B1*C2) / det;
                    double y = (A1*C2 - A2*C1) / det;
                    newKernel.push_back({x,y});
                }
            }
        }
        kernel = newKernel;
        if (kernel.empty()) break;
    }
    return kernel;
}

int main() {
    vector<Point> polygon = {
        {0,0}, {6,0}, {6,2}, {1,2}, {4,5},{3,3},{6,3},{4,6},{0,6}
    };
//right),\left(3,3\right),\left(6,3\right),\left(4,6\right),\left(0,6\right)
    vector<Point> kernel = computeKernel(polygon);

    if (kernel.empty()) {
        cout << "Polygon is NOT star-shaped." << endl;
    } else {
        cout << "Polygon is star-shaped. Kernel coordinates:" << endl;
        for (auto &p : kernel) {
            cout << "(" << p.x << ", " << p.y << ")" << endl;
        }
        cout << "Kernel area = " << polygonArea(kernel) << endl;
    }
}