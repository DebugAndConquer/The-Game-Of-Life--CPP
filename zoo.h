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

/**
 * Declare the interface of the Zoo namespace for constructing lifeforms and saving and loading them from file.
 */
namespace Zoo {
    Grid glider(); // Draws a glider on a 3x3 grid

    Grid r_pentomino(); // Draws a r_pentomino on a 3x3 grid

    Grid light_weight_spaceship(); // Draws a lightweight spaceship on a 5x4 grid

    Grid load_ascii(const std::string &path); // Reads a .gol ascii-encoded file containing the grid

    void save_ascii(const std::string &path, const Grid &grid); // Saves a grid in a .gol ascii-encoded file

    void save_binary(const std::string &path, const Grid &grid); //Saves a grid in a .bgol binary-encoded file

    Grid load_binary(const std::string &path); // Reads a .bgol file containing binary-encoded grid
};