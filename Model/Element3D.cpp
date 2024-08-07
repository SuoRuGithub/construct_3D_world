/*************************************************************************
【文件名】                  Element3D.cpp
【功能模块和目的】          定义了Element类中异常类的定义
【开发者及日期】            张章 2024-7-21
【更改记录】                24-8-5增加了注释
*************************************************************************/
#include"Element3D.hpp"

ExceptionPointsRepeated::ExceptionPointsRepeated() 
    : std::invalid_argument("Points Repeated."){
}

ExceptionNotHavePoint::ExceptionNotHavePoint() 
    : std::invalid_argument("Don't have this point."){
}

Element3D::Element3D(){
}

Element3D::~Element3D(){
}

