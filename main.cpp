#include<string>
#include<iostream>
#include"./Controller/ControllerCLI.hpp"
#include"./View/View.hpp"

int main(){
    View myView;
    std::cout << myView.MainMenu() << std::endl;
    return 0;
}