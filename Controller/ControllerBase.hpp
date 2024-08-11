/*************************************************************************
【文件名】                  ControllerBase.hpp
【功能模块和目的】          ControllerBase控制器基类的声明
【开发者及日期】            张章 2024-7-28
【更改记录】                24-8-8增加了注释
*************************************************************************/
#include<stdexcept>            // 标准库头文件，用于处理异常
#include<string>               // 标准库头文件，用于处理字符串
#include<cstddef>              // 标准库头文件，定义了几个类型和宏
#include"../Model/Point3D.hpp" // 包含Point3D类的声明
#include"../Model/Face3D.hpp"  // 包含Face3D类的声明
#include"../Model/Line3D.hpp"  // 包含Line3D类的声明
// #include"../Model/Vector3D.hpp"// 包含Vector3D类的声明
#include"../Model/Model3D.hpp" // 包含Model3D类的声明

#ifndef _CONTROLLERBASE_HPP
#define _CONTROLLERBASE_HPP

#define enum_to_string(x) #x            // 宏定义，可以使用enum_to_string(x)来将枚举变成字符串

// 前向声明
struct StatisticalInfo;    // 统计信息结构体的前向声明
struct PointDetail;        // 点详细信息结构体的前向声明
struct LineDetail;         // 线详细信息结构体的前向声明
struct FaceDetail;         // 面详细信息结构体的前向声明
struct ModelInfoPrivate;   // 模型敏感信息结构体的前向声明
struct ModelInfo;          // 模型普通信息机构体的前向声明
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

/***异常类****/
/***********************************************************************
【类名】                    ExceptionUnsupportedFormat
【功能模块和目的】          当输入的文件格式不受支持时抛出此异常
【接口说明】               继承自 std::invalid_argument，提供默认构造函数
【开发者及日期】            张章 2024-7-31
【更改记录】                无
*************************************************************************/
class ExceptionUnsupportedFormat : public std::invalid_argument{
public:
    ExceptionUnsupportedFormat();
};
/***********************************************************************
【类名】                    ExceptionNoFacesFound
【功能模块和目的】          当在模型中找不到任何面时抛出此异常
【接口说明】               继承自 std::invalid_argument，提供默认构造函数
【开发者及日期】            张章 2024-7-31
【更改记录】                无
*************************************************************************/
class ExceptionNoFacesFound : public std::invalid_argument{
public:
    ExceptionNoFacesFound();
};
/***********************************************************************
【类名】                    ExceptionNoLinesFound
【功能模块和目的】          当在模型中找不到任何线时抛出此异常
【接口说明】               继承自 std::invalid_argument，提供默认构造函数
【开发者及日期】            张章 2024-7-31
【更改记录】                无
*************************************************************************/
class ExceptionNoLinesFound : public std::invalid_argument{
public:
    ExceptionNoLinesFound();
};

// 枚举类，定义ControllerBase的返回状态
enum class ControllerReturn{
    /* MODEL */
    NO_MODEL,
    MODEL_ACTIVATED,
    CANNOT_ACTIVATE_MODEL,
    MODEL_IMPORTED,
    MODEL_EXPORTED,
    INVALID_IMPORTER_CONFIG,
    INVALID_EXPORTER_CONFIG,
    MODEL_INFO_LST_GETTED,

    /* FACE */
    NO_FACES,               // 没有找到面
    GET_FACES_INFO,         // 得到所有面的信息
    GET_FACE_INFO,          // 得到指定面的信息
    FACE_DELETED,           // 成功删除面
    FACE_ADDED,             // 成功添加面
    FACE_REPEATED,          // 面重复了
    FACE_NOT_EXIST,         // 面不存在
    POINT_OF_FACE_CHANGED,  // 面的指定点成功被修改
    FACE_NOT_HAVE_POINT,    // 面不含有指定点
    
