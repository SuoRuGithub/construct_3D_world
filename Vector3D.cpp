/*************************************************************************
【文件名】                  Vector3D.cpp
【功能模块和目的】          Vector3D类的定义
【开发者及日期】            张章 2024-7-28
【更改记录】                24-8-7增加了注释
*************************************************************************/
#include<memory>
#include"Vector3D.hpp"

using PointPtr = std::shared_ptr<Point3D>;

/*************************************************************************
【函数名称】       Vector3D
【函数功能】       Point3D类的含参构造函数与拷贝构造函数
【参数】          【含参构造函数1】
                    - 输入参数：double x, double y, double z: 表示希望构造的点的
                      坐标
                  【含参构造函数2】
                    - 输入参数：Point3D& Point: 表示向量对应的点
                  【拷贝构造函数】
                    - 输入参数：const Point3D& APoint. 希望拷贝的点的引用
【返回值】         无
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-2增加了注释
*************************************************************************/

/*************************************************************************
【函数名称】       Vector3D
【函数功能】       使用提供的x, y, z坐标构造一个向量对象
【参数】           double x: 输入参数，向量的x坐标
【参数】           double y: 输入参数，向量的y坐标
【参数】           double z: 输入参数，向量的z坐标
【返回值】         无
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
Vector3D::Vector3D(double x, double y, double z) : m_Point(x, y, z){
}

/*************************************************************************
【函数名称】       Vector3D
【函数功能】       使用提供的点的引用构造一个向量对象
【参数】           Point3D& Point: 输入参数，用于构造向量的点的引用
【返回值】         无
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
Vector3D::Vector3D(Point3D& Point) : m_Point(Point){
}

/*************************************************************************
【函数名称】       Vector3D
【函数功能】       拷贝构造函数，用于复制另一个向量对象
【参数】           const Vector3D& AVector: 输入参数，要复制的向量对象
【返回值】         无
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
Vector3D::Vector3D(const Vector3D& AVector) : m_Point(AVector.Point){
}

/*************************************************************************
【函数名称】       operator=
【函数功能】       赋值运算符，用于将一个向量对象的值赋给当前对象
【参数】           const Vector3D& AVector: 输入参数，要赋值的向量对象
【返回值】         const Vector3D&: 返回当前对象的引用
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
const Vector3D& Vector3D::operator=(const Vector3D& AVector){
    if (this != &AVector){
        m_Point = AVector.Point;
    }
    return *this;
}

/*************************************************************************
【函数名称】       ~Vector3D
【函数功能】       析构函数，释放向量对象占用的资源
【参数】           无
【返回值】         无
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
Vector3D::~Vector3D(){
}
/* non-static getters */

/*************************************************************************
【函数名称】       GetArea
【函数功能】       计算向量的面积，始终返回0.0，因为向量是零维对象
【参数】           无
【返回值】         double: 返回0.0
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
double Vector3D::GetArea() const{
    return 0.0;
}

/*************************************************************************
【函数名称】       GetLength
【函数功能】       计算向量的L2范数的长度
【参数】           无
【返回值】         double: 向量的长度
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
double Vector3D::GetLength() const{
    return GetL2Norm();    
}

/*************************************************************************
【函数名称】       GetL2Norm
【函数功能】       计算向量的L2范数
【参数】           无
【返回值】         double: 向量的L2范数
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
double Vector3D::GetL2Norm() const{
    return Point3D::Distance(Point3D(0.0, 0.0, 0.0), m_Point);
}
    
/*************************************************************************
【函数名称】       InnerProduct
【函数功能】       计算当前向量与另一个向量的内积
【参数】           const Vector3D& AVector: 输入参数，参与内积计算的另一个向量
【返回值】         double: 内积结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
double Vector3D::InnerProduct(const Vector3D& AVector) const{
    return AVector.Point.x * m_Point.x + AVector.Point.y * m_Point.y + AVector.Point.z * m_Point.z; 
}


/* non-static setters*/
    
/*************************************************************************
【函数名称】       SetPoint
【函数功能】       修改向量对应的点的坐标
【参数】           PointPtr ptrPoint: 输入参数，指向要修改的点的智能指针
【参数】           double x, double y, double z: 输入参数，新坐标
【返回值】         无
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
void Vector3D::SetPoint(PointPtr ptrPoint, double x, double y, double z){
    if (ptrPoint == PointPtr(&m_Point)){
        m_Point.SetCoordinates(x, y, z);
    }
    else{
        throw ExceptionNotHavePoint();
    }
}

/*************************************************************************
【函数名称】       SetPoint
【函数功能】       根据点的索引修改向量对应的点的坐标
【参数】           int PointIdx: 输入参数，要修改的点的索引
【参数】           double x, double y, double z: 输入参数，新坐标
【返回值】         无
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
void Vector3D::SetPoint(int PointIdx, double x, double y, double z){
    if (PointIdx != 1){
        throw ExceptionIndexOutOfRange();
    }
    else{
        m_Point.SetCoordinates(x, y, z);
    }
}

/*************************************************************************
【函数名称】       Normalize
【函数功能】       对当前向量进行归一化处理
【参数】           无
【返回值】         无
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
void Vector3D::Normalize(){
    double norm = GetLength();
    if (norm != 0){
        m_Point.SetCoordinates(m_Point.x / norm, m_Point.y / norm, m_Point.z / norm);
    }
}


/* static getters*/

/*************************************************************************
【函数名称】       GetL2Norm
【函数功能】       计算两个向量的二范数
【参数】           const Vector3D& Vector： 希望求范数的向量
【返回值】         double: 向量的二范数
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
double Vector3D::GetL2Norm(const Vector3D& Vector){
    return Point3D::Distance(Point3D(0.0, 0.0, 0.0), Vector.Point);
}

/*************************************************************************
【函数名称】       InnerProduct
【函数功能】       计算两个向量的内积
【参数】           const Vector3D& VectorA: 输入参数，第一个向量
【参数】           const Vector3D& VectorB: 输入参数，第二个向量
【返回值】         double: 两个向量的内积
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
double Vector3D::InnerProduct(const Vector3D& VectorA, const Vector3D& VectorB){
    return VectorA.Point.x * VectorB.Point.x +  
           VectorA.Point.y * VectorB.Point.y + 
           VectorA.Point.z * VectorB.Point.z; 
}

/*************************************************************************
【函数名称】       CrossProduct
【函数功能】       计算两个向量的叉积
【参数】           const Vector3D& VectorA: 输入参数，第一个向量
【参数】           const Vector3D& VectorB: 输入参数，第二个向量
【返回值】         Vector3D: 两个向量的叉积结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
Vector3D Vector3D::CrossProduct(const Vector3D& VectorA, const Vector3D& VectorB){
    double new_x = VectorA.Point.y * VectorB.Point.z - VectorA.Point.z * VectorB.Point.y;
    double new_y = VectorA.Point.z * VectorB.Point.x - VectorA.Point.x * VectorB.Point.z;
    double new_z = VectorA.Point.x * VectorB.Point.y - VectorA.Point.y * VectorB.Point.x;
    return Vector3D(new_x, new_y, new_z);
}
