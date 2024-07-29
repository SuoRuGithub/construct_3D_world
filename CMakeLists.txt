cmake_minimum_required(VERSION 3.0)
project(Construct_3D_World)

set(CMAKE_BUILD_TYPE "Debug")

aux_source_directory(./Model MODEL_LIST)
aux_source_directory(./Controller CONTROLLER_LIST)
aux_source_directory(./View VIEW_LIST)

add_executable(main main.cpp ${MODEL_LIST} ${CONTROLLER_LIST} ${VIEW_LIST})