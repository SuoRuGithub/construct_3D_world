/*************************************************************************
【文件名】                  Model3D.cpp
【功能模块和目的】          Model3D类以及Importer, Exporter, Renderer类的定义
【开发者及日期】            张章 2024-7-25
【更改记录】                24-8-6增加了注释
*************************************************************************/
#include<algorithm>
#include<limits>
#include<sstream>
#include<string>
#include<fstream>
#include<vector>
#include"Model3D.hpp"
#include"Point3D.hpp"
#include"Line3D.hpp"
#include"Face3D.hpp"

// 点线面模型的指针
using PointPtr = std::shared_ptr<Point3D>;
using LinePtr  = std::shared_ptr<Line3D>;
using FacePtr  = std::shared_ptr<Face3D>;
using ModelPtr = std::shared_ptr<Model3D>;

// 支持的文件格式，在未来可以继续添加
std::vector<std::string> SUPPORTED_FORMAT = {"obj"};

/******************************异常类*************************************/
ExceptionFaceExist::ExceptionFaceExist() 
    : std::invalid_argument("Face exist"){
}
ExceptionInvalidImporterConfig::ExceptionInvalidImporterConfig()
    : std::invalid_argument("Invalid Importer configuration!"){
}
ExceptionInvalidExporterConfig::ExceptionInvalidExporterConfig()
    : std::invalid_argument("Invalid Exporter configuration!"){
}
ExceptionInvalidRendererConfig::ExceptionInvalidRendererConfig()
    : std::invalid_argument("Invalid Renderer configuration!"){
}

/*********************Importer, Exporter, Renderer*************************/

/* Importer */

/*************************************************************************
【函数名称】       Importer
【函数功能】       Importer类的含参构造函数和拷贝构造函数
【参数】          【含参构造函数1】
                      ModelPtr pmodel, string format, string fileName: 表示模型
                      指针，模型格式，模型文件名
                  【含参构造函数2】
                      ImporterConfig& config: 表示对导入器的设置，该结构体包括
                      模型指针，模型格式，模型文件名参数
                  【含参构造函数3】
                       ModelPtr pmodel: 模型指针
                       std::string& fileName: 文件路径，文件的格式将由文件名获得
                  【拷贝构造函数】
                      Importer& AImporter: 表示希望被拷贝的导入器
【返回值】         无
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
Importer::Importer(ModelPtr pmodel, std::string& fileName, std::string format){
    m_config.pmodel   = pmodel;
    m_config.fileName = fileName;
    m_config.format   = format;
}
Importer::Importer(ImporterConfig& config)
                   : m_config {config}{
}
Importer::Importer(ModelPtr pmodel, std::string& fileName){
    m_config.pmodel   = pmodel;
    m_config.fileName = fileName;
    m_config.format   = FormatFromPath(fileName);
    
}
Importer::Importer(Importer& AImporter)
                   : m_config {AImporter.config}{
}
/*************************************************************************
【函数名称】       operator=
【函数功能】       Importer类的赋值运算符重载
【参数】           const Importer& AImporter: 希望赋值的导入器的引用 
【返回值】         无
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
const Importer& Importer::operator=(const Importer& AImporter){
    if (this != &AImporter){
        m_config.pmodel   = AImporter.config.pmodel;
        m_config.format   = AImporter.config.format;
        m_config.fileName = AImporter.config.fileName;
    }
    return *this;
}

/*************************************************************************
【函数名称】       ImportModel
【函数功能】       根据设置，导入模型
【参数】           无
【返回值】         void 
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
void Importer::ImportModel(){
    // 检查设置是否合法
    if (!IsConfigAvailable()){
        throw ExceptionInvalidImporterConfig();
    }
    // 目前只支持一种格式
    if (m_config.format == "obj"){
        ImportobjModel();
    }
}

/*************************************************************************
【函数名称】       IsConfigAvailable
【函数功能】       检查导入器的设置是否合法（）
【参数】           无
【返回值】         void 
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
bool Importer::IsConfigAvailable(){
    std::ifstream File(m_config.fileName);
    if (!File.is_open()){
        std::ofstream NewFile(m_config.fileName);
        if (!NewFile.is_open()){
            return false;
        }
    }
    
    if (std::find(SUPPORTED_FORMAT.begin(), SUPPORTED_FORMAT.end(), m_config.format) 
        == SUPPORTED_FORMAT.end()){
        return false;
    }

    return true;
}

/*************************************************************************
【函数名称】       ImportobjModel
【函数功能】       根据设置，导入obj模型
【参数】           无
【返回值】         void 
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
void Importer::ImportobjModel(){
    std::ifstream File(m_config.fileName);

    std::vector<Point3D> PointsList;    // PointsList并不作为Model3D的数据成员，
                                        // 只会在导入 / 导出模型的时候临时构造

    // 从文件中每次读取一行，从每一行读取内容
    std::string line;
    while (getline(File, line)){
        // 构造一个字符串流
        std::istringstream LineString(line);
        char type;
        LineString >> type;
        switch (type){
            case '#':
                break;
            case 'g':{                  // 使用{}声明变量作用域，否则报错
                LineString >> m_config.pmodel->m_Name;
                break;
            }
            case 'v':{
                double x = 0.0;
                double y = 0.0;
                double z = 0.0;
                LineString >> x;
                LineString >> y;
                LineString >> z;
                Point3D Point(x, y, z);
                PointsList.push_back(Point);               
                break;
            }
            case 'l':{
                int idx1 = 0;
                int idx2 = 0;
                LineString >> idx1;
                LineString >> idx2;
                Line3D Line(PointsList[idx1 - 1], PointsList[idx2 - 1]); 
                m_config.pmodel->m_LinesList.push_back(std::move(Line));
                break;
            }
            case 'f':{
                int idx1 = 0;
                int idx2 = 0;
                int idx3 = 0;
                LineString >> idx1;
                LineString >> idx2;
                LineString >> idx3;
                Face3D Face(PointsList[idx1 - 1], PointsList[idx2 - 1], 
                            PointsList[idx3 - 1]);
                m_config.pmodel->m_FacesList.push_back(std::move(Face));
                break;
            }
            default:
                break;
        }
    }

}

/*************************************************************************
【函数名称】       FormatFromPath
【函数功能】       根据文件名得到文件格式
【参数】           std::string fileName: 文件名
【返回值】         std::string
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
std::string Importer::FormatFromPath(std::string fileName){
    // 目前的文件格式非常简单，只有obj，未来可能需要根据更加复杂的匹配规则得到文件的格式
    return fileName = fileName.substr(fileName.length() - 3);
}

/* Exporter */

