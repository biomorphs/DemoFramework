cmake_minimum_required (VERSION 2.8)

# Launcher project
add_executable(Launcher "main.cpp")

# Engine projects
target_include_directories(Launcher PUBLIC ${DEMOFRAMEWORK_ROOT_PATH})

target_link_libraries(Launcher Platform)

# Link with external libraries
target_link_libraries(Launcher ${SDL2_LIBRARY})
target_link_libraries(Launcher ${SDL2_LIBRARY_MAIN})

# Copy SDL2.dll to output directory in post
add_custom_command(TARGET Launcher POST_BUILD		# Post-build event
	COMMAND ${CMAKE_COMMAND} -E copy_if_different	# execute "cmake - E copy_if_different..."
	"${SDL2_RUNTIME_LIBRARY}"						# SDL lib
	$<TARGET_FILE_DIR:Launcher>)                 	# Output directory