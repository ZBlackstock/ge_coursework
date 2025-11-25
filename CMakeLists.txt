project(BlackDragon)
cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/SFML")
set(SFML_INCS "lib/SFML/include")
link_directories("${CMAKE_BINARY_DIR}/lib/SFML/lib")

#### Practical 1 ####
add_executable(BlackDragon main.cpp  ${CMAKE_SOURCE_DIR}/Engine/RenderMan.cpp 
"Engine/SceneMan.cpp" "Engine/game_system.h" "Engine/UI_button.cpp" "Engine/event_man.cpp" 
"Engine/UI_exit_to_mainmenu.cpp")
target_include_directories(BlackDragon PRIVATE ${SFML_INCS})
target_link_libraries(BlackDragon sfml-graphics)
set_property(TARGET BlackDragon PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
