/*************************************************************************
【文件名】                  Model3D.hpp
【功能模块和目的】          Model3D类以及Importer,Exporter,Renderer类的声明
【开发者及日期】            张章 2024-7-25
【更改记录】                24-8-5增加了注释
*************************************************************************/
#include<string>
#include<vector>
#include"Point3D.hpp"
#include"Line3D.hpp"
#include"Face3D.hpp"

#ifndef _MODELBASE_HPP
#define _MODELBASE_HPP

class Model3D;                              // 前向声明

using ModelPtr = std::shared_ptr<Model3D>;  // Model3D的指针

// Note: 
// 设置这些结构体的合理性在于，虽然我们目前只支持format,fileName等简单选项，
// 但是在未来可以通过扩展结构体来轻松扩展对Importer, Exporter 与 Renderer的
// 设置。
struct ImporterConfig{
    ModelPtr     pmodel;     // 模型指针
    std::string  format;     // 导入的文件格式
    std::string  fileName;   // 导入的文件路径
};
struct ExporterConfig{
    ModelPtr     pmodel;     // 模型指针
    std::string  format;     // 导出的文件格式
    std::string  fileName;   // 导出的文件路径
};
struct RendererConfig{
    // pass 本项目不包含渲染的相关实现，只是作为完整性设计了相关接口
};

/****************************异常类****************************************
【类名】                    ExceptionFaceExist
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
class ExceptionFaceExist : public std::invalid_argument{
public:
    ExceptionFaceExist();
};

class ExceptionInvalidImporterConfig : public std::invalid_argument{
public:
    ExceptionInvalidImporterConfig();
};
class ExceptionInvalidExporterConfig : public std::invalid_argument{
public:
    ExceptionInvalidExporterConfig();
};
class ExceptionInvalidRendererConfig : public std::invalid_argument{
public:
    ExceptionInvalidRendererConfig();
};
// Note: 
// Importer, Exporter与Renderer有类似的逻辑，对外提供通用的接口（比如Importer
// 类中的ImportModel）， 而在内部实现上，这些公共接口根据自身的设置(比如
// ImporterConfig)，按照对应逻辑调用合适的私有成员函数(比如，针对obj文件，
// ImportModel函数将会调用ImportobjModel函数)。这样做的合理性在于统一了外部接
// 口，并且使用结构化的变量声明调用逻辑，将调用逻辑与具体功能的实现进行解耦。
// 这有利于未来对功能的扩展。


/*************************************************************************
【类名】                Importer
【功能】                一个三维模型的导入器，可以根据给定的设置参数实现对三维
                        模型的导入
【接口说明】            - 提供了含参构造函数（包括以设置结构体作为参数或以其各
                          成员作为参数），提供了拷贝构造函数和赋值运算符重载
                        - 提供了对外的ImportModel接口，根据设置进行导出操作
                        - 提供了修改Importer设置的接口
                        - 提供了查看设置的结构（设置的常引用）
【开发者及日期】        张章 2024-7-25
【更改记录】            24-8-6 增加了注释
*************************************************************************/
class Importer{
public:
    Importer(ModelPtr pmodel, std::string& fileName, std::string format);
    Importer(ImporterConfig& config);
    Importer(ModelPtr pmodel, std::string& fileName);
    Importer(Importer& AImporter);
    const Importer& operator=(const Importer& AImporter);

    void ImportModel();

    void SetConfig(const ImporterConfig& config);

    const ImporterConfig& config {m_config};
protected:
    bool IsConfigAvailable();
    void ImportobjModel();
    std::string FormatFromPath(std::string fileName);   // 根据输入的文件路径得到文件格式
    ImporterConfig m_config;
};
/*************************************************************************
【类名】                Exporter
【功能】                一个三维模型的导出器，可以根据给定的设置参数实现对三维
                        模型的导出
【接口说明】            - 提供了含参构造函数（包括以设置结构体作为参数或以其各
                          成员作为参数），提供了拷贝构造函数和赋值运算符重载
                        - 提供了对外的ExportModel接口，根据设置进行导出操作
                        - 提供了修改Exporter设置的接口
                        - 提供了查看设置的结构（设置的常引用）
【开发者及日期】        张章 2024-7-25
【更改记录】            24-8-6 增加了注释
*************************************************************************/
class Exporter{
public:
    Exporter(const ModelPtr pmodel, const std::string& format, const std::string& fileName);
    Exporter(const ExporterConfig& config);
    Exporter(const ModelPtr pmodel, const std::string& fileName);
    Exporter(const Exporter& AExporter);

    const Exporter& operator=(const Exporter& AExporter);

    void ExportModel();
    
    void SetConfig(const ExporterConfig& config);

