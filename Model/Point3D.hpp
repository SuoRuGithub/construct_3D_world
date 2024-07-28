#include<vector>
#include<stdexcept>
#include<memory>

#ifndef _POINT3D_HPP
#define _POINT3D_HPP

// 点的指针
using PointPtr = std::shared_ptr<Point3D>;

/* 异常类 */
// 坐标非法
class ExceptionInvalidCoordinates : public std::invalid_argument{
public:
    ExceptionInvalidCoordinates();
};
// 给定的索引超出范围
class ExceptionIndexOutOfRange : public std::invalid_argument{
public:
    ExceptionIndexOutOfRange();
};


// 点可以重复
class Point3D{
public:
    // 删除默认构造函数，构造点必须显式指定坐标，或是以另一个点作为拷贝模板
    Point3D() = delete;
    // * 带参数的构造函数
    Point3D(double x, double y, double z);
    // * 拷贝构造函数
    Point3D(const Point3D& APoint);
    // * 赋值运算符重载
    Point3D& operator=(const Point3D& APoint);
    // 析构函数
    ~Point3D();

    // 重载 == 运算符，用来比较点是否相等
    bool operator==(const Point3D& APoint);

    /* non-static setter*/
    // 修改坐标
    void SetCoordinates(double x, double y, double z);
    
    /* non-static getter*/

    // 另一个点对象到当前点对象的距离
    double Distance(const Point3D& APoint) const;

    // 判断另一个点对象和当前点对象是否重合
    bool IsCoincide(const Point3D& APoint, double precision = 1e-5) const;

    // 点对象的坐标的常引用
    const double& x {m_x};
    const double& y {m_y};
    const double& z {m_z};

    
    /* static getters*/

    // 给定三个点的指针，判断这三个点是否共线
    static bool IsCollinear(const Point3D& PointA, const Point3D& PointB, const Point3D& PointC);
    
    // 计算给定两个点之间的距离
    static double Distance(const Point3D& PointA, const Point3D& PointB);

    // 判断两个点是否重合
    static bool IsCoincide(const Point3D& PointA, const Point3D& PointB, double precision = 1e-5);
    static bool IsCoincide(const Point3D& PointA, double x, double y, double z, double precision = 1e-5);
private:
    // 当前点的坐标
    double m_x;
    double m_y;
    double m_z;
};

#endif
