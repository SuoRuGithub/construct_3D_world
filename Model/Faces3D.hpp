/*******************************************
 *【文件名】            Faces3D.hpp
 *【功能模块和目的】    三维面类的声明
 *【开发者及日期】      张章 2024-7-21
 *【更改记录】          无
 * *****************************************/

#ifndef _FACES3D_HPP
#define _FACES3D_HPP

#include<unordered_set>
#include<vector>
#include"Points3D.hpp"

// unordered set of Points (reference)
using uPointSet = std::unordered_set<Points3D&>;

/******************************************
 *【类名】              Faces3D
 *【功能】              表示三维空间中的一个三角形
 *【接口说明】          提供带参数的构造函数（同时避免重复），删除默认构造函数，删除拷贝构造函数和赋值运算符的重载
 *                      提供查询和修改当前面的三个顶点的接口
 *                      提供删除面（从面列表中删除）的接口
 *                      提供获取当前面序号的接口
 *【开发者及日期】      张章  2024-7-21
 *【更改记录】          无
 * ***************************************/

class Faces3D{
public:
    // 提供三个点的坐标，构造面，如果重复抛出异常
    Faces3D();
    // 提供三个点的集合，构造面，如果重复抛出异常
    Faces3D();
    // 提供三个点的引用，构造面，如果重复抛出异常
    Faces3D();
    // 提供三个点的序号，构造面，如果重复或序号非法则抛出异常
    Faces3D();
    // 删除默认构造函数，因为想要构造一个面至少需要已经存在三个点
    Faces3D();
    // 删除拷贝构造函数和赋值运算符，保证不会意外构造出重复的对象
    Faces3D();

    /* non-static setters */
    // 通过给定三个点的坐标 / 集合 / 引用 / 序号，来修改当前面。需要避免重复和非法情况
    void SetFaces();
    void SetFaces();
    void SetFaces();
    void SetFaces();
    // 删除面（从FaceList中删除该面）
    void DeleteFace();

    /* non-static getters */
    uPointSet& PointSet {m_PointSet};
    int& idx {m_idx};
    std::vector<Faces3D>& FaceList {m_FaceList};
    
private:
    // 一个空间中的三角形可以用三个点的（无序）集合来表示
    uPointSet m_PointSet;
    // 当前面的序号，本质是当前面在FaceList中的索引 + 1
    int m_idx {0};
    // 所有面的列表
    std::vector<Faces3D> m_FaceList;
}

#endif
