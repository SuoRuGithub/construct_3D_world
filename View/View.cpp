#include<iostream>
#include<sstream>
#include<string>
#include"View.hpp"
#include"../Controller/ControllerBase.hpp"
#include"../Controller/ControllerCLI.hpp"

std::string DEFAULT_PATH = "/home/zzpku/myCode/OOP/Construct3DWorld/data/cube.obj";

View::View(){
    // View可以获得一个Controller指针进行操作
    m_ptrController = ControllerBase::getInstance();
}

// 主菜单
std::string View::MainMenu(){
    std::string command = "Main";
    
    while (command != ":wq"){
        std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
        std::cout << "       -----------------Construct your 3D world!-----------------"         << std::endl << std::endl;
        std::cout << "                             Developed by zz                     "         << std::endl << std::endl;
        std::cout << "         - type  :import<Enter>          Skip to import menu"              << std::endl << std::endl;
        std::cout << "         - type  :export<Enter>          Skip to export menu"              << std::endl << std::endl;
        std::cout << "         - type  :model<Enter>           Skip to model menu"               << std::endl << std::endl;
        std::cout << "         - type  :display<Enter>         Skip to display menu"             << std::endl << std::endl;
        std::cout << "         - type  :modify<Enter>          Skip to modify menu"              << std::endl << std::endl;
        std::cout << "         - type  :wq<Enter>              Save(to current path) and quit"   << std::endl << std::endl;
        std::cout << "       ----------------------------------------------------------"         << std::endl << std::endl;
        getline(std::cin, command);

        if      (command == ":Import"  || command == ":import"){
            std::cout << ImportMenu() << std::endl;
        }
        else if (command == ":Export"  || command == ":export"){
            std::cout << ExportMenu() << std::endl;
        }
        else if (command == ":Model"  || command == ":model"){
            std::cout << ModelMenu() << std::endl;
        }
        else if (command == ":Display" || command == ":display"){
            std::cout << DisplayMenu() << std::endl;
        }
        else if (command == ":Modify"  || command == ":modify"){
            std::cout << ModifyMenu() << std::endl;
        }
        else if (command == ":wq"){
            ControllerReturn Msg = m_ptrController->ExportModel();
            if (Msg == ControllerReturn::NO_MODEL){
                std::cout << "model not found." << std::endl;
                break;
            }
            else if (Msg == ControllerReturn::INVALID_EXPORTER_CONFIG){
                std::cout << "invalid exporter configuration." << std::endl;
                command.clear();
                continue;   // 不允许退出
            }
            else if (Msg == ControllerReturn::MODEL_EXPORTED){
                std::cout << "write and quit." << std::endl;
                break;
            }
        }
        else{
            std::cout << "command not found: " + command << std::endl;
        }
        command.clear();
    }

    return "          -----------------Construct your 3D world!-----------------";
}

// 导入菜单
std::string View::ImportMenu(){
    std::string command = "Import";
    
    while(command != ":q"){
        std::cout << "       -----------------Import the model you want!---------------"   << std::endl << std::endl;
        std::cout << "         - type  :default                   Import default model"     << std::endl << std::endl;
        std::cout << "         - type  [path/to/model]<Enter>    Import the model"         << std::endl << std::endl;
        std::cout << "         - type  :q<Enter>                 Return to main menu"      << std::endl << std::endl;
        std::cout << "       ----------------------------------------------------------"   << std::endl << std::endl;
        getline(std::cin, command);
        if (command == ":q"){
            break;
        }
        else if (command == ":default"){
            ControllerReturn Msg = m_ptrController->ImportModel(DEFAULT_PATH);
            if (Msg == ControllerReturn::INVALID_IMPORTER_CONFIG){
                std::cout << "default path unvailable." << std::endl;
            }
            else if(Msg == ControllerReturn::MODEL_IMPORTED){
                std::cout << "Your model has been imported." << std::endl;
            }
        }
        else{
            ControllerReturn Msg = m_ptrController->ImportModel(command);
            if (Msg == ControllerReturn::INVALID_IMPORTER_CONFIG){
                std::cout << "Check your input." << std::endl;
            }
            else if(Msg == ControllerReturn::MODEL_IMPORTED){
                std::cout << "Your model has been imported." << std::endl;
            }
        }
        command.clear();
    }
    return "Quit from import menu"; 
}

