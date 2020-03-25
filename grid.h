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
    std::vector<Cell> grid;                                  // 2D Vector for storing the grid
    int get_index(int x, int y) const;                      // Gets 1D index of a 2D coordinate
public:
    // Public functions
    Grid();                                              // Default Constructor with grid size = 0
    explicit Grid(int square_size);                     // Overloaded Constructor with grid size = squareSize*squareSize
    Grid(int width, int height);                       // Overloaded Constructor with grid size = width*height
    Cell &operator()(int x, int y);
    Cell &operator()(int x, int y) const;
    friend std::ostream &operator<<(std::ostream &os, const Grid &g);

    // Member Functions
    int get_width() const;
    int get_height() const;
    int get_total_cells() const;
    int get_alive_cells() const;
    int get_dead_cells() const;
    void resize(int square_size);
    void resize(int new_width, int new_height);
    Cell get(int x, int y) const;                             // Returns the value of the cell at the desired coordinate
    void set(int x, int y, Cell value);                      // Updates the value of the cell at the desired coordinate
    Grid crop(int x0, int y0, int x1, int y1);              // Crops the grid w.r.t specified range
    void merge(const Grid& other, int x0, int y0);         // Merges the other grid into the current one w.r.t x0, y0

    // An overloaded variant might not allow alive cells to die
    void merge(const Grid &other, int x0, int y0, bool alive_only);

    // Creates a rotated to a multiple of 90 degrees copy of a grid.
    // Same computation time will apply for any rotation coefficient
    Grid rotate(int rotation) const;


};