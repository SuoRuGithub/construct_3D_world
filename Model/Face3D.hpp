/*************************************************************************
【文件名】                  Face3D.hpp
【功能模块和目的】          Face3D类的声明
【开发者及日期】            张章 2024-7-21
【更改记录】                24-8-6增加了注释
*************************************************************************/
#include<stdexcept>
#include<vector>
#include<memory>
#include"Point3D.hpp"
#include"Element3D.hpp"

#ifndef _FACE3D_HPP
#define _FACE3D_HPP

// 点的智能指针
using PointPtr      = std::shared_ptr<Point3D>;


/*************************************************************************
【类名】                Face3D
【功能】                表示三维空间中的一个面，由Element3D派生而来
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
class Face3D : public Element3D{
public:
    // 删除默认构造函数，因为想要构造一个面至少需要已经存在三个点
    Face3D() = delete;
    // 提供三个点的引用构造一个面对象
    Face3D(const Point3D& PointA, const Point3D& PointB, const Point3D& PointC);
    // 删除拷贝构造函数和赋值运算符重载，但是定义移动构造函数和移动赋值运算符重载
    // 保证不允许出现重复元素，只可以转移对象
    Face3D(const Face3D&)            = delete;
    Face3D& operator=(const Face3D&) = delete;
    Face3D(Face3D&& AFace);
    Face3D& operator=(Face3D&& AFace);
    // 析构函数
    ~Face3D();

    
    /* non-static getters */
    // 重载 == 运算符 （注：在这里我们不考虑PointA / B / C的排序）
    bool operator==(const Face3D& AFace);

    // 返回面的面积
    double GetArea()    const override;

    // 返回面的周长
    double GetLength()  const override;

    // 提供面的三个点的常引用
    const Point3D& PointA  {m_PointA};      
    const Point3D& PointB  {m_PointB}; 
    const Point3D& PointC  {m_PointC}; 


    /* non-static setters */
    // 给定点的指针进行修改
    void SetPoint(PointPtr Point, double x, double y, double z) override;
    // 给定点的索引进行修改（1，2，3分别代表ABC）
    void SetPoint(int PointIdx, double x, double y, double z) override;

private:
    Point3D m_PointA;
    Point3D m_PointB;
    Point3D m_PointC;
};

#endif