    /* LINE */
    NO_LINES,               // 没有找到面
    GET_LINES_INFO,         // 得到所有面的信息
    GET_LINE_INFO,          // 得到指定面的信息
    LINE_DELETED,           // 成功删除面
    LINE_ADDED,             // 成功添加面
    LINE_REPEATED,          // 面重复了
    LINE_NOT_EXIST,         // 面不存在
    POINT_OF_LINE_CHANGED,  // 面的指定点成功被修改
    LINE_NOT_HAVE_POINT,    // 面不含有指定点

    /* STATISTICAL */
    STATISTICAL_INFO_GETTED,
    
    /* GENERAL */
    INDEX_OUT_OF_RANGE,
    POINTS_REPEATED
};

const std::string ReturnString[] = {
    enum_to_string(ControllerReturn::NO_MODEL),                // 无模型
    enum_to_string(ControllerReturn::MODEL_ACTIVATED),         // 模型激活成功
    enum_to_string(ControllerReturn::CANNOT_ACTIVATE_MODEL),   // 模型激活失败
    enum_to_string(ControllerReturn::MODEL_IMPORTED),          // 模型导入成功
    enum_to_string(ControllerReturn::MODEL_EXPORTED),          // 模型导出成功
    enum_to_string(ControllerReturn::INVALID_IMPORTER_CONFIG), // 导入配置无效
    enum_to_string(ControllerReturn::INVALID_EXPORTER_CONFIG), // 导出配置无效
    enum_to_string(ControllerReturn::MODEL_INFO_LST_GETTED),   // 获取模型列表成功

    enum_to_string(ControllerReturn::NO_FACES),                // 未找到面
    enum_to_string(ControllerReturn::GET_FACES_INFO),          // 获取所有面信息
    enum_to_string(ControllerReturn::GET_FACE_INFO),           // 获取特定面信息
    enum_to_string(ControllerReturn::FACE_DELETED),            // 面删除成功
    enum_to_string(ControllerReturn::FACE_ADDED),              // 面添加成功
    enum_to_string(ControllerReturn::FACE_REPEATED),           // 面重复
    enum_to_string(ControllerReturn::FACE_NOT_EXIST),          // 面不存在
    enum_to_string(ControllerReturn::POINT_OF_FACE_CHANGED),   // 面顶点修改成功
    enum_to_string(ControllerReturn::FACE_NOT_HAVE_POINT),     // 面不包含指定点
  
    enum_to_string(ControllerReturn::NO_LINES),                // 未找到线
    enum_to_string(ControllerReturn::GET_LINES_INFO),          // 获取所有线信息
    enum_to_string(ControllerReturn::GET_LINE_INFO),           // 获取特定线信息
    enum_to_string(ControllerReturn::LINE_DELETED),            // 线删除成功
    enum_to_string(ControllerReturn::LINE_ADDED),              // 线添加成功
    enum_to_string(ControllerReturn::LINE_REPEATED),           // 线重复
    enum_to_string(ControllerReturn::LINE_NOT_EXIST),          // 线不存在
    enum_to_string(ControllerReturn::POINT_OF_LINE_CHANGED),   // 线端点修改成功
    enum_to_string(ControllerReturn::LINE_NOT_HAVE_POINT),     // 线不包含指定端点

    enum_to_string(ControllerReturn::STATISTICAL_INFO_GETTED), // 获取统计信息成功

    enum_to_string(ControllerReturn::INDEX_OUT_OF_RANGE),      // 索引超出范围
    enum_to_string(ControllerReturn::POINTS_REPEATED)          // 点重复
};

