#include<stdexcept>
#include<vector>
#include<memory>
#include"Point3D.hpp"
#include"Element3D.hpp"

#ifndef _FACE3D_HPP
#define _FACE3D_HPP

// 点的智能指针
using PointPtr      = std::shared_ptr<Point3D>;

/* 异常类 */
// SetPoint使用，声明在
class ExceptionIndexOutOfRange;

class Face3D : public Element3D{
public:
    // 删除默认构造函数，因为想要构造一个面至少需要已经存在三个点
    Face3D() = delete;
    // 提供两个点的引用构造一个面对象
    Face3D(Point3D& PointA, Point3D& PointB, Point3D& PointC);
    // 删除拷贝构造函数和赋值运算符，保证不会意外构造出重复的对象
    Face3D(const Face3D&)            = delete;
    Face3D& operator=(const Face3D&) = delete;
    // 析构函数
    ~Face3D();

    // 重载 == 运算符 （注：在这里我们不考虑PointA / B / C的排序）
    bool operator==(const Face3D& AFace);

    /* non-static getters */

    // 返回面的面积
    double GetArea()    const override;
    // 返回面的周长
    double GetLength()  const override;

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
