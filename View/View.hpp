/*************************************************************************
【文件名】                  View.hpp
【功能模块和目的】          View类的声明，用于构建3D世界的视图
【开发者及日期】            张章 2024-7-21
【更改记录】                24-8-5增加了注释
*************************************************************************/
#include<string>                                // string
#include"../Controller/ControllerBase.hpp"      // ControllerBase
#include"../Controller/ControllerCLI.hpp"       // ControllerCLI

#ifndef _VIEW_HPP
#define _VIEW_HPP

/*************************************************************************
【类名】             View
【功能】             提供用户界面的视图类，用于显示和用户交互
【接口说明】         包含多个虚函数，用于展示不同的菜单，以及辅助显示函数
【开发者及日期】    张章 2024-7-31
【更改记录】         无
*************************************************************************/
class View{
public:
    View();
    // 主菜单
    virtual std::string MainMenu   ();
    // 导入菜单
    virtual std::string ImportMenu ();
    // 导出菜单
    virtual std::string ExportMenu ();
    // 模型菜单
    virtual std::string ModelMenu  ();
    // 显示菜单
    virtual std::string DisplayMenu();
    // 修改菜单
    virtual std::string ModifyMenu ();
protected:
    /* 用来辅助输入输出的函数 */
    // 输出面的信息
    void ShowFaceInfo(const FaceDetail& face_info);
    // 输出线的信息
    void ShowLineInfo(const LineDetail& line_info);
    // 输出统计信息
    void ShowStatisticalInfo(const StatisticalInfo& info);
    // 显示线，其中的command共用界面的command，函数只起到封装，简化代码的功能
    void DisplayFace(std::string& command);
    // 显示面，其中的command共用界面的command，函数只起到封装，简化代码的功能
    void DisplayLine(std::string& command);
    // 修改线，其中的command共用界面的command，函数只起到封装，简化代码的功能
    void ModifyFace (std::string& command);
    // 修改面，其中的command共用界面的command，函数只起到封装，简化代码的功能
    void ModifyLine (std::string& command);

private:
    std::shared_ptr<ControllerBase> m_ptrController; // 控制器指针
};

#endif