std::string View::ExportMenu(){
    std::string command = "Export";
    
    while(command != ":q"){
        std::cout << "       -----------------Export the model you want!---------------"   << std::endl << std::endl;
        std::cout << "         - type  [path/to/model]<Enter>    Export the model"         << std::endl << std::endl;
        std::cout << "         - type  :q<Enter>                 Return to main menu"      << std::endl << std::endl;
        std::cout << "       ----------------------------------------------------------"   << std::endl << std::endl;
        getline(std::cin, command);
        if (command == ":q"){
            break;
        }
        else{
            ControllerReturn Msg = m_ptrController->ExportModel(command);
            if      (Msg == ControllerReturn::NO_MODEL){
                std::cout << "You even don't have a model." << std::endl;
            }
            else if (Msg == ControllerReturn::INVALID_EXPORTER_CONFIG){
                std::cout << "Check your input." << std::endl;
            }
            else if (Msg == ControllerReturn::MODEL_EXPORTED){
                std::cout << "Your model has been exported." << std::endl;
            }
        }
        command.clear();
    }
    return "Quit from export menu"; 
}

std::string View::ModelMenu(){
    std::string command = "Model";
    
    while(command != ":q"){
        std::cout << "       -----------------A Model, a world!---------------"   << std::endl << std::endl;
        std::cout << "         - type  :ls<Enter>                Show all models"          << std::endl << std::endl;
        std::cout << "         - type  :activate [idx]<Enter>    Choose a model"           << std::endl << std::endl;
        std::cout << "         - type  :q<Enter>                 Return to main menu"      << std::endl << std::endl;
        std::cout << "       ----------------------------------------------------------"   << std::endl << std::endl;
        getline(std::cin, command);
        if (command == ":q"){
            break;
        }
        else if (command == ":ls"){
            MdlInfoLst info_list;
            ControllerReturn Msg = m_ptrController->GetModelInfoList(info_list);
            if (Msg == ControllerReturn::MODEL_INFO_LST_GETTED){
                std::cout << "successfully getted model info." << std::endl;
                for (ModelInfo& info : info_list){
                    std::cout << info.idx << " " << info.Name << std::endl;
                }
            }
            else if (Msg == ControllerReturn::NO_MODEL){
                std::cout << "model not found." << std::endl;
            }
        }
        else if (command.substr(0, 9) == ":activate"){
            std::istringstream num(command.substr(9));
            int ModelIdx = 0;
            if (num >> ModelIdx){
                ControllerReturn Msg = m_ptrController->ActivateModel(ModelIdx);
                if (Msg == ControllerReturn::CANNOT_ACTIVATE_MODEL){
                    std::cout << "cannot activate model." << std::endl;
                }
                else if (Msg == ControllerReturn::INDEX_OUT_OF_RANGE){
                    std::cout << "invalid idx" << ModelIdx << std::endl;
                }
                else if (Msg == ControllerReturn::MODEL_ACTIVATED){
                    std::cout << "succssfully actived model" << std::endl;
                }
                else{
                    std::cout << "unknow problem" << std::endl;
                }
            }   
            else{
                std::cout << "invalid argument, please type the index of model, " << std::endl;
            }
        }
        else{
            std::cout << "command not found: " + command << std::endl;
        }
        command.clear();
    }
    return "Quit from model menu"; 
}


