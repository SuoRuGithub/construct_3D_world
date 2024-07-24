/*******************************************
 *【文件名】            Points3D.cpp
 *【功能模块和目的】    三维点类Points3D的定义
 *【开发者及日期】      张章 2024-7-22
 *【更改记录】          无
 * *****************************************/

#include<vector>
#include<stdexcept>
#include<cmath>
#include<memory>
#include"Points3D.hpp"
#include<algorithm>

using PointPtr = std::shared_ptr<Points3D>;

ExceptionPointExist::ExceptionPointExist() : std::invalid_argument("Points cannot be repeated"){ 
}

ExceptionInvalidCoordinates::ExceptionInvalidCoordinates() : std::invalid_argument("Coordinates should be a vector with 3 double"){   
}

ExceptionIndexOutOfRange::ExceptionIndexOutOfRange() : std::invalid_argument("Index out of range"){
}

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

// 静态数据成员初始化
std::vector<PointPtr>          Points3D::m_PointsList  {};
const std::vector<PointPtr>&   Points3D::PointsList    {m_PointsList};

// 构造函数
// 此处我额外要求点不得重复
// * 带默认参数的构造函数，分别给定x, y, z坐标，构造对象
Points3D::Points3D(double x = 0.0, double y = 0.0, double z = 0.0){
    if (IsPointExist(x, y, z)){
        throw ExceptionPointExist();
    }
    else{
        m_coordinates[0] = x;
        m_coordinates[0] = y;
        m_coordinates[0] = z;
    }
}
// * 不带默认参数的拷贝构造函数，给定一个长度为3的double型vector，
Points3D::Points3D(const std::vector<double>& coordinates){
    if (coordinates.size() != 3){
        throw ExceptionInvalidCoordinates();
    }
    else if (IsPointExist(coordinates[0], coordinates[1], coordinates[2])){
        throw ExceptionPointExist();
    }
    else{
        m_coordinates[0] = coordinates[0];
        m_coordinates[1] = coordinates[1];
        m_coordinates[2] = coordinates[2];
    }
}

// * 析构函数
Points3D::~Points3D(){
}

/* non-static setter*/
// 更改坐标（同时避免重复）
void Points3D::SetCoordinates(double x, double y, double z){
    if (IsPointExist(x, y, z)){
        throw ExceptionPointExist();
    }
    else{
        m_coordinates[0] = x;
        m_coordinates[1] = y;
        m_coordinates[2] = z;
    }
}
    
/* non-static getter*/
// 重载下标访问运算符，用于访问点对象的坐标
double Points3D::operator[](int idx) const {
    if (idx > 2 | idx < 0){
        throw ExceptionIndexOutOfRange();
    }
    else{
        return m_coordinates[idx];
    }
}

// 计算这一点到那一点之间的距离
double Points3D::Distance(const Points3D& APoint){
    double distance = (coordinates[0] - APoint[0]) * (coordinates[0] - APoint.coordinates[0]) +
                (coordinates[1] - APoint[1]) * (coordinates[1] - APoint.coordinates[1]) +
                (coordinates[2] - APoint[2]) * (coordinates[2] - APoint.coordinates[2]);    
    distance = sqrt(distance);
    return distance;
}

bool Points3D::IsPointExist(const double& x, const double& y, const double& z, const double& precision = 1e-5){
    // Lambda表达式寻找是否存在重复点
    auto condition = [x, y, z, precision](Points3D& Point)->bool{
        return (abs(Point[0] - x) < precision)&&
               (abs(Point[1] - y) < precision)&&
               (abs(Point[2] - z) < precision);};

    auto it = find_if(PointsList.begin(), PointsList.end(), condition);

    return it != PointsList.end();
}

/* static getters*/
// 统计当前点的总数目
int Points3D::PointsCounter(){
    return PointsList.size();
}

// 计算两个点之间的距离
double Points3D::Distance(Points3D PointA, Points3D PointB){
    double distance = (PointA[0] - PointB[0]) * (PointA[0] - PointB[0]) + 
                      (PointA[1] - PointB[1]) * (PointA[1] - PointB[1]) + 
                      (PointA[2] - PointB[2]) * (PointA[2] - PointB[2]);
    return sqrt(distance);
}
