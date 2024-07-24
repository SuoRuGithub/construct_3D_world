/*******************************************
 *【文件名】            Lines3D.hpp
 *【功能模块和目的】    三维线段类的声明
 *【开发者及日期】      张章 2024-7-21
 *【更改记录】          无
 * *****************************************/

#ifndef _LINES3D_HPP
#define _LINES3D_HPP

#include<stdexcept>
#include<vector>
#include<memory>
#include<stdexcept>
#include"Points3D.hpp"

// Pointer of Points
using PointPtr = std::shared_ptr<Points3D>;

class Lines3D;
// Pointer of lines
using LinePtr = std::shared_ptr<Lines3D>;

/*****************异常类*********************
 * 声明了可能会用到的异常，包括已经存在相应线段，
 ******************************************/
// 已经存在相应线段
class ExceptionLineExist : public std::invalid_argument{
public:
    ExceptionLineExist();
};
// 构造线段使用的两个点重复
class ExceptionPointsRepeated : public std::invalid_argument{
public:
    ExceptionPointRepeated();
};
// 线段不存在
class ExceptionTargetLineNotExist : public std::invalid_argument{
public:
    ExceptionTargetLineNotExist();
};




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
    // 删除默认构造函数，因为想要构造线段至少需要先存在两个Points3D对象
    Lines3D() = delete;

    // // 提供两个点的引用构造一个线段对象
    // Lines3D(Points3D& PointA, Points3D& PointB);
    // 提供两个点的指针构造一个线段对象
    Lines3D(PointPtr PointA, PointPtr PointB);
    // 提供两个点的序号，构造线段，如果重复或者序号非法则抛出异常
    Lines3D(int idx1, int idx2);
    
    // 删除拷贝构造函数和赋值运算符，保证不会意外构造出重复的对象
    Lines3D(const Lines3D& Line) = delete;
    const Lines3D& operator=(const Lines3D& Line) = delete;

    // 析构函数
    ~Lines3D();

    /* non-static setters*/
    // 修改线段对应的两个点
    void SetPoints(Points3D& PointA, Points3D& PointB);
    // 删除线段（从LinesList中删除该线段）
    static void DeleteLine(LinePtr Line);

    int& idx {m_idx};

    const std::vector<Lines3D&>& LinesList {m_LinesList};

    // 计算该线段的长度
    double Length();

    /* static-getters */
    // 统计所有线段的总数
    static int LinesCounter();
    // 给定两个点，判断是否存在以这两点为端点的线段
    static bool IsLineExist(Points3D& PointA, Points3D& PointB);
    // 给定两个点的指针，判断是否存在以这两点为端点的线段
    static bool IsLineExist(PointPtr ptrPointA, PointPtr ptrPointB);
private:
    // 通过两个指针来表示当前线段的两个端点 （使用引用实现的话不是太会，有一些问题无法解决）
    PointPtr m_ptrPointA;
    PointPtr m_ptrPointB;

    // 当前线段的序号，本质是在LinesSet的索引 
    int m_idx;

    // 包含当前所有线段的列表，符合Zero原则，设置为静态成员
    static std::vector<LinePtr> m_LinesList;
};

#endif 