/*************************************************************************
【结构体名】             StatisticalInfo
【功能】             存储统计信息，如模型的面数、线数、点数等
【接口说明】         提供构造函数和重载()运算符，方便从模型获取统计信息
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
struct StatisticalInfo{
    // 提供默认构造函数，创造一个空的StatisticalInfo. View可以初始化一个空的StatisticalInfo，
    // 然后将其传递给ControllerBase
    StatisticalInfo();

    // 重载()运算符，可以直接调用结构体，从模型得到统计信息
    void operator()(ModelPtr ptrModel);
    
    // 模型的名字
    std::string Name;
    // 点线面的数量
    size_t FaceNum;
    size_t LineNum;
    size_t PointNum;
    // 模型的体积、面积和线长
    double BoundingBoxVolume;
    double FaceArea;
    double LineLength;
};

/*************************************************************************
【结构体名】             PointDetail
【功能】             存储点的详细信息
【接口说明】         提供构造函数和重载()运算符，以便从三维点获取点的详细信息
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
struct PointDetail{
    // 提供默认构造函数，用于初始化一个空的PointDetail，View可以初始化一个空的
    // PointDetail，然后将其传递给ControllerBase
    PointDetail();
    // 提供拷贝构造函数，用于拷贝PointDetail
    PointDetail(const PointDetail& ADetail);
    // 重载()运算符，可以直接调用结构体，从三维点得到点的详细信息
    void operator()(const Point3D& Point);

    // 点的坐标
    double x;
    double y;
    double z;
};

/*************************************************************************
【结构体名】             LineDetail
【功能】             存储线的详细信息
【接口说明】         提供构造函数和重载()运算符，以便从三维线获取线的详细信息
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
struct LineDetail{
    // 提供默认构造函数，用于初始化一个空的LineDetail，View可以初始化一个空的
    // LineDetail，然后将其传递给ControllerBase
    LineDetail();
    // 提供拷贝构造函数，用于拷贝LineDetail
    LineDetail(const LineDetail& ADetail);
    // 重载()运算符，可以直接调用结构体，从三维线得到线的详细信息
    void operator()(size_t index, const Line3D& Line);

    size_t idx;
    PointDetail PointsInfo[2];
    double Length;
};

/*************************************************************************
【结构体名】             FaceDetail
【功能】             存储面的详细信息
【接口说明】         提供构造函数和重载()运算符，以便从三维面获取面的详细信息
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
struct FaceDetail{
    // 提供默认构造函数，用于初始化一个空的FaceDetail，View可以初始化一个空的
    // FaceDetail，然后将其传递给ControllerBase
    FaceDetail();
    // 提供拷贝构造函数，用于拷贝FaceDetail
    FaceDetail(const FaceDetail& ADetail);
    // 重载()运算符，可以直接调用结构体，从三维面得到面的详细信息
    void operator()(size_t index, const Face3D& Face);

    size_t idx;                 // 索引
    PointDetail PointsInfo[3];  // 面的点
    double Area;                // 面积
    double Length;              // 周长
};

/*************************************************************************
【结构体名】             ModelInfoPrivate
【功能】             包含模型的敏感信息，包括模型指针和路径
【接口说明】         默认拷贝构造函数
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
struct ModelInfoPrivate{
    // 提供默认构造函数
    ModelInfoPrivate(ModelPtr model_ptr = nullptr, 
                     std::string path2model = "");
    // 默认拷贝构造函数
    ModelInfoPrivate(const ModelInfoPrivate& model_info);

    ModelPtr model_ptr;         // 模型指针
    std::string path2model;     // 模型路径
};

/*************************************************************************
【结构体名】             ModelInfo
【功能】             包含模型的普通信息，如索引和名字
【接口说明】         无
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
struct ModelInfo{
    size_t      idx;    // 模型索引
    std::string Name;   // 模型名字
};

/*************************************************************************
【类名】             ControllerBase
【功能】             控制器基类，封装了对三维模型的所有操作，包括模型的导入导出、
                    模型信息的获取、模型元素（面、线）的增删改查等。
【接口说明】         - ImportModel：根据文件名导入模型。
                    - ExportModel：导出当前模型，可以指定导出路径或使用原始路径。
                    - GetModelInfoList：获取所有模型的信息列表。
                    - ActivateModel：激活指定索引的模型，使其成为当前操作的模型。
                    - GetFaces：获取所有面的信息列表。
                    - DeleteFace：删除指定索引的面。
                    - AddFace：添加一个新的面，需要提供三个顶点的坐标。
                    - GetFaceInfo：获取指定索引的面的详细信息。
                    - ModifyPointOfFace：修改面的一个顶点的位置。
                    - GetLines：获取所有线的详细信息列表。
                    - DeleteLine：删除指定索引的线。
                    - AddLine：添加一条新的线，需要提供两个端点的坐标。
                    - GetLineInfo：获取指定索引的线的详细信息。
                    - ModifyPointOfLine：修改线的一个端点的位置。
                    - GetStatisticalInfo：获取模型的统计信息。
                    - getInstance：获取ControllerBase的单例指针，用于访问控制器。
                    - 私有成员变量m_ModelList、m_ptrModel、m_ModelPath分别用于存储模型列表、当前模型指针和模型路径。
【开发者及日期】    张章 2024-7-31
【更改记录】        无
*************************************************************************/
class ControllerBase{
public:
    // 单例模式，删除拷贝构造函数和赋值运算符重载
    ControllerBase(const ControllerBase& AController) = delete;
    ControllerBase& operator=(const ControllerBase AController) = delete;
    // 提供默认的虚析构函数，方便未来派生
    virtual ~ControllerBase();
    
