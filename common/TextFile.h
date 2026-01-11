#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Line.h"
#include "Utility.h"

using namespace std;
class TextFile
{
private:
    std::string content;

public:
    // write polygon points
    // write triangle
    // write line
    // write point
    TextFile();
    ~TextFile();

    void Add2DPolygon(const vector<Vec3 *> polygonPoints);

    void Add3DPoint(const Vec3 &point);
    void Add3DLine(const Line &line);
    void Add3DTriangle(const vector<Vec3 *> &trianglePoints);

    void GeneratorFile(string fileName);

    // static void TextFileGenerator(const Line &line, const std::vector<Vec3*> &trianglePoints, const Vec3 &intersectionPoint);
    // static void TextFileGenerator(const std::vector<Vec3*> polygonPoints, std::string fileName);
};