#include<memory>
#include<algorithm>
#include<vector>
#include<stdexcept>
#include"Point3D.hpp"
#include"Line3D.hpp"

using PointPtr = std::shared_ptr<Point3D>;
 
/* 异常类 */
// 已经存在相应线段
ExceptionLineExist::ExceptionLineExist() 
    : std::invalid_argument("Line exists"){
}
// 线段不存在
ExceptionTargetLineNotExist::ExceptionTargetLineNotExist() 
    : std::invalid_argument("Target line doesn't exist"){
}


/*************************************************************************
【函数名称】       Line3D
【函数功能】       Line3D类的含参构造函数
【参数】           const Point3D& PointA, PointB: 希望构造的线段的两顶点的常引用
【返回值】         无
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
Line3D::Line3D(Point3D& PointA, Point3D& PointB) : m_PointA(PointA), m_PointB(PointB){
}

/*************************************************************************
【函数名称】       Line3D
【函数功能】       Line3D的移动构造函数
【参数】           Line3D& ALine: 希望移动的线的引用
【返回值】         无
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
Line3D::Line3D(Line3D&& ALine) : m_PointA(ALine.PointA), m_PointB(ALine.PointB){
}

/*************************************************************************
【函数名称】       operator=
【函数功能】       Line3D类转移赋值运算符的重载
【参数】           Line3D& ALine希望转移赋值的线的引用
【返回值】         Line3D& 被赋值的线对象的引用
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-2增加了注释
*************************************************************************/
Line3D& Line3D::operator=(Line3D&& ALine){
    if (this != &ALine){
        m_PointA = ALine.PointA;
        m_PointB = ALine.PointB;
    }
    return *this;
}
    
/*************************************************************************
【函数名称】       ~Line3D
【函数功能】       Line3D对象的析构函数
【参数】           无
【返回值】         无
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
Line3D::~Line3D(){
}


/* non-static getters */
/*************************************************************************
【函数名称】       operator==
【函数功能】       Face3D类==运算符的重载，用来比较两个线是否相等(i.e. 两个
                   线的顶点在不考虑排序的意义下相同)
【参数】           const Line3D& ALine: 另一条线的常引用
【返回值】         bool 两线段相同返回true，反之false
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
bool Line3D::operator==(const Line3D& ALine) const{
    if ((PointA == ALine.PointA && PointB == ALine.PointB) ||
        (PointA == ALine.PointB && PointB == ALine.PointA)){

        return true;
    }
    else{
        return false;
    }
}

/*************************************************************************
【函数名称】       GetArea
【函数功能】       计算当前线段的面积（直接返回0）
【参数】           无输入参数
【返回值】         double: 恒为0.0
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
double Line3D::GetArea() const{
    return 0.0;
}

/*************************************************************************
【函数名称】       GetLength
【函数功能】       计算当前线段的长度
【参数】           无输入参数
【返回值】         double: 当前线段的长度
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
double Line3D::GetLength() const{
    return Point3D::Distance(m_PointA, m_PointB);
}


/* non-static setters*/
/*************************************************************************
【函数名称】       SetPoint
【函数功能】       设置当前线段顶点的坐标
【参数】           const Pointptr ptrPoint: 希望被修改的点的指针(shared_ptr)
                   double x, y, z: 希望修改后点的坐标值
【返回值】         void 
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
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

/*************************************************************************
【函数名称】       SetPoint
【函数功能】       设置当前点的坐标
【参数】           int PointIdx: 希望修改的点的索引(1,2分别代表PointA,B)
                   double x, y, z: 希望修改后点的坐标值
【返回值】         void 
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
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
