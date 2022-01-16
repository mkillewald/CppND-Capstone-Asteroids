# CPPND: Capstone Asteroids

A clone of the classic 1979 Arcade game Asteroids written in C++. This is my Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

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
