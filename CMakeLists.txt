cmake_minimum_required (VERSION 3.8)

project (vkCraft)

find_package (glfw3 REQUIRED)
find_package (Vulkan REQUIRED)

set(SOURCE_FILES
    vkCraft/vkCraft/BoxGeometry.cpp
    vkCraft/vkCraft/BufferUtils.cpp
    vkCraft/vkCraft/Camera.cpp
    vkCraft/vkCraft/Chunk.cpp
    vkCraft/vkCraft/ChunkGeometry.cpp
    vkCraft/vkCraft/ChunkNode.cpp
    vkCraft/vkCraft/ChunkWorld.cpp
    vkCraft/vkCraft/CommandBufferUtils.cpp
    vkCraft/vkCraft/Device.cpp
    vkCraft/vkCraft/FileUtils.cpp
    vkCraft/vkCraft/FirstPersonCamera.cpp
    vkCraft/vkCraft/Geometry.cpp
    vkCraft/vkCraft/main.cpp
    vkCraft/vkCraft/Object3D.cpp
    vkCraft/vkCraft/PlaneGeometry.cpp
    vkCraft/vkCraft/QueueFamilyIndices.cpp
    vkCraft/vkCraft/Texture.cpp
    vkCraft/vkCraft/Vertex.cpp
    vkCraft/vkCraft/VkCraft.cpp
)

set(HEADER_FILES
    vkCraft/vkCraft/BoxGeometry.h
    vkCraft/vkCraft/BufferUtils.h
    vkCraft/vkCraft/Camera.h
    vkCraft/vkCraft/Chunk.h
    vkCraft/vkCraft/ChunkGeometry.h
    vkCraft/vkCraft/ChunkNode.h
    vkCraft/vkCraft/ChunkWorld.h
    vkCraft/vkCraft/CommandBufferUtils.h
    vkCraft/vkCraft/Device.h
    vkCraft/vkCraft/FileUtils.h
    vkCraft/vkCraft/FirstPersonCamera.h
    vkCraft/vkCraft/Geometry.h
    vkCraft/vkCraft/Object3D.h
    vkCraft/vkCraft/PlaneGeometry.h
    vkCraft/vkCraft/QueueFamilyIndices.h
    vkCraft/vkCraft/SwapChainSupportDetails.h
    vkCraft/vkCraft/UniformBufferObject.h
    vkCraft/vkCraft/Vertex.h
    vkCraft/vkCraft/VkCraft.h
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

# add_custom_command(TARGET vkCraft
#   POST_BUILD
#   COMMAND cd ${CMAKE_SOURCE_DIR}/src/scripts && python3 compile_shaders.py
# )

install(TARGETS vkCraft 
	DESTINATION bin)
install(TARGETS libvkCraft
	DESTINATION lib)
install(FILES ${HEADER_FILES} 
	DESTINATION include/vkCraft)