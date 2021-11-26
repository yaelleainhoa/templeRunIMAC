file(GLOB MY_SOURCES CONFIGURE_DEPENDS src/*)
file(GLOB MY_HEADERS CONFIGURE_DEPENDS include/*)

# add_executable(${PROJECT_NAME} ${MY_SOURCES} ${MY_HEADERS})


#add_subdirectory(src)

#file(GLOB HEADER_FILES *.hpp)
file(GLOB SRC_FILES *.cpp)
file(GLOB_RECURSE SHADER_FILES *.glsl)

foreach(SRC_FILE ${SRC_FILES})
    get_filename_component(FILE ${SRC_FILE} NAME_WE)
    set(OUTPUT ${FILE})
    add_executable(${OUTPUT} ${MY_SOURCES} ${SRC_FILE} ${HEADER_FILES} ${SHADER_FILES})
    target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})
endforeach()

file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# file(GLOB MY_SOURCES CONFIGURE_DEPENDS src/*)
# file(GLOB MY_HEADERS CONFIGURE_DEPENDS include/*)

# add_executable(${PROJECT_NAME} ${MY_SOURCES} ${MY_HEADERS})

# foreach(SOURCE &{MY_SOURCES})
#     get_filename_component(FILE ${SOURCE} NAME_WE)
#     set(OUTPUT ${FILE})
#     add_executable(${OUTPUT} ${SOURCE} ${MY_HEADERS})
#     target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})
# endforeach(())






# file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})