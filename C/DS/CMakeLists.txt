file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.c include/*.h)
set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
add_library(DS STATIC ${srcs})
target_include_directories(DS PUBLIC include)