// 显示菜单
std::string View::DisplayMenu(){
    std::string command = "Display";
    while (command != ":wq"){
        std::cout << "       ----------------Display Whatever You Need!----------------" << std::endl << std::endl;
        std::cout << "         - type  :face<Enter>              Data about Faces"       << std::endl << std::endl;
        std::cout << "         - type  :line<Enter>              Data about Lines"       << std::endl << std::endl;
        std::cout << "         - type  :total<Enter>             Statistical data"       << std::endl << std::endl;
        std::cout << "         - type  :wq<Enter>                Return to main menu."   << std::endl << std::endl;
        std::cout << "       ----------------------------------------------------------" << std::endl << std::endl;

        getline(std::cin, command);
        // 和面相关的信息
        if (command == ":face"){
            std::cout << "       ----------------What about Faces do U want?----------------"    << std::endl << std::endl;
            std::cout << "         - type  :ls<Enter>             List all faces with detail"     << std::endl << std::endl;
            std::cout << "         - type  :ls [idx]<Enter>       List info of ith face"          << std::endl << std::endl;
            command.clear();
            getline(std::cin, command);
            if (command.substr(0, 3) == ":ls"){
                std::istringstream num(command.substr(2));
                int FaceIdx = 0;
                if (num >> FaceIdx){
                    FaceDetail face_info;
                    ControllerReturn Msg = m_ptrController->GetFaceInfo(FaceIdx, face_info);
                    if(Msg == ControllerReturn::INDEX_OUT_OF_RANGE){
                        std::cout << "wrong idx! check your input!" << std::endl;
                    }
                    else if (Msg == ControllerReturn::GET_FACE_INFO){
                        ShowFaceInfo(face_info);
                    }
                }
                else{
                    FaceDetailList face_detail_list;
                    ControllerReturn Msg;
                    Msg = m_ptrController->GetFaces(face_detail_list);
                    
                    if      (Msg == ControllerReturn::NO_MODEL){
                        std::cout << "you don't even activated a model." << std::endl;
                    }
                    else if (Msg == ControllerReturn::NO_FACES){
                        std::cout << "you don't even have a face." << std::endl;
                    }
                    else if (Msg == ControllerReturn::GET_FACES_INFO){
                        for (FaceDetail& face_info : face_detail_list){
                            ShowFaceInfo(face_info);
                        }
                    }
                }
            }
            else{
                std::cout << "command not found: " + command << std::endl;
            }
        }

        else if (command == ":line"){
            std::cout << "       ----------------What about Lines do U want?----------------"    << std::endl << std::endl;
            std::cout << "         - type  :ls<Enter>             List all lines with detail"     << std::endl << std::endl;
            std::cout << "         - type  :ls [idx]<Enter>       List info of ith line"          << std::endl << std::endl;
            command.clear();
            getline(std::cin, command);
            if (command.substr(0, 3) == ":ls"){
                std::istringstream num(command.substr(2));
                int LineIdx = 0;
                if (num >> LineIdx){
                    LineDetail line_info;
                    ControllerReturn Msg = m_ptrController->GetLineInfo(LineIdx, line_info);
                    if(Msg == ControllerReturn::INDEX_OUT_OF_RANGE){
                        std::cout << "wrong idx! check your input!" << std::endl;
                    }
                    else if (Msg == ControllerReturn::GET_LINE_INFO){
                        ShowLineInfo(line_info);
                    }
                }
                else{
                    LineDetailList line_detail_list;
                    ControllerReturn Msg;
                    Msg = m_ptrController->GetLines(line_detail_list);
                    
                    if      (Msg == ControllerReturn::NO_MODEL){
                        std::cout << "you don't even have a model." << std::endl;
                    }
                    else if (Msg == ControllerReturn::NO_LINES){
                        std::cout << "you don't even have a line." << std::endl;
                    }
                    else if (Msg == ControllerReturn::GET_LINES_INFO){
                        for (LineDetail& line_info : line_detail_list){
                            ShowLineInfo(line_info);
                        }
                    }
                }
            }
            else{
                std::cout << "command not found: " + command << std::endl;
            }
        }

        // 统计信息
        else if (command == ":total"){
            StatisticalInfo info;
            ControllerReturn Msg;
            Msg = m_ptrController->GetStatisticalInfo(info);
            if (Msg == ControllerReturn::STATISTICAL_INFO_GETTED){
                ShowStatisticalInfo(info);
            }
            else{
                // this is empty
            }
        }

        else if (command == ":wq"){
            break;
        }

        else{
            std::cout << "command not found: " + command << std::endl;
        }
    }
    return "Quit from display menu.";
}

