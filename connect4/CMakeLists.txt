project(Connect-4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_executable(c4 ChessGame.cpp Connect4.cpp main.cpp)

install(TARGETS c4 DESTINATION ${PROJECT_SOURCE_DIR}/bin)
