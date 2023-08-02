file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
set(PROJECT_NAME simpleDS)
add_library(${PROJECT_NAME} STATIC ${srcs})
target_include_directories(${PROJECT_NAME} PUBLIC include)