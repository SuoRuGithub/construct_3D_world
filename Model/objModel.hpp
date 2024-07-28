#include<stdexcept>
#include<memory>
#include<vector>
#include"Point3D.hpp"
#include"Line3D.hpp"
#include"Face3D.hpp"
#include"ModelBase.hpp"

#ifndef _OBJMODEL_HPP
#define _OBJMODEL_HPP

// 定义点线面的智能指针，向controller返回值时只需要返回指针即可
using PointPtr = std::shared_ptr<Point3D>;
using LinePtr  = std::shared_ptr<Line3D>;
using FacePtr  = std::shared_ptr<Face3D>;

/* 异常类 */
// 声明在
class IndexOutOfRange;

class objModel : public ModelBase{
public:
    // 默认构造函数，初始化一个空模型
    objModel();
    // 删除拷贝构造函数和赋值运算符的重载
    objModel(const objModel& AModel)            = delete;
    objModel& operator=(const objModel& AModel) = delete;    
    ~objModel() override;       // 重写虚的析构函数
    
    /* 模型的基本功能 */
    // 导入模型
    void ImportModelFromFile(const std::string& FileName) override;
    // 导出模型
    void ExportModelToFile(const std::string& FileName) override;
    // 渲染模型（本次作业中不会实现，但是渲染本身应该是模型的基本功能）
    void RenderModel() override;

};

#endif





