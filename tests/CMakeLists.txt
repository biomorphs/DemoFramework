cmake_minimum_required (VERSION 2.8)

file(GLOB TEST_SOURCES "*.*")
add_executable(Tests ${TEST_SOURCES})

# Engine projects
target_include_directories(Tests PUBLIC ${DEMOFRAMEWORK_ROOT_PATH})

target_link_libraries(Tests Platform)
target_link_libraries(Tests Core)

# Tests use Catch framework
target_include_directories(Tests PUBLIC "${CMAKE_SOURCE_DIR}/external/Catch")

# Tests need SDL
target_link_libraries(Tests ${SDL2_LIBRARY})
target_link_libraries(Tests ${SDL2_LIBRARY_MAIN})

# Copy SDL2.dll to output directory in post
add_custom_command(TARGET Tests POST_BUILD		# Post-build event
	COMMAND ${CMAKE_COMMAND} -E copy_if_different	# execute "cmake - E copy_if_different..."
	"${SDL2_RUNTIME_LIBRARY}"						# SDL lib
	$<TARGET_FILE_DIR:Tests>)                 	# Output directory