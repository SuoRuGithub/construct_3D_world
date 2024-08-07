#include<memory>
#include"Vector3D.hpp"

using PointPtr = std::shared_ptr<Point3D>;


// 提供一个坐标构造一个向量对象
Vector3D::Vector3D(double x, double y, double z) : m_Point(x, y, z){
}
// 提供一个点的引用构造一个向量对象
Vector3D::Vector3D(Point3D& Point) : m_Point(Point){
}
// 拷贝构造
Vector3D::Vector3D(const Vector3D& AVector) : m_Point(AVector.Point){
}
const Vector3D& Vector3D::operator=(const Vector3D& AVector){
    m_Point = AVector.Point;
}

/* non-static getters */

// 计算向量的面积（直接返回0）
double Vector3D::GetArea() const{
    return 0.0;
}

// 计算向量的l2范数的长度
double Vector3D::GetLength() const{
    return GetL2Norm();    
}
double Vector3D::GetL2Norm() const{
    return Point3D::Distance(Point3D(0.0, 0.0, 0.0), m_Point);
}
    
// 计算这个向量和另外一个向量的内积
double Vector3D::InnerProduct(const Vector3D& AVector) const{
    return AVector.Point.x * m_Point.x + AVector.Point.y * m_Point.y + AVector.Point.z * m_Point.z; 
}


/* non-static setters*/
    
// 修改线段对应的某个点，如果希望删除的点并不是这个线段的端点，则抛出异常
void Vector3D::SetPoint(PointPtr ptrPoint, double x, double y, double z){
    if (ptrPoint == PointPtr(&m_Point)){
        m_Point.SetCoordinates(x, y, z);
    }
    else{
        throw ExceptionNotHavePoint();
    }
}

// 对当前的向量进行归一化
void Vector3D::Normalize(){
    double norm = GetLength();
    if (norm != 0){
        m_Point.SetCoordinates(m_Point.x / norm, m_Point.y / norm, m_Point.z / norm);
    }
}


/* static getters*/

// 计算两个向量的内积
double Vector3D::InnerProduct(const Vector3D& VectorA, const Vector3D& VectorB){
    return VectorA.Point.x * VectorB.Point.x +  
           VectorA.Point.y * VectorB.Point.y + 
           VectorA.Point.z * VectorB.Point.z; 
}

// 计算两个向量的叉积
Vector3D Vector3D::CrossProduct(const Vector3D& VectorA, const Vector3D& VectorB){
    double new_x = VectorA.Point.y * VectorB.Point.z - VectorA.Point.z * VectorB.Point.y;
    double new_y = VectorA.Point.z * VectorB.Point.x - VectorA.Point.x * VectorB.Point.z;
    double new_z = VectorA.Point.x * VectorB.Point.y - VectorA.Point.y * VectorB.Point.x;
    return Vector3D(new_x, new_y, new_z);
}