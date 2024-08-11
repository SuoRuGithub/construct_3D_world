/*************************************************************************
【文件名】                  Vector3D.hpp
【功能模块和目的】          三维向量类的声明，Vector3D由Element3D派生而来
【开发者及日期】            张章 2024-7-28
【更改记录】                24-8-6增加了注释
【注】                      Vector3D类并未在本次作业中使用，仅为三维元素的完整
                            性实现
*************************************************************************/
#ifndef _VECTOR3D_HPP
#define _VECTOR3D_HPP

#include<vector>
#include"Point3D.hpp"
#include"Element3D.hpp"

/*************************************************************************
【类名】                Vector3D
【功能】                Vector3D表示三维空间中的向量，由Element3D派生而来 
【接口说明】            - 提供构造函数 
                        - 提供了GetArea接口返回元素面积
                        - 提供了GetLength接口返回元素长度
                        - 提供SetPoint接口修改元素的点
【开发者及日期】        张章 2024-7-28
【更改记录】            24-8-7 增加了注释
*************************************************************************/
class Vector3D : public Element3D{
public:
    // 删除默认构造函数，因为想要构造向量至少需要先存在一个Point3D对象
    Vector3D() = delete;
    // 提供一个坐标，构造一个向量对象
    Vector3D(double x, double y, double z);
    // 提供一个点的引用，构造一个向量对象
    Vector3D(Point3D& Point);
    // 对向量并不要求不能重复（比如说两个不相同的平面完全可以拥有相同的法向量）
    // 所以定义了拷贝构造函数和赋值运算符的重载
    Vector3D(const Vector3D& AVector);
    const Vector3D& operator=(const Vector3D& AVector);
    // 虚析构函数，未来可派生
    virtual ~Vector3D();


    /* non-static getters */

    // 计算向量的面积（直接返回0）
    double GetArea() const override;

    // 计算向量的长度（长度定义为其L2范数）
    double GetLength() const override;
    
    // 计算向量的L2范数
    double GetL2Norm() const; 

    // 计算此向量与另一个向量的内积
    double InnerProduct(const Vector3D& AVector) const;

    const Point3D& Point {m_Point};


    /* non-static setters*/
    
    // 修改向量的对应的某个点
    // 提供点的指针
    void SetPoint(PointPtr ptrPoint, double x, double y, double z) override;
    // 提供点的索引（对于向量，只有索引1是合法的）
    void SetPoint(int PointIdx, double x, double y, double z) override;
    
    // 对当前的向量进行归一化
    void Normalize();

    
    /* static getters*/

    // 计算向量的L2范数
    static double GetL2Norm(const Vector3D& Vector);

    // 计算两个向量的内积
    static double InnerProduct(const Vector3D& VectorA, 
                               const Vector3D& VectorB);

    // 计算两个向量的叉积
    static Vector3D CrossProduct(const Vector3D& VectorA, 
                                 const Vector3D& VectorB);

private:
    // 用一个点来表示一个向量
    Point3D m_Point;
};

#endif 
