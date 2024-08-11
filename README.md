# Construct 3D World

本项目为北京某高校自动化系2024年夏季学期“面向对象的程序设计”课程大作业的实现。

## 运行

### 运行环境

**操作系统**：`Ubuntu 20.04.6 LTS`

**编译器**：`GCC 9.4.0`或更高版本

**构建工具**：`CMake 3.0`或更高版本

**编辑器**：`vim 8.1.1847`, `vscode`

### 直接运行

可以直接运行`build`文件夹下的`main`样例程序。

```bash
construct_3D_world$ cd build
construct_3D_world/build$ ./main
```

### 从编译开始运行

项目依托`CMake`进行构建，按照下面的指示进行编译并运行。

```bash
construct_3D_world$ cd build
construct_3D_world/build$ cmake ..
construct_3D_world/build$ make
construct_3D_world/build$ ./main
```

### 使用你自己的三维模型文件

将你的`.obj`文件存放在`data`目录下运行程序。你可以在导入菜单输入你的文件路径导入你的`obj`文件. 

## 目录结构

项目目录组织如下：

```
.
├── build
│   ├── main
│   └── ...
├── data
│   └── cube.obj
├── Controller
│   ├── ControllerBase.cpp
│   ├── ControllerBase.hpp
│   └── ControllerCLI.hpp
├── Model
│   ├── Element3D.cpp
│   ├── Element3D.hpp
│   ├── Face3D.cpp
│   ├── Face3D.hpp
│   ├── Line3D.cpp
│   ├── Line3D.hpp
│   ├── Model3D.cpp
│   ├── Model3D.hpp
│   ├── Point3D.cpp
│   ├── Point3D.hpp
│   ├── Vector3D.cpp
│   └── Vector3D.hpp
├── View
|   ├── View.cpp
|   └── View.hpp
├── main.cpp
├── README.md
└── CMakeLists.txt
```

下面是各目录内容的介绍

`build`：存放工程文件，包括最后的可执行文件

`Model`：项目中的模型类的声明与实现

`Controller`：项目中控制器类的声明与实现

`View`：项目中界面类的声明与实现

`data`：三维模型文件存放的目录

