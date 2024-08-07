/*************************************************************************
【文件名】                  Line3D.hpp
【功能模块和目的】          Line3D类的声明
【开发者及日期】            张章 2024-7-21
【更改记录】                24-8-5增加了注释
*************************************************************************/
#include<memory>
#include<vector>
#include"Point3D.hpp"
#include"Element3D.hpp"

#ifndef _LINE3D_HPP
#define _LINE3D_HPP

// 定义点的智能指针
using PointPtr = std::shared_ptr<Point3D>;

/****************************异常类****************************************
【类名】                    ExceptionLineExist
【功能模块和目的】          线已经存在

【类名】                    ExceptionTargetLineNotExist
【功能模块和目的】          目标线段不存在

【开发者及日期】            张章 2024-7-21
【更改记录】                24-8-5增加了注释
*************************************************************************/
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


/*************************************************************************
【类名】                Line3D
【功能】                表示三维空间的一条线段，由Element3D类继承而来
【接口说明】            - 提供构造函数，移动构造函数和移动赋值运算符重载，删除拷贝
                          构造函数和赋值运算符重载
                        - 重载了 == 运算符
                        - 提供了GetArea接口返回线段面积（0）
                        - 提供了GetLength接口返回线段长度
                        - 提供了当前线段两个点的常引用供访问
                        - 提供SetPoint接口修改线段的点
【开发者及日期】        张章 2024-7-21
【更改记录】            24-8-2 增加了注释
*************************************************************************/
class Line3D : public Element3D{
public:
    // 删除默认构造函数，因为想要构造线段至少需要先存在两个Point3D对象
    Line3D() = delete;
    // 提供两个点的引用构造一个线段对象
    Line3D(Point3D& PointA, Point3D& PointB);
    // 删除拷贝构造函数和赋值运算符重载，但是定义移动构造函数和移动赋值运算符重载
    // 保证不允许出现重复元素，只可以转移对象
    Line3D(const Line3D& ALine) = delete;
    const Line3D& operator=(const Line3D& ALine) = delete;
    Line3D(Line3D&& ALine);
    Line3D& operator=(Line3D&& ALine); // Note:移动赋值运算符和移动构造函数不可以只
                                       // 提供常引用。移动赋值运算符重载不可以只
                                       // 返回常引用
    // 析构函数
    ~Line3D();

    
    /* non-static getters */
    // == 运算符重载，比较两条线段是否相同
    bool operator==(const Line3D& ALine)const;

    // 计算线段的面积（直接返回0）
    double GetArea() const override;

    // 计算线段的长度
    double GetLength() const override;
    
    // 当前线段的两个端点的常引用
    const Point3D& PointA {m_PointA};
    const Point3D& PointB {m_PointB};

    /* non-static setters*/
    
    // 给定点的指针，修改线段对应的某个点，如果希望删除的点并不是这个线段的端点
    // 则抛出异常
    void SetPoint(PointPtr ptrPoint, double x, double y, double z) override;
    // 给定点的索引（1，2分别代表AB），修改线段对应的某个点，如果索引超出范围
    // 则抛出IndexOutOfRange异常
    void SetPoint(int PointIdx, double x, double y, double z) override;

private:
    // 线段的两个端点
    Point3D m_PointA;
    Point3D m_PointB;
};

#endif 
