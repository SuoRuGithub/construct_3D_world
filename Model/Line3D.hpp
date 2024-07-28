#include<memory>
#include<vector>
#include"Point3D.hpp"
#include"Element3D.hpp"

#ifndef _LINE3D_HPP
#define _LINE3D_HPP

using PointPtr = std::shared_ptr<Point3D>;

/* 异常类 */

// 已经存在相应线段
class ExceptionLineExist : public std::invalid_argument{
public:
    ExceptionLineExist();
};

// 线段不存在
class ExceptionTargetLineNotExist : public std::invalid_argument{
public:
    ExceptionTargetLineNotExist();
};


class Line3D : public Element3D{
public:
    // 删除默认构造函数，因为想要构造线段至少需要先存在两个Point3D对象
    Line3D() = delete;
    // 提供两个点的引用构造一个线段对象
    Line3D(Point3D& PointA, Point3D& PointB);
    // 删除拷贝构造函数和赋值运算符，从源头上保证不会构造出重复的对象
    Line3D(const Line3D& Line) = delete;
    const Line3D& operator=(const Line3D& Line) = delete;
    // 析构函数
    ~Line3D();


    /* non-static getters */

    // 计算线段的面积（直接返回0）
    double GetArea() const override;

    // 计算线段的长度
    double GetLength() const override;
    
    // 当前线段的两个端点的常引用
    const Point3D& PointA {m_PointA};
    const Point3D& PointB {m_PointB};

    /* non-static setters*/
    
    // 给定点的指针，修改线段对应的某个点，如果希望删除的点并不是这个线段的端点，则抛出异常
    void SetPoint(PointPtr ptrPoint, double x, double y, double z) override;
    // 给定点的索引（1，2分别代表AB），修改线段对应的某个点，
    void SetPoint(int PointIdx, double x, double y, double z) override;

private:
    // 线段的两个端点
    Point3D m_PointA;
    Point3D m_PointB;
};

#endif 