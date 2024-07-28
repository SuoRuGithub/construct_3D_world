#include<stdexcept>
#include<memory>
#include<vector>
#include"Point3D.hpp"
#include"Line3D.hpp"
#include"Face3D.hpp"
#include"ModelBase.hpp"

#ifndef _OBJMODEL_HPP
#define _OBJMODEL_HPP

// 定义点线面的智能指针，向controller返回值时只需要返回指针即可
using PointPtr = std::shared_ptr<Point3D>;
using LinePtr  = std::shared_ptr<Line3D>;
using FacePtr  = std::shared_ptr<Face3D>;

/* 异常类 */
// 声明在
class IndexOutOfRange;

class objModel : public ModelBase{
public:
    // 默认构造函数，初始化一个空模型
    objModel();
    // 删除拷贝构造函数和赋值运算符的重载
    objModel(const objModel& AModel)            = delete;
    objModel& operator=(const objModel& AModel) = delete;    

    /* 模型的基本功能 */

    // 导入模型
    void ImportModelFromFile(const std::string& FileName) override;
    // 导出模型
    void ExportModelToFile(const std::string& FileName) override;
    // 渲染模型（本次作业中不会实现，但是渲染本身应该是模型的基本功能）
    void RenderModel() override;


    /* non-static setters */

    // 修改模型名字
    void ChangeName(const std::string ModelName);

    // 给定面的索引，删除指定面对象
    void DeleteFace(int FaceIdx);
    // 给定线的索引，删除指定线对象
    void DeleteLine(int LineIdx);

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

    const std::string&          Name        {m_Name};
    // const std::vector<Point3D>& PointsList  {m_PointsList};
    const std::vector<Line3D>&  LinesList   {m_LinesList};
    const std::vector<Face3D>&  FacesList   {m_FacesList};
};

#endif





