#include"ControllerBase.hpp"

#ifndef _CONTROLLERCLI_HPP
#define _CONTROLLERCLI_HPP

class ControllerCLI : public ControllerBase{
public:
    using ControllerBase::ControllerBase;   // 使用基类的构造函数
    ~ControllerCLI();
private:
};


#endif
