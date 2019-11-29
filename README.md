# COM3503 3D Graphics Assignment
This folder contains all files necessary to compile and execute the COM3503 3D Graphics assignment. All code was written by myself, Luke Peacock, unless otherwise stated.

Scene graph code and model, mesh, material code was heavily based on code from the Lab class tutorials. However, almost all of it needed updating to work within C++. This primarily involved adding pointer and references rather than copying objects. Several functions needed changing to use pointers and/or references in order to function and also to preserve the hierarchy of the scene graphs. I feel it is worth mentioning that a large portion of development time involved editing the code to work in C++. There are many differences betwen Java and C++ which altered the way the code behaved. You will see lots of new functions that seem unrelated to the assignment in several files, these were necessary to be able to run the code in C++. I believe this should be taken into consideration.

Also I'd like to point out that I did try moving the lamp post and snowman scene graphs/nodes to separate class files but due to how C++ handles objects and references this caused a huge headache so in this instance I left them in the `main` function of the `main` file. The problem with moving them to their own classes is that you would need an object field for every single node in the graph. Sounds doable right? Nope. Because then you have to implicity instantiate every node when you construct an object of the class. Which is a pain when there are several dozen or so nodes. You need a static field for each node because otherwise you are simply creating them in the constructor and adding them as children there too. Which works if you print the tree at the end of the constructor, but as soon as you call a different function on the object and try to draw the tree at that point - all the children are missing! The references to the children point to locations in memory which have been used for other things. This was due to how I had to change the `SGNode` class to be able to add children in the first place. If you were to go back and copy each child to its parent you may still run into issues, and you would have to declare the scene graph upside down starting from the smallest objects and working up. As such, the scene graph nodes and construction are located inside the `main` function . 

I've also tried moving the scene graphs into separate functions in the `main` class but again the same issue occurs regarding the pointers and references. There are created, added to the graph, the graph prints out correctly, but as soon as it needs using outside the function, it no longer exists and leads to `EXC_BAD_ACCESS` errors. There are some solutions that might work but given the time frame of the assignment and balancing other modules and my disseration, I haven't had time to test them out. It's possible that you could specify every node globally but this is inefficient; you may also be able to create each node and add it in reverse order - effectively adding the smallest node to its parent and so on until you reach the root. This may copy the correct information across but requires more memory for each node since each node is created once and then copied to the parent, and then that parent (including the child) is copied to its parent and so on.  I did briefly try this solution and although the graph was created correctly, it did not render.

I'd very much appreciate if these problems were considered when looking at the length of functions and marking the code structure. I have tried to at least write code in a logical order but without being able to create scene graphs in separate functions and/or classes, it may be rather hard to find specific parts.

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

