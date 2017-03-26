file(GLOB RENDER_SOURCES "*.*")

add_library(Render STATIC ${RENDER_SOURCES})
target_include_directories(Render PUBLIC ${DEMOFRAMEWORK_ROOT_PATH})

target_link_libraries(Render Platform)