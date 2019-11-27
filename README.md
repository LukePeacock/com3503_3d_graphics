# COM3503 3D Graphics Assignment
This folder contains all files necessary to compile and execute the COM3503 3D Graphics assignment. All code was written by myself, Luke Peacock, unless otherwise stated.

Scene graph code and model, mesh, material code was heavily based on code from the Lab class tutorials. However, most of it needed updating to work within C++ (primarily adding pointer and references rather than copying objects). Several functions needed changing to use pointers and/or references in order to make the code more efficient and also to preserve the hierarchy of the scene graphs.


## File Structure
In order to run the program, open the Terminal on your mac and navigate to the `executable` folder:

`cd executable`

Once inside this folder, you should be able to run the program by running 

`./assignment` 

in the Terminal window. In the event that the program does not run, you may be missing one or more of the following libraries in your system:

- `gflw`
- `glad`


In the event that you are missing the `glfw` library files, please download the library files using your preferred method. If you wish to download `glfw` using homebrew you will need to do the following in a Terminal window:
```
xcode-select --install
brew update
brew tap homebrew/versions
brew install glfw3
```

If you wish to uninstall `glfw` after using this program, simply run `brew uninstall glfw3` in the Terminal window.


The folder [source](source) contains all header and class files used during development. You will not need to compile these yourself, they are here for marking purposes only. Inside of the [source](source) folder, you will find several files and subfolders. This folder contains all the class implementation files; to read the class header files, navigate to the [headers](source/headers) folder. Inside of the source folder, you will also find the [assets](source/assets) and [shaders](source/shaders) folders; these contain all textures and shader files, respectively.

### Texture Information
Textures were taken from the following copyright free sources, any other textures were created by me.

Hat / wool texture:
[High Resolution Texture Resource Pack, by rubberduck at OpenGameArt.org](https://opengameart.org/content/huge-texture-resource-pack-part-1)

Metal texture:
[Free Texture Resource Pack, by rubberduck at OpenGameArt.org](https://opengameart.org/content/free-texture-resource-pack-metal-and-other)

Stone texture: 
[Granite Texture, by Keith333 at OpenGameArt.org](https://opengameart.org/content/granite-texture-gray-and-white-seamless-texture-with-normalmap-0)

Snow Ground texture: 
[Free Texure Resource Pack, by rubberduck at OpenGameArt.org](https://opengameart.org/content/free-texture-resource-pack-wood-structure-walls-and-textile)

Snowman texture:
[50 free textures, by rubberduck at OpenGameArt.org](https://opengameart.org/content/50-free-textures-3)

Background:
[Vectors by Vecteezy](https://www.vecteezy.com/vector-art/430450-seamless-background-with-trees-and-snow)

