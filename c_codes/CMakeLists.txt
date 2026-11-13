add_library(libgetmaxcpus INTERFACE)
add_library(get_max_cpus::get_max_cpus ALIAS libgetmaxcpus)

target_include_directories(libgetmaxcpus INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include/get_max_cpus>)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION include/get_max_cpus FILES_MATCHING PATTERN "*.hpp")
