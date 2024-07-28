// 简单解释
// 这个类是线段、面、向量共同的基类

#include<memory>
#include<vector>
#include"Point3D.hpp"

#ifndef _ELEMENT3D_HPP
#define _ELEMENT3D_HPP

using PointPtr = std::shared_ptr<Point3D>;

/* 异常类 */

// 构造线段使用的两个点重复
class ExceptionPointsRepeated : public std::invalid_argument{
public:
    ExceptionPointsRepeated();
};
// 当前元素并不包含指定的点
class ExceptionNotHavePoint : public std::invalid_argument{
public:
    ExceptionNotHavePoint();
};


class Element3D{
public:
    // 构造函数
    Element3D();
    // 析构函数
    virtual ~Element3D();
    // 修改Element的某个点
    virtual void SetPoint(PointPtr Point, double x, double y, double z) = 0;
    virtual void SetPoint(int PointIdx, double x, double y, double z) = 0;
    // 计算面积
    virtual double GetArea() const = 0;
    // 计算长度. 向量的长度是其l2范数，面的长度是周长
    virtual double GetLength() const = 0;

private:

};

#endif