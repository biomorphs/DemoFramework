file(GLOB RENDER_SOURCES "*.*")

add_library(Render STATIC ${RENDER_SOURCES})
target_include_directories(Render PUBLIC ${DEMOFRAMEWORK_ROOT_PATH})

#Needs SDL2
target_include_directories(Render PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(Render ${SDL2_LIBRARY})

#Needs GLEW
target_include_directories(Render PUBLIC ${GLEW_INCLUDE_DIR})
target_link_libraries(Render ${GLEW_LIBRARY})

#Needs GLM
target_include_directories(Render PUBLIC ${GLM_INCLUDE_DIR})

target_link_libraries(Render Platform)