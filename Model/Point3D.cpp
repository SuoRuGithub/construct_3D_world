/*************************************************************************
【文件名】                  Point3D.cpp
【功能模块和目的】          Point3D类的定义
【开发者及日期】            张章 2024-7-21
【更改记录】                24-8-2增加了注释
*************************************************************************/
#include<memory>
#include<cmath>
#include"Point3D.hpp"

// 点的指针
using PointPtr = std::shared_ptr<Point3D>;

/* 异常类 */
ExceptionInvalidCoordinates::ExceptionInvalidCoordinates() : std::invalid_argument("Invalid Coordinates"){
}
ExceptionIndexOutOfRange::ExceptionIndexOutOfRange() : std::invalid_argument("Index oput of range"){
}

/*************************************************************************
【函数名称】       Point3D
【函数功能】       Point3D类的含参构造函数与拷贝构造函数
【参数】          【含参构造函数】
                    - 输入参数：double x, double y, double z: 表示希望构造的点的
                      坐标
                  【拷贝构造函数】
                    - 输入参数：const Point3D& APoint. 希望拷贝的点的引用
【返回值】         无
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-2增加了注释
*************************************************************************/
Point3D::Point3D(double x, double y, double z) : m_x(x), m_y(y), m_z(z){
}
Point3D::Point3D(const Point3D& APoint) : m_x(APoint.x), m_y(APoint.y), m_z(APoint.z){
}

/*************************************************************************
【函数名称】       operator=
【函数功能】       Point3D类赋值运算符的重载
【参数】           const Point3D& APoint 希望赋值的点的引用
【返回值】         Point3D&被赋值的点的引用
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-2增加了注释
*************************************************************************/
Point3D& Point3D::operator=(const Point3D& APoint){
    if (this != &APoint){
        m_x = APoint.x;
        m_y = APoint.y;
        m_z = APoint.z;
    }
    return *this;
    
}
// * 析构函数
Point3D::~Point3D(){
}



/* non-static setter*/
/*************************************************************************
【函数名称】       SetCoordinates
【函数功能】       修改当前点的坐标
【参数】           double x, y, z. 希望点在修改后的x, y, z坐标
【返回值】         void
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-2增加了注释
*************************************************************************/
void Point3D::SetCoordinates(double x, double y, double z){
    m_x = x;
    m_y = y;
    m_z = z;
}
    

/* non-static getter*/
/*************************************************************************
【函数名称】       operator==
【函数功能】       比较两个点是否重合
【参数】           const Point3D& APoint: 表示希望与当前点进行比较的点
【返回值】         bool 重合返回true，反之返回false
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-2增加了注释
*************************************************************************/
bool Point3D::operator==(const Point3D& APoint) const{
    if (std::abs(m_x - APoint.x) < 1e-5 && 
        std::abs(m_y - APoint.y) < 1e-5 && 
        std::abs(m_z - APoint.z) < 1e-5 ){

        return true;
    }
    else{
        return false;
    }
}

/*************************************************************************
【函数名称】       Distance
【函数功能】       返回另一点到此点的距离
【参数】           const Point3D& APoint: 另一点的常引用           
【返回值】         double 表示APoint到此点的距离
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-2增加了注释
*************************************************************************/
double Point3D::Distance(const Point3D& APoint) const{
    double distance = (m_x - APoint.x) * (m_x - APoint.x) + 
                      (m_y - APoint.y) * (m_y - APoint.y) + 
                      (m_z - APoint.z) * (m_z - APoint.z);
    return sqrt(distance); 
}

/*************************************************************************
【函数名称】       IsCoincide
【函数功能】       比较两个点是否重合
【参数】                      
【返回值】          bool 重合返回true，反之返回false
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-2增加了注释
*************************************************************************/
bool Point3D::IsCoincide(const Point3D& APoint, double precision) const{
    if ((std::abs(m_x - APoint.x) < precision) && 
        (std::abs(m_y - APoint.y) < precision) &&
        (std::abs(m_z - APoint.z) < precision)){

        return true;
    }
    else{
        return false;
    }
}

/* static getters*/

/*************************************************************************
 * 注：由于本次作业中没有使用该函数，故没有实现，只是为了点的功能的完整性
 * 所以加上了这个接口
【函数名称】        IsCollinear
【函数功能】        判断三点是否共线 
【参数】            const Point3D& PointA, PointB, PointC 三个点的常引用           
【返回值】          bool 共线返回true，反之返回false
【开发者及日期】    张章 2024-7-21
【更改记录】        24-8-5增加了注释
*************************************************************************/
bool Point3D::IsCollinear(const Point3D& PointA, const Point3D& PointB, const Point3D& PointC){
    // 无实现
    return false;
}

/*************************************************************************
【函数名称】        Distance
【函数功能】        返回两个给定点之间的距离
【参数】            const Point3D& PointA, PointB:
                    两个要计算距离的点的常引用
【返回值】          double 返回两点之间的距离
【开发者及日期】    张章 2024-7-21
【更改记录】        24-8-5增加了注释
*************************************************************************/
double Point3D::Distance(const Point3D& PointA, const Point3D& PointB){
    double distance = (PointA.x - PointB.x) * (PointA.x - PointB.x) +
                      (PointA.y - PointB.y) * (PointA.y - PointB.y) +
                      (PointA.z - PointB.z) * (PointA.z - PointB.z);
    return sqrt(distance);
}

/*************************************************************************
【函数名称】        IsCoincide
【函数功能】        判断给定两点是否重合
【参数】            const Point3D& PointA, PointB: 
                    两个希望比较的点的常引用
【返回值】          bool 重合返回true，反之返回false
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
bool Point3D::IsCoincide(const Point3D& PointA, const Point3D& PointB, double precision /*= 1e-5*/){    // note that default parameters shouldn't be shown in definition.
    if ((std::abs(PointA.x - PointB.x) < precision) && 
        (std::abs(PointA.y - PointB.y) < precision) &&
        (std::abs(PointA.z - PointB.z) < precision)){

        return true;
    }
    else{
        return false;
    }
}

/*************************************************************************
【函数名称】        IsCoincide
【函数功能】        判断给定两个点是否重合
【参数】            const Point3D& PointA; double x, y z          
                    一个给定点的常引用与另一个给定点的坐标
【返回值】          bool 重合返回true，反之返回false
【开发者及日期】    张章 2024-7-21
【更改记录】        24-8-5增加了注释
*************************************************************************/
bool Point3D::IsCoincide(const Point3D& PointA, double x, double y, double z, double precision){
    return Point3D::IsCoincide(PointA, Point3D(x, y, z), precision);
}
