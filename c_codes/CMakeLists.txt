add_library(libgetmaxcpus INTERFACE)

target_include_directories(libgetmaxcpus INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS libgetmaxcpus DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
    DESTINATION include 
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.tpp"
)