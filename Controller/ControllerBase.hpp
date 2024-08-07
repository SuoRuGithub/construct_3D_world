#include<stdexcept>
#include<string>
#include<cstddef>
#include"../Model/Point3D.hpp"
#include"../Model/Element3D.hpp"
#include"../Model/Face3D.hpp"
#include"../Model/Line3D.hpp"
#include"../Model/Model3D.hpp" 
// #include"../Model/Vector3D.hpp"

#ifndef _CONTROLLERBASE_HPP
#define _CONTROLLERBASE_HPP

#define enum_to_string(x) #x            // 宏定义，可以使用enum_to_string(x)来将枚举变成字符串

// 前向声明
struct StatisticalInfo;
struct PointDetail;
struct LineDetail;
struct FaceDetail;
struct ModelInfoPrivate;
struct ModelInfo;
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
using MdlInfoPrivateList  = std::vector<ModelInfoPrivate>;
using MdlInfoLst          = std::vector<ModelInfo>;

/****************************异常类****************************************
【类名】                    ExceptionUnsupportedFormat
【功能模块和目的】          提供的面在模型中已经存在，会在与面的增删改功能相关的
                            函数中使用

【类名】                    ExceptionInvalidImporterConfig
【功能模块和目的】          提供的Importer设置非法（如使用了不支持的格式，无法
                            打开文件）

【类名】                    ExceptionInvalidExporterConfig
【功能模块和目的】          提供的Exporter设置非法（如使用了不支持的格式，无法
                            打开文件）

【开发者及日期】            张章 2024-7-25
【更改记录】                24-8-6增加了注释
*************************************************************************/
class ExceptionUnsupportedFormat : public std::invalid_argument{
public:
    ExceptionUnsupportedFormat();
};

class ExceptionNoFacesFound : public std::invalid_argument{
public:
    ExceptionNoFacesFound();
};

class ExceptionNoLinesFound : public std::invalid_argument{
public:
    ExceptionNoLinesFound();
};

enum class ControllerReturn{

    NO_FACES,

    GET_ALL_FACE, 
    FACE_DELETED,
    FACE_ADDED,
    FACE_REPEATED,
    GET_POINTS_OF_FACE,
    FACE_NOT_EXIST,
    POINT_OF_FACE_CHANGED,

    FACE_NOT_HAVE_POINT,

    GET_ALL_LINE,
    LINE_DELETED,
    LINE_ADDED,
    LINE_REPEATED,
    GET_POINTS_OF_LINE,
    LINE_NOT_EXIST,
    POINT_OF_LINE_CHANGED,

    NO_LINES,

    GET_FACE_INFO,
    GET_LINE_INFO,

    INDEX_OUT_OF_RANGE,

    MODEL_ACTIVATED,
    LINE_NOT_HAVE_POINT,

    POINTS_REPEATED,

    GET_FACES_INFO,

    MODEL_IMPORTED,
    MODEL_EXPORTED,



    GET_LINES_INFO,

    NO_MODEL,

    INVALID_EXPORTER_CONFIG,
    INVALID_IMPORTER_CONFIG,

    MODEL_INFO_LST_GETTED,

    CANNOT_ACTIVATE_MODEL,

    STATISTICAL_INFO_GETTED
};

const std::string ReturnString[]{
    enum_to_string(GET_ALL_FACE),
    enum_to_string(FACE_DELETED),
    enum_to_string(FACE_ADDED),
    enum_to_string(FACE_REPEATED),
    enum_to_string(GET_POINTS_OF_FACE),
    enum_to_string(FACE_NOT_EXIST),
    enum_to_string(POINT_OF_FACE_CHANGED),

    enum_to_string(FACE_NOT_HAVE_POINT),

    enum_to_string(GET_ALL_LINE),
    enum_to_string(LINE_DELETED),
    enum_to_string(LINE_ADDED),
    enum_to_string(LINE_REPEATED),
    enum_to_string(GET_POINTS_OF_LINE),
    enum_to_string(LINE_NOT_EXIST),
    enum_to_string(POINT_OF_LINE_CHANGED),

    enum_to_string(LINE_NOT_HAVE_POINT),

    enum_to_string(INDEX_OUT_OF_RANGE),

    enum_to_string(POINTS_REPEATE)
};

