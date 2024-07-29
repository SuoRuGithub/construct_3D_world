#include<vector>
#include"Point3D.hpp"
#include"Line3D.hpp"
#include"Face3D.hpp"

#ifndef _MODELBASE_HPP
#define _MODELBASE_HPP

class ExceptionFaceExist : public std::invalid_argument{
public:
    ExceptionFaceExist();
};

// 一个模型，最基本的数据成员应该包括点线面，最基本的成员函数应该包括导入、导出和渲染（虽然渲染我们在本次作业中并不会给出实现）
class ModelBase{
public:
    // 有一个纯虚的默认构造函数，作用是生成一个空模型
    ModelBase();
    // 删除拷贝构造函数、赋值运算符的重载
    ModelBase(const ModelBase& AModel)            = delete;
    ModelBase& operator=(const ModelBase& AModel) = delete;    
    // 虚的析构函数
    virtual ~ModelBase(); // = 0; 或者将基类的析构函数作为虚函数，给出基类的实现；或者将基类的析构函数作为纯虚函数，但是要在写派生类的时候同时完成基类和派生类的析构函数

    // 导入模型
    virtual void ImportModelFromFile(const std::string& FileName) = 0;
    // 导出模型
    virtual void ExportModelToFile(const std::string& FileName)   = 0;
    // 渲染模型（本次作业中不会实现）
    virtual void RenderModel() = 0;

    /* non-static setters */

    // 修改模型名字
    void ChangeName(const std::string ModelName);

    // 给定面的索引，删除指定面对象
    void DeleteFace(unsigned int FaceIdx);
    // 给定线的索引，删除指定线对象
    void DeleteLine(unsigned int LineIdx);

    // 给定三个点坐标，向模型中添加一个面
    void AddFace(double x1, double y1, double z1, 
                 double x2, double y2, double z2, 
                 double x3, double y3, double z3);
    // 给定两个点坐标，向模型中添加一个线
    void AddLine(double x1, double y1, double z1,
                 double x2, double y2, double z2); 

    // 改变指定面对象的某一个顶点
    //  给定面的序号和点的指针，如果不是这个面的顶点则抛出异常
    void SetPointOfFace(int FaceIdx, PointPtr ptrPoint, double x, double y, double z);
    //  给定面的序号和点的序号（1，2，3分别表示PointA，B，C），如果不是这个面的顶点则抛出异常
    void SetPointOfFace(int FaceIdx, int PointIdx, double x, double y, double z);
    // 改变指定线对象的某一个顶点
    //  给定点的指针，如果不是这个线的顶点则抛出异常
    void SetPointOfLine(int LineIdx, PointPtr ptrPoint, double x, double y, double z);
    //  给定点的序号，如果不是这个线的顶点则抛出异常
    void SetPointOfLine(int LineIdx, int PointIdx, double x, double y, double z);
    
    /* non-static getters*/

    // 得到给定面的三个顶点
    //  给定面的序号
    std::vector<Point3D> GetFacePoints(int idx);
    // 得到给定线的两个顶点
    //  给定线的序号
    std::vector<Point3D> GetLinePoints(int idx);

    // 统计面对象的总数
    int GetTotalFacesNum();
    // 统计线对象的总数
    int GetTotalLinesNum();
    // 统计点对象的总数
    int GetTotalPointsNum();

    // 统计面对象的总面积
    double GetTotalFacesArea();
    // 统计线对象的总长度
    double GetTotalLinesLength();

    // 计算最小包围盒的体积
    double GetMinBoundingBox();

    // 判断线 / 面是否已经存在，防止重复
    bool IsFaceExist(const Face3D& Face);
    bool IsLineExist(const Line3D& Line);

    const std::string&          Name        {m_Name};
    // const std::vector<Point3D>& PointsList  {m_PointsList};
    const std::vector<Line3D>&  LinesList   {m_LinesList};
    const std::vector<Face3D>&  FacesList   {m_FacesList};
    
protected:
    // 模型的名字
    std::string          m_Name;
    // 模型的点线面列表
    // std::vector<Point3D> m_PointsList;   // 规定模型不拥有的点而只拥有线和面，在导入模型时单独的点会被忽略
    std::vector<Line3D>  m_LinesList;
    std::vector<Face3D>  m_FacesList;
};

#endif


