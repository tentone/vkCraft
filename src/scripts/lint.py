#!/bin/python3

# MIT License

# Copyright © 2022, Maeve Garside

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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