/*************************************************************************
【函数名称】       Exporter
【函数功能】       Exporter类的含参构造函数和拷贝构造函数
【参数】          【含参构造函数1】
                      ModelPtr pmodel, string format, string fileName: 表示模型
                      指针，模型格式，模型文件名
                  【含参构造函数2】
                      ExporterConfig& config: 表示对导出器的设置，该结构体包括
                      模型指针，模型格式，模型文件名参数
                  【含参构造函数3】
                       ModelPtr pmodel: 模型指针
                       string fileName: 文件名字，文件格式将通过文件名得到
                  【拷贝构造函数】
                      Exporter& AExporter: 表示希望被拷贝的导出器
【返回值】         无
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
Exporter::Exporter(ModelPtr pmodel, const std::string& format, 
                   const std::string& fileName)
                   : m_config {pmodel, format, fileName}{
}
Exporter::Exporter(const ExporterConfig& config)
                   : m_config {config}{
}
Exporter::Exporter(const ModelPtr pmodel, const std::string& fileName){
    m_config.pmodel   = pmodel;
    m_config.fileName = fileName;
    m_config.format   = FormatFromPath(fileName);
}
Exporter::Exporter(const Exporter& AExporter)
                   : m_config {AExporter.config}{
}
/*************************************************************************
【函数名称】       operator=
【函数功能】       Exporter类的赋值运算符重载
【参数】           const Exporter& AExporter: 希望赋值的导出器的引用 
【返回值】         无
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
const Exporter& Exporter::operator=(const Exporter& AExporter){
    if (this != &AExporter){
        m_config.pmodel   = AExporter.config.pmodel;
        m_config.format   = AExporter.config.format;
        m_config.fileName = AExporter.config.fileName;
    }
    return *this;
}

/*************************************************************************
【函数名称】       ExportModel
【函数功能】       根据设置，导出模型
【参数】           无
【返回值】         void 
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
void Exporter::ExportModel(){
    if (!IsConfigAvailable()){
        throw ExceptionInvalidExporterConfig();
    }
    
    if (m_config.format == "obj"){
        ExportAsobj();
    }
}

/*************************************************************************
【函数名称】       IsConfigAvailable
【函数功能】       检查导出器的设置是否合法（）
【参数】           无
【返回值】         void 
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
bool Exporter::IsConfigAvailable(){
    std::ofstream File(m_config.fileName);
    if (!File.is_open()){
        return false;
    }
    
    if (std::find(SUPPORTED_FORMAT.begin(), SUPPORTED_FORMAT.end(), m_config.format) 
        == SUPPORTED_FORMAT.end()){
        return false;
    }

    return true;
}

/*************************************************************************
【函数名称】       ExportobjModel
【函数功能】       根据设置，导出obj模型
【参数】           无
【返回值】         void 
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
void Exporter::ExportAsobj(){
    std::ofstream File(m_config.fileName);

    std::vector<Point3D> PointsList;    // 所有点的列表（避免重复）
    std::vector<int>     LineIdx;       // 线的顶点的索引
    std::vector<int>     FaceIdx;       // 面的顶点的索引
    
    
    auto AddPointAndIdx = [&PointsList](std::vector<int>& IdxList, 
                                        const Point3D& point){
        auto it = std::find(PointsList.begin(), PointsList.end(), point);
        if (it == PointsList.end()){
            PointsList.push_back(point);
            IdxList.push_back(PointsList.size());
        }
        else{
            int Idx = (it - PointsList.begin()) + 1;
            IdxList.push_back(Idx);
        }
    };
    auto AddLinePointsAndIdx = [&](const Line3D& line){
        AddPointAndIdx(LineIdx, line.PointA);
        AddPointAndIdx(LineIdx, line.PointB);
    };
    auto AddFacePointsAndIdx = [&](const Face3D& face){
        AddPointAndIdx(FaceIdx, face.PointA);
        AddPointAndIdx(FaceIdx, face.PointB);
        AddPointAndIdx(FaceIdx, face.PointC);
    };

    std::for_each(m_config.pmodel->m_LinesList.begin(), 
                  m_config.pmodel->m_LinesList.end(), AddLinePointsAndIdx);
    std::for_each(m_config.pmodel->m_FacesList.begin(), 
                  m_config.pmodel->m_FacesList.end(), AddFacePointsAndIdx);
    

    // 开始导出
    //  名字
    File << "g " << m_config.pmodel->m_Name << std::endl;
    //  点
    auto PointSaver = [&File](Point3D& point){
        File << "v " << point.x << " " << point.y << " " << point.z <<std::endl;
    };
    std::for_each(PointsList.begin(), PointsList.end(), PointSaver);
    //  线
    if (LineIdx.size() % 2 != 0){
        throw std::invalid_argument(
            "Error! Numbers of vertices of lines cannot be devided by 2!");
    }
    if (LineIdx.size() != 0){
        for (int i = 0; i < LineIdx.size(); i += 2){
            File << "l " << LineIdx[i] << " " << LineIdx[i + 1] << std::endl;
        }
    }
    //  面
    if (FaceIdx.size() % 3 != 0){
        throw std::invalid_argument(
            "Error! Numbers of vertices of faces cannot be devided by 3!");
    }
    if (FaceIdx.size() != 0){
        for (int i = 0; i < FaceIdx.size(); i += 3){
            File << "f " << FaceIdx[i] << " " << FaceIdx[i + 1] << 
            " " << FaceIdx[i + 2] << std::endl;
        }
    }
}


/*************************************************************************
【函数名称】       FormatFromPath
【函数功能】       根据文件名得到文件格式
【参数】           std::string fileName: 文件名
【返回值】         std::string
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
std::string Exporter::FormatFromPath(std::string fileName){
    // 目前的文件格式非常简单，只有obj，未来可能需要根据更加复杂的匹配规则得到文件的格式
    return fileName = fileName.substr(fileName.length() - 3);
}

/*****************************Model3D******************************** */


