#include<stdexcept>
#include<string>
#include"../Model/Point3D.hpp"
#include"../Model/Element3D.hpp"
#include"../Model/Face3D.hpp"
#include"../Model/Line3D.hpp"
#include"../Model/ModelBase.hpp"
#include"../Model/objModel.hpp"
#include"../Model/Vector3D.hpp"

#ifndef _CONTROLLERBASE_HPP
#define _CONTROLLERBASE_HPP

#define enum_to_string(x) #x            // 宏定义，可以使用enum_to_string(x)来将枚举变成字符串

using PointPtr = std::shared_ptr<Point3D>;
using LinePtr  = std::shared_ptr<Line3D>;
using FacePtr  = std::shared_ptr<Face3D>;
using ModelBasePtr = std::shared_ptr<ModelBase>;

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

    LINE_NOT_HAVE_POINT,

    INDEX_OUT_OF_RANGE,

    POINTS_REPEATED
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
    unsigned int FaceNum;
    unsigned int LineNum;
    unsigned int PointNum;
    double BoundingBoxVolume;
    double FaceArea;
    double LineLength;
};

// 用来显示点线面信息的结构体
struct FaceDetail{
    unsigned int idx;
    double x1;
    double y1;
    double z1;
    double x2;
    double y2;
    double z2;
    double x3;
    double y3;
    double z3;
};

struct LineDetail{
    unsigned int idx;
    double x1;
    double y1;
    double z1;
    double x2;
    double y2;
    double z2;
};

struct PointDetail{
    unsigned int idx;
    double x;
    double y;
    double z;
};

// Controller上传下达，接受用户输入，返回对应的输出给View


class ControllerBase{
public:
    // 从给定的obj文件中创建模型的相关信息，
    ControllerBase(const std::string& objFileName);
    // 将修改后的模型存储在给定的文件中
    virtual ~ControllerBase();

     
    /******************FACE**************** */
    const std::vector<Face3D>& GetFaces();

    ControllerReturn DeleteFace(unsigned int FaceIdx);

    ControllerReturn AddFace(double x1, double y1, double z1,
                             double x2, double y2, double z2,
                             double x3, double y3, double z3);

    FaceDetail GetPointsOfFace(unsigned int FaceIdx);

    ControllerReturn ModifyPointOfFace(unsigned int FaceIdx, unsigned int PointIdx, double x, double y, double z);

    /******************LINE**************** */
    const std::vector<Line3D>& GetLines();

    ControllerReturn DeleteLine(unsigned int LineIdx);

    ControllerReturn AddLine(double x1, double y1, double z1,
                             double x2, double y2, double z2);

    LineDetail GetPointsOfLine(unsigned int LineIdx);

    ControllerReturn ModifyPointOfLine(unsigned int LineIdx, unsigned int PointIdx, double x, double y, double z);

private:
    // 给定的三维模型文件
    std::string m_FileName;
    // 三维模型的指针
    ModelBasePtr    m_ptrModel;         // 在这里设置为基类Model的指针，在构造Controller时会分析文件格式，将Model
};

#endif