# RPG-Project
Starting files needed to start creating great products with the RPG-Engine and RPG-Editor

## Starting Out
Initial Project Building requires download and extracting the latest release into an empty folder where yourrepofor your project is located.

Extracting the files will create the below folder structure for you including some basic files needed for a specific target.

- project/
  - code/
    - project
  - targets/
    - android
    - console
    - emscripten
    - ios
    - macos
    - windows
  - third-party
  
### Linking the Engine Submodule
Perform a standard addition of a submodule in the project folder under the folder project/code/engine/ placing the contents of the repo into the engine folder itself. This gives us seperation between engine and game code while compiling it all together still.

### Linking the Editor Submodule
Perform a standard addition of a submodule in the project folder under the folder project/code/editor/ placing the contents of the repo into the editor folder itself. This allows us during release builds to exclude any code specific to the editor and or items needed by the editor system.
