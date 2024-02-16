project(TestForSort)

add_executable("${PROJECT_NAME}_C" main.c)
add_executable("${PROJECT_NAME}_CXX" main.cpp)
target_link_libraries("${PROJECT_NAME}_C" PRIVATE myDS myTools)
target_link_libraries("${PROJECT_NAME}_CXX" PRIVATE myDS simpleDS)