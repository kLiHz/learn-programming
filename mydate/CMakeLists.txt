project(MyDate-Class)

add_library(mydate STATIC MyDate.cpp)

add_executable(mydate_test test.cpp)

add_executable(national_day national_day.cpp)

target_link_libraries(mydate_test mydate)

target_link_libraries(national_day mydate)
