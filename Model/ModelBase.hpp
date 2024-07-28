#include<vector>
#include"Point3D.hpp"
#include"Line3D.hpp"
#include"Face3D.hpp"

#ifndef _MODELBASE_HPP
#define _MODELBASE_HPP

// 一个模型，最基本的数据成员应该包括点线面，最基本的成员函数应该包括导入、导出和渲染（虽然渲染我们在本次作业中并不会给出实现）
class ModelBase{
public:
    // 有一个纯虚的默认构造函数，作用是生成一个空模型
    ModelBase();
    // 删除拷贝构造函数、赋值运算符的重载
    ModelBase(const ModelBase& AModel)            = delete;
    ModelBase& operator=(const ModelBase& AModel) = delete;    
    // 虚的析构函数
    virtual ~ModelBase();

    // 导入模型
    virtual void ImportModelFromFile(const std::string& FileName) = 0;
    // 导出模型
    virtual void ExportModelToFile(const std::string& FileName)   = 0;
    // 渲染模型（本次作业中不会实现）
    virtual void RenderModel() = 0;

protected:
    // 模型的名字
    std::string          m_Name;
    // 模型的点线面列表
    // std::vector<Point3D> m_PointsList;   // 规定模型不拥有的点而只拥有线和面，在导入模型时单独的点会被忽略
    std::vector<Line3D>  m_LinesList;
    std::vector<Face3D>  m_FacesList;
};

#endif


