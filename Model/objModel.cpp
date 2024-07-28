#include<algorithm>
#include<limits>
#include<sstream>
#include<string>
#include<fstream>
#include"objModel.hpp"
#include"Point3D.hpp"
#include"Line3D.hpp"
#include"Face3D.hpp"

using PointPtr = std::shared_ptr<Point3D>;
using LinePtr  = std::shared_ptr<Line3D>;
using FacePtr  = std::shared_ptr<Face3D>;


// 默认构造函数，初始化一个空模型
objModel::objModel(){
}


/* 模型的基本功能 */

// 导入模型
void objModel::ImportModelFromFile(const std::string& FileName){
    // 尝试打开文件
    std::ifstream File(FileName);
    // 如果打不开文件，尝试创建一个文件
    if (!File.is_open()){
        std::ofstream NewFile(FileName);
        // 如果创建不了文件，抛出一个异常
        if (!NewFile.is_open()){
            throw std::invalid_argument("Can't open/create file " + FileName + ".");
        }
        // 关闭文件并保存
        NewFile.close();

        // 打开新文件
        File.open(FileName);
    }
    
    std::vector<Point3D> PointsList;    // PointsList并不作为Model的数据成员，只会在导入 / 导出模型的时候临时构造

    // 从文件中每次读取一行，从每一行读取内容
    std::string line;
    while (getline(File, line)){
        // 构造一个字符串流
        std::istringstream LineString(line);
        char type;
        LineString >> type;
        switch (type){
            case '#':
                break;
            case 'g':{                  // 使用{}声明变量作用域，否则报错
                // 吃掉空格
                LineString >> type;
                LineString >> m_Name;
                break;
            }
            case 'v':{
                LineString >> type;
                double x = 0.0;
                double y = 0.0;
                double z = 0.0;
                LineString >> x;
                LineString >> y;
                LineString >> z;
                Point3D Point(x, y, z);
                PointsList.push_back(Point);               
                break;
            }
            case 'l':{
                LineString >> type;
                int idx1 = 0;
                int idx2 = 0;
                LineString >> idx1;
                LineString >> idx2;
                Line3D Line(PointsList[idx1 - 1], PointsList[idx2 - 1]); 
                m_LinesList.push_back(Line);
                break;
            }
            case 'f':{
                LineString >> type;
                int idx1 = 0;
                int idx2 = 0;
                int idx3 = 0;
                LineString >> idx1;
                LineString >> idx2;
                LineString >> idx3;
                Face3D Face(PointsList[idx1 - 1], PointsList[idx2 - 1], PointsList[idx3 - 1]);
                m_FacesList.push_back(Face);
                break;
            }
            default:
                break;
        }
    }
}


// 导出模型
void objModel::ExportModelToFile(const std::string& FileName){
    // 我们使用一种较为低效的方式进行导出，我们首先逐面逐线将点导出到PointsList，然后去除重复，然后再按照点的序号导出线和面

    // 尝试打开文件
    std::ofstream File(FileName);
    if (!File.is_open()){
        throw std::invalid_argument("Cannot open / create file " + FileName + ".");
    }

    std::vector<Point3D> PointsList;    // 所有点的列表（避免重复）
    std::vector<int>     LineIdx;       // 线的顶点的索引
    std::vector<int>     FaceIdx;       // 面的顶点的索引
    
    
    auto AddPointAndIdx = [&PointsList](std::vector<int>& IdxList, const Point3D& point){
        auto it = std::find(PointsList.begin(), PointsList.end(), point);
        if (it == PointsList.end()){
            PointsList.push_back(point);
            IdxList.push_back(PointsList.size());
        }
        else{
            int Idx = (it - PointsList.begin()) + 1;
            IdxList.push_back(Idx);
        }
    };
    auto AddLinePointsAndIdx = [&](const Line3D& line){
        AddPointAndIdx(LineIdx, line.PointA);
        AddPointAndIdx(LineIdx, line.PointB);
    };
    auto AddFacePointsAndIdx = [&](const Face3D& face){
        AddPointAndIdx(FaceIdx, face.PointA);
        AddPointAndIdx(FaceIdx, face.PointB);
        AddPointAndIdx(FaceIdx, face.PointC);
    };

    std::for_each(m_LinesList.begin(), m_LinesList.end(), AddLinePointsAndIdx);
    std::for_each(m_FacesList.begin(), m_FacesList.end(), AddFacePointsAndIdx);
    

    // 开始导出
    //  名字
    File << "g " << m_Name << std::endl;
    //  点
    auto PointSaver = [&File](Point3D& point){
        File << "v " << point.x << " " << point.y << " " << point.z << std::endl;
    };
    std::for_each(PointsList.begin(), PointsList.end(), PointSaver);
    //  线
    if (LineIdx.size() % 2 != 0){
        throw std::invalid_argument("Error! Numbers of vertices of lines cannot be devided by 2!");
    }
    if (LineIdx.size() != 0){
        for (int i = 0; i < LineIdx.size(); i += 2){
            File << "l " << LineIdx[i] << " " << LineIdx[i + 1] << std::endl;
        }
    }
    //  面
    if (FaceIdx.size() % 3 != 0){
        throw std::invalid_argument("Error! Numbers of vertices of faces cannot be devided by 3!");
    }
    if (LineIdx.size() != 0){
        for (int i = 0; i < FaceIdx.size(); i += 3){
            File << "f " << FaceIdx[i] << " " << FaceIdx[i + 1] << " " << FaceIdx[i + 2] << std::endl;
        }
    }
}


