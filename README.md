# RPG-Project
Starting files needed to start creating great products with the [RPG-Engine](https://github.com/oohicksyoo/RPG-Engine) and [RPG-Editor](https://github.com/oohicksyoo/RPG-Editor)

## Starting Out
Initial Project Building requires download and extracting the latest release into an empty folder where your repo for your project is located.

Extracting the files will create the below folder structure for you including some basic files needed for a specific target. Some folders such as the **third-party** will not be created as it is generated through setup scripts for a target.

TODO: Talk about how to relink the submodules because sourcetree never picked them up

- project/
  - assets/
    - models
    - scripts
    - shaders
      - opengl
      - vulkan (created during builds)
    - textures
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
  - third-party (created during target setups)
  - vulkan-shader-source

### Submodules
Included in the template files is a **.gitmodules** file which will link the [RPG-Engine](https://github.com/oohicksyoo/RPG-Engine) and [RPG-Editor](https://github.com/oohicksyoo/RPG-Editor) repos to the project. These files are located under the **project/code/engine/** & **project/code/editor/**. This gives us seperation between engine, editor and game code while still being able to compile it all together still.

### Android
You can adjust the settings below using the **project/targets/android/build.gradle** file but this is what is currently working by default
- **Android Studio Version:** 4.1.1
- **Android NDK:** 20.0.5594570
- **Gradle: 6.5**
- **Min SDK Version:** 21
- **Target SDK Version:** 29

#### Known Issues
Currently having issues building on Windows.

### Console (MacOS)
Rather than building a MacOS xcode project I have also setup a default console project you can setup, build through command line. This will produce an executable for you to launch.

### Emscripten (WebGL)
Builds the project to web assembly for use in the browser.

#### Known Issues
Currently can not build via Windows.

### iOS
- **Target SDK Version:** 12.0

### MacOS
- **Taget SDK Version::** 10.14 (Mojave)

### Windows
Before running the setup.ps1 on Windows you will need to download the [Vulkan SDK (1.2.135.0)](https://vulkan.lunarg.com/sdk/home#windows) manually and install the files to the **project/third-party/vulkan-windows**

#### Setup
* Download vulkan and during the installation set it to the **project/third-party/vulkan-windows** (If this is not your first time simply copy the vulkan-windows from another project)
* Run setup.ps1
  * open CMD
  * cd to **project/targets/windows**
  * powershell -File setup.ps1
    * This will run through and download all third-party assets needed for the Windows target

### Lua
Lua has a function that uses a deprecated function called on **iOS** & **Android**. To avoid this issue it is reconmended to change this below after running the setup file for any target.

Open Ioslib.c inside of **third-party/lua** line **141**
```lua
static int os_execute (lua_State *L) {
  const char *cmd = luaL_optstring(L, 1, NULL);
  int stat = system(cmd);
  if (cmd != NULL)
    return luaL_execresult(L, stat);
  else {
    lua_pushboolean(L, stat);  /* true if there is a shell */
    return 1;
  }
}
```

to

```lua
static int os_execute (lua_State *L) {
    return 1;
}
```
