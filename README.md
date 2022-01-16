# CPPND: Capstone Asteroids
A clone of the classic 1979 Arcade game Asteroids written in C++. This is my Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).   

![Asteroids](https://github.com/mkillewald/CppND-Capstone-Asteroids/blob/master/images/Asteroids.png)

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL2 >= 2.0.0
  * Linux: `sudo apt install libsdl2-dev libsdl2-2.0-0`
  * Mac, Windows and Other:
      * [Obtaining SDL's source code](https://www.libsdl.org/download-2.0.php)
      * [Installing SDL](https://wiki.libsdl.org/Installation)
* SDL_ttf >= 2.0
   * Linux: `sudo apt install libsdl2-ttf-dev`
   * Mac, Windows and Other: [download and install](https://www.libsdl.org/projects/SDL_ttf/)

## Third Party Libraries (included in this repository)
* [SDL_FontCache](https://github.com/grimfang4/SDL_FontCache)

## Build Instructions

1. Install dependencies, if not already installed. 
2. Clone this repo.
3. Make a build directory in the top level directory: `mkdir build && cd build`
4. Compile: `cmake .. && make`
5. Run it: `./Asteroids`.

## Controls

#### Start Game
I - Insert Coin   
1 - 1 Player Start   
2 - 2 Player Start
 
#### In Game
A - Rotate Left   
S - Rotate Right   
K - Thrust   
L - Fire   
SPACE - Hyperspace   
  
#### High Score Entry
A - Next Letter   
S - Previous Letter   
SPACE - Select Current Letter   

## Class Structure

* main.cpp
  * contains main function entry point
  * holds unique_ptr to Renderer, InputController and Game classes
  * starts game loop
   
* Renderer.h/Rederer.cpp
  * reponsible for creating window and rendering objects to screen using SDL2

* InputController.h/InputController.cpp
  * handles input from user depending on game state

 * Game.h/Game.cpp
   * maintains game state
   * holds unique_ptr to PlayerController, HighScore and HUD classes

* Random.h/Random.cpp
  * utility class which contains static random number generator functions 
   
* HUD.h/HUD.cpp
  * responsible for displaying all text and displaying each player's remaining lives  

* HighScore.h/HighScore.cpp
  * maintains top score and high score table
  * reads/writes high score table to file
  * handles high score entry
 
* PlayerController.h/PlayerController.cpp
  * one instance per player 
  * handles players's ship, player shots, asteroid waves, and ufo

* GameObject.h/GameObject.cpp
  * base class for all game objects (players's ship, player shots, asteroids, and ufo)

* PlayerShip.h/PlayerShip.cpp
  * derived from GameObject class
  * defines player's ship

* PlayerShot.h/PlayerShot.cpp
  * derived from GameObject class
  * defines player shots

* Asteroid.h/Asteroid.cpp
  * derived from GameObject.class
  * defines asteroids 

* UFO.h/UFO.cpp
  * derived from GameObject.class
  * deifines UFO 

## Rubric Items

For this capstone project, I chose to do Option 2 using the Snake game code base as a starting point to make a clone of the classic 1979 arcade game Asteroids. 

* The project demonstrates an understanding of C++ functions and control structures.
  * A variety of control structures are used in the project.
  * The project code is clearly organized into functions.
  * example: PlayerController.h/PlayerController.cpp
* The project reads data from a file and process the data, or the program writes data to a file.
  * The project reads data from an external file or writes data to a file as part of the necessary operation of the program.
  * example: HighScore.cpp line 77 readScores() and line 96 writeScores()
* The project accepts user input and processes the input.
  * The project accepts input from a user as part of the necessary operation of the program.
  * example: InputController.cpp line 56 play()
* The project uses Object Oriented Programming techniques.
  * The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
  * example: PlayerShip.h/PlayerShip.cpp
* Classes use appropriate access specifiers for class members.
  * All class data members are explicitly specified as public, protected, or private.
  * example: GameObject.h
* Class constructors utilize member initialization lists.
  * All class members that are set to argument values are initialized through member initialization lists.
  * example GameObject.cpp line 23
* Classes abstract implementation details from their interfaces.
  * All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.
  * example: PlayerController.h/PlayerController.cpp
* Classes encapsulate behavior.
  * Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions
  * example: PlayerController.h/PlayerController.cpp
* Derived class functions override virtual base class functions.
  * One member function in an inherited class overrides a virtual base class member function.
  * exmaple: PlayerShip.cpp line 145 drawObject() overrides base class GameObject.cpp line 164 drawObject()
* The project makes use of references in function declarations. (at least 2 functions)
  * At least two variables are defined as references, or two functions use pass-by-reference in the project code.
  * example: GameObject.cpp line 111 rotateMoveAndScalePoints() and line 145 checkPointsAtEdges()
* The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
  * The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.
  * example: Game.cpp line 24 the Game() constructor uses smart pointers to allocate instances of PlayerController, HighScore and HUD classes which are autotomatically destroyed when tbe Game instance goes out of scope (ie. the user quits the game). 
* The project uses smart pointers instead of raw pointers.
  * The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.
  * example: Game.cpp line 27 use of unique_ptr. My project, however, does use raw pointers as parameters to classes/methods that need a reference back to the unique pointers. 