/*************************************************************************
【函数名称】       Model3D
【函数功能】       初始化一个空模型
【参数】           无
【返回值】         无 
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
Model3D::Model3D(){
}

/*************************************************************************
【函数名称】       ~Model3D 
【函数功能】       Model3D的析构函数 
【参数】           无
【返回值】         无
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
Model3D::~Model3D(){
}


/* non-static setters*/

/*************************************************************************
【函数名称】       ChangeName
【函数功能】       设置模型名称
【参数】           const string ModelName: 表示希望修改的名称
【返回值】         void
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
void Model3D::ChangeName(const std::string ModelName){
    m_Name = ModelName;
}

/*************************************************************************
【函数名称】       DeleteFace / DeleteLine
【函数功能】       删除对应面 / 线
【参数】           【DeleteFace】 size_t FaceIdx: 表示面对应的索引
                   【DeleteLine】 size_t LineIdx: 表示线对应的索引
【返回值】         void 
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
void Model3D::DeleteFace(unsigned int FaceIdx){
    if (FaceIdx >= m_FacesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    m_FacesList.erase(m_FacesList.begin() + FaceIdx);
}
void Model3D::DeleteLine(unsigned int LineIdx){
    if (LineIdx >= m_LinesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    m_LinesList.erase(m_LinesList.begin() + LineIdx);
}


/*************************************************************************
【函数名称】       AddFace / AddLine
【函数功能】       增加一个点 / 线
【参数】           【AddFace】 double x1, y1, z1, x2, y2, z2, x3, y3, z3
                               表示三个顶点的坐标
                   【AddLine】 double x1, y1, z1, x2, y2, z2
                               表示两个点的坐标
【返回值】         void 
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
void Model3D::AddFace(double x1, double y1, double z1, 
                        double x2, double y2, double z2, 
                        double x3, double y3, double z3){

    Point3D Point1(x1, y1, z1);
    Point3D Point2(x2, y2, z2);
    Point3D Point3(x3, y3, z3);
    if (Point1 == Point2 || Point1 == Point3 || Point2 == Point3){
        throw ExceptionPointsRepeated();
    }
    Face3D  Face(Point1, Point2, Point3);
    if (IsFaceExist(Face)){
        throw ExceptionFaceExist();
    }
    m_FacesList.push_back(std::move(Face));     // 删除了拷贝构造，使用移动构造
}
void Model3D::AddLine(double x1, double y1, double z1,
                        double x2, double y2, double z2){
    
    Point3D Point1(x1, y1, z1);
    Point3D Point2(x2, y2, z2);
    Line3D  Line(Point1, Point2);
    if (IsLineExist(Line)){
        throw ExceptionLineExist();
    }
    m_LinesList.push_back(std::move(Line));
}


/*************************************************************************
【函数名称】       SetPointOfFace
【函数功能】       设置面的某一个点
【参数】           【1】size_t FaceIdx:     表示面的索引
                        PointPtr ptrPoint:  表示点的指针
                        double x, y, z:     表示修改后点的坐标
                   【2】size_t FaceIdx:     表示面的索引
                        size_t PointIdx:    表示点的索引
                        double x, y, z:     表示修改后点的坐标
【返回值】         void 
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
void Model3D::SetPointOfFace(int FaceIdx, PointPtr ptrPoint, double x, double y, double z){
    if (FaceIdx < 0 || FaceIdx >= m_FacesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    else{
        FacePtr ptrFace(&m_FacesList[FaceIdx]);
        ptrFace->SetPoint(ptrPoint, x, y, z);
    }
}
void Model3D::SetPointOfFace(int FaceIdx, int PointIdx, double x, double y, double z){
    if (FaceIdx < 0 || FaceIdx >= m_FacesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    else{
        m_FacesList[FaceIdx].SetPoint(PointIdx, x, y, z);
    }
}

/*************************************************************************
【函数名称】       SetPointOfLine
【函数功能】       设置线的某一个点
【参数】           【1】size_t LineIdx:     表示线的索引
                        PointPtr ptrPoint:  表示点的指针
                        double x, y, z:     表示修改后点的坐标
                   【2】size_t LineIdx:     表示线的索引
                        size_t PointIdx:    表示点的索引
                        double x, y, z:     表示修改后点的坐标
【返回值】         void 
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
void Model3D::SetPointOfLine(int LineIdx, PointPtr ptrPoint, double x, double y, double z){
    if (LineIdx < 0 || LineIdx >= m_LinesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    else{
        LinePtr ptrLine(&m_LinesList[LineIdx]);
        ptrLine->SetPoint(ptrPoint, x, y, z);
    }
}
void Model3D::SetPointOfLine(int LineIdx, int PointIdx, double x, double y, double z){
    if (LineIdx < 0 || LineIdx >= m_LinesList.size()){
        throw ExceptionIndexOutOfRange();
    }
    else{
        m_LinesList[LineIdx].SetPoint(PointIdx, x, y, z);
    }
}


/* non-static getters */

