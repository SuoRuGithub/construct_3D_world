/*************************************************************************
【文件名】                  ControllerBase.cpp
【功能模块和目的】          定义了ControllerBase类的成员函数
【开发者及日期】            张章 2024-7-31
【更改记录】                24-8-8增加了注释
*************************************************************************/
#include<cstddef>              // size_t
#include<stdexcept>            // std::invalid_argument
#include<iostream>             // 输入输出
#include<filesystem>           // 文件系统
#include"ControllerBase.hpp"   // ControllerBase类

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

/********异常类******** */
/*************************************************************************
【异常类】             ExceptionUnsupportedFormat
【构造函数功能】    构造一个不支持的格式异常对象
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
ExceptionUnsupportedFormat::ExceptionUnsupportedFormat() 
    : std::invalid_argument("This format is not supported."){
}

/*************************************************************************
【异常类】             ExceptionNoFacesFound
【构造函数功能】    构造一个未找到面异常对象
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
ExceptionNoFacesFound::ExceptionNoFacesFound() 
    : std::invalid_argument("No face is found."){
}

/*************************************************************************
【异常类】             ExceptionNoLinesFound
【构造函数功能】    构造一个未找到线异常对象
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
ExceptionNoLinesFound::ExceptionNoLinesFound() 
    : std::invalid_argument("No line is found."){
}

/********各个结构体******** */
/*************************************************************************
【类名】             StatisticalInfo
【构造函数功能】    构造一个具有默认值的统计信息对象
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
StatisticalInfo::StatisticalInfo()
    : Name(""), FaceNum(0), LineNum(0), PointNum(0), 
      BoundingBoxVolume(0.0), FaceArea(0.0), LineLength(0.0){
}

/*************************************************************************
【函数名称】       operator()
【函数功能】        从模型中提取统计信息并赋值给当前对象
【参数】           ModelPtr ptrModel: 输入参数，指向模型的智能指针
【返回值】         无
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
void StatisticalInfo::operator()(ModelPtr ptrModel){
    Name              = ptrModel->Name;
    FaceNum           = ptrModel->GetTotalFacesNum();
    LineNum           = ptrModel->GetTotalLinesNum();
    PointNum          = ptrModel->GetTotalPointsNum();
    BoundingBoxVolume = ptrModel->GetMinBoundingBox();
    FaceArea          = ptrModel->GetTotalFacesArea();
    LineLength        = ptrModel->GetTotalLinesLength();
}

/*************************************************************************
【类名】             PointDetail
【构造函数功能】    构造一个具有默认坐标(0.0, 0.0, 0.0)的点详细信息对象
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
PointDetail::PointDetail()
    : x(0.0), y(0.0), z(0.0){
}

/*************************************************************************
【类名】             PointDetail
【构造函数功能】    通过复制已有的点详细信息对象来构造新对象
【输入参数】       const PointDetail& ADetail: 输入参数，要复制的点详细信息对象
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
PointDetail::PointDetail(const PointDetail& ADetail){
    x = ADetail.x;
    y = ADetail.y;
    z = ADetail.z;
}

/*************************************************************************
【函数名称】       operator()
【所属类】         PointDetail
【函数功能】       更新点详细信息对象的坐标
【输入参数】       const Point3D& Point: 输入参数，包含新坐标的三维点对象
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
void PointDetail::operator()(const Point3D& Point){
    x = Point.x;
    y = Point.y;
    z = Point.z;
}

/*************************************************************************
【类名】             LineDetail
【构造函数功能】    构造一个具有默认索引和点详细信息的线详细信息对象
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
LineDetail::LineDetail()
    : idx(0), PointsInfo({PointDetail(), PointDetail()}){
}

/*************************************************************************
【类名】             LineDetail
【构造函数功能】    通过复制已有的线详细信息对象来构造新对象
【输入参数】       const LineDetail& ADetail: 输入参数，要复制的线详细信息对象
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
LineDetail::LineDetail(const LineDetail& ADetail){
    idx = ADetail.idx;
    PointsInfo[0] = ADetail.PointsInfo[0];
    PointsInfo[1] = ADetail.PointsInfo[1];
    Length = ADetail.Length;
}

/*************************************************************************
【函数名称】       operator()
【所属类】         LineDetail
【函数功能】       使用线对象的索引和端点更新线详细信息对象
【输入参数】       size_t index: 输入参数，线的索引
【输入参数】       const Line3D& Line: 输入参数，包含端点和长度的线对象
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
void LineDetail::operator()(size_t index, const Line3D& Line){
    idx = index;
    PointsInfo[0](Line.PointA);
    PointsInfo[1](Line.PointB);
    Length = Line.GetLength();
}

/*************************************************************************
【类名】             FaceDetail
【构造函数功能】    构造一个具有默认索引和顶点详细信息的面详细信息对象
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
FaceDetail::FaceDetail()
    : idx {0}, PointsInfo({PointDetail(), PointDetail(), PointDetail()}), 
     Area(0.0){
}

/*************************************************************************
【类名】             FaceDetail
【构造函数功能】    通过复制已有的面详细信息对象来构造新对象
【输入参数】       const FaceDetail& ADetail: 输入参数，要复制的面详细信息对象
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
FaceDetail::FaceDetail(const FaceDetail& ADetail){
    idx = ADetail.idx;
    PointsInfo[0] = ADetail.PointsInfo[0];
    PointsInfo[1] = ADetail.PointsInfo[1];
    PointsInfo[2] = ADetail.PointsInfo[2];
    Area   = ADetail.Area;
    Length = ADetail.Length;
}

/*************************************************************************
【类名】             ModelInfoPrivate
【构造函数功能】    ModelInfoPrivate的带有默认参数的构造函数
【输入参数】       ModelPtr model_ptr = nullptr: 输入参数，模型指针，默认为空
                 std::string path2model = "": 输入参数，模型路径，默认为空
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
ModelInfoPrivate::ModelInfoPrivate(ModelPtr model_ptr, std::string path2model){

    model_ptr  = model_ptr;
    path2model = path2model;
}

/*************************************************************************
【类名】             ModelInfoPrivate
【构造函数功能】    ModelInfoPrivate的复制构造函数
【输入参数】       ModelInfoPrivate& model_info: 输入参数，要复制的模型信息对象
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
ModelInfoPrivate::ModelInfoPrivate(const ModelInfoPrivate& model_info){
    model_ptr  = model_info.model_ptr;
    path2model = model_info.path2model; 
}

/*************************************************************************
【函数名称】       operator()
【所属类】         FaceDetail
【函数功能】       使用面对象的索引和顶点更新面详细信息对象
【输入参数】       size_t index: 输入参数，面的索引
【输入参数】       const Face3D& Face: 输入参数，包含顶点和面积的面对象
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
void FaceDetail::operator()(size_t index, const Face3D& Face){
    idx = index;
    PointsInfo[0](Face.PointA);
    PointsInfo[1](Face.PointB);
    PointsInfo[2](Face.PointC);
    Area   = Face.GetArea();
    Length = Face.GetLength();
}

/********ControllerBase类******** */

