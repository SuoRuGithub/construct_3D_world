#include<algorithm>
#include<vector>
#include<memory>
#include<stdexcept>
#include"Faces3D.hpp"
#include"Points3D.hpp"

// 点的智能指针
using PointPtr      = std::shared_ptr<Points3D>;
// 点的智能指针，且无法通过指针改变指针指向的数据
using PointConstPtr = std::shared_ptr<const Points3D>;
// 面的智能指针
using FacePtr       = std::shared_ptr<Faces3D>;




ExceptionCollinear::ExceptionCollinear() : std::invalid_argument("Three points shouldn't be collinear"){
}

ExceptionPlaneExist::ExceptionPlaneExist() : std::invalid_argument("Plane exist"){
}

ExceptionPlaneNotExist::ExceptionPlaneNotExist() : std::invalid_argument("Plane doesn't exist"){
}









// 提供三个点的指针，构造一个平面
Faces3D::Faces3D(PointPtr ptrPointA, PointPtr ptrPointB, PointPtr ptrPointC){
    if (Points3D::IsCollinear(ptrPointA, ptrPointB, ptrPointC)){
        throw ExceptionCollinear();
    }
    if (PlaneIsExist(ptrPointA, ptrPointB, ptrPointC)){
        throw ExceptionPlaneExist();
    }
    m_ptrPointA = ptrPointA;
    m_ptrPointB = ptrPointB;
    m_ptrPointC = ptrPointC;
}

// 提供三个点的序号，构造面，如果重复或序号非法则抛出异常
Faces3D::Faces3D(int idx1, int idx2, int idx3){
    if (Points3D::IsIdxInRange(idx1) || Points3D::IsIdxInRange(idx2) || Points3D::IsIdxInRange(idx3)){
        throw ExceptionIndexOutOfRange();
    }
    if (Points3D::IsCollinear(Points3D::PointsList[idx1], Points3D::PointsList[idx2], Points3D::PointsList[idx3])){
        throw ExceptionCollinear();
    }
    if (PlaneIsExist(Points3D::PointsList[idx1], Points3D::PointsList[idx2], Points3D::PointsList[idx3])){
        throw ExceptionPlaneExist();
    }
    m_ptrPointA = Points3D::PointsList[idx1];
    m_ptrPointB = Points3D::PointsList[idx2];
    m_ptrPointC = Points3D::PointsList[idx3];
}

// 析构函数
Faces3D::~Faces3D(){
}

/* non-static setters */
// 给定三个点的指针重新修改一个面
void Faces3D::SetFaces(PointPtr ptrPointA, PointPtr ptrPointB, PointPtr ptrPointC){
    if (Points3D::IsCollinear(ptrPointA, ptrPointB, ptrPointC)){
        throw ExceptionCollinear();
    }
    if (PlaneIsExist(ptrPointA, ptrPointB, ptrPointC)){
        throw ExceptionPlaneExist();
    }
    m_ptrPointA = ptrPointA;
    m_ptrPointB = ptrPointB;
    m_ptrPointC = ptrPointC;
}
// 给定三个点的索引重新修改一个面
void Faces3D::SetFaces(int idx1, int idx2, int idx3){
    if (Points3D::IsIdxInRange(idx1) || Points3D::IsIdxInRange(idx2) || Points3D::IsIdxInRange(idx3)){
        throw ExceptionIndexOutOfRange();
    }
    if (Points3D::IsCollinear(Points3D::PointsList[idx1], Points3D::PointsList[idx2], Points3D::PointsList[idx3])){
        throw ExceptionCollinear();
    }
    if (PlaneIsExist(Points3D::PointsList[idx1], Points3D::PointsList[idx2], Points3D::PointsList[idx3])){
        throw ExceptionPlaneExist();
    }
    m_ptrPointA = Points3D::PointsList[idx1];
    m_ptrPointB = Points3D::PointsList[idx2];
    m_ptrPointC = Points3D::PointsList[idx3];
}



// 删除面（从FaceList中删除该面）
void Faces3D::DeleteFace(FacePtr ptrFace){
    auto Finder = [ptrFace](FacePtr ptr)->bool {return ptrFace == ptr;};     // shared_ptr是这样的
    auto it = std::find_if(m_ptrFaceList.begin(), m_ptrFaceList.end(), Finder);

    if (it != m_ptrFaceList.end()){
        m_ptrFaceList.erase(it);
    }
    else{
        throw ExceptionPlaneNotExist();
    }
}

bool Faces3D::PlaneIsExist(PointPtr ptrPointA, PointPtr ptrPointB, PointPtr ptrPointC){
    for (FacePtr ptrFace : m_ptrFaceList){
        if ((ptrFace->ptrPointA == ptrPointA && ptrFace->ptrPointB == ptrPointB && ptrFace->ptrPointC == ptrPointC) || 
            (ptrFace->ptrPointA == ptrPointA && ptrFace->ptrPointB == ptrPointC && ptrFace->ptrPointC == ptrPointB) ||
            (ptrFace->ptrPointA == ptrPointB && ptrFace->ptrPointB == ptrPointA && ptrFace->ptrPointC == ptrPointC) ||
            (ptrFace->ptrPointA == ptrPointB && ptrFace->ptrPointB == ptrPointC && ptrFace->ptrPointC == ptrPointA) ||
            (ptrFace->ptrPointA == ptrPointC && ptrFace->ptrPointB == ptrPointA && ptrFace->ptrPointC == ptrPointB) ||
            (ptrFace->ptrPointA == ptrPointC && ptrFace->ptrPointB == ptrPointB && ptrFace->ptrPointC == ptrPointA) ){

            return true;
            }
    }

    return false;
}
