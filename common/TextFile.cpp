#include "TextFile.h"

TextFile::TextFile(){}
TextFile::~TextFile(){}


void TextFile::Add2DPolygon(std::vector<Vec3> polygonPoints){
    std::string polygonStr = "\\operatorname{polygon}\\left(";
    for (size_t i = 0; i < polygonPoints.size(); i++)
    {
        polygonStr += "\\left(" + std::to_string(polygonPoints[i].x) + "," + std::to_string(polygonPoints[i].y) + "\\right)";
        if (Utility::AreEqual(i + 1, polygonPoints.size())) break;
        polygonStr += ",";
    }
    polygonStr += "\\right)";
    this->content += "\n" + polygonStr;
}

void TextFile::Add3DPoint(const Vec3 &point){
    std::string pointStr = "(" + std::to_string(point.x) + "," + std::to_string(point.y) + "," + std::to_string(point.z) + ")";
    this->content += "\n" + pointStr;
}

//vector form equation
void TextFile::Add3DLine(const Line &line)
{
    std::string lineStr = "\\ \\left(" +
                         std::to_string(line.origin.x) + "," + std::to_string(line.origin.y) + "," + std::to_string(line.origin.z) +
                         "\\right)+t\\left(" + std::to_string(line.direction.x) + "," + std::to_string(line.direction.y) + "," + std::to_string(line.direction.z) +
                         "\\right)";

    this->content += "\n" + lineStr;
}

void TextFile::Add3DTriangle(const std::vector<Vec3 *> &trianglePoints){
    std::string triangleStr = "\\operatorname{triangle}\\left(\\left(" +
                         std::to_string(trianglePoints[0]->x) + "," + std::to_string(trianglePoints[0]->y) + "," + std::to_string(trianglePoints[0]->z) + "\\right),\\left(" +
                         std::to_string(trianglePoints[1]->x) + "," + std::to_string(trianglePoints[1]->y) + "," + std::to_string(trianglePoints[1]->z) + "\\right),\\left(" +
                         std::to_string(trianglePoints[2]->x) + "," + std::to_string(trianglePoints[2]->y) + "," + std::to_string(trianglePoints[2]->z) + "\\right)\\right)";
    this->content += "\n" + triangleStr;
}

void TextFile::GeneratorFile(std::string fileName){
    const std::string filePath = std::string(PROJECT_SOURCE_DIR) +"/"+ fileName + ".txt";
//"..//"+fileName+".txt";
    std::ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return; // Return an error code
    }
    outputFile << this->content;
    outputFile.close();
    std::cout << "Data successfully written to " << fileName << ".txt" << std::endl;
}
