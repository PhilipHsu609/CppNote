add_executable(SOLID)
target_sources(SOLID PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SOLID.cpp)
target_link_libraries(SOLID PRIVATE fmt::fmt)
target_link_libraries(SOLID PRIVATE compile_flags_interface)

add_subdirectory(creational)
add_subdirectory(structural)