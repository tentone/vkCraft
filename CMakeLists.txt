cmake_minimum_required (VERSION 3.8)

project (vkCraft)

find_package (glfw3 REQUIRED)
find_package (Vulkan REQUIRED)

set(SOURCE_FILES
    src/vkCraft/BoxGeometry.cpp
    src/vkCraft/BufferUtils.cpp
    src/vkCraft/Camera.cpp
    src/vkCraft/Chunk.cpp
    src/vkCraft/ChunkGeometry.cpp
    src/vkCraft/ChunkNode.cpp
    src/vkCraft/ChunkWorld.cpp
    src/vkCraft/CommandBufferUtils.cpp
    src/vkCraft/Device.cpp
    src/vkCraft/FileUtils.cpp
    src/vkCraft/FirstPersonCamera.cpp
    src/vkCraft/Geometry.cpp
    src/vkCraft/main.cpp
    src/vkCraft/Object3D.cpp
    src/vkCraft/PlaneGeometry.cpp
    src/vkCraft/QueueFamilyIndices.cpp
    src/vkCraft/Texture.cpp
    src/vkCraft/Vertex.cpp
    src/vkCraft/VkCraft.cpp
)

set(HEADER_FILES
    src/vkCraft/BoxGeometry.h
    src/vkCraft/BufferUtils.h
    src/vkCraft/Camera.h
    src/vkCraft/Chunk.h
    src/vkCraft/ChunkGeometry.h
    src/vkCraft/ChunkNode.h
    src/vkCraft/ChunkWorld.h
    src/vkCraft/CommandBufferUtils.h
    src/vkCraft/Device.h
    src/vkCraft/FileUtils.h
    src/vkCraft/FirstPersonCamera.h
    src/vkCraft/Geometry.h
    src/vkCraft/Object3D.h
    src/vkCraft/PlaneGeometry.h
    src/vkCraft/QueueFamilyIndices.h
    src/vkCraft/SwapChainSupportDetails.h
    src/vkCraft/UniformBufferObject.h
    src/vkCraft/Vertex.h
    src/vkCraft/VkCraft.h
)

include_directories(src/include 
  ${glfw_INCLUDE_DIRS} 
)

add_executable(vkCraft ${SOURCE_FILES})
add_library(libvkCraft SHARED ${SOURCE_FILES})
set_target_properties(libvkCraft PROPERTIES OUTPUT_NAME "vkCraft")

target_link_libraries(vkCraft 
  glfw3
  tinyobjloader
  ${Vulkan_LIBRARIES}
)

add_custom_command(TARGET vkCraft
  POST_BUILD
  COMMAND cd ${CMAKE_SOURCE_DIR}/src/scripts && python3 compile_shaders.py
)

add_custom_command(TARGET vkCraft
  POST_BUILD
  COMMAND cp -r ${CMAKE_SOURCE_DIR}/src/vkCraft/texture ${CMAKE_CURRENT_BINARY_DIR}/texture
)

install(TARGETS vkCraft 
	DESTINATION bin)
install(TARGETS libvkCraft
	DESTINATION lib)
install(FILES ${HEADER_FILES} 
	DESTINATION include/vkCraft)