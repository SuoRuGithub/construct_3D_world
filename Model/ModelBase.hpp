/*******************************************
 *【文件名】            ModelBase.hpp
 *【功能模块和目的】    三维模型基类的声明
 *【开发者及日期】      张章 2024-7-21
 *【更改记录】          无
 * *****************************************/

#ifndef _MODELBASE_HPP
#define _MODELBASE_HPP

#include<unordered_set>
#include<vector>
#include<string>
#include"Points3D.hpp"
#include"Lines3D.hpp"
#include"Faces3D.hpp"
/******************************************
 *【类名】              ModelBase3D
 *【功能】              表示一个三维模型
 *【接口说明】          提供三维模型的三种基本功能的接口（加载模型、渲染模型、获取模型信息） 
 *                      包含三维模型的基本元素（包括点、线和面）
 *【开发者及日期】      张章  2024-7-21
 *【更改记录】          无
 * ***************************************/

class ModelBase{
public:
    ModelBase();
    ModelBase();
    ModelBase();
    ModelBase();
    ModelBase();
    ModelBase();
    ModelBase();
    ModelBase();
    ModelBase();


    virtual void LoadModel(const string& FileName) = 0;
    virtual void ExportModel(const string& FileName) = 0;

    virtual void RenderModel() = 0;
    
    /* non-static getters */
    /* non-static setters */
     
private:
}




