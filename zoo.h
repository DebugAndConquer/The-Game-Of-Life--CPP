/**
 * Declares a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 * Rich documentation for the api and behaviour the Zoo namespace can be found in zoo.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author YOUR_STUDENT_NUMBER
 * @date March, 2020
 */
#pragma once
#include <string>
#include <algorithm>
#include "grid.h"

// Add the minimal number of includes you need in order to declare the namespace.
// #include ...

/**
 * Declare the interface of the Zoo namespace for constructing lifeforms and saving and loading them from file.
 */
namespace Zoo {
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.

    Grid glider(); // Draws a glider on a 3x3 grid
    Grid r_pentomino(); // Draws a r_pentomino on a 3x3 grid
    Grid light_weight_spaceship(); // Draws a lightweight spaceship on a 5x4 grid
    Grid load_ascii(std::string path); // Reads a .gol file containing the grid and produces a Grid object
    void save_ascii(std::string path, Grid grid); // Saves a grid in a .gol file
    void save_binary(std::string path, Grid grid); //Saves a grid in a .bgol binary-encoded file
    Grid load_binary(std::string path); // Reads a .bgol file containing binary-encoded grid and produces a Grid object
};