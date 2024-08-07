/*************************************************************************
【文件名】                  Point3D.hpp
【功能模块和目的】          Point3D类的声明
【开发者及日期】            张章 2024-7-21
【更改记录】                24-8-2增加了注释
*************************************************************************/

#include<vector>
#include<stdexcept>
#include<memory>

#ifndef _POINT3D_HPP
#define _POINT3D_HPP

// 点的指针
class Point3D;  // 前向声明
using PointPtr = std::shared_ptr<Point3D>;

/****************************异常类****************************************
【类名】                    ExceptionInvalidCoordinates
【功能模块和目的】          提供的坐标非法

【类名】                    ExceptionIndexOutOfRange
【功能模块和目的】          给出的索引超出范围

【开发者及日期】            张章 2024-7-21
【更改记录】                24-8-2增加了注释
*************************************************************************/
class ExceptionInvalidCoordinates : public std::invalid_argument{
public:
    ExceptionInvalidCoordinates();
};
class ExceptionIndexOutOfRange : public std::invalid_argument{
public:
    ExceptionIndexOutOfRange();
};


/*************************************************************************
【类名】                Point3D
【功能】                表示三维空间中的一个点，可以作为向量、线段或面的成员
【接口说明】            - 删除默认构造函数，提供带参数的构造函数、拷贝构造函数和
                          赋值运算符的重载
                        - void SetCoordinates(double, double, double)修改点的坐标
                        - const double& x, y, z 该点三个坐标的常引用
                        - 重载 == 运算符，用来判断空间中的两点是否重合
                        - double Distance(const Point3D)返回另一个点到该点的距离 
                        - bool IsCoincide(const Point3D, double)与 == 功能相同，但
                          是可以自定义精度
                        - bool IsCollinear(const Point3D&, const Point3D&, const 
                          Point3D&)判断三点是否共线
                        - double Distance(const Point3D&, const Poiont3D&)返回两
                          点之间的距离
                        - bool IsCoincide(const Point3D&, const Point3D&, double)
                          给定两点引用，判断是否共线，可以指定精度
                        - bool IsCoincide(const Point3D&, double, double, double,
                          double)给定一点引用和另一点坐标，判断是否共线，可以指定
                          精度
【开发者及日期】        张章 2024-7-21
【更改记录】            24-8-2 增加了注释
*************************************************************************/
class Point3D{
public:
    // 删除默认构造函数，构造点必须显式指定坐标，或是以另一个点作为拷贝模板
    Point3D() = delete;
    // 带参数的构造函数
    Point3D(double x, double y, double z);
    // 拷贝构造函数（注：允许有重复点）
    Point3D(const Point3D& APoint);
    // 赋值运算符重载
    Point3D& operator=(const Point3D& APoint);
    // 析构函数，为方便未来派生，设置为虚函数
    virtual ~Point3D();


    /* non-static setter*/
    // 修改坐标
    void SetCoordinates(double x, double y, double z);
    

    /* non-static getter*/
    // 重载 == 运算符，用来比较点是否重合，默认精度1e-5
    bool operator==(const Point3D& APoint) const;

    // 另一个点到当前点的距离
    double Distance(const Point3D& APoint) const;

    // 判断另一个点和当前点是否重合
    bool IsCoincide(const Point3D& APoint, double precision = 1e-5) const;

    // 点对象的坐标的常引用
    const double& x {m_x};
    const double& y {m_y};
    const double& z {m_z};
    

    /* static getters*/
    // 给定三个点的引用，判断这三个点是否共线
    static bool IsCollinear(const Point3D& PointA, const Point3D& PointB, const Point3D& PointC);
    
    // 计算给定两个点之间的距离
    static double Distance(const Point3D& PointA, const Point3D& PointB);

    // 判断两个点是否重合
    static bool IsCoincide(const Point3D& PointA, const Point3D& PointB, double precision = 1e-5);
    static bool IsCoincide(const Point3D& PointA, double x, double y, double z, double precision = 1e-5);

private:
    // 当前点的坐标
    double m_x;
    double m_y;
    double m_z;
};

#endif
