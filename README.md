# Dev Check Bypass

When the game Scrap Mechanic is launched with the flag `-dev` it will open a developer console along with hot reloading of Lua files being enabled.
This mod makes it so that the developer flag is not required to be the same across all players in a multiplayer game meaning you can join a host who doesn't have the flag enabled and still have access to the developer console and hot reloading.

An explanation of how this mod works is available in the [dllmain](dllmain.cpp) file at the top.

## Installation

The recommended method of installing this is [Carbon Launcher](https://github.com/ScrappySM/CarbonLauncher) which is maintained by me and will let you simply press download and launch the game!
However, there are many other ways. Here's a launcher agnostic way of installing this mod:
- Go to releases and download the latest `.dll` file.
- Open a tool like Process Hacker/System Informer and find the process of Scrap Mechanic.
- Inject the `.dll` file as a module into the process.
- You can also use a tool like [SM-DLL-Injector](https://github.com/QuestionableM/SM-DLL-Injector) maintained by [QuestionableM](https://github.com/QuestionableM) and will let you simply inject any DLL files in a folder called `DllModules`, you could use this project and put the `.dll` file in the folder and it will automatically inject it for you.

## Building

To build this project you will need to have Visual Studio installed and then you can simply open the `.sln` file and press build, it is recommended to build in Release mode as it will be smaller and faster.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