ControllerBase::~ControllerBase(){
    m_ptrController.reset();    // 释放空间
}
/*************************************************************************
【函数名称】       ImportModel
【函数功能】       导入模型
【参数】           std::string& fileName: 输入参数，模型文件的名称
【返回值】         ControllerReturn: 返回值，导入操作的结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
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

/*************************************************************************
【函数名称】       ExportModel
【函数功能】       导出当前激活的模型
【返回值】         ControllerReturn: 导出操作的结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
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

/*************************************************************************
【函数名称】       ExportModel
【函数功能】       导出当前激活的模型
【返回值】         ControllerReturn: 导出操作的结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
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

/*************************************************************************
【函数名称】       GetStatisticalInfo
【函数功能】       获取当前激活模型的统计信息
【输出参数】       StatisticalInfo& statistic_info: 存储统计信息的对象
【返回值】         ControllerReturn: 操作结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
ControllerReturn ControllerBase::GetModelInfoList(MdlInfoLst& info_list) const{
    info_list.clear();
    for (size_t i = 0; i < m_ModelList.size(); i++){
        ModelInfo model_info = {i, m_ModelList[i].model_ptr->Name};
        info_list.push_back(model_info);
    }
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
/*************************************************************************
【函数名称】       GetFaces
【函数功能】       获取模型中所有面的详细信息列表
【输出参数】       FaceDetailList& face_detail_list: 输出参数，存储面详细信息的列表
【返回值】         ControllerReturn: 操作结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
ControllerReturn ControllerBase::GetFaces(FaceDetailList& face_detail_list) const{
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

/*************************************************************************
【函数名称】       DeleteFace
【函数功能】       根据索引删除模型中的面
【输入参数】       size_t FaceIdx: 要删除的面的索引
【返回值】         ControllerReturn: 操作结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
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

/*************************************************************************
【函数名称】       AddFace
【函数功能】       向模型中添加一个新的面
【参数】
【输入参数】       double x1, y1, z1: 第一个顶点的坐标
【输入参数】       double x2, y2, z2: 第二个顶点的坐标
【输入参数】       double x3, y3, z3: 第三个顶点的坐标
【返回值】         ControllerReturn: 操作结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
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

/*************************************************************************
【函数名称】       GetFaceInfo
【函数功能】       获取模型中指定索引的面的详细信息
【输入参数】       size_t FaceIdx: 要获取信息的面的索引
【输出参数】       FaceDetail& face_detail: 存储面详细信息的对象
【返回值】         ControllerReturn: 操作结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
ControllerReturn ControllerBase::GetFaceInfo(size_t FaceIdx, 
    FaceDetail& face_detail) const{

    if (FaceIdx >= m_ptrModel->FacesList.size()){
        return ControllerReturn::INDEX_OUT_OF_RANGE;
    }
    else{
        const Face3D& Face = m_ptrModel->FacesList[FaceIdx];
        face_detail(FaceIdx, Face);     // 更新face+detail
        return ControllerReturn::GET_FACE_INFO;
    }
}

/*************************************************************************
【函数名称】       ModifyPointOfFace
【函数功能】       修改模型中指定面的特定顶点的坐标
【参数】
【输入参数】       size_t FaceIdx: 要修改的面的索引
【输入参数】       size_t PointIdx: 要修改的顶点的索引
【输入参数】       double x, y, z: 新的顶点坐标
【返回值】         ControllerReturn: 操作结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
ControllerReturn ControllerBase::ModifyPointOfFace(size_t FaceIdx, 
    size_t PointIdx, double x, double y, double z){

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
}

/******************LINE**************** */
/*************************************************************************
【函数名称】       GetLines
【函数功能】       获取模型中所有线的详细信息列表
【输出参数】       LineDetailList& line_detail_list: 输出参数，存储线详细信息的列表
【返回值】         ControllerReturn: 操作结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
ControllerReturn ControllerBase::GetLines(
    LineDetailList& line_detail_list) const{
        
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

/*************************************************************************
【函数名称】       DeleteLine
【函数功能】       根据索引删除模型中的线
【输入参数】       size_t LineIdx: 要删除的线的索引
【返回值】         ControllerReturn: 操作结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
ControllerReturn ControllerBase::DeleteLine(size_t LineIdx){
    if (LineIdx < m_ptrModel->LinesList.size()){
        m_ptrModel->DeleteLine(LineIdx);
        return ControllerReturn::LINE_DELETED;
    }
    else{
        return ControllerReturn::INDEX_OUT_OF_RANGE;
    }
}

/*************************************************************************
【函数名称】       AddLine
【函数功能】       向模型中添加一条新的线
【参数】
【输入参数】       double x1, y1, z1: 线的一个端点的坐标
【输入参数】       double x2, y2, z2: 线的另一个端点的坐标
【返回值】         ControllerReturn: 操作结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
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

/*************************************************************************
【函数名称】       GetLineInfo
【函数功能】       获取模型中指定索引的线的详细信息
【输入参数】       size_t LineIdx: 要获取信息的线的索引
【输出参数】       LineDetail& line_detail: 存储线详细信息的对象
【返回值】         ControllerReturn: 操作结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
ControllerReturn ControllerBase::GetLineInfo(size_t LineIdx, 
    LineDetail& line_detail) const{

    if (LineIdx >= m_ptrModel->LinesList.size()){
        return ControllerReturn::INDEX_OUT_OF_RANGE;
    }
    else{
        const Line3D& Line = m_ptrModel->LinesList[LineIdx];
        line_detail(LineIdx, Line);     // 更新face+detail
        return ControllerReturn::GET_LINE_INFO;
    }
}

/*************************************************************************
【函数名称】       ModifyPointOfLine
【函数功能】       修改模型中指定线的特定端点的坐标
【参数】
【输入参数】       size_t LineIdx: 要修改的线的索引
【输入参数】       size_t PointIdx: 要修改的端点的索引
【输入参数】       double x, y, z: 新的端点坐标
【返回值】         ControllerReturn: 操作结果
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
ControllerReturn ControllerBase::ModifyPointOfLine(size_t LineIdx, 
    size_t PointIdx, double x, double y, double z){

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
/*************************************************************************
【函数名称】       GetStatisticalInfo
【函数功能】       获取当前激活模型的统计信息
【输出参数】       StatisticalInfo& statistic_info: 输出参数，用于接收统计信息
【返回值】         ControllerReturn: 操作结果，表示是否成功获取统计信息
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
ControllerReturn ControllerBase::GetStatisticalInfo(
    StatisticalInfo& statistic_info) const{
        
    statistic_info.FaceNum           = m_ptrModel->GetTotalFacesNum();
    statistic_info.LineNum           = m_ptrModel->GetTotalLinesNum();
    statistic_info.PointNum          = m_ptrModel->GetTotalPointsNum();
    statistic_info.BoundingBoxVolume = m_ptrModel->GetMinBoundingBox();
    statistic_info.FaceArea          = m_ptrModel->GetTotalFacesArea();
    statistic_info.LineLength        = m_ptrModel->GetTotalLinesLength();
    return ControllerReturn::STATISTICAL_INFO_GETTED;
}

/*************************************************************************
【类名】             ControllerBase
【构造函数功能】    构造ControllerBase类的实例，初始化时模型指针和模型路径为空
【参数】
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
ControllerBase::ControllerBase(){
    m_ptrModel  = nullptr;
    m_ModelPath = "";
}

/*************************************************************************
【函数名称】       getInstance
【函数功能】       提供ControllerBase类的单例访问
【功能说明】       使用单例模式确保全局只有一个ControllerBase实例
【返回值】         std::shared_ptr<ControllerBase>: ControllerBase类的单例实例的共享指针
【开发者及日期】  张章 2024-7-31
【更改记录】       无
*************************************************************************/
std::shared_ptr<ControllerBase> ControllerBase::getInstance(){
    // 单例模式
    if(m_ptrController == nullptr){
        m_ptrController = std::shared_ptr<ControllerBase>(new ControllerBase);
    }
    return m_ptrController;
}
