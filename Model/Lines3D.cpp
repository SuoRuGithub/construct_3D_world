/*******************************************
 *【文件名】            Lines3D.cpp
 *【功能模块和目的】    三维线类的定义
 *【开发者及日期】      张章 2024-7-23
 *【更改记录】          无
 * *****************************************/

#include<unordered_set>
#include<algorithm>
#include<vector>
#include<stdexcept>
#include"Points3D.hpp"
#include"Lines3D.hpp"

// Pointer of Points
using PointPtr = std::shared_ptr<Points3D>;

// Pointer of lines
using LinePtr = std::vector<Lines3D>;

/* 异常类 */    
ExceptionLineExist::ExceptionLineExist() : std::invalid_argument("Line exists"){
}

ExceptionPointsRepeated::ExceptionPointRepeated() : std::invalid_argument("Two Points are repeated"){
}

ExceptionTargetLineNotExist::ExceptionTargetLineNotExist() : std::invalid_argument("Target line doesn't exist"){
}


// // 提供两个点的引用构造一个线段对象
// Lines3D(Points3D& PointA, Points3D& PointB){
// }

// 提供两个点的指针构造一个线段对象
Lines3D::Lines3D(PointPtr PointA, PointPtr PointB){
    if (PointA == PointB){
        throw ExceptionPointsRepeated();
    }
    m_ptrPointA = PointA;
    m_ptrPointB = PointB;
}

// 提供两个点的序号，构造线段，如果重复或者序号非法则抛出异常
Lines3D::Lines3D(int idx1, int idx2){
    if (idx1 >= Points3D::PointsList.size() || idx1 < 0 ||
        idx2 >= Points3D::PointsList.size() || idx2 < 0 ||){
            throw ExceptionIndexOutOfRange();
        }
    if (idx1 == idx2){
        throw ExceptionPointsRepeated();
    }

    m_ptrPointA = Points3D::PointsList[idx1];
    m_ptrPointB = Points3D::PointsList[idx2];
}
    
// 析构函数
~Lines3D(){
}

/* non-static setters*/
// 修改线段对应的两个点
void Lines3D::SetPoints(PointPtr PointA, PointPtr, PointB){
    if (PointA == PointB){
        throw ExceptionPointsRepeated();
    }
    m_ptrPointA = PointA;
    m_ptrPointB = PointB;
}

// 删除线段（从LinesList中删除该线段）
static void Lines3D::DeleteLine(LinePtr TargetLine){
    auto Finder = [TargetLine](LinePtr Line) -> bool{return TargetLine == Line;};
    auto it = find_if(m_LinesList.begin(), m_LinesList.end());
    if (it != m_LinesList.end()){
        m_LinesList.erase(it);
    }
    else{
        throw ExceptionTargetLineNotExist();
    }
}


// 计算该线段的长度
double Lines3D::Length(){
    return Points3D::Distance(*m_ptrPointA, *m_ptrPointB);
}

/* static-getters */
// 统计所有线段的总数
int Lines3D::LinesCounter(){
    return m_LinesList.size();
}

// 给定两个点，判断是否存在以这两点为端点的线段
bool Lines3D::IsLineExist(Points3D& PointA, Points3D& PointB){
    for (const LinePtr line : m_LinesList){
        if ((line->m_ptrPointA == &PointA && line->m_ptrPointB == &PointB)||
            (line->m_ptrPointA == &PointB && line->m_ptrPointB == &PointA)){

            return true;
        }
    }
    return false;
}

bool Lines3D::IsLineExist(PointPtr ptrPointA, PointPtr ptrPointB){
    for (const LinePtr line : m_LinesList){
        if ((line->m_ptrPointA == ptrPointA && line->m_ptrPointB == ptrPointB)||
            (line->m_ptrPointA == ptrPointB && line->m_ptrPointB == ptrPointA)){

            return true;
        }
    }
    return false;
}