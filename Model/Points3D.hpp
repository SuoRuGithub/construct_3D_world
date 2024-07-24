/*******************************************
 *【文件名】            Points3D.hpp
 *【功能模块和目的】    三维点类Points3D的声明
 *【开发者及日期】      张章 2024-7-21
 *【更改记录】          无
 * *****************************************/

#ifndef _POINTS3D_HPP
#define _POINTS3D_HPP

#include<vector>
#include<stdexcept>
#include<memory>

using PointPtr = std::shared_ptr<Points3D>;

/********异常类**********
 * 声明了可能用到的异常，包括出现重复点、给定的坐标不是三维的
 ***********************/

class ExceptionPointExist : public std::invalid_argument{
public:
    ExceptionPointExist();
};

class ExceptionInvalidCoordinates : public std::invalid_argument{
public:
    ExceptionInvalidCoordinates();
};

class ExceptionIndexOutOfRange : public std::invalid_argument{
public:
    ExceptionIndexOutOfRange();
};

/******************************************
 *【类名】              Points3D
 *【功能】              创建三维空间中的点对象，作为线对象与面对象的基础
 *【接口说明】          提供默认、带参构造函数，删除了拷贝构造函数和赋值运算符的重载
 *                      提供修改和查询坐标的接口
 *                      提供删除点（析构并从点列表中删除）的接口
 *                      提供获取当前点序号的索引
 *【开发者及日期】      张章  2024-7-21
 *【更改记录】          无
 * ***************************************/

// 此处我额外要求点不得重复

class Points3D{
public:
    /* 构造函数 */
    // * 带默认参数的构造函数，分别给定x, y, z坐标，构造对象
    Points3D(double x = 0.0, double y = 0.0, double z = 0.0);
    // * 不带默认参数的拷贝构造函数，给定一个长度为3的double型vector，构造一个点对象
    Points3D(const std::vector<double>& coordinates);
    // * 为避免出现重复点，拷贝构造函数和赋值运算符重载删去
    Points3D(const Points3D& APoint) = delete;
    Points3D& operator=(const Points3D& aPoint) = delete;

    /* 析构函数 */
    ~Points3D();

    /* non-static setter*/
    // 更改坐标（同时避免重复）
    void SetCoordinates(double x, double y, double z);
    
    /* non-static getter*/
    // 重载下标访问运算符，用于访问点对象的坐标
    double operator[](int idx) const;

    // 当前点的坐标的常引用
    const std::vector<double>&            coordinates     {m_coordinates};
    // 当前点的索引的常引用
    const int&                            idx             {m_idx};
    // 所有点的列表的常引用         * NOTE: 请注意静态成员的初始化要在定义中完成，不可以在这里绑定
    static const std::vector<PointPtr>&   PointsList;

    // 计算这一点到那一点之间的距离
    double Distance(const Points3D& APoint);
    // 给定一个坐标，判断是否已经存在了由这个坐标确定的点。该函数用于避免在构造对象或者修改对象时出现点重复的情况
    static bool IsPointExist(const double& x, const double& y, const double& z, const double& precision = 1e-5);


    // 给定一个索引，判断这个索引是否越界
    static bool IsIdxInRange(int idx);

    // 给定三个点的指针，判断这三个点是否共线
    static bool IsCollinear(PointPtr ptrPointA, PointPtr ptrPointB, PointPtr ptrPointC);



    /* static getters*/
    // 统计当前点的总数目
    static int PointsCounter();
    // 计算两个点之间的距离
    static double Distance(Points3D PointA, Points3D PointB);

private:
    // 当前点坐标
    std::vector<double> m_coordinates = std::vector<double>(3, 0.0);
    // 当前点序号. 本质为m_PointsList中该点的索引加一（indexing from 1）
    int m_idx {0};
    // 包含当前所有点的引用的列表，符合Zero原则，设置为静态成员
    static std::vector<PointPtr> m_PointsList;
};

#endif