    /******************MODEL*************** */
    // 导入模型
    ControllerReturn ImportModel(std::string& fileName);
    // 导出模型到默认路径（也即模型导入时的路径）
    ControllerReturn ExportModel();                       // 导出到当前原来的路径
    // 导出模型到指定路径
    ControllerReturn ExportModel(std::string& fileName);  // 指定导出路径
    
    // 获得所有模型的基本信息
    ControllerReturn GetModelInfoList(MdlInfoLst& info_list) const;

    // 激活指定索引的模型
    ControllerReturn ActivateModel(size_t ModelIdx);

    /******************FACE**************** */
    // 得到所有面的信息
    ControllerReturn GetFaces(FaceDetailList& face_detail_list) const;

    // 删除指定面
    ControllerReturn DeleteFace(size_t FaceIdx);

    // 添加一个面
    ControllerReturn AddFace(double x1, double y1, double z1,
                             double x2, double y2, double z2,
                             double x3, double y3, double z3);
    
    // 得到指定面的信息
    ControllerReturn GetFaceInfo(size_t FaceIdx, FaceDetail& face_detail) const;

    // 修改指定面的指定点
    ControllerReturn ModifyPointOfFace(size_t FaceIdx, size_t PointIdx, double x, double y, double z);

    /******************LINE**************** */
    // 得到所有线的信息
    ControllerReturn GetLines(LineDetailList& line_detail_list) const;

    // 删除指定线
    ControllerReturn DeleteLine(size_t LineIdx);

    // 添加一条线
    ControllerReturn AddLine(double x1, double y1, double z1,
                             double x2, double y2, double z2);

    // 返回指定线的信息
    ControllerReturn GetLineInfo(size_t LineIdx, LineDetail& line_detail) const;

    // 修改指定线的指定点
    ControllerReturn ModifyPointOfLine(size_t LineIdx, size_t PointIdx, double x, double y, double z);

    /******************STATISTICAL**************** */
    // 返回当前模型的统计信息
    ControllerReturn GetStatisticalInfo(StatisticalInfo& statistic_info) const;


    /* static getter function*/
    // 获取控制器实例指针
    static std::shared_ptr<ControllerBase> getInstance();
    
private:
    // 单例模式，将构造函数设置为私有
    ControllerBase();

    // 维护一个包含当前所有模型重要信息（指针，路径）的列表
    MdlInfoPrivateList   m_ModelList;

    // 当前三维模型的指针
    ModelPtr    m_ptrModel;
    // 当前三维模型的存储路径
    std::string m_ModelPath;

    // ControllerBase实例的指针，可以通过getInstance获得
    static std::shared_ptr<ControllerBase> m_ptrController;
};

#endif