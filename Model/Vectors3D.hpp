/*******************************************
 *【文件名】            Vectors3D.hpp
 *【功能模块和目的】    三维向量类的声明
 *【开发者及日期】      张章 2024-7-21
 *【更改记录】          无
 * *****************************************/

/******************************************
 * Note:
 * 在本次大作业的实现中，只需要使用线段类而无需使用向量类。但是向量本身是一个重要的元素，在未来三维模型的渲染方面也许
 * 会有用，所以我在本次作业中加上了对向量类的实现
 ******************************************/

#ifndef _VECTORS3D_HPP
#define _VECTORS3D_HPP

#include<vector>
#include"Points3D.hpp"

/******************************************
 *【类名】              Vectors3D
 *【功能】              表示三维空间中的一个向量
 *【接口说明】          提供带参数的构造函数，删除默认构造函数，删除拷贝构造函数和赋值运算符的重载
 *                      提供查询和修改当前向量起迄坐标的接口（同时避免重复）
 *                      提供删除向量（从向量列表中删除）的接口
 *                      提供获取当前向量序号的接口
 *【开发者及日期】      张章  2024-7-21
 *【更改记录】          无
 * ***************************************/

class Vectors3D{
public:
    // 提供两个点的坐标，构造向量，如果重复则抛出异常
    Vectors3D(double x1, double y1, double z1, double x2, double y2, double z2);
    // 提供两个点的列表，构造向量，如果重复则抛出异常
    Vectors3D(std::vector<Points3D&>& pointSet);
    // 提供两个点的引用，构造向量，如果出现重复则抛出异常
    Vectors3D(Points3D& PointStart, Points3D& PointEnd);
    // 提供两个点的序号，构造向量，如果重复或者序号非法则抛出异常
    Vectors3D(int idx1, int idx2);
    // 删除默认构造函数，因为想要构造向量至少需要先存在两个Points3D对象
    Vectors3D() = delete;
    // 删除拷贝构造函数和赋值运算符，保证不会意外构造出重复的对象
    Vectors3D(const Vectors3D& Vector) = delete;
    const Vectors3D& operator=(const Vectors3D& Vector) = delete;
    // 析构函数
    ~Vectors3D();

    /* non-static setters*/
    // 通过给定两个点的坐标 / 给定点的列表 / 给定两个点（的引用） / 给定两个点的序号 来修改向量。同时避免重复
    void SetPoint(double x1, double y1, double z1, double x2, double y2, double z2);
    void SetPoints(std::vector<Points3D&> APointList);
    void SetPoints(Points3D& PointA, Points3D& PointB);
    void SetPoints(int idxStart, int idxEnd);
    // 删除向量（从LinesList中删除该向量）
    void DeleteVector();
    // 对向量进行归一化
    void Normalization();

    /* non-static getters*/
    const std::vector<Points3D&>& PointList {m_PointList}
    const int& idx {m_idx};
    const std::vector<Vectors3D&>& VectorList {m_VectorList};

private:
    // 一个向量可以通过两个点的列表 [point, end point]来确定
    std::vector<Points3D&> m_PointList;
    // 当前向量的序号，本质是在VectorsSet的索引 + 1
    int m_idx;
    // 包含当前所有线段的列表，符合Zero原则，设置为静态成员
    static std::vector<Vectors3D&> m_VectorsList {};
}

#endif 