// 渲染模型（本次作业中不会实现，但是渲染本身应该是模型的基本功能）
void objModel::RenderModel(){
}


/* non-static setters*/

// 修改模型名字
void objModel::ChangeName(const std::string ModelName){
    m_Name = ModelName;
}

// 给定面的索引，删除指定面对象
void objModel::DeleteFace(int FaceIdx){
    if (FaceIdx < 0 || FaceIdx >= m_FacesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    m_FacesList.erase(m_FacesList.begin() + FaceIdx);
}
// 给定线的索引，删除指定线对象
void objModel::DeleteLine(int LineIdx){
    if (LineIdx < 0 || LineIdx >= m_LinesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    m_LinesList.erase(m_LinesList.begin() + LineIdx);
}


// 给定三个点坐标，向模型中添加一个面
void objModel::AddFace(double x1, double y1, double z1, 
                       double x2, double y2, double z2, 
                       double x3, double y3, double z3){

    Point3D Point1(x1, y1, z1);
    Point3D Point2(x2, y2, z2);
    Point3D Point3(x3, y3, z3);
    Face3D  Face(Point1, Point2, Point3);
    m_FacesList.push_back(Face);
}
// 给定两个点坐标，向模型中添加一个线
void objModel::AddLine(double x1, double y1, double z1,
                       double x2, double y2, double z2){
    
    Point3D Point1(x1, y1, z1);
    Point3D Point2(x2, y2, z2);
    Line3D  Line(Point1, Point2);
    m_LinesList.push_back(Line);
}


// 改变指定面对象的某一个顶点
//  给定面的序号和点的指针
void objModel::SetPointOfFace(int FaceIdx, PointPtr ptrPoint, double x, double y, double z){
    if (FaceIdx < 0 || FaceIdx >= m_FacesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    else{
        FacePtr ptrFace(&m_FacesList[FaceIdx]);
        ptrFace->SetPoint(ptrPoint, x, y, z);
    }
}
//  给定面的序号和点的序号（1，2，3分别表示PointA，B，C），如果不是这个面的顶点则抛出异常
void objModel::SetPointOfFace(int FaceIdx, int PointIdx, double x, double y, double z){
    if (FaceIdx < 0 || FaceIdx >= m_FacesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    else{
        m_FacesList[FaceIdx].SetPoint(PointIdx, x, y, z);
    }
}

// 改变指定线对象的某一个顶点
//  给定点的指针，如果不是这个线的顶点则抛出异常
void objModel::SetPointOfLine(int LineIdx, PointPtr ptrPoint, double x, double y, double z){
    if (LineIdx < 0 || LineIdx >= m_LinesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    else{
        LinePtr ptrLine(&m_LinesList[LineIdx]);
        ptrLine->SetPoint(ptrPoint, x, y, z);
    }
}
//  给定点的序号，如果不是这个线的顶点则抛出异常
void objModel::SetPointOfLine(int LineIdx, int PointIdx, double x, double y, double z){
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
std::vector<Point3D> objModel::GetFacePoints(int idx){
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
std::vector<Point3D> objModel::GetLinePoints(int idx){
    LinePtr ptrLine(&m_LinesList[idx]);
    Point3D PointA = ptrLine->PointA;
    Point3D PointB = ptrLine->PointB;
    std::vector<Point3D> LinePoint;
    LinePoint.push_back(PointA);
    LinePoint.push_back(PointB);
    return LinePoint;
}

// 统计面对象的总数
int objModel::GetTotalFacesNum(){
    return m_FacesList.size();
}
// 统计线对象的总数
int objModel::GetTotalLinesNum(){
    return m_LinesList.size();
}
// 统计点对象的总数
int objModel::GetTotalPointsNum(){
    // 空间坐标重复的顶点需要重复计数，所以点的总数其实是 面 * 3 + 线 * 2
    return m_FacesList.size() * 3 + m_LinesList.size() * 2;
}

// 统计面对象的总面积
double objModel::GetTotalFacesArea(){
    double TotalArea = 0.0;
    // 使用Lambda表达式
    auto Accumulator = [&TotalArea](const Face3D& face){TotalArea += face.GetArea();};
    std::for_each(m_FacesList.begin(), m_FacesList.end(), Accumulator);
    return TotalArea;
}
// 统计线对象的总长度
double objModel::GetTotalLinesLength(){
    double TotalLength = 0.0;
    auto Accumulator = [&TotalLength](const Line3D& line){TotalLength += line.GetLength();};
    std::for_each(m_LinesList.begin(), m_LinesList.end(), Accumulator);
    return TotalLength;
}

// 计算最小包围盒的体积
double objModel::GetMinBoundingBox(){
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