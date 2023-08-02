file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.c include/*.h)
add_library(simpleDS STATIC ${srcs})
target_include_directories(simpleDS PUBLIC include)