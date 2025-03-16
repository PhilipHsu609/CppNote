add_executable(adpater)
target_sources(adpater PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/adapter.cpp)
target_link_libraries(adpater PRIVATE fmt::fmt)
target_link_libraries(adpater PRIVATE compile_flags_interface)