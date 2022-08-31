#!/bin/python3

#region Modules

import subprocess
import os

#endregion

#region Variables

srcDirectory = '../'
includeDirectory = '../include/'

#endregion

#region Functions

def Lint():
    # src
    for fileName in os.listdir(srcDirectory):
        filePath = os.path.join(srcDirectory, fileName)
        if os.path.isfile(filePath):
            subprocess.run(['uncrustify', '-c', '../../.uncrustify.config', filePath, '--no-backup', '--replace', filePath])
    # include
    for fileName in os.listdir(includeDirectory):
        filePath = os.path.join(includeDirectory, fileName)
        if os.path.isfile(filePath):
            subprocess.run(['uncrustify', '-c', '../../.uncrustify.config', filePath, '--no-backup', '--replace', filePath])

#endregion

if __name__ == '__main__':
    Lint()