/*************************************************************************
【函数名称】       GetFacePoints / GetLinePoints
【函数功能】       返回指定面 / 线的三个点
【参数】           size_t idx: 表示面 / 线的索引
【返回值】         std::vector<Point3D>: 一个动态数组，包含面 / 线的顶点
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
std::vector<Point3D> Model3D::GetFacePoints(int idx){
    // 为了避免面的重复，我们删除了面的赋值运算符重载，
    // 对面的操作需要使用指针进行
    FacePtr ptrFace(&m_FacesList[idx]);
    Point3D PointA = ptrFace->PointA;
    Point3D PointB = ptrFace->PointB;
    Point3D PointC = ptrFace->PointC;
    std::vector<Point3D> FacePoint;
    FacePoint.push_back(PointA);
    FacePoint.push_back(PointB);
    FacePoint.push_back(PointC);
    return FacePoint;
}
std::vector<Point3D> Model3D::GetLinePoints(int idx){
    LinePtr ptrLine(&m_LinesList[idx]);
    Point3D PointA = ptrLine->PointA;
    Point3D PointB = ptrLine->PointB;
    std::vector<Point3D> LinePoint;
    LinePoint.push_back(PointA);
    LinePoint.push_back(PointB);
    return LinePoint;
}

/*************************************************************************
【函数名称】       GetTotalFacesNum / GetTotalLinesNum / GetTotalPointsNum
【函数功能】       得到面 / 线 / 点的总数
【参数】           无
【返回值】         size_t: 表示面 / 线 / 点的总数
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
int Model3D::GetTotalFacesNum(){
    return m_FacesList.size();
}
int Model3D::GetTotalLinesNum(){
    return m_LinesList.size();
}
int Model3D::GetTotalPointsNum(){
    // 空间坐标重复的顶点需要重复计数，所以点的总数其实是 面 * 3 + 线 * 2
    return m_FacesList.size() * 3 + m_LinesList.size() * 2;
}

/*************************************************************************
【函数名称】       GetTotalFacesArea / GetTotalLinesLength
【函数功能】       得到面的总面积 / 线的总长度
【参数】           无
【返回值】         double: 表示总面积 / 长度
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
double Model3D::GetTotalFacesArea(){
    double TotalArea = 0.0;
    // 使用Lambda表达式
    auto Accumulator = [&TotalArea](const Face3D& face){TotalArea += face.GetArea();};
    std::for_each(m_FacesList.begin(), m_FacesList.end(), Accumulator);
    return TotalArea;
}
double Model3D::GetTotalLinesLength(){
    double TotalLength = 0.0;
    auto Accumulator = [&TotalLength](const Line3D& line){TotalLength += line.GetLength();};
    std::for_each(m_LinesList.begin(), m_LinesList.end(), Accumulator);
    return TotalLength;
}

/*************************************************************************
【函数名称】       GetMinBoundingBox
【函数功能】       得到最小包围盒的体积
【参数】           无
【返回值】         double: 表示最小包围盒的体积
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
double Model3D::GetMinBoundingBox(){
    double xMin =  std::numeric_limits<double>::infinity();
    double xMax = -std::numeric_limits<double>::infinity();
    double yMin =  std::numeric_limits<double>::infinity();
    double yMax = -std::numeric_limits<double>::infinity();
    double zMin =  std::numeric_limits<double>::infinity();
    double zMax = -std::numeric_limits<double>::infinity();
    
    auto updateBounds        = [&](double& min, double& max, double value){
        min = std::min(min, value);
        max = std::max(max, value);
    };
    auto updateBoundsOfPoint = [&](const Point3D& point){
        updateBounds(xMin, xMax, point.x);
        updateBounds(yMin, yMax, point.y);
        updateBounds(zMin, zMax, point.z);
    };

    for (Face3D& face : m_FacesList){
        updateBoundsOfPoint(face.PointA);
        updateBoundsOfPoint(face.PointB);
        updateBoundsOfPoint(face.PointC);
    }
    for (Line3D& line : m_LinesList){
        updateBoundsOfPoint(line.PointA);
        updateBoundsOfPoint(line.PointB);
    }

    double Volume = (xMax - xMin) * (yMax - yMin) * (zMax - zMin);

    return Volume;
}


/*************************************************************************
【函数名称】       IsFaceExist / IsLineExist
【函数功能】       判断面 / 线是否已在模型中存在
【参数】           【IsFaceExist】const Face3D& Face: 另一个面的常引用
                   【IsLineExist】cosnt Line3D& Line: 另一个线的常引用
【返回值】         bool: 如果已存在则返回true，反之false 
【开发者及日期】   张章 2024-7-25
【更改记录】       24-8-6增加了注释
*************************************************************************/
bool Model3D::IsFaceExist(const Face3D& Face){
    auto it =  std::find(m_FacesList.begin(), m_FacesList.end(), Face);
    if (it == m_FacesList.end()){
        return false;
    }
    else{
        return true;
    }
}
bool Model3D::IsLineExist(const Line3D& Line){
    auto it =  std::find(m_LinesList.begin(), m_LinesList.end(), Line);
    if (it == m_LinesList.end()){
        return false;
    }
    else{
        return true;
    }
}
