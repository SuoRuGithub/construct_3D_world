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

objModel::~objModel(){
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
                m_LinesList.push_back(std::move(Line));
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
                m_FacesList.push_back(std::move(Face));
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

