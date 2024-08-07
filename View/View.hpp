#include<string>
// #include"../Controller/ControllerCLI.hpp"
#include"../Controller/ControllerBase.hpp"
#include"../Controller/ControllerCLI.hpp"

#ifndef _VIEW_HPP
#define _VIEW_HPP

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
    /* 用来辅助显示的函数 */
    void ShowFaceInfo(const FaceDetail& face_info);
    void ShowLineInfo(const LineDetail& line_info);
    void ShowStatisticalInfo(const StatisticalInfo& info);
private:
    std::shared_ptr<ControllerBase> m_ptrController;
};

#endif