#include<cmath>
#include<vector>
#include<memory>
#include<stdexcept>
#include"Face3D.hpp"
#include"Point3D.hpp"

// 点的智能指针
using PointPtr      = std::shared_ptr<Point3D>;

// ExceptionCollinear::ExceptionCollinear() : std::invalid_argument("Three points shouldn't be collinear"){
// }

// 提供两个点的引用构造一个面对象
Face3D::Face3D(Point3D& PointA, Point3D& PointB, Point3D& PointC)
    : m_PointA(PointA), m_PointB(PointB), m_PointC(PointC){
}

// 析构函数
Face3D::~Face3D(){
}


/* non-static getters */

// 返回面的面积
double Face3D::GetArea()    const{
    double a = Point3D::Distance(PointA, PointB);
    double b = Point3D::Distance(PointA, PointC);
    double c = Point3D::Distance(PointB, PointC);
    double p = (a + b + c) / 2;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

// 返回面的周长
double Face3D::GetLength()  const{
    return Point3D::Distance(PointA, PointB) + Point3D::Distance(PointA, PointC) + Point3D::Distance(PointB, PointC);
}


/* non-static setters */

// 修改面对应的某个点
void Face3D::SetPoint(PointPtr ptrPoint, double x, double y, double z){
    if (ptrPoint == PointPtr(&m_PointA)){
        if (Point3D::IsCoincide(m_PointB, x, y, z) || 
            Point3D::IsCoincide(m_PointC, x, y, z)){

            throw ExceptionPointsRepeated();
        }
        ptrPoint->SetCoordinates(x, y, z);
    }
    else if (ptrPoint == PointPtr(&m_PointB)){
        if (Point3D::IsCoincide(m_PointA, x, y, z) ||
            Point3D::IsCoincide(m_PointC, x, y, z)){

            throw ExceptionPointsRepeated();
        }
        ptrPoint->SetCoordinates(x, y, z);
    }
    else if (ptrPoint == PointPtr(&m_PointC)){
        if (Point3D::IsCoincide(m_PointA, x, y, z) ||
            Point3D::IsCoincide(m_PointB, x, y, z)){

            throw ExceptionPointsRepeated();
        }
        ptrPoint->SetCoordinates(x, y, z);
    }
    else{
        throw ExceptionNotHavePoint();
    }
}

// 给定点的索引进行修改（1，2，3分别代表ABC）
void Face3D::SetPoint(int PointIdx, double x, double y, double z){
    switch (PointIdx){
        case 1:
            m_PointA.SetCoordinates(x, y, z);
            break;
        case 2:
            m_PointB.SetCoordinates(x, y, z);
            break;
        case 3:
            m_PointC.SetCoordinates(x, y, z);
            break;
        default:
            throw ExceptionIndexOutOfRange();
    }
}