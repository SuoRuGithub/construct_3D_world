/*******************************************
 *【文件名】            Lines3D.hpp
 *【功能模块和目的】    三维线类的声明
 *【开发者及日期】      张章 2024-7-21
 *【更改记录】          无
 * *****************************************/

#ifndef _LINES3D_HPP
#define _LINES3D_HPP

#include<unordered_set>
#include<vector>
#include"Points3D.hpp"

// unordered set of Points (reference)
using uPointSet = std::unordered_set<Points3D&>;

/******************************************
 *【类名】              Lines3D
 *【功能】              表示三维空间中的一条线段
 *【接口说明】          提供带参数的构造函数（同时避免重复），删除默认构造函数，删除拷贝构造函数和赋值运算符的重载
 *                      提供查询和修改当前线段起迄坐标的接口（同时避免重复）
 *                      提供删除线段（从线段列表中删除）的接口
 *                      提供获取当前线段序号的接口
 *【开发者及日期】      张章  2024-7-21
 *【更改记录】          无
 * ***************************************/

class Lines3D{
public:
    // 提供两个点的坐标，构造线段，如果重复则抛出异常
    Lines3D(double x1, double y1, double z1, double x2, double y2, double z2);
    // 提供两个点的集合，构造线段，如果重复则抛出异常
    Lines3D(uPointSet& pointSet);
    // 提供两个点的引用，构造线段，如果出现重复则抛出异常
    Lines3D(Points3D& PointA, Points3D& PointB);
    // 提供两个点的序号，构造线段，如果重复或者序号非法则抛出异常
    Lines3D(int idx1, int idx2);
    // 删除默认构造函数，因为想要构造线段至少需要先存在两个Points3D对象
    Lines3D() = delete;
    // 删除拷贝构造函数和赋值运算符，保证不会意外构造出重复的对象
    Lines3D(const Lines3D& Line) = delete;
    const Lines3D& operator=(const Lines3D& Line) = delete;
    // 析构函数
    ~Lines3D();

    /* non-static setters*/
    // 通过给定两个点的坐标 / 点的集合 / 给定两个点（的引用） / 给定两个点的序号 来修改线段。同时避免重复
    void SetPoints(uPointSet APointSet);
    void SetPoints(Points3D& PointA, Points3D& PointB);
    // 删除线段（从LinesList中删除该线段）
    void DeleteLine(Lines3D& Line);
    

    /* non-static getters*/
    uPointSet& PointSet {m_PointSet};
    int& idx {m_idx};
    const std::vector<Lines3D&>& LinesList {m_LinesList};
    // 计算该线段的长度
    double Length();

    /* static-getters */
    // 统计所有线段的总数
    static int LinesCounter();

private:
    // 一条（无向）线段可以看作是两个点的（无序）集合
    uPointSet m_PointSet {};
    // 当前线段的序号，本质是在LinesSet的索引 + 1
    int m_idx;
    // 包含当前所有线段的列表，符合Zero原则，设置为静态成员
    static std::vector<Lines3D&> m_LinesList {};
}

#endif 
