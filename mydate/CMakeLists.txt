project(MyDate-Class)

add_library(mydate STATIC MyDate.h MyDate.cpp)

add_executable(mydate_demo demo.cpp)
target_link_libraries(mydate_demo mydate)

add_executable(national_day national_day.cpp)
target_link_libraries(national_day mydate)
