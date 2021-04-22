project(Connect4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(c4_TextUI ChessGame.cpp Connect4.cpp C4_Text_Interface.cpp main_TextUI.cpp)

install(TARGETS c4_TextUI DESTINATION ${PROJECT_SOURCE_DIR}/bin)
