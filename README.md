# RPG-Project
Starting files needed to start creating great products with the [RPG-Engine](https://github.com/oohicksyoo/RPG-Engine) and [RPG-Editor](https://github.com/oohicksyoo/RPG-Editor)

## Starting Out
Initial Project Building requires download and extracting the latest release into an empty folder where your repo for your project is located.

Extracting the files will create the below folder structure for you including some basic files needed for a specific target. Some folders such as the **third-party** will not be created as it is generated through setup scripts for a target.

- project/
  - code/
    - project
  - shared
  - targets/
    - android
    - console (mac)
    - emscripten
    - ios
    - macos
    - windows
  - third-party
  - vulkan-shader-source

### Submodules
Included in the template files is a **.gitmodules** file which will link the [RPG-Engine](https://github.com/oohicksyoo/RPG-Engine) and [RPG-Editor](https://github.com/oohicksyoo/RPG-Editor) repos to the project. These files are located under the **project/code/engine/** & **project/code/editor/**. This gives us seperation between engine, editor and game code while still being able to compile it all together still.

### Windows Setup
After running the setup.ps1 on Windows you will need to download the Vulkan SDK manually and install the files to the **project/third-party/vulkan-windows**