// 修改菜单
std::string View::ModifyMenu (){
    std::string command = "Modify";
    while (command != ":wq"){
        std::cout << "       ----------------Modify Whatever U Need!----------------"     << std::endl << std::endl;
        std::cout << "         - type  :face<Enter>              Modify Faces"           << std::endl << std::endl;
        std::cout << "         - type  :line<Enter>              Modify Lines"           << std::endl << std::endl;
        std::cout << "         - type  :wq<Enter>                Return to Main Menu"    << std::endl << std::endl;
        std::cout << "       -------------------------------------------------------"    << std::endl << std::endl;
        command.clear();
        getline(std::cin, command);
        if (command == ":face"){
            std::cout << "       ----------------How do you want to modify?----------------" << std::endl << std::endl;
            std::cout << "         - type  :add [coordinates x 3]<Enter> "                    << std::endl << std::endl;
            std::cout << "                 Add a new face."                                  << std::endl << std::endl;
            std::cout << "         - type  :delete [idx]<Enter>"                              << std::endl << std::endl;
            std::cout << "                 Delete a face."                                   << std::endl << std::endl;
            std::cout << "         - type  :modify [idx1] [idx2] [coordinate]<Enter> "        << std::endl << std::endl;
            std::cout << "                 Modify idx2th point of idx1th face"                 << std::endl << std::endl;
            std::cout << "         - type  :wq<Enter>"                                       << std::endl << std::endl;
            std::cout << "                 Return to modify menu"                            << std::endl << std::endl;
            command.clear();
            getline(std::cin, command);
            if(command.substr(0, 4) == ":add"){
                std::vector<double> coordinates;
                std::istringstream iss(command.substr(4));
                // 读取三个点的坐标
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
                    ControllerReturn Msg;
                    Msg = m_ptrController->AddFace(coordinates[0], coordinates[1], coordinates[2], 
                                                   coordinates[3], coordinates[4], coordinates[5], 
                                                   coordinates[6], coordinates[7], coordinates[8]);
                    if (Msg == ControllerReturn::FACE_REPEATED){
                        std::cout << "the face you want to add already exist." << std::endl;
                    }
                    else if (Msg == ControllerReturn::POINTS_REPEATED){
                        std::cout << "the points of a face shouldn't be repeated." << std::endl;
                    }
                    else if (Msg == ControllerReturn::FACE_ADDED){
                        std::cout << "the face are added successfully!" << std::endl;
                    }
                }
                else{
                    std::cout << "missing arguments." << std::endl;
                }
            }
            else if (command.substr(0, 7) == ":delete"){
                std::istringstream iss(command.substr(7));
                unsigned int idx = 0;
                if (iss >> idx){
                    ControllerReturn Msg;
                    Msg = m_ptrController->DeleteFace(idx);
                    if (Msg == ControllerReturn::FACE_DELETED){
                        std::cout << "the face is deleted successfully." << std::endl;
                    }
                    else if(Msg == ControllerReturn::INDEX_OUT_OF_RANGE){
                        std::cout << "the index provided is out of range." << std::endl;
                    }
                }
                else{
                    std::cout << "please enter the index of a face." << std::endl;
                }
            }
            else if (command.substr(0, 7) == ":modify"){
                std::istringstream iss(command.substr(7));
                int FaceIdx     = 0;
                int PointIdx    = 0;
                double x        = 0.0;
                double y        = 0.0;
                double z        = 0.0;
                if (iss >> FaceIdx && iss >> PointIdx && iss >> x && iss >> y && iss >> z){
                    ControllerReturn Msg;
                    Msg = m_ptrController->ModifyPointOfFace(FaceIdx, PointIdx, x, y, z);
                    if (Msg == ControllerReturn::POINT_OF_FACE_CHANGED){
                        std::cout << "The point " << PointIdx << " of " << FaceIdx << " face has been changed successfully." << std::endl;
                    }
                    else if (Msg == ControllerReturn::INDEX_OUT_OF_RANGE){
                        std::cout << "The index provided is out of range." << std::endl;
                    }
                    else if (Msg == ControllerReturn::POINTS_REPEATED){
                        std::cout << "A face shouldn't has repeated face." << std::endl;
                    }
                }
                else{
                    std::cout << "invalid argument." << std::endl;
                }
            }
            else if (command == ":wq"){
                continue;
            }
            else{
                std::cout << "command not found: " + command << std::endl;
            }
        }

        else if (command == ":line"){
            std::cout << "       ----------------How do you want to modify?----------------" << std::endl << std::endl;
            std::cout << "         - type  :add [coordinates x 2]<Enter> "                    << std::endl << std::endl;
            std::cout << "                 Add a new line."                                  << std::endl << std::endl;
            std::cout << "         - type  :delete [idx]<Enter>"                              << std::endl << std::endl;
            std::cout << "                 Delete a line."                                   << std::endl << std::endl;
            std::cout << "         - type  :modify [idx1] [idx2] [coordinate]<Enter> "        << std::endl << std::endl;
            std::cout << "                 Modify idx2th point of idx1th line"                 << std::endl << std::endl;
            std::cout << "         - type  :wq<Enter>"                                       << std::endl << std::endl;
            std::cout << "                 Return to modify menu"                            << std::endl << std::endl;
            command.clear();
            getline(std::cin, command);
            if(command.substr(0, 4) == ":add"){
                std::vector<double> coordinates;
                std::istringstream iss(command.substr(4));
                // 读取三个点的坐标
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
                    ControllerReturn Msg;
                    Msg = m_ptrController->AddLine(coordinates[0], coordinates[1], coordinates[2], 
                                                   coordinates[3], coordinates[4], coordinates[5]);
                    if (Msg == ControllerReturn::LINE_REPEATED){
                        std::cout << "the line you want to add already exist." << std::endl;
                    }
                    else if (Msg == ControllerReturn::POINTS_REPEATED){
                        std::cout << "the points of a line shouldn't be repeated." << std::endl;
                    }
                    else if (Msg == ControllerReturn::LINE_ADDED){
                        std::cout << "the line are added successfully!" << std::endl;
                    }
                }
                else{
                    std::cout << "missing arguments." << std::endl;
                }
            }
            else if (command.substr(0, 7) == ":delete"){
                std::istringstream iss(command.substr(7));
                unsigned int idx = 0;
                if (iss >> idx){
                    ControllerReturn Msg;
                    Msg = m_ptrController->DeleteLine(idx);
                    if (Msg == ControllerReturn::LINE_DELETED){
                        std::cout << "the line is deleted successfully." << std::endl;
                    }
                    else if(Msg == ControllerReturn::INDEX_OUT_OF_RANGE){
                        std::cout << "the index provided is out of range." << std::endl;
                    }
                }
                else{
                    std::cout << "please enter the index of a line." << std::endl;
                }
            }
            else if (command.substr(0, 7) == ":modify"){
                std::istringstream iss(command.substr(7));
                int lineIdx     = 0;
                int PointIdx    = 0;
                double x        = 0.0;
                double y        = 0.0;
                double z        = 0.0;
                if (iss >> lineIdx && iss >> PointIdx && iss >> x && iss >> y && iss >> z){
                    ControllerReturn Msg;
                    Msg = m_ptrController->ModifyPointOfLine(lineIdx, PointIdx, x, y, z);
                    if (Msg == ControllerReturn::POINT_OF_LINE_CHANGED){
                        std::cout << "The point " << PointIdx << " of " << lineIdx << " line has been changed successfully." << std::endl;
                    }
                    else if (Msg == ControllerReturn::INDEX_OUT_OF_RANGE){
                        std::cout << "The index provided is out of range." << std::endl;
                    }
                    else if (Msg == ControllerReturn::POINTS_REPEATED){
                        std::cout << "A line shouldn't has repeated line." << std::endl;
                    }
                }
                else{
                    std::cout << "invalid argument." << std::endl;
                }
            }
            else if (command == ":wq"){
                continue;
            }
            else{
                std::cout << "command not found: " + command << std::endl;
            }
        }
    }
    return "Quit from modify menu.";
}
void View::ShowFaceInfo(const FaceDetail& face_info){
    std::cout << "Face "     << face_info.idx             << std::endl;
    std::cout << "PointA: "  << face_info.PointsInfo[0].x << " " <<
                                face_info.PointsInfo[0].y << " " <<
                                face_info.PointsInfo[0].z << std::endl;
    std::cout << "PointB: "  << face_info.PointsInfo[1].x << " " <<
                                face_info.PointsInfo[1].y << " " <<
                                face_info.PointsInfo[1].z << std::endl;
    std::cout << "PointC: "  << face_info.PointsInfo[2].x << " " <<
                                face_info.PointsInfo[2].y << " " <<
                                face_info.PointsInfo[2].z << std::endl;
    std::cout << "Area: "    << face_info.Area            << std::endl;
    std::cout << "Perimater: " << face_info.Length      << std::endl<<std::endl;

}

void View::ShowLineInfo(const LineDetail& line_info){
    std::cout << "Line "    << line_info.idx             << std::endl;
    std::cout << "PointA: " << line_info.PointsInfo[0].x << " " <<
                               line_info.PointsInfo[0].y << " " <<
                               line_info.PointsInfo[0].z << std::endl;
    std::cout << "PointB: " << line_info.PointsInfo[1].x << " " <<
                               line_info.PointsInfo[1].y << " " <<
                               line_info.PointsInfo[1].z << std::endl;
    std::cout << "Length: "   << line_info.Length          << std::endl;
}

void View::ShowStatisticalInfo(const StatisticalInfo& info){
    std::cout << "Name of model: "             << info.Name              << std::endl
              << "Number of faces: "           << info.FaceNum           << std::endl
              << "Number of lines: "           << info.LineNum           << std::endl
              << "Number of points: "          << info.PointNum          << std::endl
              << "Volume of bounding box:"      << info.BoundingBoxVolume << std::endl
              << "Total area of all faces: "    << info.FaceArea          << std::endl
              << "Total length of all lines: " << info.LineLength        << std::endl;
}