// 用来存储统计信息，包括点线面的数量，面的面积，线的长度，包围盒体积
struct StatisticalInfo{
    // 提供默认构造函数，创造一个空的StatisticalInfo. View可以初始化一个空的StatisticalInfo，
    // 然后将其传递给ControllerBase
    StatisticalInfo();

    // 重载()运算符，可以直接调用结构体，从模型得到统计信息
    void operator()(ModelPtr ptrModel);
    
    std::string Name;
    size_t FaceNum;
    size_t LineNum;
    size_t PointNum;
    double BoundingBoxVolume;
    double FaceArea;
    double LineLength;
};

struct PointDetail{
    PointDetail();
    PointDetail(const PointDetail& ADetail);
    void operator()(const Point3D& Point);

    double x;
    double y;
    double z;
};

struct LineDetail{
    LineDetail();
    LineDetail(const LineDetail& ADetail);
    void operator()(size_t index, const Line3D& Line);

    size_t idx;
    PointDetail PointsInfo[2];
    double Length;
};

struct FaceDetail{
    FaceDetail();
    FaceDetail(const FaceDetail& ADetail);
    void operator()(size_t index, const Face3D& Face);

    size_t idx;
    PointDetail PointsInfo[3];
    double Area;
    double Length;
};

// ModelInfoPrivate包含模型的敏感信息（路径和指针，Controller用来维护所有模型）
struct ModelInfoPrivate{
    ModelInfoPrivate(const ModelInfoPrivate& model_info) = default;
    ModelPtr model_ptr;
    std::string path2model;
};
// ModelInfo包含模型的普通信息（索引和名字），用来返回给View类给用户展示
struct ModelInfo{
    size_t      idx;
    std::string Name;
};


class ControllerBase{
public:
    // 删除拷贝构造函数和赋值运算符重载
    ControllerBase(const ControllerBase& AController) = delete;
    ControllerBase& operator=(const ControllerBase AController) = delete;
    virtual ~ControllerBase() = default;
    
     
    
    /******************MODEL*************** */
    ControllerReturn ImportModel(std::string& fileName);
    ControllerReturn ExportModel();                       // 导出到当前原来的路径
    ControllerReturn ExportModel(std::string& fileName);  // 指定导出路径
    
    ControllerReturn GetModelInfoList(MdlInfoLst& info_list);
    ControllerReturn ActivateModel(size_t ModelIdx);
    /******************FACE**************** */
    ControllerReturn GetFaces(FaceDetailList& face_detail_list);

    ControllerReturn DeleteFace(size_t FaceIdx);

    ControllerReturn AddFace(double x1, double y1, double z1,
                             double x2, double y2, double z2,
                             double x3, double y3, double z3);

    ControllerReturn GetFaceInfo(size_t FaceIdx, FaceDetail& face_detail);
    FaceDetail GetPointsOfFace(size_t FaceIdx);

    ControllerReturn ModifyPointOfFace(size_t FaceIdx, size_t PointIdx, double x, double y, double z);

    /******************LINE**************** */
    ControllerReturn GetLines(LineDetailList& line_detail_list);
    const std::vector<Line3D>& GetLines();

    ControllerReturn DeleteLine(size_t LineIdx);

    ControllerReturn AddLine(double x1, double y1, double z1,
                             double x2, double y2, double z2);

    ControllerReturn GetLineInfo(size_t LineIdx, LineDetail& line_detail);
    LineDetail GetPointsOfLine(size_t LineIdx);

    ControllerReturn ModifyPointOfLine(size_t LineIdx, size_t PointIdx, double x, double y, double z);

    /******************STATISTICAL**************** */
    ControllerReturn GetStatisticalInfo(StatisticalInfo& statistic_info);
    StatisticalInfo GetStatisticalInfo();

    // 获取控制器指针
    static std::shared_ptr<ControllerBase> getInstance();

    
    
private:
    // 单例
    ControllerBase();
    
    

    // 维护一个包含当前所有模型重要信息（指针，路径）的列表
    MdlInfoPrivateList   m_ModelList;
    // 当前三维模型的指针
    ModelPtr    m_ptrModel;
    // 当前三维模型的存储路径
    std::string m_ModelPath;

    // Controller指针
    static std::shared_ptr<ControllerBase> m_ptrController;
};

#endif