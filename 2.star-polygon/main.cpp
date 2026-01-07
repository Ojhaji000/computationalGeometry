#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

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