    const ExporterConfig& config {m_config};
protected:
    bool IsConfigAvailable();
    void ExportAsobj();
    std::string FormatFromPath(std::string fileName);
    ExporterConfig m_config;
};
/*************************************************************************
【类名】                Renderer
【功能】                一个三维模型的渲染器，可以根据给定的设置参数实现对三维
                        模型的渲染
【接口说明】            无接口，仅出于完整性声明于此 
【开发者及日期】        张章 2024-7-25
【更改记录】            24-8-6 增加了注释
*************************************************************************/
class Renderer{
    // pass 本项目不包含渲染的相关实现
public:
protected:
    RendererConfig m_config;
};


/*************************************************************************
【类名】                Model3D
【功能】                表示三维模型 
【接口说明】            - 提供默认构造函数，删除拷贝和赋值运算符重载    
                        - 提供修改名称的接口
                        - 提供对线、面进行增删改(修改某一顶点)操作的接口
                        - 提供对线、面的顶点进行查询的接口
                        - 提供对统计信息进行查询的接口（线面总数，最小包围盒
                          体积，总面积，总长度等）
                        - 提供判断给定线面是否已经在模型中存在的接口
                        - 提供直接读取线、面列表的接口（线面列表的常引用）
【开发者及日期】        张章 2024-7-25
【更改记录】            24-8-6 增加了注释
*************************************************************************/
class Model3D{
public:
    // 有一个纯虚的默认构造函数，作用是生成一个空模型
    Model3D();
    // 删除拷贝构造函数、赋值运算符的重载
    Model3D(const Model3D& AModel)            = delete;
    Model3D& operator=(const Model3D& AModel) = delete;    
    // 虚的析构函数
    virtual ~Model3D(); 

    /* non-static setters */
    // 修改模型名字
    void ChangeName(const std::string ModelName);

    // 给定面的索引，删除指定面对象
    void DeleteFace(unsigned int FaceIdx);
    // 给定线的索引，删除指定线对象
    void DeleteLine(unsigned int LineIdx);

    // 给定三个点坐标，向模型中添加一个面
    void AddFace(double x1, double y1, double z1, 
                 double x2, double y2, double z2, 
                 double x3, double y3, double z3);
    // 给定两个点坐标，向模型中添加一个线
    void AddLine(double x1, double y1, double z1,
                 double x2, double y2, double z2); 

    // 改变指定面对象的某一个顶点
    //  给定面的序号和点的指针，如果不是这个面的顶点则抛出异常
    void SetPointOfFace(int FaceIdx, PointPtr ptrPoint, 
                        double x, double y, double z);
    //  给定面的序号和点的序号（1，2，3分别表示PointA，B，C），
    //  如果不是这个面的顶点则抛出异常
    void SetPointOfFace(int FaceIdx, int PointIdx, 
                        double x, double y, double z);

    // 改变指定线对象的某一个顶点
    //  给定点的指针，如果不是这个线的顶点则抛出异常
    void SetPointOfLine(int LineIdx, PointPtr ptrPoint, 
                        double x, double y, double z);
    //  给定点的序号，如果不是这个线的顶点则抛出异常
    void SetPointOfLine(int LineIdx, int PointIdx, 
                        double x, double y, double z);
    
    /* non-static getters*/
    // 得到给定面的三个顶点
    //  给定面的序号
    std::vector<Point3D> GetFacePoints(int idx);

    // 得到给定线的两个顶点
    //  给定线的序号
    std::vector<Point3D> GetLinePoints(int idx);

    // 统计面对象的总数
    int GetTotalFacesNum();
    // 统计线对象的总数
    int GetTotalLinesNum();
    // 统计点对象的总数
    int GetTotalPointsNum();

    // 统计面对象的总面积
    double GetTotalFacesArea();
    // 统计线对象的总长度
    double GetTotalLinesLength();

    // 计算最小包围盒的体积
    double GetMinBoundingBox();

    // 判断线 / 面是否已经存在，防止重复
    bool IsFaceExist(const Face3D& Face);
    bool IsLineExist(const Line3D& Line);

    const std::string&          Name        {m_Name};
    const std::vector<Line3D>&  LinesList   {m_LinesList};
    const std::vector<Face3D>&  FacesList   {m_FacesList};
    
protected:
    // 将Importer, Exporter, Renderer作为友元类
    friend class Importer;
    friend class Exporter;
    friend class Renderer;

    // 模型的名字
    std::string          m_Name;

    // 模型的线面列表（规定模型不允许有不依赖于线面的点，
    // 这样的点在导入时将被忽视）
    std::vector<Line3D>  m_LinesList;
    std::vector<Face3D>  m_FacesList;
};

#endif


