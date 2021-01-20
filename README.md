# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

## Features Added
* Added a "Bonus Food Item" indicated by Green Color. If this Food is eaten by the snake, the size of the snake reduces by 10% of the current size.
* Added Functionality to Exit the game using "ESC" button.
* Reduced the Rate of Change of Snake Speed, to make game more playable for much longer amount time.
* Normalize the Speed of the Snake once the size becomes a multiple of 20.
* Integrated Smart Pointers in the Project for the snake body.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Rubrics Addressed

1. README(All Rubrics Points Addressed)
2. Compiling and Testing (All Rubric Points Addressed)
3. Loops, Functions, I/O
  * The project demonstrates an understanding of C++ functions and control structures.
  * The project accepts user input and processes the input.(controller.cpp ->line 12-40)
4. Object Oriented Programming
  * The project uses Object Oriented Programming techniques.
  * Classes use appropriate access specifiers for class members(snake.h and snake.cpp).
  * Class constructors utilize member initialization lists.
  * Classes abstract implementation details from their interfaces(ShrinkBody and GrowBody functions in game.cpp ).
  * Classes encapsulate behavior.
  * Overloaded functions allow the same function to operate on different parameters(render.cpp ->line 78 ).
  * Templates generalize functions in the project(SnakeBody class in snake.cpp ->line 5).
5. Memory Management
  * The project makes use of references in function declarations.
  * The project uses smart pointers instead of raw pointers(snake.h ->line 57).
6. Concurrency
  * A mutex or lock is used in the project(snake.cpp ->line 19 and 24).
