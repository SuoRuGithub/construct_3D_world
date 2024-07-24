/*******************************************
 *【文件名】            Faces3D.hpp
 *【功能模块和目的】    三维面类的声明
 *【开发者及日期】      张章 2024-7-21
 *【更改记录】          无
 * *****************************************/

#ifndef _FACES3D_HPP
#define _FACES3D_HPP

#include<vector>
#include<memory>
#include"Points3D.hpp"

// 点的智能指针
using PointPtr      = std::shared_ptr<Points3D>;
// 点的智能指针，且无法通过指针改变指针指向的数据
using PointConstPtr = std::shared_ptr<const Points3D>;

class Faces3D;
// 面的智能指针
using FacePtr       = std::shared_ptr<Faces3D>;

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

/*****************异常类******************** 
 * 三个点共线
 * 平面已经存在
 * 
*******************************************/
// 三点共线
class ExceptionCollinear : public std::invalid_argument{
public:
    ExceptionCollinear();
};

// 平面已经存在
class ExceptionPlaneExist : public std::invalid_argument{
public:
    ExceptionPlaneExist();
};

// 平面不存在
class ExceptionPlaneNotExist : public std::invalid_argument{
public:
    ExceptionPlaneNotExist();
};








class Faces3D{
public:
    // 提供三个点的指针，构造一个平面
    Faces3D(PointPtr ptrPointA, PointPtr ptrPointB, PointPtr ptrPointC);
    // 提供三个点的序号，构造面，如果重复或序号非法则抛出异常
    Faces3D(int idx1, int idx2, int idx3);
    // 删除默认构造函数，因为想要构造一个面至少需要已经存在三个点
    Faces3D() = delete;

    // 删除拷贝构造函数和赋值运算符，保证不会意外构造出重复的对象
    Faces3D(const Faces3D&) = delete;
    Faces3D& operator=(const Faces3D&) = delete;

    // 析构函数
    ~Faces3D();

    /* non-static setters */
    // 给定三个点重新修改一个面
    void SetFaces(PointPtr ptrPointA, PointPtr ptrPointB, PointPtr ptrPointC);
    void SetFaces(int idx1, int idx2, int idx3);

    // 删除面（从FaceList中删除该面）
    static void DeleteFace(FacePtr ptrFace);


    bool PlaneIsExist(PointPtr ptrPointA, PointPtr ptrPointB, PointPtr ptrPointC);





    /* non-static getters */
    const PointConstPtr& ptrPointA  {m_ptrPointA};     // 常引用，用来保证指针的指向不被改变； 常指针，用来保证指针指向的内容不能通过指针被改变
    const PointConstPtr& ptrPointB  {m_ptrPointB}; 
    const PointConstPtr& ptrPointC  {m_ptrPointC}; 

    int& idx {m_idx};

    const std::vector<FacePtr>& ptrFaceList {m_ptrFaceList};  
    
private:
    // 该三角形的三个顶点的指针
    PointPtr m_ptrPointA;
    PointPtr m_ptrPointB;
    PointPtr m_ptrPointC;

    // 当前面的序号，本质是当前面在FaceList中的索引
    int m_idx;

    // 所有面的指针的列表
    static std::vector<FacePtr> m_ptrFaceList;
};

#endif
