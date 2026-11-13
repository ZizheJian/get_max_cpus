add_library(get_max_cpus INTERFACE)

target_include_directories(get_max_cpus INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include/get_max_cpus>)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION include/get_max_cpus FILES_MATCHING PATTERN "*.hpp")
