#include<memory>
#include<algorithm>
#include<vector>
#include<stdexcept>
#include"Point3D.hpp"
#include"Line3D.hpp"

using PointPtr = std::shared_ptr<Point3D>;
 
/* 异常类 */    

// 已经存在相应线段
ExceptionLineExist::ExceptionLineExist() : std::invalid_argument("Line exists"){
}
// 线段不存在
ExceptionTargetLineNotExist::ExceptionTargetLineNotExist() : std::invalid_argument("Target line doesn't exist"){
}


// 提供两个点的引用构造一个线段对象
Line3D::Line3D(Point3D& PointA, Point3D& PointB) : m_PointA(PointA), m_PointB(PointB){
}
    
// 析构函数
Line3D::~Line3D(){
}


/* non-static getters */

// 计算线段的面积（直接返回0）
double Line3D::GetArea() const{
    return 0.0;
}

// 计算线段的长度
double Line3D::GetLength() const{
    return Point3D::Distance(m_PointA, m_PointB);
}


/* non-static setters*/
    
// 修改线段对应的某个点，如果希望删除的点并不是这个线段的端点，则抛出异常
void Line3D::SetPoint(PointPtr ptrPoint, double x, double y, double z){
    if (ptrPoint == PointPtr(&m_PointA)){
        if (Point3D::IsCoincide(m_PointB, x, y, z)){
            throw ExceptionPointsRepeated();
        }
        ptrPoint->SetCoordinates(x, y, z);
    }
    else if (ptrPoint == PointPtr(&m_PointB)){
        if (Point3D::IsCoincide(m_PointA, x, y, z)){
            throw ExceptionPointsRepeated();
        }
        ptrPoint->SetCoordinates(x, y, z);
    }
    else{
        throw ExceptionNotHavePoint();
    }
}

// 给定点的索引（1，2分别代表AB），修改线段对应的某个点，
void Line3D::SetPoint(int PointIdx, double x, double y, double z){
    switch (PointIdx){
        case 1:
            m_PointA.SetCoordinates(x, y, z);
            break;
        case 2:
            m_PointB.SetCoordinates(x, y, z);
            break;
        default:
            throw ExceptionIndexOutOfRange();
    }

}