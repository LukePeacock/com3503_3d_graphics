# COM3503 3D Graphics Assignment
This folder contains all files necessary to compile and execute the COM3503 3D Graphics assignment. All code was written by myself, Luke Peacock, unless otherwise stated.

Scene graph code and model, mesh, material code was heavily based on code from the Lab class tutorials. However, almost all of it needed updating to work within C++. This primarily involved adding pointer and references rather than copying objects. Several functions needed changing to use pointers and/or references in order to function and also to preserve the hierarchy of the scene graphs. I feel it is worth mentioning that a large portion of development time involved editing the code to work in C++. There are many differences betwen Java and C++ which altered the way the code behaved. You will see lots of new functions that seem unrelated to the assignment in several files, these were necessary to be able to run the code in C++. I believe this should be taken into consideration.

# Instructions 
In order to run the program, open the Terminal on your mac and navigate to the `executable` folder:

`cd executable`

Once inside this folder, you should be able to run the program by running 

`./assignment` 

in the Terminal window.


### Button Layout 
In order to be able to move the camera the `Q` key must be pressed. This will capture the mouse and allow the camera to move. The following is a list of actions and their corresponding keys:


- `Q`: Activate/Deactive user camera controls
- `A` : Move forwards
- `Z`: Move backwards
- `Arrow Keys`: move left, right, up and down
- `F`: active wireframe mode 
- `L`: turn spotlight on or off
- `K`: turn directional light on or off
- `E`: activate/deactivate spotlight animation
- `R`: Reset the snowman position
- `G`: Begin animation to slide snowman forwards and backwards
- `T`: Begin animation to slide snowman left and right
- `H`: Begin animation to rock snowman forwards and backwards
- `Y`: Begin animation to rock snowman left and right 
- `J`: Begin animation to roll the snowman's head around its body
- `U`: Begin animation to slide snowman left and right, rock  left and right, and roll its head around its body



## Troubleshooting Tips
 In the event that the program does not run, you may be missing one or more of the following libraries in your system:

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

## File Structure
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

