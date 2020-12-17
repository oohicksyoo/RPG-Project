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

### Android
- **Android Studio Version:** 4.1.1
- **Android NDK:** 20.0.5594570
- **Gradle: 6.5**
- **Min SDK Version:** 21
- **Target SDK Version:** 29

#### Known Issues
Currently having issues building on Windows.

### Windows
After running the setup.ps1 on Windows you will need to download the [Vulkan SDK (1.2.135.0)](https://vulkan.lunarg.com/sdk/home#windows) manually and install the files to the **project/third-party/vulkan-windows**

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
