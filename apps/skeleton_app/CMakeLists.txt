cmake_minimum_required (VERSION 2.8)

file(GLOB SKELETON_APP_SOURCES "*.*")
Add_library(SkeletonApp SHARED ${SKELETON_APP_SOURCES})

# Engine projects
target_include_directories(SkeletonApp PUBLIC ${DEMOFRAMEWORK_ROOT_PATH})

target_link_libraries(SkeletonApp Core)
target_link_libraries(SkeletonApp Render)