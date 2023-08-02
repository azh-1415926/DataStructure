file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.c include/*.h)
add_library(myTools STATIC ${srcs})
target_include_directories(myTools PUBLIC include)