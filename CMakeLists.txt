project(BlackDragon)
cmake_minimum_required(VERSION 3.11)
#Require modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
#Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/SFML")
set(SFML_INCS "lib/SFML/include")
link_directories("${CMAKE_BINARY_DIR}/lib/SFML/lib")

#### Engine ####
add_library(engine STATIC Engine/RenderMan.cpp
                        Engine/AudioManager.cpp)
target_include_directories(engine INTERFACE engine ${SFML_INCS})
target_link_libraries(engine sfml-graphics sfml-audio sfml-system)

#### Practical 1 ####
add_executable(BlackDragon 
    main.cpp
    Engine/RenderMan.cpp 
    Engine/AudioManager.cpp
)

target_include_directories(BlackDragon PRIVATE ${SFML_INCS})

target_link_libraries(BlackDragon 
    sfml-graphics 
    sfml-audio 
    sfml-system
)
set_target_properties(BlackDragon 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))

add_custom_command(TARGET BlackDragon POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/lib/SFMLBIN/bin"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

##add_custom_command(TARGET BlackDragon POST_BUILD
##    COMMAND ${CMAKE_COMMAND} -E copy
##    "${PROJECT_SOURCE_DIR}/lib/SFMLBIN/bin/OpenAL32.dll"
##    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
##)