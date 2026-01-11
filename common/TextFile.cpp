#include "TextFile.h"

TextFile::TextFile(){}
TextFile::~TextFile(){}


void TextFile::Add2DPolygon(vector<Vec3 *> polygonPoints){
    string polygonStr = "\\operatorname{polygon}\\left(";
    for (size_t i = 0; i < polygonPoints.size(); i++)
    {
        polygonStr += "\\left(" + to_string((*polygonPoints[i]).x) + "," + to_string((*polygonPoints[i]).y) + "\\right)";
        if (Utility::AreEqual(i + 1, polygonPoints.size())) break;
        polygonStr += ",";
    }
    polygonStr += "\\right)";
    this->content += "\n" + polygonStr;
}

void TextFile::Add3DPoint(const Vec3 &point){
    string pointStr = "(" + to_string(point.x) + "," + to_string(point.y) + "," + to_string(point.z) + ")";
    this->content += "\n" + pointStr;
}

//vector form equation
void TextFile::Add3DLine(const Line &line)
{
    string lineStr = "\\ \\left(" +
                         to_string(line.origin.x) + "," + to_string(line.origin.y) + "," + to_string(line.origin.z) +
                         "\\right)+t\\left(" + to_string(line.direction.x) + "," + to_string(line.direction.y) + "," + to_string(line.direction.z) +
                         "\\right)";

    this->content += "\n" + lineStr;
}

void TextFile::Add3DTriangle(const vector<Vec3 *> &trianglePoints){
    string triangleStr = "\\operatorname{triangle}\\left(\\left(" +
                         to_string(trianglePoints[0]->x) + "," + to_string(trianglePoints[0]->y) + "," + to_string(trianglePoints[0]->z) + "\\right),\\left(" +
                         to_string(trianglePoints[1]->x) + "," + to_string(trianglePoints[1]->y) + "," + to_string(trianglePoints[1]->z) + "\\right),\\left(" +
                         to_string(trianglePoints[2]->x) + "," + to_string(trianglePoints[2]->y) + "," + to_string(trianglePoints[2]->z) + "\\right)\\right)";
    this->content += "\n" + triangleStr;
}

void TextFile::GeneratorFile(string fileName){
    const string filePath =     string(PROJECT_SOURCE_DIR) +"/"+ fileName + ".txt";
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
