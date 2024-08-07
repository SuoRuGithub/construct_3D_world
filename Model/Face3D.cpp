/*************************************************************************
【文件名】                  Face3D.cpp
【功能模块和目的】          Face3D类的定义
【开发者及日期】            张章 2024-7-21
【更改记录】                24-8-5增加了注释
*************************************************************************/
#include<cmath>
#include<vector>
#include<memory>
#include<stdexcept>
#include"Face3D.hpp"
#include"Point3D.hpp"


// 点的智能指针
using PointPtr = std::shared_ptr<Point3D>;


/*************************************************************************
【函数名称】       Face3D
【函数功能】       Face3D类的含参构造函数
【参数】           const Point3D& PointA, PointB, PointC 
                   该面的三个顶点的常引用
【返回值】         无
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
Face3D::Face3D(const Point3D& PointA, const Point3D& PointB, 
               const Point3D& PointC)
        : m_PointA(PointA), m_PointB(PointB), m_PointC(PointC){
}

/*************************************************************************
【函数名称】       Face3D
【函数功能】       Face3D的转移构造函数
【参数】           Face3D& AFace: 希望转移的面的引用
【返回值】         无
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
Face3D::Face3D(Face3D&& AFace) 
    : m_PointA(AFace.PointA), m_PointB(AFace.PointB), m_PointC(AFace.PointC){
}
/*************************************************************************
【函数名称】       operator=
【函数功能】       Point3D类转移赋值运算符的重载
【参数】           Face3D& AFace: 希望赋值的面的引用
【返回值】         Face3D& 被赋值的面的引用
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
Face3D& Face3D::operator=(Face3D&& AFace){
    if (this != &AFace){
        m_PointA = AFace.PointA;
        m_PointB = AFace.PointB;
        m_PointC = AFace.PointC;
    }
    return *this;
}

// 析构函数
Face3D::~Face3D(){
}



/* non-static getters */
/*************************************************************************
【函数名称】       operaator==
【函数功能】       Face3D运算符==的重载，用来判断两个面是否相同（i.e.两个面
                   的三个顶点在不考虑排序的意义下相同）
【参数】           const Face3D& AFace 另一个参与比较的面的常引用
【返回值】         bool 如果两个面相等返回true，反之返回false
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
bool Face3D::operator==(const Face3D& AFace){
    // 我们不考虑面的三个顶点的顺序
    if ((PointA == AFace.PointA && PointB == AFace.PointB && 
         PointC == AFace.PointC) ||
        (PointA == AFace.PointA && PointB == AFace.PointC && 
         PointC == AFace.PointB) ||
        (PointA == AFace.PointB && PointB == AFace.PointA && 
         PointC == AFace.PointC) ||
        (PointA == AFace.PointB && PointB == AFace.PointC && 
         PointC == AFace.PointA) ||
        (PointA == AFace.PointC && PointB == AFace.PointA && 
         PointC == AFace.PointB) ||
        (PointA == AFace.PointC && PointB == AFace.PointB && 
         PointC == AFace.PointA)){

        return true;
    }
    else{
        return false;
    }
}

/*************************************************************************
【函数名称】       GetArea
【函数功能】       返回当前面的面积
【参数】           无输入参数
【返回值】         double 表示当前面的面积
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
double Face3D::GetArea()    const{
    double a = Point3D::Distance(PointA, PointB);
    double b = Point3D::Distance(PointA, PointC);
    double c = Point3D::Distance(PointB, PointC);
    double p = (a + b + c) / 2;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

/*************************************************************************
【函数名称】       GetLength
【函数功能】       返回当前面(三角形)的周长
【参数】           无输入参数
【返回值】         double 表示当前三角形的周长
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
double Face3D::GetLength()  const{
    return Point3D::Distance(PointA, PointB) + Point3D::Distance(PointA, PointC) + Point3D::Distance(PointB, PointC);
}


/* non-static setters */
/*************************************************************************
【函数名称】       SetPoint
【函数功能】       改变Face3D对象的某一个顶点
【参数】           PointPtr ptrPoint: 表示希望改变的顶点的指针（shared_ptr）
                   double x, y, z: 表示希望该点修改后的坐标
【返回值】         void
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
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

/*************************************************************************
【函数名称】       SetPoint
【函数功能】       改变Face3D对象的某一个顶点
【参数】           int PointIdx: 表示希望改变的顶点的索引
                                 (1,2,3分别代表PointA,B,C)
                   double x, y, z: 表示希望该点修改后的坐标
【返回值】         void
【开发者及日期】   张章 2024-7-21
【更改记录】       24-8-5增加了注释
*************************************************************************/
void Face3D::SetPoint(int PointIdx, double x, double y, double z){
    Point3D point(x, y, z);
    switch (PointIdx){
        case 1:
            if (point == PointB || point == PointC){
                throw ExceptionPointsRepeated();
            }
            m_PointA.SetCoordinates(x, y, z);
            break;
        case 2:
            if (point == PointA || point == PointC){
                throw ExceptionPointsRepeated();
            }
            m_PointB.SetCoordinates(x, y, z);
            break;
        case 3:
            if (point == PointA || point == PointB){
                throw ExceptionPointsRepeated();
            }
            m_PointC.SetCoordinates(x, y, z);
            break;
        default:
            throw ExceptionIndexOutOfRange();
    }
}
