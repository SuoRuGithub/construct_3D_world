#include<string>
#include"../Controller/ControllerCLI.hpp"

#ifndef _VIEW_HPP
#define _VIEW_HPP

class View{
public:
    View();
    // 主菜单
    std::string MainMenu   (ControllerCLI& Controller);
    // 显示菜单
    std::string DisplayMenu(ControllerCLI& Controller);
    // 修改菜单
    std::string ModifyMenu (ControllerCLI& Controller);
private:
};

#endif