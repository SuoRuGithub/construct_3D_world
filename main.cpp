#include<string>
#include<iostream>
#include"./Controller/ControllerCLI.hpp"
#include"./View/View.hpp"

int main(){
    std::string FileName = "/home/zzpku/myCode/OOP/Construct3DWorld/data/cube.obj"; 
    ControllerCLI Controller(FileName);

    View myView;        // 注意，调用默认构造函数不要写括号
    std::cout << myView.MainMenu(Controller) << std::endl;
    return 0;
}