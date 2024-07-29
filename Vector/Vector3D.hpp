/******************************************
 * Note:
 * 在本次大作业的实现中，只需要使用线段类而无需使用向量类。但是向量本身是一个重要的元素，在未来三维模型的渲染方面也许
 * 会有用，所以我在本次作业中加上了对向量类的实现
 ******************************************/

#ifndef _VECTOR3D_HPP
#define _VECTOR3D_HPP

#include<vector>
#include"Point3D.hpp"
#include"Element3D.hpp"

class Vector3D : public Element3D{
public:
    // 删除默认构造函数，因为想要构造向量至少需要先存在一个Point3D对象
    Vector3D() = delete;
    // 提供一个坐标，构造一个向量对象
    Vector3D(double x, double y, double z);
    // 提供一个点的引用构造一个向量对象
    Vector3D(Point3D& Point);
    // 对向量并不要求不能重复（比如说两个不相同的平面完全可以拥有相同的法向量）
    Vector3D(const Vector3D& Vector);
    const Vector3D& operator=(const Vector3D& Vector);
    // 析构函数
    ~Vector3D();

    /* non-static getters */

    // 计算向量的面积（直接返回0）
    double GetArea() const override;

    // 计算向量的l2范数的长度
    double GetLength() const override;
    
    // 计算这个向量与另一个向量的内积
    double InnerProduct(const Vector3D& AVector) const;

    const Point3D& Point {m_Point};


    /* non-static setters*/
    
    // 修改向量的对应的某个点，如果希望删除的点并不是这个线段的端点，则抛出异常
    void SetPoint(PointPtr ptrPoint, double x, double y, double z)override;
    
    // 对当前的向量进行归一化
    void Normalize();

    
    /* static getters*/

    // 计算两个向量的内积
    static double InnerProduct(const Vector3D& VectorA, const Vector3D& VectorB);

    // 计算两个向量的叉积
    static Vector3D CrossProduct(const Vector3D& VectorA, const Vector3D& VectorB);

private:
    // 用一个点来表示一个向量
    Point3D m_Point;
};

#endif 