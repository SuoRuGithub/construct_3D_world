#include<iostream>
#include<sstream>
#include<string>
#include"View.hpp"

View::View(){
}

// 主菜单
std::string View::MainMenu   (ControllerCLI& Controller){
    std::string command = "Main";
    
    while (command != "wq" && command != ":wq"){
        std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
        std::cout << "          -----------------Construct your 3D world!-----------------" << std::endl << std::endl;
        std::cout << "                                Developed by zz                     " << std::endl << std::endl;
        std::cout << "                - Enter  Display<Enter>         Skip to display menu" << std::endl << std::endl;
        std::cout << "                - Enter  Modify<Enter>          Skip to modify menu"  << std::endl << std::endl;
        std::cout << "                - Enter  wq<Enter>              Save and quit"        << std::endl << std::endl;
        std::cout << "          ----------------------------------------------------------" << std::endl << std::endl;
        getline(std::cin, command);

        if      (command == "Display" || command == "display"){
            std::cout << DisplayMenu(Controller) << std::endl;
        }
        else if (command == "Modify" || command == "modify"){
            std::cout << ModifyMenu(Controller) << std::endl;
        }
        else if (command == "wq" || command == ":wq"){
            break;
        }
        else{
            std::cout << "command not found: " + command << std::endl;
        }
        command.clear();
    }
    return "          -----------------Construct your 3D world!-----------------";
}
// 显示菜单
std::string View::DisplayMenu(ControllerCLI& Controller){
    std::string command {};
    while (command != "wq"){
        std::cout << "          ----------------Display Whatever You Need!----------------"     << std::endl << std::endl;
        std::cout << "                - Enter  Face<Enter>              Data about Faces"       << std::endl << std::endl;
        std::cout << "                - Enter  Line<Enter>              Data about Lines"       << std::endl << std::endl;
        std::cout << "                - Enter  Total<Enter>             Statistical data"       << std::endl << std::endl;
        std::cout << "                - Enter  wq<Enter>                Return to main menu."   << std::endl << std::endl;
        std::cout << "          ----------------------------------------------------------"     << std::endl << std::endl;

        getline(std::cin, command);
        // 和面相关的信息
        if (command == "Face"){
            std::cout << "          ----------------What about Faces do U want?----------------"            << std::endl << std::endl;
            std::cout << "                - Enter  ls<Enter>                List all info of all faces"     << std::endl << std::endl;
            std::cout << "                - Enter  ls [idx]<Enter>          List info of face of No. idx"   << std::endl << std::endl;
            command.clear();
            getline(std::cin, command);
            if (command.substr(0, 2) == "ls"){
                std::istringstream num(command.substr(2));
                int FaceIdx = 0;
                if (num >> FaceIdx){
                    try{
                        FaceDetail detail = Controller.GetPointsOfFace(FaceIdx);
                        std::cout << "Face: " << detail.idx
                        << " (" << detail.x1 << ", " << detail.y1 << ", " << detail.z1 << ")" 
                        << " (" << detail.x2 << ", " << detail.y2 << ", " << detail.z2 << ")" 
                        << " (" << detail.x3 << ", " << detail.y3 << ", " << detail.z3 << ") " << std::endl;
                    }
                    catch(ExceptionIndexOutOfRange){
                        std::cout << "Index out of range." << std::endl;
                    }
                }
                else{
                    try{
                    const std::vector<Face3D>& FacesList = Controller.GetFaces();
                    for (int idx = 0; idx < FacesList.size(); idx++){
                        const Face3D& face = FacesList[idx];
                        std::cout << "Face: " << idx 
                        << " (" << face.PointA.x << ", " << face.PointA.y << ", " << face.PointA.z << ")" 
                        << " (" << face.PointB.x << ", " << face.PointB.y << ", " << face.PointB.z << ")" 
                        << " (" << face.PointC.x << ", " << face.PointC.y << ", " << face.PointC.z << ") " 
                        << "Area: " << face.GetArea() << std::endl;
                    }
                    }
                    catch(ExceptionNoFacesFound){
                        std::cout << "There is no face exist!" << std::endl;
                    }
                }
            }
            else{
                std::cout << "command not found: " + command << std::endl;
            }
        }
        // 和线相关的信息
        else if (command == "Line"){
            std::cout << "          ----------------What about lines do U want?----------------"            << std::endl << std::endl;
            std::cout << "                - Enter  ls<Enter>                List all info of all lines"     << std::endl << std::endl;
            std::cout << "                - Enter  ls [idx]<Enter>          List info of line of No. idx"   << std::endl << std::endl;
            command.clear();
            getline(std::cin, command);
            if (command.substr(0, 2) == "ls"){
                std::istringstream num(command.substr(2));
                int LineIdx = 0;
                if (num >> LineIdx){
                    try{
                        LineDetail detail = Controller.GetPointsOfLine(LineIdx);
                        std::cout << "Line: " << detail.idx
                        << " (" << detail.x1 << ", " << detail.y1 << ", " << detail.z1 << ")" 
                        << " (" << detail.x2 << ", " << detail.y2 << ", " << detail.z2 << ")" << std::endl;
                    }
                    catch(ExceptionIndexOutOfRange){
                        std::cout << "Index out of range." << std::endl;
                    }
                }
                else{
                    try{
                    const std::vector<Line3D>& LinesList = Controller.GetLines();
                    for (int idx = 0; idx < LinesList.size(); idx++){
                        const Line3D& line = LinesList[idx];
                        std::cout << "Line: " << idx 
                        << " (" << line.PointA.x << ", " << line.PointA.y << ", " << line.PointA.z << ")" 
                        << " (" << line.PointB.x << ", " << line.PointB.y << ", " << line.PointB.z << ")" 
                        << "Length: " << line.GetLength() << std::endl;
                    }
                    }
                    catch(ExceptionNoLinesFound){
                        std::cout << "There is no line exist!" << std::endl;
                    }
                }
            }
            else{
                std::cout << "command not found: " + command << std::endl;
            }
        }
        // 统计信息
        else if (command == "Total"){
            StatisticalInfo info = Controller.GetStatisticalInfo();
            std::cout << "Number of faces: "           << info.FaceNum           << std::endl
                      << "Number of lines: "           << info.LineNum           << std::endl
                      << "Number of points: "          << info.PointNum          << std::endl
                      << "Volume of bounding box"      << info.BoundingBoxVolume << std::endl
                      << "Total area of all faces "    << info.FaceArea          << std::endl
                      << "Total length of all lines: " << info.LineLength        << std::endl;
        }
        else if (command == "wq"){
            break;
        }
        else{
            std::cout << "command not found: " + command << std::endl;
        }
    }
    return "Quit from display menu.";
}
// 修改菜单
std::string View::ModifyMenu (ControllerCLI& Controller){
    
    std::string command {};
    while (command != "wq"){
        std::cout << "          ----------------Modify Whatever U Need!----------------"     << std::endl << std::endl;
        std::cout << "                - Enter  Face<Enter>              Modify Faces"        << std::endl << std::endl;
        std::cout << "                - Enter  Line<Enter>              Modify Lines"        << std::endl << std::endl;
        std::cout << "                - Enter  wq<Enter>                Return to Main Menu" << std::endl << std::endl;
        std::cout << "          --------------------------------------------------------"     << std::endl << std::endl;
        command.clear();
        getline(std::cin, command);
        if (command == "Face"){
            std::cout << "          ----------------How do you want to modify?----------------"                                             << std::endl << std::endl;
            std::cout << " - Enter  Add [x1] [y1] [z1] [x2] [y2] [z2] [x3] [y3] [z3]<Enter>             Add a new face."                    << std::endl << std::endl;
            std::cout << " - Enter  Delete [idx]<Enter>                                                 Delete idx face."                   << std::endl << std::endl;
            std::cout << " - Enter  Modify [idx1] [idx2] [x] [y] [z]<Enter>                             Modify idx2 point of idx1 face."    << std::endl << std::endl;
            std::cout << " - Enter  wq<Enter>                                                           Return to Modify Menu"              << std::endl << std::endl;
            command.clear();
            getline(std::cin, command);
            if(command.substr(0, 3) == "Add"){
                std::vector<double> coordinates;
                std::istringstream iss(command.substr(3));
                for (int i = 0; i < 9; i++){
                    double coordinate = 0.0;
                    if (iss >> coordinate){
                        coordinates.push_back(coordinate);
                    }
                    else{
                        std::cout << "invalid input!" << std::endl;
                        break;
                    }
                }
                if (coordinates.size() == 9){
                    ControllerReturn res = Controller.AddFace(coordinates[0], coordinates[1], coordinates[2], 
                                                              coordinates[3], coordinates[4], coordinates[5], 
                                                              coordinates[6], coordinates[7], coordinates[8]);
                    if (res == ControllerReturn::FACE_REPEATED){
                        std::cout << "The face you want to add already exist." << std::endl;
                    }
                    else if (res == ControllerReturn::POINTS_REPEATED){
                        std::cout << "The points of a face shouldn't be repeated." << std::endl;
                    }
                    else if (res == ControllerReturn::FACE_ADDED){
                        std::cout << "The face are added successfully!" << std::endl;
                    }
                }
                else{
                    std::cout << "Lack of argument." << std::endl;
                }
            }
            else if (command.substr(0, 6) == "Delete"){
                std::istringstream iss(command.substr(6));
                unsigned int idx = 0;
                if (iss >> idx){
                    ControllerReturn res = Controller.DeleteFace(idx);
                    if (res == ControllerReturn::FACE_DELETED){
                        std::cout << "The face is deleted successfully." << std::endl;
                    }
                    else if(res == ControllerReturn::INDEX_OUT_OF_RANGE){
                        std::cout << "The index provided is out of range." << std::endl;
                    }
                }
                else{
                    std::cout << "Please enter the index of a face." << std::endl;
                }
            }
            else if (command.substr(0, 6) == "Modify"){
                std::istringstream iss(command.substr(6));
                int FaceIdx     = 0;
                int PointIdx    = 0;
                double x        = 0.0;
                double y        = 0.0;
                double z        = 0.0;
                if (iss >> FaceIdx && iss >> PointIdx && iss >> x && iss >> y && iss >> z){
                    ControllerReturn res;
                    res = Controller.ModifyPointOfFace(FaceIdx, PointIdx, x, y, z);
                    if (res == ControllerReturn::POINT_OF_FACE_CHANGED){
                        std::cout << "The point " << PointIdx << " of " << FaceIdx << " face has been changed successfully." << std::endl;
                    }
                    else if (res == ControllerReturn::INDEX_OUT_OF_RANGE){
                        std::cout << "The index provided is out of range." << std::endl;
                    }
                    else if (res == ControllerReturn::POINTS_REPEATED){
                        std::cout << "A face shouldn't has repeated face." << std::endl;
                    }
                }
                else{
                    std::cout << "invalid argument." << std::endl;
                }
            }
            else if (command == "wq"){
                continue;
            }
            else{
                std::cout << "command not found: " + command << std::endl;
            }
        }

        // 这一段代码和面的代码基本长得一模一样，设计有待提升
        else if (command == "Line"){
            std::cout << "          ----------------How do you want to modify?----------------"                                             << std::endl << std::endl;
            std::cout << " - Enter  Add [x1] [y1] [z1] [x2] [y2] [z2]<Enter>                            Add a new line."                    << std::endl << std::endl;
            std::cout << " - Enter  Delete [idx]<Enter>                                                 Delete idx line."                   << std::endl << std::endl;
            std::cout << " - Enter  Modify [idx1] [idx2] [x] [y] [z]<Enter>                             Modify idx2 point of idx1 line."    << std::endl << std::endl;
            std::cout << " - Enter  wq<Enter>                                                           Return to Modify Menu"              << std::endl << std::endl;
            command.clear();
            getline(std::cin, command);
            if(command == "Add"){
                std::vector<double> coordinates;
                std::istringstream iss(command.substr(3));
                for (int i = 0; i < 6; i++){
                    double coordinate = 0.0;
                    if (iss >> coordinate){
                        coordinates.push_back(coordinate);
                    }
                    else{
                        std::cout << "invalid input!" << std::endl;
                        break;
                    }
                }
                if (coordinates.size() == 6){
                    ControllerReturn res = Controller.AddLine(coordinates[0], coordinates[1], coordinates[2], 
                                                              coordinates[3], coordinates[4], coordinates[5]);
                    if (res == ControllerReturn::LINE_REPEATED){
                        std::cout << "The line you want to add already exist." << std::endl;
                    }
                    else if (res == ControllerReturn::POINTS_REPEATED){
                        std::cout << "The points of a line shouldn't be repeated." << std::endl;
                    }
                    else if (res == ControllerReturn::LINE_ADDED){
                        std::cout << "The line are added successfully!" << std::endl;
                    }
                    
                }
            }
            else if (command.substr(0, 6) == "Delete"){
                std::istringstream iss(command.substr(6));
                unsigned int idx = 0;
                if (iss >> idx){
                    ControllerReturn res = Controller.DeleteLine(idx);
                    if (res == ControllerReturn::LINE_DELETED){
                        std::cout << "The line is deleted successfully." << std::endl;
                    }
                    else if(res == ControllerReturn::INDEX_OUT_OF_RANGE){
                        std::cout << "The index provided is out of range." << std::endl;
                    }
                }
                else{
                    std::cout << "Please enter the index of a line." << std::endl;
                }
            }
            else if (command.substr(0, 6) == "Modify"){
                std::istringstream iss(command.substr(6));
                int LineIdx     = 0;
                int PointIdx    = 0;
                double x        = 0.0;
                double y        = 0.0;
                double z        = 0.0;
                if (iss >> LineIdx && iss >> PointIdx && iss >> x && iss >> y && iss >> z){
                    ControllerReturn res;
                    res = Controller.ModifyPointOfLine(LineIdx, PointIdx, x, y, z);
                    if (res == ControllerReturn::POINT_OF_LINE_CHANGED){
                        std::cout << "The point " << PointIdx << " of " << LineIdx << " line has been changed successfully." << std::endl;
                    }
                    else if (res == ControllerReturn::INDEX_OUT_OF_RANGE){
                        std::cout << "The index provided is out of range." << std::endl;
                    }
                    else if (res == ControllerReturn::POINTS_REPEATED){
                        std::cout << "A line shouldn't has repeated line." << std::endl;
                    }
                }
                else{
                    std::cout << "invalid argument." << std::endl;
                }
            }
            else if (command == "wq"){
                continue;
            }
            else{
                std::cout << "command not found: " + command << std::endl;
            }
        }

        else if (command == "wq"){
            break;
        }
        else{
            std::cout << "command not found: " + command << std::endl;
        }
    }
    return "Quit from modify menu.";
}
