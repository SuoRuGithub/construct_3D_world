/*******************************************
 *【文件名】            Points3D.hpp
 *【功能模块和目的】    三维点类Points3D的声明
 *【开发者及日期】      张章 2024-7-21
 *【更改记录】          无
 * *****************************************/

#ifndef _POINTS3D_HPP
#define _POINTS3D_HPP

#include<vector>

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

class Points3D{
public:
    // 构造函数
    // 此处我额外要求点不得重复
    // * 带默认参数的构造函数，分别给定x, y, z坐标，构造对象
    Points3D(double x = 0.0, double y = 0.0, double z = 0.0);
    // * 不带默认参数的拷贝构造函数，给定一个长度为3的double型vector，
    //   构造一个点对象
    Points3D(const std::vector<double>& coordinates);
    // * 为避免出现重复点，拷贝构造函数和赋值运算符重载删去
    Points3D(const Points3d& APoint) = delete;
    Points3D& operator=(const Points3D& aPoint) = delete;
    // * 析构函数
    ~Points3D();

    /* non-static setter*/
    // 更改坐标（同时避免重复）
    void SetCoordinates(double x, double y, double z);
    
    /* non-static getter*/
    // 当前点坐标，当前点序号以及所有点列表的常引用，只读
    const std::vector<double>&            coordinates     {m_coordinates};
    const int&                            idx             {m_idx};
    const static std::vector<Points3D>    PointsList      {m_PointsList};
    // 计算这一点到那一点之间的距离
    double Distance(const Points3D& APoint);

    /* static getters*/
    // 统计当前点的总数目
    static int PointsCounter() const;

protected:
private:
    // 当前点坐标
    std::vector<double> m_coordinates(3)  {0.0, 0.0, 0.0};
    // 当前点序号. 本质为m_PointsList中该点的索引加一（indexing from 1）
    int m_idx {0};
    // 包含当前所有点的引用的列表，符合Zero原则，设置为静态成员
    static std::vector<Points3D&> m_PointsList;
}

#endif
