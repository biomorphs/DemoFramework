file(GLOB PLATFORM_SOURCES "*.*")

add_library(Platform STATIC ${PLATFORM_SOURCES})

#Needs SDL2
target_include_directories(Platform PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(Platform ${SDL2_LIBRARY})