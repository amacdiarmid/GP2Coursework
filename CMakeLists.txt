cmake_minimum_required (VERSION 2.8)
project (GP2Coursework)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -ftest-coverage -fprofile-arcs")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(FBX REQUIRED)

add_executable(GP2Coursework 
				src/main.cpp 
				src/OpenGL.cpp
				src/Shader.cpp
				src/Texture.cpp
				src/SDL2.cpp
				src/Window.cpp
				src/Game.cpp
				src/Scene.cpp
				src/InputManager.cpp
				src/PlayerController.cpp
				src/FileSystem.cpp
				src/FBXLoader.cpp
				src/GameObject.cpp
				src/Object.cpp
				src/Editor.cpp
				src/Components/RenderComponent.cpp
				src/Components/InputComponent.cpp
				include/Common.h
				include/OpenGL.h
				include/Vertex.h
				include/Shader.h
				include/Texture.h
				include/SDL2.h
				include/Window.h
				include/Game.h
				include/Scene.h
				include/InputManager.h
				include/PlayerController.h
				include/FileSystem.h
				include/Mesh.h
				include/FBXLoader.h
				include/GameObject.h
				include/Object.h
				include/Editor.h
				include/KeyboardListener.h
				include/Components/Components.h
				include/Components/BaseComponent.h
				include/Components/RenderComponent.h 
				include/Components/InputComponent.h )
include_directories(GP2Coursework include/ 
					${SDL2_INCLUDE_DIR}
					${OPENGL_INCLUDE_DIRS}
					${GLEW_INCLUDE_DIRS}
					${GLM_INCLUDE_DIRS}
					${SDL2IMAGE_INCLUDE_DIR}
					${SDL2_TTF_INCLUDE_DIR}
					${FBX_INCLUDE_DIR} )
target_link_libraries(GP2Coursework 
						${SDL2_LIBRARY}
						${SDL2MAIN_LIBRARY}
						${OPENGL_LIBRARIES}
						${GLEW_LIBRARIES}
						${SDL2IMAGE_LIBRARY}
						${SDL2_TTF_LIBRARIES}
						${FBX_LIBRARY} )
add_custom_command(TARGET GP2Coursework POST_BUILD COMMAND
					${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/assets
					$<TARGET_FILE_DIR:GP2Coursework>/assets)

if (MSVC)
add_custom_command(TARGET GP2Coursework POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/dlls $<TARGET_FILE_DIR:GP2Coursework>)
endif (MSVC)