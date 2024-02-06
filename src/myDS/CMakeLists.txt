project(myDS)

file(GLOB_RECURSE srcs_c CONFIGURE_DEPENDS *.c)

add_library(${PROJECT_NAME} STATIC ${srcs_c})