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

#### Engine ####
add_library(engine STATIC engine/game_system.cpp 
                        engine/renderer.cpp 
                        engine/ecm.cpp
						engine/RenderMan.cpp
						)

target_include_directories(engine INTERFACE engine ${SFML_INCS})
target_link_libraries(engine sfml-graphics)

### executable ###
add_executable(BlackDragon
	main.cpp
	SceneMan.cpp
	consumable_man.cpp
	UI_button.cpp
	UI_exit_to_mainmenu.cpp
	input_man.cpp
	event_man.cpp
	console.cpp
	fight_manager.cpp
	BasicEntityStats.cpp)

target_include_directories(BlackDragon PRIVATE ${SFML_INCS} engine)
target_link_libraries(BlackDragon sfml-graphics engine)
set_property(TARGET BlackDragon PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
