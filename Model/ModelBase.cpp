#include<algorithm>
#include<limits>
#include<sstream>
#include<string>
#include<fstream>
#include"ModelBase.hpp"
#include"Point3D.hpp"
#include"Line3D.hpp"
#include"Face3D.hpp"

using PointPtr = std::shared_ptr<Point3D>;
using LinePtr  = std::shared_ptr<Line3D>;
using FacePtr  = std::shared_ptr<Face3D>;

ExceptionFaceExist::ExceptionFaceExist() : std::invalid_argument("Face exist"){
}

// 初始化一个空模型
ModelBase::ModelBase(){
}


/* non-static setters*/

// 修改模型名字
void ModelBase::ChangeName(const std::string ModelName){
    m_Name = ModelName;
}

// 给定面的索引，删除指定面对象
void ModelBase::DeleteFace(unsigned int FaceIdx){
    if (FaceIdx >= m_FacesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    m_FacesList.erase(m_FacesList.begin() + FaceIdx);
}
// 给定线的索引，删除指定线对象
void ModelBase::DeleteLine(unsigned int LineIdx){
    if (LineIdx >= m_LinesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    m_LinesList.erase(m_LinesList.begin() + LineIdx);
}


// 给定三个点坐标，向模型中添加一个面
void ModelBase::AddFace(double x1, double y1, double z1, 
                        double x2, double y2, double z2, 
                        double x3, double y3, double z3){

    Point3D Point1(x1, y1, z1);
    Point3D Point2(x2, y2, z2);
    Point3D Point3(x3, y3, z3);
    if (Point1 == Point2 || Point1 == Point3 || Point2 == Point3){
        throw ExceptionPointsRepeated();
    }
    Face3D  Face(Point1, Point2, Point3);
    if (IsFaceExist(Face)){
        throw ExceptionFaceExist();
    }
    m_FacesList.push_back(Face);
}
// 给定两个点坐标，向模型中添加一个线
void ModelBase::AddLine(double x1, double y1, double z1,
                        double x2, double y2, double z2){
    
    Point3D Point1(x1, y1, z1);
    Point3D Point2(x2, y2, z2);
    Line3D  Line(Point1, Point2);
    if (IsLineExist(Line)){
        throw ExceptionLineExist();
    }
    m_LinesList.push_back(Line);
}


// 改变指定面对象的某一个顶点
//  给定面的序号和点的指针
void ModelBase::SetPointOfFace(int FaceIdx, PointPtr ptrPoint, double x, double y, double z){
    if (FaceIdx < 0 || FaceIdx >= m_FacesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    else{
        FacePtr ptrFace(&m_FacesList[FaceIdx]);
        ptrFace->SetPoint(ptrPoint, x, y, z);
    }
}
//  给定面的序号和点的序号（1，2，3分别表示PointA，B，C），如果不是这个面的顶点则抛出异常
void ModelBase::SetPointOfFace(int FaceIdx, int PointIdx, double x, double y, double z){
    if (FaceIdx < 0 || FaceIdx >= m_FacesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    else{
        m_FacesList[FaceIdx].SetPoint(PointIdx, x, y, z);
    }
}

// 改变指定线对象的某一个顶点
//  给定点的指针，如果不是这个线的顶点则抛出异常
void ModelBase::SetPointOfLine(int LineIdx, PointPtr ptrPoint, double x, double y, double z){
    if (LineIdx < 0 || LineIdx >= m_LinesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    else{
        LinePtr ptrLine(&m_LinesList[LineIdx]);
        ptrLine->SetPoint(ptrPoint, x, y, z);
    }
}
//  给定点的序号，如果不是这个线的顶点则抛出异常
void ModelBase::SetPointOfLine(int LineIdx, int PointIdx, double x, double y, double z){
    if (LineIdx < 0 || LineIdx >= m_LinesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    else{
        m_LinesList[LineIdx].SetPoint(PointIdx, x, y, z);
    }
}


/* non-static getters */

// 得到给定面的三个顶点
//  给定面的序号
std::vector<Point3D> ModelBase::GetFacePoints(int idx){
    // 为了避免面的重复，我们删除了面的赋值运算符重载，对面的操作需要使用指针进行
    FacePtr ptrFace(&m_FacesList[idx]);
    Point3D PointA = ptrFace->PointA;
    Point3D PointB = ptrFace->PointB;
    Point3D PointC = ptrFace->PointC;
    std::vector<Point3D> FacePoint;
    FacePoint.push_back(PointA);
    FacePoint.push_back(PointB);
    FacePoint.push_back(PointC);
    return FacePoint;
}
// 得到给定线的两个顶点
//  给定线的序号
std::vector<Point3D> ModelBase::GetLinePoints(int idx){
    LinePtr ptrLine(&m_LinesList[idx]);
    Point3D PointA = ptrLine->PointA;
    Point3D PointB = ptrLine->PointB;
    std::vector<Point3D> LinePoint;
    LinePoint.push_back(PointA);
    LinePoint.push_back(PointB);
    return LinePoint;
}

// 统计面对象的总数
int ModelBase::GetTotalFacesNum(){
    return m_FacesList.size();
}
// 统计线对象的总数
int ModelBase::GetTotalLinesNum(){
    return m_LinesList.size();
}
// 统计点对象的总数
int ModelBase::GetTotalPointsNum(){
    // 空间坐标重复的顶点需要重复计数，所以点的总数其实是 面 * 3 + 线 * 2
    return m_FacesList.size() * 3 + m_LinesList.size() * 2;
}

// 统计面对象的总面积
double ModelBase::GetTotalFacesArea(){
    double TotalArea = 0.0;
    // 使用Lambda表达式
    auto Accumulator = [&TotalArea](const Face3D& face){TotalArea += face.GetArea();};
    std::for_each(m_FacesList.begin(), m_FacesList.end(), Accumulator);
    return TotalArea;
}
// 统计线对象的总长度
double ModelBase::GetTotalLinesLength(){
    double TotalLength = 0.0;
    auto Accumulator = [&TotalLength](const Line3D& line){TotalLength += line.GetLength();};
    std::for_each(m_LinesList.begin(), m_LinesList.end(), Accumulator);
    return TotalLength;
}

// 计算最小包围盒的体积
double ModelBase::GetMinBoundingBox(){
    double xMin =  std::numeric_limits<double>::infinity();
    double xMax = -std::numeric_limits<double>::infinity();
    double yMin =  std::numeric_limits<double>::infinity();
    double yMax = -std::numeric_limits<double>::infinity();
    double zMin =  std::numeric_limits<double>::infinity();
    double zMax = -std::numeric_limits<double>::infinity();
    
    auto updateBounds        = [&](double& min, double& max, double value){
        min = std::min(min, value);
        max = std::max(max, value);
    };
    auto updateBoundsOfPoint = [&](const Point3D& point){
        updateBounds(xMin, xMax, point.x);
        updateBounds(yMin, yMax, point.y);
        updateBounds(zMin, zMax, point.z);
    };

    for (Face3D& face : m_FacesList){
        updateBoundsOfPoint(face.PointA);
        updateBoundsOfPoint(face.PointB);
        updateBoundsOfPoint(face.PointC);
    }
    for (Line3D& line : m_LinesList){
        updateBoundsOfPoint(line.PointA);
        updateBoundsOfPoint(line.PointB);
    }

    double Volume = (xMax - xMin) * (yMax - yMin) * (zMax - zMin);

    return Volume;
}


// 判断线 / 面是否已经存在，防止重复
bool ModelBase::IsFaceExist(const Face3D& Face){
    auto it =  std::find(m_FacesList.begin(), m_FacesList.end(), Face);
    if (it == m_FacesList.end()){
        return false;
    }
    else{
        return true;
    }
}
bool ModelBase::IsLineExist(const Line3D& Line){
    auto it =  std::find(m_LinesList.begin(), m_LinesList.end(), Line);
    if (it == m_LinesList.end()){
        return false;
    }
    else{
        return true;
    }

}