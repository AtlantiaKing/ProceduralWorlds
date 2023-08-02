# ProcedularWorlds

Procedular Worlds is a dynamic link library that can be used to generate different types of worlds in any project that uses C++ or C#.

All world types that can currently be made:
- Infinite worlds
- Circular-shaped worlds
- Square-shaped worlds

A preset has been added to the library to generate a heightmap, but you can create a custom one as well.

As an example of what this library can do:  
You can use this noise, generated by only a few lines of code ([see below](#ExampleCode)) using this library, to generate an island like this in mere minutes!  
![ProcedularWorldsExample](https://github.com/AtlantiaKing/ProcedularWorlds/assets/35343159/5b0faaac-139a-4c5f-ac1e-5edcbad4c301)

## Example code: <a name="ExampleCode"></a>

### C++

![procedularworldsexamplecplusplus](https://github.com/AtlantiaKing/ProcedularWorlds/assets/35343159/fec4bbb3-7ec6-4fbc-a8b5-3f94fe65945c)

### C#

![procedularworldsexamplecsharp](https://github.com/AtlantiaKing/ProcedularWorlds/assets/35343159/ad19104a-b98b-485f-b965-967b269cdd0c)

## Installation
Download the latest version of the C# or C++ library [here](https://github.com/AtlantiaKing/ProcedularWorlds/releases/).

### C++
The C++ zip file contains 
- an include folder with all the headers necessary to use the library.
- a lib folder that contains the x64 and x86 .lib and .dll files necessary to use the library.

### C#
The C# zip file contains  
- a lib folder that contains the x64 and x86 .dll file necessary to use the library.  
- a src folder that contains all the C# equivalent code that hooks into the library ready to use.  

## Usage
Check out the documentation [here](https://atlantiaking.github.io/ProcedularWorlds/).

## Github project structure
   
This project contains two source directories:
- **src**  
    This is the C++ source of the project.  
    This solution contains of two projects:  
    - **ProcedularWorlds library**  
    A dynamic link library that can be used to generate different kinds of worlds.  
    The dll is usable in both C++ and in C#.
    - **SDLWorld**  
    A test project that uses SDL to draw a world generated by the ProcedularWorlds library.

- **csharpsrc**  
   This is the C# wrapper around the ProcedularWorlds dll
