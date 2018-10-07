# vkCraft
 - Minecraft clone written with C++ and Vulkan
 - Project made as a way of learning the basics about the Vulkan API.

## How to run
 - Download GLW, GLFW and the LunarG Vulkan SDK.
 - Open the solution in Visual Studio.
 - Configure project with the downloaded libs.
 - Build and run project.

## Screenshots
![alt tag](https://raw.githubusercontent.com/tentone/vkCraft/master/images/a.png)![alt tag](https://raw.githubusercontent.com/tentone/vkCraft/master/images/b.png)!

## World generator
 - The world generator is based on perlin noise.
 - Multiple generations of noise are used, one for the terrain and other one for cloud placement.
 - Blocks types are decided based on the weight relative to the surface, the same goes for underwater blocks.

## Chunk structure
 - World chunks are ornganized as linked list of chunks.
 - Each chunk holds its data and 6 pointers to its neighbors (left, right, up, down, front, back). 
 - On generation the nodes flood trough the known links to find already created neighbors.
```
            Up
            |    Back
            |   /
            | /
  Left ---- N ---- Right
          / |
        /   |
     Front  |
           Down
```

## To do
 - Better world generation.
 - Generate nodes in separate threads.
 - Generate only the required faces relative to the world.
 - Handle the water geometry separately and implement wavy shader animation.
 - Try to use a geometry shader to generate the chunk geometry on the fly.

## References
 - Mike Bailey's Vulkan Guide (http://web.engr.oregonstate.edu/~mjb/vulkan/)
 - Alexander Overvoorde Vulkan Guide (https://vulkan-tutorial.com/Introduction)

## License
 - The project is under MIT license (Available on the project repository).
 