#include<cstddef>
#include<stdexcept>
#include<iostream>
#include<filesystem>
#include"ControllerBase.hpp"

// I forget this shit at first.
std::shared_ptr<ControllerBase> ControllerBase::m_ptrController {nullptr};

// 点、线、面和模型的指针
using PointPtr = std::shared_ptr<Point3D>;
using LinePtr  = std::shared_ptr<Line3D>;
using FacePtr  = std::shared_ptr<Face3D>;
using ModelPtr = std::shared_ptr<Model3D>;
// 统计信息，点、线、面信息的列表
using StatisticalInfoList = std::vector<StatisticalInfo>;
using PointDetailList     = std::vector<PointDetail>;
using LineDetailList      = std::vector<LineDetail>;
using FaceDetailList      = std::vector<FaceDetail>;

ExceptionUnsupportedFormat::ExceptionUnsupportedFormat() : std::invalid_argument("This format is not supported."){
}

ExceptionNoFacesFound::ExceptionNoFacesFound() : std::invalid_argument("No face is found."){
}

ExceptionNoLinesFound::ExceptionNoLinesFound() : std::invalid_argument("No line is found."){
}

// 定义几种结构体的函数
StatisticalInfo::StatisticalInfo()
    : Name(""), FaceNum(0), LineNum(0), PointNum(0), 
      BoundingBoxVolume(0.0), FaceArea(0.0), LineLength(0.0){
}

void StatisticalInfo::operator()(ModelPtr ptrModel){
    Name              = ptrModel->Name;
    FaceNum           = ptrModel->GetTotalFacesNum();
    LineNum           = ptrModel->GetTotalLinesNum();
    PointNum          = ptrModel->GetTotalPointsNum();
    BoundingBoxVolume = ptrModel->GetMinBoundingBox();
    FaceArea          = ptrModel->GetTotalFacesArea();
    LineLength        = ptrModel->GetTotalLinesLength();
}

PointDetail::PointDetail()
    : x(0.0), y(0.0), z(0.0){
}

PointDetail::PointDetail(const PointDetail& ADetail){
    x = ADetail.x;
    y = ADetail.y;
    z = ADetail.z;
}

void PointDetail::operator()(const Point3D& Point){
    x = Point.x;
    y = Point.y;
    z = Point.z;
}


LineDetail::LineDetail()
    : idx(0), PointsInfo({PointDetail(), PointDetail()}){
}

LineDetail::LineDetail(const LineDetail& ADetail){
    idx = ADetail.idx;
    PointsInfo[0] = ADetail.PointsInfo[0];
    PointsInfo[1] = ADetail.PointsInfo[1];
    Length = ADetail.Length;
}

void LineDetail::operator()(size_t index, const Line3D& Line){
    idx = index;
    PointsInfo[0](Line.PointA);
    PointsInfo[1](Line.PointB);
    Length = Line.GetLength();
}

FaceDetail::FaceDetail()
    : idx {0}, PointsInfo({PointDetail(), PointDetail(), PointDetail()}), Area(0.0){
}

FaceDetail::FaceDetail(const FaceDetail& ADetail){
    idx = ADetail.idx;
    PointsInfo[0] = ADetail.PointsInfo[0];
    PointsInfo[1] = ADetail.PointsInfo[1];
    PointsInfo[2] = ADetail.PointsInfo[2];
    Area   = ADetail.Area;
    Length = ADetail.Length;
}

void FaceDetail::operator()(size_t index, const Face3D& Face){
    idx = index;
    PointsInfo[0](Face.PointA);
    PointsInfo[1](Face.PointB);
    PointsInfo[2](Face.PointC);
    Area   = Face.GetArea();
    Length = Face.GetLength();
}

/********************ControllerBase*********************** */
ControllerReturn ControllerBase::ImportModel(std::string& fileName){
    m_ptrModel = ModelPtr(new Model3D);
    try{
        Importer ModelImporter(m_ptrModel, fileName);
        ModelImporter.ImportModel();
    }
    catch(const ExceptionInvalidImporterConfig& e){
        // 设置非法
        return ControllerReturn::INVALID_IMPORTER_CONFIG;
    }
    ModelInfoPrivate model_info_private = {m_ptrModel, fileName};
    m_ModelList.push_back(model_info_private);
    return ControllerReturn::MODEL_IMPORTED;
}
ControllerReturn ControllerBase::ExportModel(){
    if (m_ptrModel == nullptr){
        return ControllerReturn::NO_MODEL;
    }
    try{
        Exporter ModelExporter(m_ptrModel, m_ModelPath);
        ModelExporter.ExportModel();
        return ControllerReturn::MODEL_EXPORTED;
    }
    catch(const ExceptionInvalidExporterConfig& e){
        return ControllerReturn::INVALID_EXPORTER_CONFIG;
    }
}
ControllerReturn ControllerBase::ExportModel(std::string& fileName){
    if (m_ptrModel == nullptr){
        return ControllerReturn::NO_MODEL;
    }
    try{
        Exporter ModelExporter(m_ptrModel, fileName);
        ModelExporter.ExportModel();
        return ControllerReturn::MODEL_EXPORTED;
    }
    catch(const ExceptionInvalidExporterConfig& e){
        return ControllerReturn::INVALID_EXPORTER_CONFIG;
    }
}

ControllerReturn ControllerBase::GetModelInfoList(MdlInfoLst& info_list){
    info_list.clear();
    for (size_t i = 0; i < m_ModelList.size(); i++){
        ModelInfo model_info = {i, m_ModelList[i].model_ptr->Name};
        info_list.push_back(model_info);
    }
    // if (info_list.size() == 0){
        // return ControllerReturn::NO_MODEL;
    // }
    return ControllerReturn::MODEL_INFO_LST_GETTED;
}

