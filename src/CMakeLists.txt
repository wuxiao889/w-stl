file(GLOB_RECURSE Headers "${PROJECT_SOURCE_DIR}/src/*.h")

add_library(wstl ${Headers})
# install(TARGETS wstl DESTINATION lib)
set_target_properties(wstl PROPERTIES LINKER_LANGUAGE CXX)