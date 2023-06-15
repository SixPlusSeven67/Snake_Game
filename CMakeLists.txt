cmake_minimum_required(VERSION 3.0.0)
project(snake VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(snake 
SnakeNode.cpp
Fruit.cpp
Game.cpp
GameOverScreen.cpp
GameScreen.cpp
main.cpp
MenuScreen.cpp
Screen.cpp
Snake.cpp
Button.cpp
OptionScreen.cpp
Grid.cpp
HelpScreen.cpp
PauseScreen.cpp
)


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/3rd/SFML-2.5.1/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/3rd/SFML-2.5.1/lib)
target_link_libraries (${PROJECT_NAME}  PRIVATE sfml-window sfml-graphics sfml-audio sfml-system)

# 将SFML/bin下的所有*.dll复制到 /build文件下，保证编译程序正常运行，不报缺少dll错误
file(GLOB_RECURSE PROJECT_DLL ${CMAKE_CURRENT_LIST_DIR}/3rd/SFML-2.5.1/bin/*.dll)
message(${PROJECT_DLL})
# 复制库到工作目录
# POST_BUILD 在编译后操作
# copy命令拷贝单个文件，下面的 copy_directory是拷贝目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_DLL}
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

#set(SFML_LIBS sfml-system sfml-window sfml-graphics sfml-audio)


