#include<stdexcept>
#include"ControllerBase.hpp"

using PointPtr      = std::shared_ptr<Point3D>;
using LinePtr       = std::shared_ptr<Line3D>;
using FacePtr       = std::shared_ptr<Face3D>;
using ModelBasePtr  = std::shared_ptr<ModelBase>;
using objModelPtr   = std::shared_ptr<objModel>;

ExceptionUnsupportedFormat::ExceptionUnsupportedFormat() : std::invalid_argument("This format is not supported."){
}

ExceptionNoFacesFound::ExceptionNoFacesFound() : std::invalid_argument("No face is found."){
}

ExceptionNoLinesFound::ExceptionNoLinesFound() : std::invalid_argument("No line is found."){
}


// 从给定的文件中创建模型的相关信息
ControllerBase::ControllerBase(const std::string& FileName){
    m_FileName = FileName;
    if (m_FileName.length() > 3 && 
        m_FileName.substr(m_FileName.length() - 3) == std::string("obj")){

        m_ptrModel = std::shared_ptr<objModel>(new objModel);   // ModelBase指针指向objModel
        m_ptrModel->ImportModelFromFile(m_FileName);            // 使用基类指针调用虚函数，会调用派生类的实现
    }
    // else if (未来如果支持新的三维模型格式，请在这里加入分析格式的条件){
    //     m_ptrModel = std::shared_ptr<new_type_model>(new new_type_model);
    //     m_ptrModel->ImportModelFormFile(m_FileName);
    // }
    else{
        throw ExceptionUnsupportedFormat();
    }
}
// 将修改后的模型存储在给定的文件中，然后析构模型
ControllerBase::~ControllerBase(){
    if (m_FileName.length() > 3 && 
        m_FileName.substr(m_FileName.length() - 3) == std::string("obj")){

        m_ptrModel->ExportModelToFile(m_FileName); 
        std::dynamic_pointer_cast<objModel>(m_ptrModel).reset();
        // delete m_ptrModel;                  // 什么鬼报错
    }
    // else if (未来如果支持新的三维模型格式，请在这里加入分析格式的条件){
    // 
    // }
    else{
        throw ExceptionUnsupportedFormat();
    }
}

     
/******************FACE**************** */
const std::vector<Face3D>& ControllerBase::GetFaces(){
    if (m_ptrModel->FacesList.size() == 0){
        throw ExceptionNoFacesFound();
    }
    else{
        return m_ptrModel->FacesList;
    }
}

ControllerReturn ControllerBase::DeleteFace(unsigned int FaceIdx){
    if (FaceIdx < m_ptrModel->FacesList.size()){
        m_ptrModel->DeleteFace(FaceIdx);
        return ControllerReturn::FACE_DELETED;
    }
    else{
        // return ControllerReturn::FACE_NOT_EXIST; //(abandon)
        return ControllerReturn::INDEX_OUT_OF_RANGE;
    }
}

ControllerReturn ControllerBase::AddFace(double x1, double y1, double z1,
                                         double x2, double y2, double z2,
                                         double x3, double y3, double z3){

    try{
        m_ptrModel->AddFace(x1, y1, z1, x2, y2, z2, x3, y3, z3);
    }
    catch(ExceptionFaceExist e){
        return ControllerReturn::FACE_REPEATED;
    }
    catch(ExceptionPointsRepeated e){
        return ControllerReturn::POINTS_REPEATED;
    }
    return ControllerReturn::FACE_ADDED;
}

FaceDetail ControllerBase::GetPointsOfFace(unsigned int FaceIdx){
    if (FaceIdx >= m_ptrModel->FacesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    else{
        const Face3D& Face = m_ptrModel->FacesList[FaceIdx];
        FaceDetail detail = {FaceIdx, Face.PointA.x, Face.PointA.y, Face.PointA.z,
                                      Face.PointB.x, Face.PointB.y, Face.PointB.z,
                                      Face.PointC.x, Face.PointC.y, Face.PointC.z};
        return detail;
    }
}

ControllerReturn ControllerBase::ModifyPointOfFace(unsigned int FaceIdx, unsigned int PointIdx, double x, double y, double z){
    try{
        m_ptrModel->SetPointOfFace(FaceIdx, PointIdx, x, y, z);
        return ControllerReturn::POINT_OF_FACE_CHANGED;
    }
    catch(ExceptionIndexOutOfRange e){
        // 给的索引不在范围内
        return ControllerReturn::INDEX_OUT_OF_RANGE;
    }
    catch(ExceptionPointsRepeated e){
        // 点和其他两个点之一重复了
        return ControllerReturn::POINTS_REPEATED;
    }
    // catch(ExceptionNotHavePoint e){
        // // 面没有这个点（这个和第一个是重复的）
        // return ControllerReturn::FACE_NOT_HAVE_POINT;
    // }
}

/******************LINE**************** */
const std::vector<Line3D>& ControllerBase::GetLines(){
    if (m_ptrModel->FacesList.size() == 0){
        throw ExceptionNoLinesFound();
    }
    else{
        return m_ptrModel->LinesList;
    }
}

ControllerReturn ControllerBase::DeleteLine(unsigned int LineIdx){
    if (LineIdx < m_ptrModel->LinesList.size()){
        m_ptrModel->DeleteLine(LineIdx);
        return ControllerReturn::LINE_DELETED;
    }
    else{
        return ControllerReturn::INDEX_OUT_OF_RANGE;
    }
}

ControllerReturn ControllerBase::AddLine(double x1, double y1, double z1,
                                         double x2, double y2, double z2){

    try{
        m_ptrModel->AddLine(x1, y1, z1, x2, y2, z2);
    }
    catch(ExceptionLineExist e){
        return ControllerReturn::LINE_REPEATED;
    }
    catch(ExceptionPointsRepeated e){
        return ControllerReturn::POINTS_REPEATED;
    }
    return ControllerReturn::LINE_ADDED;
}

LineDetail GetPointsOfLine(unsigned int LineIdx);

ControllerReturn ModifyPointOfLine(unsigned int LineIdx, unsigned int PointIdx, double x, double y, double z);
