/*************************************************************************
【文件名】                  Element3D.hpp
【功能模块和目的】          Element3D类的声明，其作为Line3D, Vector3D与Face3D
                            共同的基类
【开发者及日期】            张章 2024-7-21
【更改记录】                24-8-5增加了注释
*************************************************************************/
#include<memory>
#include<vector>
#include"Point3D.hpp"

#ifndef _ELEMENT3D_HPP
#define _ELEMENT3D_HPP

using PointPtr = std::shared_ptr<Point3D>;

/****************************异常类****************************************
【类名】                    ExceptionPointsRepeated
【功能模块和目的】          表示（线段或面的）点出现了重合的情况（用于SetPoint
                            时将线段或面的点设置为重合的情况）

【类名】                    ExceptionNotHavePoint
【功能模块和目的】          表示当前元素并不包含给定的点（用于SetPoint中输入的
                            点非法的情况）

【开发者及日期】            张章 2024-7-21
【更改记录】                24-8-5增加了注释
*************************************************************************/
class ExceptionPointsRepeated : public std::invalid_argument{
public:
    ExceptionPointsRepeated();
};
class ExceptionNotHavePoint : public std::invalid_argument{
public:
    ExceptionNotHavePoint();
};


/*************************************************************************
【类名】                Element3D
【功能】                Element3D表示三维空间中的元素，由此类派生出Vector3D, 
                        Point3D和Face3D三类
【接口说明】            - 提供构造函数 
                        - 提供了GetArea接口返回元素面积
                        - 提供了GetLength接口返回元素长度
                        - 提供SetPoint接口修改元素的点
【开发者及日期】        张章 2024-7-21
【更改记录】            24-8-5 增加了注释
*************************************************************************/
class Element3D{
public:
    // 构造函数
    Element3D();
    // 析构函数
    virtual ~Element3D();

    /* non-static getters */
    // 计算元素的面积
    virtual double GetArea() const = 0;
    // 计算元素的长度
    virtual double GetLength() const = 0;
    
    /* non-static setters */
    // 修改Element的某个点
    // - 给定点的指针进行修改
    virtual void SetPoint(PointPtr Point, double x, double y, double z) = 0;
    // - 给定点的索引进行修改
    virtual void SetPoint(int PointIdx, double x, double y, double z) = 0;

private:
    // Note:
    // 在设计时，我经过考虑后放弃了最初的在Element3D中维护一个Point3D（或其指针）的列表作为私有数据成员的实现方案
    // 而是选择在Vector3D, Line3D, Face3D中让它们各自维护自身的点元素. 我认为这样做可能带来的一个好处是能够给派生
    // 类较大的自主裁量空间，让它们自行决定需要包含什么元素，而且这样实现的Face3D和Line3D类可以较强地确定自身点的个数，
    // 避免一些使用数组（或vector等容器）时可能出现的问题。
    // 当然这样做也有弊端，最显著的就是在Model3D类针对线、面的操作会出现较多的重复.
};

#endif
