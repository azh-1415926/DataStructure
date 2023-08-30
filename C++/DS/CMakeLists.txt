file(GLOB_RECURSE srcs CONFIGURE_DEPENDS include/*.hpp)
set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
add_library(DS OBJECT ${srcs})
target_include_directories(DS PUBLIC include)