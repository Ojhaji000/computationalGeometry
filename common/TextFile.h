#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Line.h"
#include "Utility.h"

class TextFile
{
private:
    std::string content;

public:
    TextFile();
    ~TextFile();

    void Add2DPolygon(const std::vector<Vec3> polygonPoints);

    void Add3DPoint(const Vec3 &point);
    void Add3DLine(const Line &line);
    void Add3DTriangle(const std::vector<Vec3 *> &trianglePoints);

    void GeneratorFile(std::string fileName);
};