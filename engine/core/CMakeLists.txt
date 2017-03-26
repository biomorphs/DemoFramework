file(GLOB CORE_SOURCES "*.*")

add_library(Core STATIC ${CORE_SOURCES})
target_include_directories(Core PUBLIC ${DEMOFRAMEWORK_ROOT_PATH})

target_link_libraries(Core Platform)