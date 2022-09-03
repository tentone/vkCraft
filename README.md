# vkCraft
 - Minecraft clone written with C++ and Vulkan
 - Project made as a way of learning the basics about the Vulkan API.

## How to run
 - Download and install the required libraries
   - [GLM](https://github.com/g-truc/glm), [GLW](https://github.com/mallocc/glw), [GLFW](https://www.glfw.org/), [STB Image](https://github.com/nothings/stb) and [LunarG Vulkan SDK](https://www.lunarg.com/vulkan-sdk/).
 - On windows open the solution in [Visual Studio](https://visualstudio.microsoft.com/vs/community/).
 - On linux run the project using [CMake](https://cmake.org/) (added by [@MolassesLover](https://github.com/MolassesLover))
 - Make sure that you have Vulkan compatible drivers installed.
 - Build and run project.

## Screenshots
![alt tag](https://raw.githubusercontent.com/tentone/vkCraft/master/images/a.png)![alt tag](https://raw.githubusercontent.com/tentone/vkCraft/master/images/b.png)!

## World generator
 - The world generator is based on simple perlin noise.
 - Multiple generations of noise are used, one for the terrain and other one for cloud placement.
 - Blocks types are decided based on the weight relative to the surface, the same goes for underwater blocks.

## Chunk structure
 - World chunks are organized as 3D linked list of chunks.
 - Each chunk holds its data and 6 pointers to its neighbors (left, right, up, down, front, back). 
 - The linked structure allows for fast navigation and to find already created neighbors.


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
 - Better world generation with biome support.
 - Generate nodes in separate threads.
 - Simplify geometry further (create only visible faces).
 - Handle the water geometry separately and implement wavy shader animation.
 - Try to use a geometry shader to generate the chunk geometry on the fly.

## References
 - [Mike Bailey's Vulkan Guide](http://web.engr.oregonstate.edu/~mjb/vulkan/)
 - [Alexander Overvoorde Vulkan Guide](https://vulkan-tutorial.com/Introduction)

## License
 - The project is under MIT license, available on the project repository.
 