/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 965217
 * @date March, 2020
 */
#pragma once

#include <iostream>
#include <vector>

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {
private:
    int width, height;

    std::vector<Cell> grid;                          // 2D Vector for storing the grid

    int get_index(const int x, const int y) const;   // Gets 1D index of a 2D coordinate
public:
    // Public functions
    Grid();                                          // Default Constructor with grid size = 0

    explicit Grid(const int square_size);            // Overloaded Constructor with grid size = squareSize*squareSize

    Grid(const int width, const int height);         // Overloaded Constructor with grid size = width*height

    Cell &operator()(const int x, const int y);

    Cell &operator()(const int x, const int y) const;

    friend std::ostream &operator<<(std::ostream &os, const Grid &g);

    // Member Functions
    int get_width() const;

    int get_height() const;

    int get_total_cells() const;

    int get_alive_cells() const;

    int get_dead_cells() const;

    void resize(const int square_size);

    void resize(const int new_width, const int new_height);

    // Returns the value of the cell at the desired coordinate
    Cell get(const int x, const int y) const;

    // Updates the value of the cell at the desired coordinate
    void set(const int x, const int y, const Cell value);

    // Crops the grid w.r.t specified range
    Grid crop(const int x0,const  int y0,const  int x1,const  int y1);

    // Merges the other grid into the current one w.r.t x0, y0
    void merge(const Grid& other, const int x0, const int y0);

    // An overloaded variant might not allow alive cells to die
    void merge(const Grid &other, const int x0, const int y0,const  bool alive_only);

    // Creates a rotated to a multiple of 90 degrees copy of a grid.
    // Same computation time will apply for any rotation coefficient
    Grid rotate(const int rotation) const;


};