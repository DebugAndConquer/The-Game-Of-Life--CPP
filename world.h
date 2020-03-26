/**
 * Declares a class representing a 2d grid world for simulating a cellular automaton.
 * Rich documentation for the api and behaviour the World class can be found in world.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 965217
 * @date March, 2020
 */
#pragma once
#include "grid.h"

/**
 * Declare the structure of the World class for representing a 2d grid world.
 *
 * A World holds two equally sized Grid objects for the current state and next state.
 *      - These buffers should be swapped using std::swap after each update step.
 */
class World {
private:
    Grid current;

    Grid next;

    int count_alive_neighbours(const int x, const int y, const bool toroidal); // Alive cells wrapped in 3x3 square. Current cell - center

public:
    World(const int width,const  int height);

    explicit World(const int square_size);

    explicit World(const Grid &initial_state);

    World();

    // Member functions
    int get_width() const;

    int get_height() const;

    int get_total_cells() const;

    int get_alive_cells() const;

    int get_dead_cells() const;

    // A reference to the grid with current state
    Grid &get_state() const;

    void resize(const int new_width, const int new_height);

    void resize(const int square_size);

    // Perform a 1 step in Conway's Game of Life
    void step(const bool toroidal);

    void step();

    // Perform multiple steps in Conway's Game of Life
    void advance(const int steps, const bool toroidal);

    void advance(const int steps);
};