ControllerReturn ControllerBase::ActivateModel(size_t ModelIdx){
    if(ModelIdx < m_ModelList.size()){
        m_ptrModel = m_ModelList[ModelIdx].model_ptr;
        if (m_ptrModel == nullptr){
            return ControllerReturn::CANNOT_ACTIVATE_MODEL;
        }
        m_ModelPath = m_ModelList[ModelIdx].path2model;
        return ControllerReturn::MODEL_ACTIVATED;
    }
    else{
        return ControllerReturn::INDEX_OUT_OF_RANGE;
    }

}


/******************FACE**************** */
ControllerReturn ControllerBase::GetFaces(FaceDetailList& face_detail_list){
    if (m_ptrModel->FacesList.size() == 0){
        return ControllerReturn::NO_FACES;
    }
    if (m_ptrModel == nullptr){
        return ControllerReturn::NO_MODEL;
    }
    else{
        for(int i = 0; i < m_ptrModel->FacesList.size(); i++){
            const Face3D& face = m_ptrModel->FacesList[i];
            FaceDetail face_detail;
            face_detail(i, face);
            face_detail_list.push_back(face_detail);
        }
        return ControllerReturn::GET_FACES_INFO;
    }
}

ControllerReturn ControllerBase::DeleteFace(size_t FaceIdx){
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

ControllerReturn ControllerBase::GetFaceInfo(size_t FaceIdx, FaceDetail& face_detail){
    if (FaceIdx >= m_ptrModel->FacesList.size()){
        return ControllerReturn::INDEX_OUT_OF_RANGE;
    }
    else{
        const Face3D& Face = m_ptrModel->FacesList[FaceIdx];
        face_detail(FaceIdx, Face);     // 更新face+detail
        return ControllerReturn::GET_FACE_INFO;
    }
}

ControllerReturn ControllerBase::ModifyPointOfFace(size_t FaceIdx, size_t PointIdx, double x, double y, double z){
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
ControllerReturn ControllerBase::GetLines(LineDetailList& line_detail_list){
    if (m_ptrModel->LinesList.size() == 0){
        return ControllerReturn::NO_LINES;
    }
    if (m_ptrModel == nullptr){
        return ControllerReturn::NO_MODEL;
    }
    else{
        for(int i = 0; i < m_ptrModel->LinesList.size(); i++){
            const Line3D& line = m_ptrModel->LinesList[i];
            LineDetail line_detail;
            line_detail(i, line);
            line_detail_list.push_back(line_detail);
        }
        return ControllerReturn::GET_LINES_INFO;
    }
}

ControllerReturn ControllerBase::DeleteLine(size_t LineIdx){
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

ControllerReturn ControllerBase::GetLineInfo(size_t LineIdx, LineDetail& line_detail){
    if (LineIdx >= m_ptrModel->LinesList.size()){
        return ControllerReturn::INDEX_OUT_OF_RANGE;
    }
    else{
        const Line3D& Line = m_ptrModel->LinesList[LineIdx];
        line_detail(LineIdx, Line);     // 更新face+detail
        return ControllerReturn::GET_LINE_INFO;
    }
}
// abandon
// LineDetail ControllerBase::GetPointsOfLine(size_t LineIdx){
    // if (LineIdx >= m_ptrModel->LinesList.size()){
        // throw ExceptionIndexOutOfRange();
    // }   
    // else{
        // const Line3D& Line = m1_ptrModel->LinesList[LineIdx];
        // LineDetail detail = {LineIdx, Line.PointA.x, Line.PointA.y, Line.PointA.z,
                                      // Line.PointB.x, Line.PointB.y, Line.PointB.z};
        // return detail;
    // }
// }

ControllerReturn ControllerBase::ModifyPointOfLine(size_t LineIdx, size_t PointIdx, double x, double y, double z){
    try{
        m_ptrModel->SetPointOfLine(LineIdx, PointIdx, x, y, z);
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
}


/******************STATISTICAL**************** */
ControllerReturn ControllerBase::GetStatisticalInfo(StatisticalInfo& statistic_info){
    statistic_info.FaceNum           = m_ptrModel->GetTotalFacesNum();
    statistic_info.LineNum           = m_ptrModel->GetTotalLinesNum();
    statistic_info.PointNum          = m_ptrModel->GetTotalPointsNum();
    statistic_info.BoundingBoxVolume = m_ptrModel->GetMinBoundingBox();
    statistic_info.FaceArea          = m_ptrModel->GetTotalFacesArea();
    statistic_info.LineLength        = m_ptrModel->GetTotalLinesLength();
    return ControllerReturn::STATISTICAL_INFO_GETTED;
}
StatisticalInfo ControllerBase::GetStatisticalInfo(){
    StatisticalInfo info;
    info.FaceNum           = m_ptrModel->GetTotalFacesNum();
    info.LineNum           = m_ptrModel->GetTotalLinesNum();
    info.PointNum          = m_ptrModel->GetTotalPointsNum();
    info.BoundingBoxVolume = m_ptrModel->GetMinBoundingBox();
    info.FaceArea          = m_ptrModel->GetTotalFacesArea();
    info.LineLength        = m_ptrModel->GetTotalLinesLength();
    return info;
}

ControllerBase::ControllerBase(){
    m_ptrModel  = nullptr;
    m_ModelPath = "";
}

std::shared_ptr<ControllerBase> ControllerBase::getInstance(){
    // 单例模式
    if(m_ptrController == nullptr){
        m_ptrController = std::shared_ptr<ControllerBase>(new ControllerBase);
    }
    return m_ptrController;
}
