project(TestForTire)

add_executable("${PROJECT_NAME}_C" main.c)
target_link_libraries("${PROJECT_NAME}_C" PRIVATE myDS simpleDS myTools)