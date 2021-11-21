# Source example plugin

A minimal example plugin for the 2007 branch of the Source engine.

### Building
You will need Visual Studio 2019 and [git](https://git-scm.com).

1. Open Visual Studio 2019. Click on Tools → Get Tools and Features... from the top bar of the window. 
This should open the Visual Studio Installer in another window. From the Workload tab, install "Desktop development with C++". From the Individual Components tab, install:
	- MSVC v141 - VS 2017 C++ x64/x86 build tools
	- C++ Windows XP Support for VS 2017 (v141) tools

1. Run the following in cmd:
    ```
    git clone --recurse-submodules https://github.com/lipsanen/source_example_plugin
    ```

1. Open source_example_plugin.sln inside the source_example_plugin folder

1. If Windows asks which program to open `source_example_plugin.sln` with, choose Visual Studio.

   Do not upgrade the Platform Toolset when prompted, this will make the plugin not build on Debug.

1. Click `Build > Build Solution`.

   `source_example_plugin.dll` will be in `source_example_plugin\<Build Configuration>`
