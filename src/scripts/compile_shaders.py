#!/bin/python3

#region Modules

import subprocess
import os

#endregion

#region Variables

shaderSourceDirectory = '../shaders'
shaderBuildDirectory = '../../bin/shaders'

#endregion

def CompileShaders():
    if os.path.exists(shaderBuildDirectory) == False:
        subprocess.run(f"mkdir {shaderBuildDirectory}", shell=True)

    for fileName in os.listdir(shaderSourceDirectory):
        sourceFilePath = os.path.join(shaderSourceDirectory, fileName)
        if os.path.isfile(sourceFilePath):
            subprocess.run(f"cp {sourceFilePath} {shaderBuildDirectory}/{fileName}", shell=True)
            subprocess.run(f"cd {shaderBuildDirectory} && glslangValidator --target-env vulkan1.3 {sourceFilePath}", shell=True)

if __name__ == '__main__':
    CompileShaders()