/*******************************************
 *【文件名】            objModel.hpp
 *【功能模块和目的】    针对obj格式的三维模型类的声明
 *【开发者及日期】      张章 2024-7-22
 *【更改记录】          无
 * *****************************************/

#ifndef _OBJMODEL_HPP
#define _OBJMODEL_HPP

#include<unordered_set>
#include<vector>
#include<string>
#include"Points3D.hpp"
#include"Lines3D.hpp"
#include"Faces3D.hpp"
/******************************************
 *【类名】              objModel3D
 *【功能】              表示一个遵循obj格式的三维模型
 *【接口说明】           
 *                
 *【开发者及日期】      张章  2024-7-22
 *【更改记录】          无
 * ***************************************/

class objModel{
public:
    objModel();
    objModel();
    objModel();
    objModel();
    objModel();
    objModel();
    objModel();
    objModel();
    objModel();


    void LoadModel(const string& FileName) override;
    void ExportModel(const string& FileName) override;
    void RenderModel() override;
    
    /* non-static getters */
    /* non-static setters */
     
private:
    // 维护三个列表，分别包含点、线和面的所有引用
    std::vector<Points3D&>  PointsList;
    std::vector<Lines3D&>   LinesList;
    std::vector<Faces3D&>   FacesList;    
}




