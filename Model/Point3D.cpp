#include<memory>
#include<cmath>
#include"Point3D.hpp"

using PointPtr = std::shared_ptr<Point3D>;

ExceptionInvalidCoordinates::ExceptionInvalidCoordinates() : std::invalid_argument("Invalid Coordinates"){
}

ExceptionIndexOutOfRange::ExceptionIndexOutOfRange() : std::invalid_argument("Index oput of range"){
}

// 构造函数
// * 带参数的构造函数
Point3D::Point3D(double x, double y, double z) : m_x(x), m_y(y), m_z(z){
}
// * 拷贝构造函数
Point3D::Point3D(const Point3D& APoint) : m_x(APoint.x), m_y(APoint.y), m_z(APoint.z){
}
// * 赋值运算符重载
Point3D& Point3D::operator=(const Point3D& APoint){
    if (this != &APoint){
        m_x = APoint.x;
        m_y = APoint.y;
        m_z = APoint.z;
    }
    return *this;
    
}
// * 析构函数
Point3D::~Point3D(){
}

// 重载 == 运算符，比较两个点是否相等
bool Point3D::operator==(const Point3D& APoint) const{
    if (std::abs(m_x - APoint.x) < 1e-5 && 
        std::abs(m_y - APoint.y) < 1e-5 && 
        std::abs(m_z - APoint.z) < 1e-5 ){

        return true;
    }
    else{
        return false;
    }
}

/* non-static setter*/

// 修改坐标
void Point3D::SetCoordinates(double x, double y, double z){
    m_x = x;
    m_y = y;
    m_z = z;
}
    

/* non-static getter*/

// 计算这一点到那一点之间的距离
double Point3D::Distance(const Point3D& APoint) const{
    double distance = (m_x - APoint.x) * (m_x - APoint.x) + 
                      (m_y - APoint.y) * (m_y - APoint.y) + 
                      (m_z - APoint.z) * (m_z - APoint.z);
    return sqrt(distance); 
}

// 判断另一个点对象和当前点是否重合
bool Point3D::IsCoincide(const Point3D& APoint, double precision) const{
    if ((std::abs(m_x - APoint.x) < precision) && 
        (std::abs(m_y - APoint.y) < precision) &&
        (std::abs(m_z - APoint.z) < precision)){

        return true;
    }
    else{
        return false;
    }
}

/* static getters*/

bool Point3D::IsCollinear(const Point3D& PointA, const Point3D& PointB, const Point3D& PointC){
    // 使用Vector类的叉积进行判断
    return false;
}

double Point3D::Distance(const Point3D& PointA, const Point3D& PointB){
    double distance = (PointA.x - PointB.x) * (PointA.x - PointB.x) +
                      (PointA.y - PointB.y) * (PointA.y - PointB.y) +
                      (PointA.z - PointB.z) * (PointA.z - PointB.z);
    return sqrt(distance);
}

bool Point3D::IsCoincide(const Point3D& PointA, const Point3D& PointB, double precision /*= 1e-5*/){    // note that default parameters shouldn't be shown in definition.
    if ((std::abs(PointA.x - PointB.x) < precision) && 
        (std::abs(PointA.y - PointB.y) < precision) &&
        (std::abs(PointA.z - PointB.z) < precision)){

        return true;
    }
    else{
        return false;
    }
}

bool Point3D::IsCoincide(const Point3D& PointA, double x, double y, double z, double precision){
    return Point3D::IsCoincide(PointA, Point3D(x, y, z), precision);
}
